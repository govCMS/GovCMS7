<?php

/**
 * A wrapper for legacy plugins with suffixed methods like findTitle__node_x().
 */
class crumbs_MonoPlugin_LegacyWrapper implements crumbs_MonoPlugin_FindParentInterface, crumbs_MonoPlugin_FindTitleInterface {

  /**
   * @var crumbs_MonoPlugin
   */
  private $wrappedPlugin;

  /**
   * @var string[]
   *   Format: $[$route] = $method
   */
  private $findParentRouteMethods;

  /**
   * @var string[]
   *   Format: $[$route] = $method
   */
  private $findTitleRouteMethods;

  /**
   * @param crumbs_MonoPlugin $wrappedPlugin
   * @param string[] $findParentRouteMethods
   *   Format: $[$route] = $method
   * @param string[] $findTitleRouteMethods
   *   Format: $[$route] = $method
   */
  function __construct(
    crumbs_MonoPlugin $wrappedPlugin,
    array $findParentRouteMethods,
    array $findTitleRouteMethods
  ) {
    $this->wrappedPlugin = $wrappedPlugin;
    $this->findParentRouteMethods = $findParentRouteMethods;
    $this->findTitleRouteMethods = $findTitleRouteMethods;
  }

  /**
   * @param crumbs_InjectedAPI_describeMonoPlugin $api
   *   Injected API object, with methods that allows the plugin to further
   *   describe itself.
   *
   * @return string|void
   *   As an alternative to the API object's methods, the plugin can simply
   *   return a string label.
   */
  function describe($api) {
    return $this->wrappedPlugin->describe($api);
  }

  /**
   * Find candidates for the parent path.
   *
   * @param string $path
   *   The path that we want to find a parent for.
   * @param array $item
   *   Item as returned from crumbs_get_router_item()
   *
   * @return string
   *   Parent path candidate.
   */
  function findParent($path, $item) {
    $route = $item['route'];
    if (isset($this->findParentRouteMethods[$route])) {
      $method = $this->findParentRouteMethods[$route];
      if (method_exists($this->wrappedPlugin, $method)) {
        return $this->wrappedPlugin->$method($path, $item);
      }
    }
    elseif (method_exists($this->wrappedPlugin, 'findParent')) {
      return $this->wrappedPlugin->findParent($path, $item);
    }

    return NULL;
  }

  /**
   * Find candidates for the parent path.
   *
   * @param string $path
   *   The path that we want to find a parent for.
   * @param array $item
   *   Item as returned from crumbs_get_router_item()
   *
   * @return string
   *   Title candidate.
   */
  function findTitle($path, $item) {
    $route = $item['route'];
    if (isset($this->findTitleRouteMethods[$route])) {
      $method = $this->findTitleRouteMethods[$route];
      return $this->wrappedPlugin->$method($path, $item);
    }
    elseif (method_exists($this->wrappedPlugin, 'findTitle')) {
      return $this->wrappedPlugin->findTitle($path, $item);
    }

    return NULL;
  }

}
