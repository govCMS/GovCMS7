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
    'effects' => array(
      1 => array(
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

  // Exported image style: govcms_ui_kit_banner.
  $styles['govcms_ui_kit_banner'] = array(
    'label' => 'govCMS UI-KIT - Banner',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1650,
          'height' => 440,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: govcms_ui_kit_thumbnail.
  $styles['govcms_ui_kit_thumbnail'] = array(
    'label' => 'govCMS UI-KIT - Thumbnail',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 370,
          'height' => 275,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
