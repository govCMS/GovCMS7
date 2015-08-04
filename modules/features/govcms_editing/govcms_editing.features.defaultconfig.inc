<?php
/**
 * @file
 * govcms_editing.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function govcms_editing_defaultconfig_features() {
  return array(
    'govcms_editing' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function govcms_editing_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathologic_local_paths';
  $strongarm->value = '';
  $export['pathologic_local_paths'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathologic_protocol_style';
  $strongarm->value = 'path';
  $export['pathologic_protocol_style'] = $strongarm;

  return $export;
}
