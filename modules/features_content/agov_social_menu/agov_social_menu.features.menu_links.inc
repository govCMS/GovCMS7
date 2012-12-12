<?php
/**
 * @file
 * agov_social_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function agov_social_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-social-media:contact
  $menu_links['menu-social-media:contact'] = array(
    'menu_name' => 'menu-social-media',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Email',
    'options' => array(
      'attributes' => array(
        'id' => 'sc-email',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: menu-social-media:http://www.facebook.com/pages/PreviousNext/170975076260877
  $menu_links['menu-social-media:http://www.facebook.com/pages/PreviousNext/170975076260877'] = array(
    'menu_name' => 'menu-social-media',
    'link_path' => 'http://www.facebook.com/pages/PreviousNext/170975076260877',
    'router_path' => '',
    'link_title' => 'Facebook',
    'options' => array(
      'attributes' => array(
        'id' => 'sc-facebook',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: menu-social-media:http://www.twitter.com/PreviousNext
  $menu_links['menu-social-media:http://www.twitter.com/PreviousNext'] = array(
    'menu_name' => 'menu-social-media',
    'link_path' => 'http://www.twitter.com/PreviousNext',
    'router_path' => '',
    'link_title' => 'Twitter',
    'options' => array(
      'attributes' => array(
        'id' => 'sc-twitter',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: menu-social-media:rss.xml
  $menu_links['menu-social-media:rss.xml'] = array(
    'menu_name' => 'menu-social-media',
    'link_path' => 'rss.xml',
    'router_path' => 'rss.xml',
    'link_title' => 'RSS',
    'options' => array(
      'attributes' => array(
        'id' => 'sc-rss',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Email');
  t('Facebook');
  t('RSS');
  t('Twitter');


  return $menu_links;
}
