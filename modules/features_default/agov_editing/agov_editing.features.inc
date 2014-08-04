<?php
/**
 * @file
 * agov_editing.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function agov_editing_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
