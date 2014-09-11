<?php


/**
 * API object to be used as an argument for hook_crumbs_plugins()
 * This is a sandbox class, currently not used..
 */
class crumbs_InjectedAPI_hookCrumbsPlugins {

  /**
   * @var string $module
   *   The module for the current hook implementation.
   */
  private $module;

  /**
   * @var crumbs_InjectedAPI_Collection_PluginCollection
   */
  private $pluginCollection;

  /**
   * @var crumbs_InjectedAPI_Collection_EntityPluginCollection
   */
  private $entityPluginCollection;

  /**
   * @var crumbs_InjectedAPI_Collection_CallbackCollection
   */
  private $callbackCollection;

  /**
   * @var crumbs_InjectedAPI_Collection_DefaultValueCollection
   */
  private $defaultValueCollection;

  /**
   * @param crumbs_InjectedAPI_Collection_PluginCollection $pluginCollection
   * @param crumbs_InjectedAPI_Collection_EntityPluginCollection $entityPluginCollection
   * @param crumbs_InjectedAPI_Collection_CallbackCollection $callbackCollection
   * @param crumbs_InjectedAPI_Collection_DefaultValueCollection $defaultValueCollection
   */
  function __construct(
    crumbs_InjectedAPI_Collection_PluginCollection $pluginCollection,
    crumbs_InjectedAPI_Collection_EntityPluginCollection $entityPluginCollection,
    crumbs_InjectedAPI_Collection_CallbackCollection $callbackCollection,
    crumbs_InjectedAPI_Collection_DefaultValueCollection $defaultValueCollection
  ) {
    $this->pluginCollection = $pluginCollection;
    $this->entityPluginCollection = $entityPluginCollection;
    $this->callbackCollection = $callbackCollection;
    $this->defaultValueCollection = $defaultValueCollection;
  }

  /**
   * This is typically called before each invocation of hook_crumbs_plugins(),
   * to let the object know about the module implementing the hook.
   * Modules can call this directly if they want to let other modules talk to
   * the API object.
   *
   * @param string $module
   *   The module name.
   */
  function setModule($module) {
    $this->module = $module;
  }

  /**
   * Register an entity route.
   * This should be called by those modules that define entity types and routes.
   *
   * @param string $entity_type
   * @param string $route
   * @param string $bundle_key
   * @param string $bundle_name
   */
  function entityRoute($entity_type, $route, $bundle_key, $bundle_name) {
    $this->entityPluginCollection->entityRoute($entity_type, $route, $bundle_key, $bundle_name);
  }

