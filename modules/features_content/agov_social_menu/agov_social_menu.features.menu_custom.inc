<?php
/**
 * @file
 * agov_social_menu.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function agov_social_menu_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-social-media.
  $menus['menu-social-media'] = array(
    'menu_name' => 'menu-social-media',
    'title' => 'Social Media',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Social Media');


  return $menus;
}
