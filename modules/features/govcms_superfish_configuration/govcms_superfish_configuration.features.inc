<?php
/**
 * @file
 * govcms_superfish_configuration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_superfish_configuration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