  /**
   * Register an entity parent plugin.
   *
   * @param string $key
   * @param string|crumbs_EntityPlugin $entity_plugin
   * @param array $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  function entityParentPlugin($key, $entity_plugin = NULL, $types = NULL) {
    $this->entityPlugin('parent', $key, $entity_plugin, $types);
  }

  /**
   * Register a callback that will determine a parent path for a breadcrumb item
   * with an entity route. The behavior will be available for all known entity
   * routes, e.g. node/% or taxonomy/term/%, with different plugin keys.
   *
   * @param string $key
   * @param callable $callback
   * @param array $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  function entityParentCallback($key, $callback, $types = NULL) {
    $entity_plugin = new crumbs_EntityPlugin_Callback($callback, $this->module, $key, 'entityParent');
    $this->entityPlugin('parent', $key, $entity_plugin, $types);
    $this->callbackCollection->addCallback($this->module, 'entityParent', $key, $callback);
  }

  /**
   * Register an entity title plugin.
   *
   * @param string $key
   * @param string|crumbs_EntityPlugin $entity_plugin
   * @param array $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  function entityTitlePlugin($key, $entity_plugin = NULL, $types = NULL) {
    $this->entityPlugin('title', $key, $entity_plugin, $types);
  }

  /**
   * Register a callback that will determine a title for a breadcrumb item with
   * an entity route. The behavior will be available for all known entity
   * routes, e.g. node/% or taxonomy/term/%, with different plugin keys.
   *
   * @param string $key
   *   The plugin key under which this callback will be listed on the weights
   *   configuration form.
   * @param callback $callback
   *   The callback, e.g. an anonymous function. The signature must be
   *   $callback(stdClass $entity, string $entity_type, string $distinction_key),
   *   like the findCandidate() method of a typical crumbs_EntityPlugin.
   * @param array $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  function entityTitleCallback($key, $callback, $types = NULL) {
    $entity_plugin = new crumbs_EntityPlugin_Callback($callback, $this->module, $key, 'entityTitle');
    $this->entityPlugin('title', $key, $entity_plugin, $types);
    $this->callbackCollection->addCallback($this->module, 'entityTitle', $key, $callback);
  }

  /**
   * @param string $type
   *   Either 'title' or 'parent'.
   * @param string $key
   *   The plugin key under which this callback will be listed on the weights
   *   configuration form.
   * @param string|crumbs_EntityPlugin $entity_plugin
   * @param string[]|string|NULL $types
   *   An array of entity types, or a single entity type, or NULL to allow all
   *   entity types.
   */
  protected function entityPlugin($type, $key, $entity_plugin, $types) {
    if (!isset($entity_plugin)) {
      $class = $this->module . '_CrumbsEntityPlugin';
      $entity_plugin = new $class();
    }
    elseif (is_string($entity_plugin)) {
      $class = $this->module . '_CrumbsEntityPlugin_' . $entity_plugin;
      $entity_plugin = new $class();
    }
    if ($entity_plugin instanceof crumbs_EntityPlugin) {
      $this->entityPluginCollection->entityPlugin($type, $this->module . '.' . $key, $entity_plugin, $types);
    }
  }

  /**
   * Register a "Mono" plugin.
   * That is, a plugin that defines exactly one rule.
   *
   * @param string $key
   *   Rule key, relative to module name.
   * @param Crumbs_MonoPlugin $plugin
   *   Plugin object. Needs to implement crumbs_MultiPlugin.
   *   Or NULL, to have the plugin object automatically created based on a
   *   class name guessed from the $key parameter and the module name.
   * @throws Exception
   */
  function monoPlugin($key = NULL, crumbs_MonoPlugin $plugin = NULL) {
    $this->addPluginByType($plugin, $key, NULL, FALSE);
  }

  /**
   * Register a "Mono" plugin that is restricted to a specific route.
   *
   * @param string $route
   * @param string $key
   * @param crumbs_MonoPlugin $plugin
   */
  function routeMonoPlugin($route, $key = NULL, crumbs_MonoPlugin $plugin = NULL) {
    $this->addPluginByType($plugin, $key, $route, FALSE);
  }

  /**
   * Register a "Multi" plugin.
   * That is, a plugin that defines more than one rule.
   *
   * @param string|null $key
   *   Rule key, relative to module name.
   * @param crumbs_MultiPlugin|null $plugin
   *   Plugin object. Needs to implement crumbs_MultiPlugin.
   *   Or NULL, to have the plugin object automatically created based on a
   *   class name guessed from the $key parameter and the module name.
   *
   * @throws Exception
   */
  function multiPlugin($key = NULL, crumbs_MultiPlugin $plugin = NULL) {
    $this->addPluginByType($plugin, $key, NULL, TRUE);
  }

  /**
   * @param string $route
   * @param string|null $key
   * @param crumbs_MultiPlugin|null $plugin
   */
  function routeMultiPlugin($route, $key = NULL, crumbs_MultiPlugin $plugin = NULL) {
    $this->addPluginByType($plugin, $key, $route, TRUE);
  }

