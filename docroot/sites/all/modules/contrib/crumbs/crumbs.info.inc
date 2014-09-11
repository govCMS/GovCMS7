<?php

/**
 * Implements hook_permission().
 */
function crumbs_permission() {
  return array(
    'administer crumbs' => array(
      'title' => t('Administer Crumbs'),
    ),
  );
}

/**
 * Implements hook_menu().
 */
function crumbs_menu() {
  $base = 'admin/structure/crumbs';
  $items = array();
  $items["$base"] = array(
    'title' => 'Crumbs',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('crumbs_admin_weights_form'),
    'access arguments' => array('administer crumbs'),
    'file' => 'admin/crumbs.admin.inc',
  );
  $items["$base/weights"] = array(
    'title' => 'Plugin weights',
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'weight' => -10,
  );
  $items["$base/display"] = array(
    'title' => 'Display',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('crumbs_admin_display_form'),
    'access arguments' => array('administer crumbs'),
    'file' => 'admin/crumbs.admin.inc',
    'type' => MENU_LOCAL_TASK,
    'weight' => 0,
  );
  $items["$base/entity-parent"] = array(
    'title' => 'Entity parent',
    'weight' => 10,
    'type' => MENU_LOCAL_TASK,
  );
  $items["$base/debug"] = array(
    'title' => 'Debug',
    'page callback' => 'crumbs_debug_page',
    'access arguments' => array('administer crumbs'),
    'file' => 'admin/crumbs.debug.inc',
    'weight' => 20,
    'type' => MENU_LOCAL_TASK,
  );

  foreach (array(
    'node' => 'Node',
    'taxonomy_term' => module_exists('taxonomy') ? 'Taxonomy' : FALSE,
    'user' => 'User',
  ) as $entity_type => $title) {
    if (FALSE !== $title) {
      $entity_slug = str_replace('_', '-', $entity_type);
      $items["$base/entity-parent/$entity_slug"] = array(
        'title' => $title,
        'page callback' => 'drupal_get_form',
        'page arguments' => array('crumbs_admin_entity_parent_form', $entity_type),
        'access arguments' => array('administer crumbs'),
        'file' => 'admin/crumbs.entity_parent.inc',
        'type' => MENU_LOCAL_TASK,
      );
    }
  }

  $items["$base/entity-parent"] += $items["$base/entity-parent/node"];

  $items["$base/entity-parent/node"] = array(
    'title' => 'Node',
    'weight' => -10,
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  if (module_exists('menu')) {
    $items['crumbs/special-menu-item/%menu_link'] = array(
      'access callback' => TRUE,
      'page callback' => 'crumbs_special_menu_link_page',
      'page arguments' => array(2),
      'title callback' => 'crumbs_special_menu_link_title',
      'title arguments' => array(2),
      'type' => MENU_CALLBACK,
    );
  }

  return $items;
}

/**
 * Implements hook_theme().
 */
function crumbs_theme() {
  return array(
    'crumbs_breadcrumb_link' => array(
      'item' => NULL,
      'file' => 'crumbs.theme.inc',
    ),
    'crumbs_breadcrumb_current_page' => array(
      'variables' => array('item' => NULL, 'show_current_page' => TRUE),
      'file' => 'crumbs.theme.inc',
    ),
    'crumbs_weights_tabledrag' => array(
      'file' => 'admin/crumbs.tabledrag.inc',
      'render element' => 'element',
    ),
    'crumbs_weights_textual' => array(
      'file' => 'admin/crumbs.textual.inc',
      'render element' => 'element',
    ),
    'crumbs_weights_expansible' => array(
      'file' => 'admin/crumbs.expansible.inc',
      'render element' => 'element',
    ),
  );
}

/**
 * Implements hook_theme_registry_alter()
 *
 * @param array $registry
 */
function crumbs_theme_registry_alter(array &$registry) {
  if (!isset($registry['breadcrumb']['function'])) {
    return;
  }

  // Figure out which theme this applies to.
  if (version_compare(PHP_VERSION, '5.4.0', '>=')) {
    $trace = debug_backtrace(0, 3);
  }
  else {
    // Second parameter not supported in PHP < 5.4.0. It would cause a
    // "Warning: debug_backtrace() expects at most 1 parameter, 2 given".
    $trace = debug_backtrace(0);
  }
  if (1
    && isset($trace[2]['function'])
    && '_theme_build_registry' === $trace[2]['function']
    && isset($trace[2]['args'][0])
  ) {
    // Get the first argument of _theme_build_registry().
    $theme = $trace[2]['args'][0];
  }
  else {
    // The hook is called from a weird place.
    return;
  }

  // Remember the original theme function for the settings page.
  $f = $registry['breadcrumb']['function'];
  $originals = variable_get('crumbs_original_theme_breadcrumb', array());
  $originals[$theme->name] = $f;
  variable_set('crumbs_original_theme_breadcrumb', $originals);

  $settings = variable_get('crumbs_override_theme_breadcrumb', array('theme_breadcrumb'));
  if (in_array($f, $settings, TRUE)) {
    $registry['breadcrumb']['includes'][] = drupal_get_path('module', 'crumbs') . '/crumbs.theme.inc';
    $registry['breadcrumb']['function'] = 'crumbs_theme_breadcrumb';
  }
}

/**
 * Implements hook_themekey_properties().
 */
function crumbs_themekey_properties() {
  $attributes = array();
  $attributes['crumbs:trail_paths'] = array(
    'description' => t('Crumbs trail paths'),
    'validator' => '',
    'page cache' => THEMEKEY_PAGECACHE_SUPPORTED,
  );

  $maps = array();
  $maps[] = array(
    'src' => 'drupal:get_q',
    'dst' => 'crumbs:trail_paths',
    'callback' => '_crumbs_themekey_path2trailpaths',
  );

  return array('attributes' => $attributes, 'maps' => $maps);
}
