<?php

/**
 * Info about available plugins and their weights.
 *
 * @property array $weights
 * @property crumbs_Container_WeightMap $weightMap
 * @property array $defaultWeights
 *
 * @property true[][] $routelessPluginMethodsUnsorted
 *   Format: $['findParent'][$plugin_key] = true
 * @property true[][][] $routePluginMethodsUnsorted
 *   Format: $['findParent'][$route][$plugin_key] = true.
 *
 * @property true[][] $pluginRoutelessMethods
 *   Format: $[$pluginKey]['findParent'] = true
 * @property true[][][] $pluginRouteMethods
 *   Format: $[$pluginKey]['findParent'][$route] = true
 *
 * @property true[][] $routelessPluginMethods
 *   Format: $['findParent'][$plugin_key] = true
 * @property true[][][] $routePluginMethods
 *   Format: $['findParent'][$route][$plugin_key] = true.
 *
 * @property array $userWeights
 * @property crumbs_Container_MultiWildcardData $availableKeysMeta
 * @property crumbs_Container_MultiWildcardDataOffset[][] $availableKeysMetaGrouped
 *   Format: $['inherit'][$key] = $meta
 *
 * @property crumbs_PluginInterface[] $plugins
 * @property array $pluginsCached
 *
 * @property crumbs_InjectedAPI_Collection_CollectionResult $discovery
 *   The result of running hook_crumbs_plugins()
 *
 * @property array $pluginOrder
 * @property array $pluginsSorted
 * @property bool $includePluginFiles
 */
class crumbs_PluginSystem_PluginInfo extends crumbs_Container_AbstractLazyDataCached {

  /**
   * Which keys to load from persistent cache.
   *
   * @return string[]
   */
  protected function keysToCache() {

    // Plugin cache is special, because these are objects.
    // If this fails, we want to totally circumvent the cache.
    $callback_before = ini_get('unserialize_callback_func');
    ini_set('unserialize_callback_func', '_crumbs_unserialize_failure');
    try {
      // Trigger $this->__get('plugins').
      $this->plugins;
    }
    catch (crumbs_UnserializeException $exception) {
      // Don't cache anything this round.
      return array();
    }
    ini_set('unserialize_callback_func', $callback_before);

    return array('weights', 'pluginsCached', 'defaultWeights', 'pluginRoutes', 'pluginOrder');
  }

  /**
   * Combination of user-defined weights and default weights
   *
   * @return array
   *
   * @see crumbs_PluginSystem_PluginInfo::$weights
   */
  protected function get_weights() {
    $weights = $this->defaultWeights;
    foreach ($this->userWeights as $key => $weight) {
      // Make sure to skip NULL values.
      if (isset($weight)) {
        $weights[$key] = $weight;
      }
    }
    return $weights;
  }

  /**
   * Object that can calculate rule weights based on the weight settings.
   * (which are often wildcards)
   *
   * @return crumbs_Container_WeightMap
   *
   * @see crumbs_PluginSystem_PluginInfo::$weightMap
   */
  protected function get_weightMap() {
    return new crumbs_Container_WeightMap($this->weights);
  }

  /**
   * Default weights without the user configuration
   *
   * @return array
   *
   * @see crumbs_PluginSystem_PluginInfo::$defaultWeights
   */
  protected function get_defaultWeights() {
    return $this->discovery->getDefaultValues();
  }

  /**
   * @return true[][][]
   *   Format: $['findParent'][$route][$plugin_key] = true.
   *
   * @see crumbs_PluginSystem_PluginInfo::$routePluginMethodsUnsorted
   */
  protected function get_routePluginMethodsUnsorted() {
    return $this->discovery->getRoutePluginMethods();
  }

  /**
   * @return true[][]
   *   Format: $['findParent'][$plugin_key] = true
   *
   * @see crumbs_PluginSystem_PluginInfo::$routelessPluginMethodsUnsorted
   */
  protected function get_routelessPluginMethodsUnsorted() {
    return $this->discovery->getRoutelessPluginMethods();
  }

  /**
   * @return true[][]
   *   Format: $[$pluginKey]['findParent'] = true
   *
   * @see crumbs_PluginSystem_PluginInfo::$pluginRoutelessMethods
   */
  protected function get_pluginRoutelessMethods() {
    return $this->discovery->getPluginRoutelessMethods();
  }

  /**
   * @return true[][][]
   *   Format: $[$pluginKey]['findParent'] = true
   *
   * @see crumbs_PluginSystem_PluginInfo::$pluginRouteMethods
   */
  protected function get_pluginRouteMethods() {
    return $this->discovery->getPluginRouteMethods();
  }

