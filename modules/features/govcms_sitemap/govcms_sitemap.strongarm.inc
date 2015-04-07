<?php
/**
 * @file
 * govcms_sitemap.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function govcms_sitemap_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_minimum_lifetime';
  $strongarm->value = '86400';
  $export['xmlsitemap_minimum_lifetime'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_menu_link_main-menu';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_menu_link_main-menu'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_menu_link_menu-footer-sub-menu';
  $strongarm->value = array(
    'status' => '1',
    'priority' => '0.5',
  );
  $export['xmlsitemap_settings_menu_link_menu-footer-sub-menu'] = $strongarm;

  return $export;
}
