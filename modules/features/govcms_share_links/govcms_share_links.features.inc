<?php
/**
 * @file
 * govcms_share_links.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_share_links_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
