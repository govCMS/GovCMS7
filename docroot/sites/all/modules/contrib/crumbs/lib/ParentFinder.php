<?php


/**
 * Can find a parent path for a given path.
 * Contains a cache.
 */
class crumbs_ParentFinder {

  /**
   * @var crumbs_PluginSystem_PluginEngine
   */
  protected $pluginEngine;

  /**
   * @var crumbs_Router;
   */
  protected $router;

  /**
   * @var array
   *   Cached parent paths
   */
  protected $parents = array();

  /**
   * @param crumbs_PluginSystem_PluginEngine $pluginEngine
   * @param crumbs_Router $router
   */
  function __construct($pluginEngine, $router) {
    $this->pluginEngine = $pluginEngine;
    $this->router = $router;
  }

  /**
   * @param string $path
   * @param array &$item
   *
   * @return string
   */
  function getParentPath($path, &$item) {
    if (!isset($this->parents[$path])) {
      $parent_path = $this->_findParentPath($path, $item);
      if (is_string($parent_path)) {
        $parent_path = $this->router->getNormalPath($parent_path);
      }
      $this->parents[$path] = $parent_path;
    }
    return $this->parents[$path];
  }

  /**
   * @param string $path
   * @param array &$item
   *
   * @return string|bool
   */
  protected function _findParentPath($path, &$item) {
    if ($item) {
      if (!$item['access']) {
        // Parent should be the front page.
        return FALSE;
      }
      $parent_path = $this->pluginEngine->findParent($path, $item);
      if (isset($parent_path)) {
        return $parent_path;
      }
    }
    // fallback: chop off the last fragment of the system path.
    $parent_path = $this->router->reducePath($path);
    return isset($parent_path) ? $parent_path : FALSE;
  }

}
