<?php
/**
 * @file
 * agov_chosen.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function agov_chosen_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
