<?php
/**
 * @file
 * govcms_media_releases.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_media_releases_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function govcms_media_releases_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function govcms_media_releases_node_info() {
  $items = array(
    'media_release' => array(
      'name' => t('Media Release'),
      'base' => 'node_content',
      'description' => t('<em>Media releases</em> can be used to list the latest official releases distributed to the media.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