  /**
   * @return true[][][]
   *   Format: $['findParent'][$route][$plugin_key] = true.
   *
   * @see crumbs_PluginSystem_PluginInfo::$routePluginMethods
   */
  protected function get_routePluginMethods() {
    $unsorted_all = $this->routePluginMethodsUnsorted;
    $types = array(
      'decorateBreadcrumb' => 'alter',
      'findParent' => 'find',
      'findTitle' => 'find',
    );
    $order = $this->pluginOrder;
    $sorted_all = array();
    foreach ($types as $base_method_name => $type) {
      if (!isset($unsorted_all[$base_method_name])) {
        continue;
      }
      foreach ($unsorted_all[$base_method_name] as $route => $unsorted) {
        $sorted = $this->sortPluginMethods($unsorted_all[$base_method_name][$route], $order[$type]);
        if (!empty($sorted)) {
          $sorted_all[$base_method_name][$route] = $sorted;
        }
      }
    }
    return $sorted_all;
  }

  /**
   * @return true[][]
   *   Format: $['findParent'][$plugin_key] = $method
   *
   * @see crumbs_PluginSystem_PluginInfo::$routelessPluginMethods
   */
  protected function get_routelessPluginMethods() {
    $unsorted = $this->routelessPluginMethodsUnsorted;
    $types = array(
      'decorateBreadcrumb' => 'alter',
      'findParent' => 'find',
      'findTitle' => 'find',
    );
    $order = $this->pluginOrder;
    $sorted_all = array();
    foreach ($types as $base_method_name => $type) {
      if (!isset($unsorted[$base_method_name])) {
        continue;
      }
      $sorted = $this->sortPluginMethods($unsorted[$base_method_name], $order[$type]);
      if (!empty($sorted)) {
        $sorted_all[$base_method_name] = $sorted;
      }
    }
    return $sorted_all;
  }

  /**
   * @param string[] $plugin_methods
   * @param mixed[] $order
   *
   * @return array
   */
  private function sortPluginMethods(array $plugin_methods, array $order) {
    $sorted = array();
    foreach ($order as $plugin_key => $x) {
      if (isset($plugin_methods[$plugin_key])) {
        $sorted[$plugin_key] = $plugin_methods[$plugin_key];
      }
    }
    return $sorted;
  }

  /**
   * User-defined weights
   *
   * @return array
   *
   * @see crumbs_PluginSystem_PluginInfo::$userWeights
   */
  protected function get_userWeights() {
    $user_weights = variable_get('crumbs_weights', array(
      // The user expects the crumbs.home_title plugin to be dominant.
      // @todo There must be a better way to do this.
      'crumbs.home_title' => 0,
    ));
    // '*' always needs to be set.
    if (!isset($user_weights['*'])) {
      // Put '*' last.
      $max = -1;
      foreach ($user_weights as $k => $v) {
        if ($v >= $max) {
          $max = $v;
        }
      }
      $user_weights['*'] = $max + 1;
    }
    return $user_weights;
  }

  /**
   * @return crumbs_Container_MultiWildcardData
   *
   * @see crumbs_PluginSystem_PluginInfo::$availableKeysMeta
   */
  protected function get_availableKeysMeta() {
    $op = new crumbs_PluginOperation_describe();
    /**
     * @var crumbs_PluginInterface $plugin
     */
    foreach ($this->plugins as $plugin_key => $plugin) {
      $op->invoke($plugin, $plugin_key);
    }
    foreach ($this->defaultWeights as $key => $default_weight) {
      $op->setDefaultWeight($key, $default_weight);
    }
    $info = $op->collectedInfo();

    $info->basicMethods = $this->pluginRoutelessMethods;
    $info->routeMethods = $this->pluginRouteMethods;

    return $info;
  }

  /**
   * @return crumbs_Container_MultiWildcardDataOffset[][]
   *   Format: $['inherit'][$key] = $meta
   *
   * @see crumbs_PluginSystem_PluginInfo::$availableKeysMetaGrouped
   */
  protected function get_availableKeysMetaGrouped() {
    $sectionKeys = array();
    foreach ($this->availableKeysMeta as $key => $meta) {
      $sectionKeys[$key] = 'inherit';
    }
    foreach ($this->defaultWeights as $key => $weight) {
      if (!isset($sectionKeys[$key])) {
        continue;
      }
      elseif (FALSE === $weight) {
        $sectionKeys[$key] = 'default:disabled';
      }
      else {
        $sectionKeys[$key] = "default:$weight";
      }
    }
    $weights = $this->weights;
    asort($weights);
    $enabled = array();
    foreach ($weights as $key => $weight) {
      if (!isset($sectionKeys[$key])) {
        continue;
      }
      elseif (FALSE === $weight) {
        $sectionKeys[$key] = 'disabled';
      }
      elseif (isset($sectionKeys[$key])) {
        $sectionKeys[$key] = 'enabled';
        $enabled[$key] = TRUE;
      }
    }
    $grouped = array(
      'enabled' => $enabled,
      'disabled' => array(),
      'default:disabled' => array(),
      'inherit' => array(),
    );
    foreach ($this->availableKeysMeta as $key => $meta) {
      $sectionKey = $sectionKeys[$key];
      $grouped[$sectionKey][$key] = $meta;
    }
  }

