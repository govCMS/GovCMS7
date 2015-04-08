<?php
/**
 * @file
 * govcms_image_styles.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_image_styles_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function govcms_image_styles_image_default_styles() {
  $styles = array();

  // Exported image style: article_page_620x349.
  $styles['article_page_620x349'] = array(
    'name' => 'article_page_620x349',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 620,
          'height' => 349,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'article_page_620x349',
  );

  return $styles;
}
