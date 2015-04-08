<?php
/**
 * @file
 * govcms_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function govcms_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_about-us:node/1
  $menu_links['main-menu_about-us:node/1'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'About Us',
    'options' => array(
      'identifier' => 'main-menu_about-us:node/1',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 0,
  );
  // Exported menu link: main-menu_contact:contact
  $menu_links['main-menu_contact:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'identifier' => 'main-menu_contact:contact',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-footer-sub-menu_sitemap-and-feeds:sitemap
  $menu_links['menu-footer-sub-menu_sitemap-and-feeds:sitemap'] = array(
    'menu_name' => 'menu-footer-sub-menu',
    'link_path' => 'sitemap',
    'router_path' => 'sitemap',
    'link_title' => 'Sitemap and Feeds',
    'options' => array(
      'identifier' => 'menu-footer-sub-menu_sitemap-and-feeds:sitemap',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -39,
    'customized' => 0,
  );
  // Exported menu link: menu-quick-links_australigovcmsau:http://australia.gov.au
  $menu_links['menu-quick-links_australigovcmsau:http://australia.gov.au'] = array(
    'menu_name' => 'menu-quick-links',
    'link_path' => 'http://australia.gov.au',
    'router_path' => '',
    'link_title' => 'Australia.gov.au',
    'options' => array(
      'attributes' => array(
        'title' => 'Your connection with govenemtn',
      ),
      'identifier' => 'menu-quick-links_australigovcmsau:http://australia.gov.au',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-quick-links_smartraveller:http://www.smartraveller.gov.au/
  $menu_links['menu-quick-links_smartraveller:http://www.smartraveller.gov.au/'] = array(
    'menu_name' => 'menu-quick-links',
    'link_path' => 'http://www.smartraveller.gov.au/',
    'router_path' => '',
    'link_title' => 'Smartraveller',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-quick-links_smartraveller:http://www.smartraveller.gov.au/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: user-menu_site-map-and-feeds:sitemap
  $menu_links['user-menu_site-map-and-feeds:sitemap'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'sitemap',
    'router_path' => 'sitemap',
    'link_title' => 'Site map and Feeds',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'user-menu_site-map-and-feeds:sitemap',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About Us');
  t('Australia.gov.au');
  t('Contact');
  t('Site map and Feeds');
  t('Sitemap and Feeds');
  t('Smartraveller');


  return $menu_links;
}
