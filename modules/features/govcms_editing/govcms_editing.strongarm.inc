<?php
/**
 * @file
 * govcms_editing.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function govcms_editing_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'media__wysiwyg_browser_plugins';
  $strongarm->value = array(
    0 => 'upload',
    1 => 'media_default--media_browser_1',
    2 => 'media_default--media_browser_my_files',
  );
  $export['media__wysiwyg_browser_plugins'] = $strongarm;

  return $export;
}
