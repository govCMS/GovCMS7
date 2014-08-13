<?php
/**
 * @file
 * agov_slideshow.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function agov_slideshow_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function agov_slideshow_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function agov_slideshow_image_default_styles() {
  $styles = array();

  // Exported image style: slideshow_reorder.
  $styles['slideshow_reorder'] = array(
    'name' => 'slideshow_reorder',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 320,
          'height' => 140,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'slideshow_reorder',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function agov_slideshow_node_info() {
  $items = array(
    'slide' => array(
      'name' => t('Slide'),
      'base' => 'node_content',
      'description' => t('Content to be displayed in the slideshow.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
