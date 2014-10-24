<?php

/**
 * Implements hook_views_bulk_operations_form_alter().
 *
 * Tweaks the appearance of the VBO selector.
 */
function shiny_views_bulk_operations_form_alter(&$form, &$form_state, $vbo) {
  if ($form_state['step'] == 'views_form_views_form') {
    $form['select']['#title'] = '';
    $form['select']['#collapsible'] = FALSE;
    $form['select']['submit']['#value'] = t('Apply');
    $form['select']['operation']['#options'][0] = t('Bulk operations');
    $form['select']['#weight'] = 99999;
  }
}

/**
 * Override or insert variables into the html template.
 * @link https://drupal.org/node/2014851 @endlink
 * Issue #2014851 explains the core bug causing the font css import workaround.
 */
function shiny_preprocess_html(&$vars) {
  drupal_add_css(path_to_theme() . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 9', '!IE' => FALSE), 'weight' => 999, 'preprocess' => FALSE));
  // Add conditional CSS for IE8 and below.
  drupal_add_css(path_to_theme() . '/css/ie8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 8', '!IE' => FALSE), 'weight' => 999, 'preprocess' => FALSE));
  // Add conditional CSS for IE7 and below.
  drupal_add_css(path_to_theme() . '/css/ie7.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'weight' => 999, 'preprocess' => FALSE));
  // Add conditional CSS for IE6.
  drupal_add_css(path_to_theme() . '/css/ie6.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 6', '!IE' => FALSE), 'weight' => 999, 'preprocess' => FALSE));
  // Add external CSS for Open Sans from Google Fonts.
  drupal_add_css('//fonts.googleapis.com/css?family=Open+Sans:300,400,600,700,800&subset=latin,latin-ext',array('type' => 'external'));
}

/**
 * Override or insert variables into the page template.
 */
function shiny_preprocess_page(&$vars) {
  $vars['primary_local_tasks'] = $vars['tabs'];
  unset($vars['primary_local_tasks']['#secondary']);
  $vars['secondary_local_tasks'] = array(
    '#theme' => 'menu_local_tasks',
    '#secondary' => $vars['tabs']['#secondary'],
  );

  if (module_exists('overlay')) {
    if (overlay_get_mode() == 'child') {
      $vars['breadcrumb'] = '';
    }
  }
}

/**
 * Overrides theme_admin_block_content().
 *
 * Use unordered list markup in both compact and extended mode.
 */
function shiny_admin_block_content($variables) {
  $content = $variables['content'];
  $output = '';
  if (!empty($content)) {
    $output = system_admin_compact_mode() ? '<ul class="admin-list compact">' : '<ul class="admin-list">';
    foreach ($content as $item) {
      $output .= '<li class="leaf">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);
      if (isset($item['description']) && !system_admin_compact_mode()) {
        $output .= '<div class="description">' . filter_xss_admin($item['description']) . '</div>';
      }
      $output .= '</li>';
    }
    $output .= '</ul>';
  }
  return $output;
}

/**
 * Override of theme_tablesort_indicator().
 *
 * Use our own image versions, so they show up as black and not gray on gray.
 */
function shiny_tablesort_indicator($variables) {
  $style = $variables['style'];
  $theme_path = drupal_get_path('theme', 'shiny');
  if ($style == 'asc') {
    return theme('image', array('path' => $theme_path . '/images/arrow-asc.png', 'alt' => t('sort ascending'), 'width' => 13, 'height' => 13, 'title' => t('sort ascending')));
  }
  else {
    return theme('image', array('path' => $theme_path . '/images/arrow-desc.png', 'alt' => t('sort descending'), 'width' => 13, 'height' => 13, 'title' => t('sort descending')));
  }
}

/**
 * Implements hook_css_alter().
 */
function shiny_css_alter(&$css) {
  // Use shiny's vertical tabs style instead of the default one.
  if (isset($css['misc/vertical-tabs.css'])) {
    $css['misc/vertical-tabs.css']['data'] = drupal_get_path('theme', 'shiny') . '/css/vertical-tabs.css';
  }
  if (isset($css['misc/vertical-tabs-rtl.css'])) {
    $css['misc/vertical-tabs-rtl.css']['data'] = drupal_get_path('theme', 'shiny') . '/css/vertical-tabs-rtl.css';
  }
  // Use shiny's jQuery UI theme style instead of the default one.
  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    $css['misc/ui/jquery.ui.theme.css']['data'] = drupal_get_path('theme', 'shiny') . '/css/jquery.ui.theme.css';
  }
}

function shiny_breadcrumb($variables) {
  $sep = ' <span></span> ';
  if (count($variables['breadcrumb']) > 0) {
    return '<div class="breadcrumb clearfix">' . implode($sep, $variables['breadcrumb']) . '</div>';
  }
  else {
    return t("Home");
  }
}

/**
 * Preprocesses template variables for overlay.tpl.php
 *
 * @see overlay.tpl.php
 */
function shiny_preprocess_overlay(&$variables) {
  if (module_exists('crumbs')) {
    $breadcrumb_data = crumbs_get_breadcrumb_data();
    $variables['crumbs_trail'] = $breadcrumb_data['trail'];
    $variables['breadcrumb'] = $breadcrumb_data['html'];
  } else {
    $variables['breadcrumb'] = theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb()));
  }
}

function shiny_system_info_alter(&$info, $file, $type) {
  if ($type == 'theme') {
    $info['overlay_regions'][] = 'footer';
  }
}
