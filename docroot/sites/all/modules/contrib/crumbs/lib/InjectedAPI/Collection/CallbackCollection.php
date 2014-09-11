<?php

/**
 * @see crumbs_InjectedAPI_hookCrumbsPlugins
 */
class crumbs_InjectedAPI_Collection_CallbackCollection {

  /**
   * @var callback[][][]
   *   Format: $[$module][$callbackType][$pluginKey] = $callback
   *   Where $callbackType = 'routeParent'|'routeTitle'|'entityParent'|'entityTitle'.
   */
  protected $callbacks = array();

  /**
   * @param string $module
   * @param string $callbackType
   *   One of 'routeParent', 'routeTitle', 'entityParent' and 'entityTitle'.
   * @param string $pluginKey
   *
   * @return callable|false
   */
  function getCallbackOrFalse($module, $callbackType, $pluginKey) {
    return isset($this->callbacks[$module][$callbackType][$pluginKey])
      ? $this->callbacks[$module][$callbackType][$pluginKey]
      : FALSE;
  }

  /**
   * @param string $module
   * @param string $callbackType
   *   One of 'routeParent', 'routeTitle', 'entityParent' and 'entityTitle'.
   * @param string $pluginKey
   * @param callback $callback
   */
  function addCallback($module, $callbackType, $pluginKey, $callback) {
    $this->callbacks[$module][$callbackType][$pluginKey] = $callback;
  }

} 