  /**
   * @param crumbs_MonoPlugin|crumbs_PluginInterface|null $plugin
   * @param string|null $key
   * @param string|null $route
   * @param bool $is_multi
   *   TRUE for a multi plugin.
   *
   * @throws Exception
   */
  private function addPluginByType(crumbs_PluginInterface $plugin = NULL, $key = NULL, $route = NULL, $is_multi) {
    $plugin_key = isset($key)
      ? $this->module . '.' . $key
      : $this->module;
    if (!isset($plugin)) {
      $class = $is_multi
        ? $this->module . '_CrumbsMultiPlugin'
        : $this->module . '_CrumbsMonoPlugin';
      $class .= isset($key) ? '_' . $key : '';
      if (!class_exists($class)) {
        throw new \Exception("Plugin class $class does not exist.");
      }
      $plugin = new $class();
    }
    else {
      $class = get_class($plugin);
    }
    if ($is_multi) {
      if (!$plugin instanceof crumbs_MultiPlugin) {
        throw new Exception("$class must implement class_MultiPlugin.");
      }
    }
    else {
      if (!$plugin instanceof crumbs_MonoPlugin) {
        throw new Exception("$class must implement class_MonoPlugin.");
      }
    }
    $this->addPlugin($plugin, $plugin_key, $route);
  }

  /**
   * @param crumbs_PluginInterface $plugin
   * @param string $plugin_key
   * @param string|null $route
   *
   * @throws Exception
   */
  private function addPlugin(crumbs_PluginInterface $plugin, $plugin_key, $route = NULL) {
    $this->pluginCollection->addPlugin($plugin, $plugin_key, $route);
  }

  /**
   * @param string $route
   * @param string $key
   * @param string $parent_path
   */
  function routeParentPath($route, $key, $parent_path) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_FixedParentPath($parent_path));
  }

  /**
   * Register a callback that will determine a parent for a breadcrumb item.
   *
   * @param string $route
   *   The route where this callback should be used, e.g. "node/%".
   * @param string $key
   *   The plugin key under which this callback will be listed on the weights
   *   configuration form.
   * @param callback $callback
   *   The callback, e.g. an anonymous function. The signature must be
   *   $callback(string $path, array $item), like the findParent() method of
   *   a typical crumbs_MonoPlugin.
   */
  function routeParentCallback($route, $key, $callback) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_ParentPathCallback($callback, $this->module, $key));
    $this->callbackCollection->addCallback($this->module, 'routeParent', $key, $callback);
  }

  /**
   * @param string $route
   * @param string $key
   * @param string $title
   */
  function routeTranslateTitle($route, $key, $title) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_TranslateTitle($title));
  }

  /**
   * Register a callback that will determine a title for a breadcrumb item.
   *
   * @param string $route
   *   The route where this callback should be used, e.g. "node/%".
   * @param string $key
   *   The plugin key under which this callback will be listed on the weights
   *   configuration form.
   * @param callback $callback
   *   The callback, e.g. an anonymous function. The signature must be
   *   $callback(string $path, array $item), like the findParent() method of
   *   a typical crumbs_MonoPlugin.
   */
  function routeTitleCallback($route, $key, $callback) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_TitleCallback($callback, $this->module, $key));
    $this->callbackCollection->addCallback($this->module, 'routeTitle', $key, $callback);
  }

  /**
   * @param string $route
   * @param string $key
   */
  function routeSkipItem($route, $key) {
    $this->routeMonoPlugin($route, $key, new crumbs_MonoPlugin_SkipItem());
  }

  /**
   * Set specific rules as disabled by default.
   *
   * @param array|string $keys
   *   Array of keys, relative to the module name, OR
   *   a single string key, relative to the module name.
   */
  function disabledByDefault($keys = NULL) {
    if (is_array($keys)) {
      foreach ($keys as $key) {
        $this->_disabledByDefault($key);
      }
    }
    else {
      $this->_disabledByDefault($keys);
    }
  }

  /**
   * @param string|NULL $key
   */
  protected function _disabledByDefault($key) {
    $key = isset($key)
      ? ($this->module . '.' . $key)
      : $this->module;
    $this->defaultValueCollection->setDefaultValue($key, FALSE);
  }

}
