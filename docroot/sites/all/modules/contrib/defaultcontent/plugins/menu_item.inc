<?php
/**
 * @file
 *
 * Is an alter plugin for defaultcontent
 *
 * Handles the exporting and importing menu items attach to
 * a node
 */

$plugin = array();

/**
 * Handles the exporting of menu links attached to nodes
 *
 * We convert the menu item to use a machine name path and then
 * load it in to the export array
 */
function menu_item_export_alter(&$node, &$export) {
  menu_node_prepare($node);
  if (isset($node->menu['link_path']) && $node->menu['link_path']) {
    module_load_include('inc', 'features', 'includes/features.menu');
    $identifier = $node->menu['menu_name'] . ":" . $node->menu['link_path'];
    if ($link = features_menu_link_load($identifier)) {
      if (!empty($link['plid']) && $parent = menu_link_load($link['plid'])) {
        $link['parent_path'] = defaultcontent_alter_path($parent['link_path']);
      }
      unset($link['plid']);
      unset($link['mlid']);
      $link['link_path'] = defaultcontent_alter_path($link['link_path']);
      $link['identifier'] = defaultcontent_alter_identifier($identifier);
      $export->link = $link;
    }
  }
  unset($node->menu);
}

/**
 * Handles a sort to insure that parent menu links are imported first.
 */
function menu_item_import_sort($a, $b) {
  if (!empty($a->link['has_children']) && empty($b->link['has_children'])) {
    return -1;
  }
  elseif (!empty($b->link['has_children']) && empty($a->link['has_children'])) {
    return 1;
  }
  else {
    return 0;
  }
}

/**
 * Handles the importing of menu item after the node is loaded
 *
 * Convert the menu item path from machine to nid and save
 */
function menu_item_post_import($node) {
  if (isset($node->nid) && ($nid = $node->nid) && (isset($node->link))) {
    defaultcontent_import_menu_link($node->link['identifier'], $node->link);
  }
}
