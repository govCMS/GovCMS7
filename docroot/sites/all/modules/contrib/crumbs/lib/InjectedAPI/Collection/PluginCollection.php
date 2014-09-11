<?php

/**
 * @see crumbs_InjectedAPI_hookCrumbsPlugins
 */
class crumbs_InjectedAPI_Collection_PluginCollection {

  /**
   * @var crumbs_PluginInterface[]
   */
  private $plugins = array();

  /**
   * @var true[][]
   *   Format: $['findParent'][$pluginKey] = true
   */
  private $routelessPluginMethods = array();

  /**
   * @var true[][]
   *   Format: $[$pluginKey]['findParent'] = true
   */
  private $pluginRoutelessMethods = array();

  /**
   * @var true[][][]
   *   Format: $['findParent'][$route][$pluginKey] = true
   */
  private $routePluginMethods = array();

  /**
   * @var true[][][]
   *   Format: $[$pluginKey]['findParent'][$route] = true
   */
  private $pluginRouteMethods = array();

  /**
   * @return array
   * @throws Exception
   */
  function getPlugins() {
    return $this->plugins;
  }

  /**
   * @return string[][]
   *   Format: $['findParent'][$plugin_key] = $method
   */
  function getRoutelessPluginMethods() {
    return $this->routelessPluginMethods;
  }

  /**
   * @return string[][][]
   *   Format: $['findParent'][$route][$plugin_key] = $method.
   */
  function getRoutePluginMethods() {
    $routePluginMethods = $this->routePluginMethods;
    foreach ($routePluginMethods as $base_method => &$route_plugin_methods) {
      if (isset($this->routelessPluginMethods[$base_method])) {
        foreach ($route_plugin_methods as $route => &$methods_by_plugin_key) {
          $methods_by_plugin_key += $this->routelessPluginMethods[$base_method];
        }
      }
    }
    return $routePluginMethods;
  }

  /**
   * @return true[][]
   *   Format: $[$pluginKey]['findParent'] = true
   */
  function getPluginRoutelessMethods() {
    return $this->pluginRoutelessMethods;
  }

  /**
   * @return true[][][]
   *   Format: $[$pluginKey]['findParent'][$route] = true
   */
  function getPluginRouteMethods() {
    return $this->pluginRouteMethods;
  }

  /**
   * @param crumbs_PluginInterface $plugin
   * @param string $plugin_key
   * @param string|null $route
   *
   * @throws Exception
   */
  function addPlugin(crumbs_PluginInterface $plugin, $plugin_key, $route = NULL) {
    if (isset($this->plugins[$plugin_key])) {
      throw new Exception("There already is a plugin with key '$plugin_key'.");
    }
    if (isset($route)) {
      $legacyMethods = $this->analyzeRoutePluginMethods($route, $plugin_key, $plugin);
    }
    else {
      $legacyMethods = $this->analyzePluginMethods($plugin_key, $plugin);
    }

    if (!empty($legacyMethods)) {
      $legacyMethods += array(
        'findParent' => array(),
        'findTitle' => array(),
      );
      if ($plugin instanceof crumbs_MultiPlugin) {
        $plugin = new crumbs_MultiPlugin_LegacyWrapper(
          $plugin,
          $legacyMethods['findParent'],
          $legacyMethods['findTitle']);
      }
      elseif ($plugin instanceof crumbs_MonoPlugin) {
        $plugin = new crumbs_MonoPlugin_LegacyWrapper(
          $plugin,
          $legacyMethods['findParent'],
          $legacyMethods['findTitle']);
      }
    }

    $this->plugins[$plugin_key] = $plugin;
  }

  /**
   * @param string $plugin_key
   * @param crumbs_PluginInterface $plugin
   *
   * @return string[][]
   *   Format: $['findParent']['node/%'] = 'findParent__node_x'
   *   Any legacy methods.
   */
  private function analyzePluginMethods($plugin_key, crumbs_PluginInterface $plugin) {

    $reflectionObject = new ReflectionObject($plugin);
    $legacyMethods = array();

    $wildcardKey = ($plugin instanceof crumbs_MultiPlugin)
      ? $plugin_key . '.*'
      : $plugin_key;

    foreach ($reflectionObject->getMethods() as $method) {
      switch ($method->name) {

        case 'decorateBreadcrumb':
          $this->routelessPluginMethods['decorateBreadcrumb'][$plugin_key] = true;
          $this->pluginRoutelessMethods[$wildcardKey]['decorateBreadcrumb'] = true;
          break;

        case 'findParent':
        case 'findTitle':
          $this->routelessPluginMethods[$method->name][$plugin_key] = true;
          $this->pluginRoutelessMethods[$wildcardKey][$method->name] = true;
          break;

        default:
          if (0 === strpos($method->name, 'findParent__')) {
            $baseMethodName = 'findParent';
            $methodSuffix = substr($method->name, 12);
          }
          elseif (0 === strpos($method->name, 'findTitle__')) {
            $baseMethodName = 'findTitle';
            $methodSuffix = substr($method->name, 12);
          }
          else {
            break;
          }
          $route = crumbs_Util::routeFromMethodSuffix($methodSuffix);
          $this->routePluginMethods[$baseMethodName][$route][$plugin_key] = true;
          $this->pluginRouteMethods[$wildcardKey][$baseMethodName][$route] = true;
          $legacyMethods[$baseMethodName][$route] = $method->name;
      }
    }

    return $legacyMethods;
  }

  /**
   * @param string $route
   * @param string $plugin_key
   * @param crumbs_PluginInterface $plugin
   *
   * @return string[][]
   *   Format: $['findParent']['node/%'] = 'findParent__node_x'
   *   Any legacy methods.
   */
  private function analyzeRoutePluginMethods($route, $plugin_key, crumbs_PluginInterface $plugin) {

    $method_suffix = crumbs_Util::buildMethodSuffix($route);
    $legacyMethods = array();

    $wildcardKey = ($plugin instanceof crumbs_MultiPlugin)
      ? $plugin_key . '.*'
      : $plugin_key;

    foreach (array('findTitle', 'findParent') as $base_method_name) {
      if (!empty($method_suffix)) {
        $method_with_suffix = $base_method_name . '__' . $method_suffix;
        if (method_exists($plugin, $method_with_suffix)) {
          $this->routePluginMethods[$base_method_name][$route][$plugin_key] = true;
          $this->pluginRouteMethods[$wildcardKey][$base_method_name][$route] = true;
          $legacyMethods[$base_method_name][$route] = $method_with_suffix;
          continue;
        }
      }
      if (method_exists($plugin, $base_method_name)) {
        $this->routePluginMethods[$base_method_name][$route][$plugin_key] = true;
        $this->pluginRouteMethods[$wildcardKey][$base_method_name][$route] = true;
      }
    }

    return $legacyMethods;
  }

} 
