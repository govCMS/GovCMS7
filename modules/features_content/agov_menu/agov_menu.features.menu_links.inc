<?php
/**
 * @file
 * agov_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function agov_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:<front>
  $menu_links['main-menu:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
  );
  // Exported menu link: main-menu:contact
  $menu_links['main-menu:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Exported menu link: main-menu:news-media
  $menu_links['main-menu:news-media'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'news-media',
    'router_path' => 'news-media',
    'link_title' => 'News & Media',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
  );
  // Exported menu link: main-menu:news-media/blog
  $menu_links['main-menu:news-media/blog'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'news-media/blog',
    'router_path' => 'news-media/blog',
    'link_title' => 'Blog',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'parent_path' => 'news-media',
  );
  // Exported menu link: main-menu:news-media/events
  $menu_links['main-menu:news-media/events'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'news-media/events',
    'router_path' => 'news-media/events',
    'link_title' => 'Events',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'parent_path' => 'news-media',
  );
  // Exported menu link: main-menu:news-media/media-releases
  $menu_links['main-menu:news-media/media-releases'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'news-media/media-releases',
    'router_path' => 'news-media/media-releases',
    'link_title' => 'Media Releases',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'parent_path' => 'news-media',
  );
  // Exported menu link: main-menu:news-media/news
  $menu_links['main-menu:news-media/news'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'news-media/news',
    'router_path' => 'news-media/news',
    'link_title' => 'Current News',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'parent_path' => 'news-media',
  );
  // Exported menu link: main-menu:news-media/news-archive
  $menu_links['main-menu:news-media/news-archive'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'news-media/news-archive',
    'router_path' => 'news-media/news-archive',
    'link_title' => 'Archived News',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'parent_path' => 'news-media',
  );
  // Exported menu link: main-menu:node/1
  $menu_links['main-menu:node/1'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'About Us',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
  );
  // Exported menu link: main-menu:publications
  $menu_links['main-menu:publications'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'publications',
    'router_path' => 'publications',
    'link_title' => 'Publications',
    'options' => array(),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
  );
  // Exported menu link: menu-footer-sub-menu:sitemap
  $menu_links['menu-footer-sub-menu:sitemap'] = array(
    'menu_name' => 'menu-footer-sub-menu',
    'link_path' => 'sitemap',
    'router_path' => 'sitemap',
    'link_title' => 'Sitemap and Feeds',
    'options' => array(),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -39,
  );
  // Exported menu link: menu-quick-links:http://australia.gov.au
  $menu_links['menu-quick-links:http://australia.gov.au'] = array(
    'menu_name' => 'menu-quick-links',
    'link_path' => 'http://australia.gov.au',
    'router_path' => '',
    'link_title' => 'Australia.gov.au',
    'options' => array(
      'attributes' => array(
        'title' => 'Your connection with govenemtn',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Exported menu link: menu-quick-links:http://www.agedcareaustralia.gov.au/
  $menu_links['menu-quick-links:http://business.gov.au/'] = array(
    'menu_name' => 'menu-quick-links',
    'link_path' => 'http://business.gov.au/',
    'router_path' => '',
    'link_title' => 'business.gov.au',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Exported menu link: menu-quick-links:http://www.smartraveller.gov.au/
  $menu_links['menu-quick-links:http://www.smartraveller.gov.au/'] = array(
    'menu_name' => 'menu-quick-links',
    'link_path' => 'http://www.smartraveller.gov.au/',
    'router_path' => '',
    'link_title' => 'Smartraveller',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Exported menu link: user-menu:sitemap
  $menu_links['user-menu:sitemap'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'sitemap',
    'router_path' => 'sitemap',
    'link_title' => 'Site map and Feeds',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
  );
  // Exported menu link: user-menu:user/login
  $menu_links['user-menu:user/login'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/login',
    'router_path' => 'user/login',
    'link_title' => 'Member login',
    'options' => array(
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About Us');
  t('business.gov.au');
  t('Archived News');
  t('Australia.gov.au');
  t('Blog');
  t('Contact');
  t('Current News');
  t('Events');
  t('Home');
  t('Media Releases');
  t('Member login');
  t('News & Media');
  t('Publications');
  t('Site map and Feeds');
  t('Sitemap and Feeds');
  t('Smartraveller');


  return $menu_links;
}
