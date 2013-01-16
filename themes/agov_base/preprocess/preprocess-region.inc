<?php

/**
 * @file
 * Provides preprocess for agov_base.
 */

$theme = alpha_get_theme();
$site_name = variable_get('site_name', '');

// Build logo for light style themes.
$colour_scheme = theme_get_setting('colour_scheme');
$colour_toggle = theme_get_setting('colour_toggle');
if (strpos($theme->page['logo'], 'themes/agov_base/logo.png')) {
  if ($colour_toggle == '0' || $colour_scheme == 'reid') {
    $theme->page['logo'] = drupal_get_path('theme', 'agov_base') . '/images/logo-alt.png';
  }
}

// Build logo html.
$logo_img = theme('image', array('path' => $theme->page['logo'], 'alt' => check_plain($site_name)));
$vars['logo'] = l($logo_img, '<front>', array('html' => TRUE));

// Vars for content region.
if ($vars['elements']['#region'] == 'content') {
  $vars['tabs'] = render($theme->page['tabs']);
}
