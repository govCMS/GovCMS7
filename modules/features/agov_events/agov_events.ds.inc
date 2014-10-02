<?php
/**
 * @file
 * agov_events.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function agov_events_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|event|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'event';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'agov_event_date' => array(
      'weight' => '4',
      'label' => 'inline',
      'format' => 'default',
    ),
    'agov_event_details_title' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|event|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function agov_events_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|event|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'event';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_event_date',
        1 => 'field_feature_image',
        2 => 'body',
        3 => 'agov_event_details_title',
        4 => 'agov_event_date',
        5 => 'field_location',
        6 => 'field_cost',
        7 => 'field_contact',
      ),
    ),
    'fields' => array(
      'field_event_date' => 'ds_content',
      'field_feature_image' => 'ds_content',
      'body' => 'ds_content',
      'agov_event_details_title' => 'ds_content',
      'agov_event_date' => 'ds_content',
      'field_location' => 'ds_content',
      'field_cost' => 'ds_content',
      'field_contact' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|event|default'] = $ds_layout;

  return $export;
}
