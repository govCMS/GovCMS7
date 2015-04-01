<?php
/**
 * @file
 * govcms_promotion.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_promotion_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function govcms_promotion_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function govcms_promotion_node_info() {
  $items = array(
    'footer_teaser' => array(
      'name' => t('Promotion'),
      'base' => 'node_content',
      'description' => t('Use <em>Promotions</em> to promote site content that would not be seen otherwise <em>eg. Promoting an old Blog Article that is relevant in today\'s context</em>.  The default location for promotions is above the page footer.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
