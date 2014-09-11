<?php


class crumbs_BreadcrumbBuilder {

  /**
   * @var crumbs_PluginSystem_PluginEngine
   */
  protected $pluginEngine;

  /**
   * @param crumbs_PluginSystem_PluginEngine $pluginEngine
   */
  function __construct($pluginEngine) {
    $this->pluginEngine = $pluginEngine;
  }

  /**
   * @param array $trail
   * @return array
   */
  function buildBreadcrumb($trail) {
    $breadcrumb = array();
    foreach ($trail as $path => $item) {
      if ($item) {
        $title = $this->pluginEngine->findTitle($path, $item, $breadcrumb);
        if (!isset($title)) {
          $title = $item['title'];
        }
        // The item will be skipped, if $title === FALSE.
        if (isset($title) && $title !== FALSE && $title !== '') {
          $item['title'] = $title;
          $breadcrumb[] = $item;
        }
      }
    }
    return $breadcrumb;
  }
}
