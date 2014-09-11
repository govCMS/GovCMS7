<?php

namespace Drupal\crumbs\Tests;

class MenuLinkPluginTest extends \DrupalWebTestCase {

  /**
   * @return array
   */
  static function getInfo() {
    return array(
      'name' => 'Crumbs menu plugin test',
      'description' => 'Test the menu plugins for Crumbs.',
      'group' => 'Crumbs',
    );
  }

  function setUp() {
    parent::setUp('crumbs');
    // Include the menu plugin file, because those classes are not autoloaded!
    module_load_include('inc', 'crumbs', 'plugins/crumbs.menu');
  }

  function testMenuLinkTitle() {
    $plugin = new \menu_CrumbsMultiPlugin_link_title();
    $q = db_select('menu_links', 'ml');
    $q->fields('ml', array('mlid', 'link_path', 'menu_name'));
    $titles_by_path = array();
    foreach ($q->execute() as $row) {
      $link = menu_link_load($row->mlid);
      if ($link && !isset($links_by_path[$row->link_path][$row->menu_name])) {
        $titles_by_path[$row->link_path][$row->menu_name] = $link['title'];
      }
    }
    foreach ($titles_by_path as $path => $titles) {
      $router_item = crumbs_get_router_item($path);
      if ($router_item) {
        $plugin_result = $plugin->findTitle($path, $router_item);
        if (!is_array($plugin_result)) {
          $this->fail("Plugin result for !path should not be empty.", array(
            '!path' => $path,
          ));
          continue;
        }
        ksort($plugin_result);
        ksort($titles);
        $this->assertEqual($titles, $plugin_result);
      }
    }
  }
}
