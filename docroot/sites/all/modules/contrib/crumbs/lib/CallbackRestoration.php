<?php

/**
 * Can recover anonymous functions registered with hook_crumbs_plugins() via
 * e.g. $api->routeParentCallback() or $api->entityParentCallback()
 *
 * On an average request, Crumbs plugins are not defined via
 * hook_crumbs_plugins() but loaded from cache. Since anonymouse function are
 * not serializable, they need to be loaded explicitly by calling the respective
 * implementation of hook_crumbs_plugins().
 */
class crumbs_CallbackRestoration {

  /**
   * @var crumbs_InjectedAPI_Collection_CallbackCollection
   */
  private $callbackCollection;

  /**
   * @var true[]
   *   Format: $[$module] = true
   */
  private $modulesRestored = array();

  /**
   * @var crumbs_InjectedAPI_hookCrumbsPlugins
   */
  private $api;

  /**
   * Constructor
   */
  function __construct() {
    $this->callbackCollection = new crumbs_InjectedAPI_Collection_CallbackCollection;
    $this->api = new crumbs_InjectedAPI_hookCrumbsPlugins(
      new crumbs_InjectedAPI_Collection_PluginCollection,
      new crumbs_InjectedAPI_Collection_EntityPluginCollection,
      $this->callbackCollection,
      new crumbs_InjectedAPI_Collection_DefaultValueCollection);
  }

  /**
   * @param string $module
   * @param string $key
   * @param string $callback_type
   *   E.g. 'routeParent'.
   *
   * @return callback
   */
  function restoreCallback($module, $key, $callback_type) {

    if (!isset($this->modulesRestored[$module])) {
      $f = $module . '_crumbs_plugins';
      // The module may have been disabled in the meantime,
      // or the function may have been removed by a developer.
      if (function_exists($f)) {
        $this->api->setModule($module);
        $f($this->api);
      }
      $this->modulesRestored[$module] = TRUE;
    }

    return $this->callbackCollection->getCallbackOrFalse($module, $callback_type, $key);
  }

}
