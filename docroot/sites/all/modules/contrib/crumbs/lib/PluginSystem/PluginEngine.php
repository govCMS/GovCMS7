<?php


class crumbs_PluginSystem_PluginEngine {

  /**
   * @var crumbs_PluginSystem_PluginBag
   */
  protected $pluginBag;

  /**
   * @var crumbs_Router
   */
  protected $router;

  /**
   * @var crumbs_Container_WeightMap
   */
  protected $weightMap;

  /**
   * @param crumbs_PluginSystem_PluginBag $pluginBag
   * @param crumbs_Router $router
   * @param crumbs_Container_WeightMap $weightMap
   */
  function __construct($pluginBag, $router, $weightMap) {
    $this->pluginBag = $pluginBag;
    $this->router = $router;
    $this->weightMap = $weightMap;
  }

  /**
   * Ask applicable plugins to "decorate" (alter) the breadcrumb.
   *
   * @param array $breadcrumb
   */
  function decorateBreadcrumb($breadcrumb) {
    $iterator = $this->pluginBag->getDecorateBreadcrumbPlugins();
    foreach ($iterator as $plugin_key => $plugin) {
      if (!method_exists($plugin, 'decorateBreadcrumb')) {
        // This means the code has changed, without the cache being cleared.
        // It is the user's responsibility to clear the cache.
        // Until then, we simply ignore and move on.
        continue;
      }
      $plugin->decorateBreadcrumb($breadcrumb);
    }
  }

  /**
   * Invoke all relevant plugins to find the parent for a given path.
   *
   * @param string $path
   * @param array $item
   *
   * @return mixed|null
   */
  function findParent($path, $item) {
    $iterator = $this->pluginBag->getRoutePluginMethodIterator('findParent', $item['route']);
    $result = $this->find($iterator, array($path, $item), TRUE);
    return $result;
  }

  /**
   * Invoke all relevant plugins to find all possible parents for a given path.
   *
   * @param string $path
   * @param array $item
   *
   * @return string[]
   */
  function findAllParents($path, $item) {
    $plugin_methods = $this->pluginBag->getRoutePluginMethodIterator('findParent', $item['route']);
    return $this->findAll($plugin_methods, array($path, $item), TRUE);
  }

  /**
   * @param string $parent_raw
   *
   * @return string
   */
  protected function processFindParent($parent_raw) {
    if ($this->router->urlIsExternal($parent_raw)) {
      // Always discard external paths.
      return NULL;
    }
    return $this->router->getNormalPath($parent_raw);
  }

  /**
   * Invoke all relevant plugins to find the title for a given path.
   *
   * @param string $path
   * @param array $item
   * @param array $breadcrumb
   *
   * @return mixed|null
   */
  function findTitle($path, $item, $breadcrumb) {
    $plugin_methods = $this->pluginBag->getRoutePluginMethodIterator('findTitle', $item['route']);
    $result = $this->find($plugin_methods, array($path, $item, $breadcrumb), FALSE);
    return $result;
  }

  /**
   * Invoke all relevant plugins to find all possible titles for a given path.
   *
   * @param string $path
   * @param array $item
   * @param array $breadcrumb
   *
   * @return string[]
   */
  function findAllTitles($path, $item, $breadcrumb) {
    $plugin_methods = $this->pluginBag->getRoutePluginMethodIterator('findTitle', $item['route']);
    return $this->findAll($plugin_methods, array($path, $item, $breadcrumb), FALSE);
  }

  /**
   * Invoke all relevant plugins to find title or parent for a given path.
   *
   * @param crumbs_PluginSystem_PluginMethodIterator $iterator
   * @param array $args
   *   Parameter values to pass to plugin methods.
   * @param bool $processFindParent
   *
   * @return mixed|null
   */
  protected function find($iterator, $args, $processFindParent = FALSE) {
    $best_candidate = NULL;
    $best_candidate_weight = 999999;
    $best_candidate_key = NULL;
    /**
     * @var string $plugin_key
     * @var crumbs_PluginSystem_PluginMethodIterator $position
     */
    foreach ($iterator as $plugin_key => $position) {
      if ($position->isMultiPlugin()) {
        $localWeightMap = $this->weightMap->localWeightMap($plugin_key);
        if ($best_candidate_weight <= $localWeightMap->smallestValue()) {
          return $best_candidate;
        }
        $candidates = $position->invokeFinderMethod($args);
        if (empty($candidates)) {
          continue;
        }
        foreach ($candidates as $candidate_key => $candidate_raw) {
          if (!isset($candidate_raw)) {
            continue;
          }
          $candidate_weight = $localWeightMap->valueAtKey($candidate_key);
          if (FALSE === $candidate_weight) {
            continue;
          }
          if ($best_candidate_weight <= $candidate_weight) {
            continue;
          }
          if ($processFindParent) {
            $candidate = $this->processFindParent($candidate_raw);
            if (!isset($candidate)) {
              continue;
            }
          }
          else {
            $candidate = $candidate_raw;
          }
          $best_candidate = $candidate;
          $best_candidate_weight = $candidate_weight;
        }
      }
      elseif ($position->isMonoPlugin()) {
        $candidate_weight = $this->weightMap->valueAtKey($plugin_key);
        if ($best_candidate_weight <= $candidate_weight) {
          return $best_candidate;
        }
        $candidate_raw = $position->invokeFinderMethod($args);
        if (!isset($candidate_raw)) {
          continue;
        }
        $candidate = $processFindParent
          ? $this->processFindParent($candidate_raw)
          : $candidate_raw;
        if (isset($candidate)) {
          $best_candidate = $candidate;
          $best_candidate_weight = $candidate_weight;
        }
      }
    }
    return $best_candidate;
  }

  /**
   * Invoke all relevant plugins to find title or parent for a given path.
   *
   * @param crumbs_PluginSystem_PluginMethodIterator $iterator
   * @param array $args
   *   Parameter values to pass to plugin methods.
   * @param bool $processFindParent
   *
   * @return mixed|null
   */
  protected function findAll($iterator, $args, $processFindParent = FALSE) {

    $all_candidates = array();
    /**
     * @var string $plugin_key
     * @var crumbs_PluginSystem_PluginMethodIterator $position
     */
    foreach ($iterator as $plugin_key => $position) {
      if ($position->isMultiPlugin()) {
        // That's a crumbs_MultiPlugin
        $candidates = $position->invokeFinderMethod($args);
        if (empty($candidates)) {
          continue;
        }
        foreach ($candidates as $candidate_key => $candidate) {
          if (!isset($candidate)) {
            continue;
          }
          if ($processFindParent) {
            $candidate = $this->processFindParent($candidate);
            if (!isset($candidate)) {
              continue;
            }
          }
          $all_candidates["$plugin_key.$candidate_key"] = $candidate;
        }
      }
      else {
        // That's a crumbs_MonoPlugin
        $candidate = $position->invokeFinderMethod($args);
        if (!isset($candidate)) {
          continue;
        }
        if ($processFindParent) {
          $candidate = $this->processFindParent($candidate);
          if (!isset($candidate)) {
            continue;
          }
        }
        $all_candidates[$plugin_key] = $candidate;
      }
    }

    return $all_candidates;
  }

}
