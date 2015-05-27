<?php
/**
 * @file
 * govcms_basic_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_basic_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function govcms_basic_page_node_info() {
  $items = array(
    'page' => array(
      'name' => t('Standard page'),
      'base' => 'node_content',
      'description' => t('Use <em>Standard pages</em> for your static content such as an \'About us\' page or other informational pages that will always be accessible on the site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
