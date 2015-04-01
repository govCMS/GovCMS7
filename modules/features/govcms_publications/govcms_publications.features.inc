<?php
/**
 * @file
 * govcms_publications.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_publications_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function govcms_publications_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function govcms_publications_node_info() {
  $items = array(
    'publication' => array(
      'name' => t('Publication'),
      'base' => 'node_content',
      'description' => t('<em>Publications</em> are downloadable reports and documents that will be listed in chronological on the Publications landing page.  This content type can be used for reports tabled in Parliament, Annual Reports, and other special reports.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
