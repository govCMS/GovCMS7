<?php

/**
 * Represents the result of hook_crumbs_plugins()
 */
class crumbs_InjectedAPI_Collection_CollectionResult {

  /**
   * @var crumbs_InjectedAPI_Collection_PluginCollection
   */
  private $pluginCollection;

  /**
   * @var crumbs_InjectedAPI_Collection_DefaultValueCollection
   */
  private $defaultValueCollection;

  /**
   * @param crumbs_InjectedAPI_Collection_PluginCollection $pluginCollection
   * @param crumbs_InjectedAPI_Collection_DefaultValueCollection $defaultValueCollection
   */
  function __construct(
    crumbs_InjectedAPI_Collection_PluginCollection $pluginCollection,
    crumbs_InjectedAPI_Collection_DefaultValueCollection $defaultValueCollection
  ) {
    $this->pluginCollection = $pluginCollection;
    $this->defaultValueCollection = $defaultValueCollection;
  }

  /**
   * @return array
   * @throws Exception
   */
  function getPlugins() {
    return $this->pluginCollection->getPlugins();
  }

  /**
   * @return true[][]
   *   Format: $['findParent'][$plugin_key] = true
   */
  function getRoutelessPluginMethods() {
    return $this->pluginCollection->getRoutelessPluginMethods();
  }

  /**
   * @return true[][][]
   *   Format: $['findParent'][$route][$plugin_key] = true.
   */
  function getRoutePluginMethods() {
    return $this->pluginCollection->getRoutePluginMethods();
  }

  /**
   * @return true[][]
   *   Format: $[$pluginKey]['findParent'] = true
   */
  function getPluginRoutelessMethods() {
    return $this->pluginCollection->getPluginRoutelessMethods();
  }

  /**
   * @return true[][][]
   *   Format: $[$pluginKey]['findParent'][$route] = true
   */
  function getPluginRouteMethods() {
    return $this->pluginCollection->getPluginRouteMethods();
  }

  /**
   * @return mixed[]
   *   Format: $[$key] = false|$weight
   * @throws Exception
   */
  function getDefaultValues() {
    return $this->defaultValueCollection->getDefaultValues();
  }

} 
