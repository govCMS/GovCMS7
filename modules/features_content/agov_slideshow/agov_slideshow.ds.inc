<?php
/**
 * @file
 * agov_slideshow.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function agov_slideshow_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|slide|feature';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'slide';
  $ds_fieldsetting->view_mode = 'feature';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|slide|feature'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function agov_slideshow_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|slide|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'slide';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_slide_image',
      ),
      'right' => array(
        1 => 'title',
        2 => 'body',
        3 => 'field_read_more',
      ),
    ),
    'fields' => array(
      'field_slide_image' => 'left',
      'title' => 'right',
      'body' => 'right',
      'field_read_more' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left' => 'div',
      'right' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
  );
  $export['node|slide|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|slide|feature';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'slide';
  $ds_layout->view_mode = 'feature';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_slide_image',
        1 => 'title',
        2 => 'body',
        3 => 'field_read_more',
      ),
    ),
    'fields' => array(
      'field_slide_image' => 'ds_content',
      'title' => 'ds_content',
      'body' => 'ds_content',
      'field_read_more' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
  );
  $export['node|slide|feature'] = $ds_layout;

  return $export;
}
