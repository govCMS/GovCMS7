<?php
/**
 * @file
 * govcms_chosen.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_chosen_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
