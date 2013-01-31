<?php
/**
 * @file
 * agov_media_releases.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function agov_media_releases_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function agov_media_releases_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function agov_media_releases_node_info() {
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
  return $items;
}
