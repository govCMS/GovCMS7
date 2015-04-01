<?php
/**
 * @file
 * govcms_image_styles.file_default_displays.inc
 */

/**
 * Implements hook_file_default_displays().
 */
function govcms_image_styles_file_default_displays() {
  $export = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'medium',
    'alt' => '[file:field_image_alt]',
    'title' => '[file:field_image_title]',
  );
  $export['image__default__file_image'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__media_small__file_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'medium',
    'alt' => '[file:field_image_alt]',
    'title' => '[file:field_image_title]',
  );
  $export['image__media_small__file_image'] = $file_display;

  return $export;
}
