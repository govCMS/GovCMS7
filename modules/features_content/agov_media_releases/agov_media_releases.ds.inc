<?php
/**
 * @file
 * agov_media_releases.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function agov_media_releases_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|media_release|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'media_release';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'post_date' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'ds_post_date_agov_month_day_year',
    ),
  );
  $export['node|media_release|full'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function agov_media_releases_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|media_release|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'media_release';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'post_date',
        1 => 'field_file',
        2 => 'field_image',
        3 => 'body',
        4 => 'field_tags',
      ),
    ),
    'fields' => array(
      'post_date' => 'ds_content',
      'field_file' => 'ds_content',
      'field_image' => 'ds_content',
      'body' => 'ds_content',
      'field_tags' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|media_release|full'] = $ds_layout;

  return $export;
}