  /**
   * Plugins, not sorted, but already with the weights information.
   *
   * @return array
   *
   * @see crumbs_PluginSystem_PluginInfo::$plugins
   */
  protected function get_plugins() {
    // We use a trick to always include the plugin files, even if the plugins
    // are coming from the cache.
    $this->includePluginFiles;
    return $this->pluginsCached;
  }

  /**
   * Plugins, not sorted, but already with the weights information.
   *
   * @return array
   *
   * @see crumbs_PluginSystem_PluginInfo::$pluginsCached
   */
  protected function get_pluginsCached() {
    $plugins = $this->discovery->getPlugins();
    foreach ($plugins as $plugin_key => $plugin) {
      // Let plugins know about the weights, if they want to.
      if (method_exists($plugin, 'initWeights')) {
        $plugin->initWeights($this->weightMap->localWeightMap($plugin_key));
      }
    }
    return $plugins;
  }

  /**
   * Information returned from hook_crumbs_plugins()
   *
   * @return crumbs_InjectedAPI_Collection_CollectionResult
   *
   * @see crumbs_PluginSystem_PluginInfo::$discovery
   */
  protected function get_discovery() {
    $this->includePluginFiles;

    // Pass a by-reference parameter to the $api object, that can only be
    // changed from here.
    $api = new crumbs_InjectedAPI_hookCrumbsPlugins(
      $pluginCollection = new crumbs_InjectedAPI_Collection_PluginCollection,
      $entityPluginCollection = new crumbs_InjectedAPI_Collection_EntityPluginCollection,
      new crumbs_InjectedAPI_Collection_CallbackCollection,
      $defaultValueCollection = new crumbs_InjectedAPI_Collection_DefaultValueCollection);

    foreach (module_implements('crumbs_plugins') as $module) {
      $function = $module .'_crumbs_plugins';
      $api->setModule($module);
      $function($api);
    }

    $entityPluginCollection->finalize($pluginCollection);

    return new crumbs_InjectedAPI_Collection_CollectionResult($pluginCollection, $defaultValueCollection);
  }

  /**
   * Order of plugins, for 'find' and 'alter' operations.
   *
   * @return array
   *   Format: $['find'][$pluginKey] = $weight.
   *
   * @see crumbs_PluginSystem_PluginInfo::$pluginOrder
   */
  protected function get_pluginOrder() {

    $order = array(
      'find' => array(),
      'alter' => array(),
    );

    // Sort the plugins, using the weights from weight map.
    $weightMap = $this->weightMap;
    foreach ($this->plugins as $plugin_key => $plugin) {
      if ($plugin instanceof crumbs_MultiPlugin) {
        $localWeightMap = $weightMap->localWeightMap($plugin_key);
        $w_find = $localWeightMap->smallestValue();
        if ($w_find !== FALSE) {
          $order['find'][$plugin_key] = $w_find;
        }
        // Multi plugins cannot participate in alter operations.
      }
      else {
        $weight = $weightMap->valueAtKey($plugin_key);
        if ($weight !== FALSE) {
          $order['find'][$plugin_key] = $weight;
          $order['alter'][$plugin_key] = $weight;
        }
      }
    }

    // Lowest weight first = highest priority first
    asort($order['find']);

    // Lowest weight last = highest priority last
    arsort($order['alter']);

    return $order;
  }

  /**
   * Sorted plugins for 'find' and 'alter' operations.
   *
   * @return array
   *
   * @see crumbs_PluginSystem_PluginInfo::$pluginsSorted
   */
  protected function get_pluginsSorted() {
    $sorted = $this->pluginOrder;
    $plugins = $this->plugins;
    foreach (array('find', 'alter') as $type) {
      foreach ($sorted[$type] as $plugin_key => &$x) {
        $x = $plugins[$plugin_key];
      }
    }
    return $sorted;
  }

  /**
   * Include files in the /plugin/ folder.
   * We use the cache mechanic to make sure this happens exactly once.
   *
   * @return bool
   *
   * @see crumbs_PluginSystem_PluginInfo::$includePluginFiles
   */
  protected function get_includePluginFiles() {

    $dir = drupal_get_path('module', 'crumbs') . '/plugins';

    $files = array();
    foreach (scandir($dir) as $candidate) {
      if (preg_match('/^crumbs\.(.+)\.inc$/', $candidate, $m)) {
        if (module_exists($m[1])) {
          $files[$m[1]] = $dir . '/' . $candidate;
        }
      }
    }

    // Organic groups is a special case,
    // because 7.x-2.x behaves different from 7.x-1.x.
    if (1
      && isset($files['og'])
      && !function_exists('og_get_group')
    ) {
      // We are using the og-7.x-1.x branch.
      $files['og'] = $dir . '/crumbs.og.2.inc';
    }

    // Since the directory order may be anything, sort alphabetically.
    ksort($files);
    foreach ($files as $file) {
      require_once $file;
    }

    return TRUE;
  }

}
