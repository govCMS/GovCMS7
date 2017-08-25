<?php
/**
 * @file
 * govcms_beans.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_beans_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "bean_admin_ui" && $api == "bean") {
    return array("version" => "5");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function govcms_beans_image_default_styles() {
  $styles = array();

  // Exported image style: image_and_text_bean.
  $styles['image_and_text_bean'] = array(
    'effects' => array(
      9 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 300,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'image_and_text_bean',
  );

  // Exported image style: image_and_text_bean_large.
  $styles['image_and_text_bean_large'] = array(
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 690,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'image_and_text_bean_large',
  );

  // Exported image style: image_and_text_bean_small.
  $styles['image_and_text_bean_small'] = array(
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 80,
          'height' => 80,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'image_and_text_bean_small',
  );

  return $styles;
}
