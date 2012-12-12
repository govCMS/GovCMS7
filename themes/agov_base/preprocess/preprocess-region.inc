<?php

/**
 * @file
 * Provides preprocess for agov_base.
 */

$theme = alpha_get_theme();
$site_name = variable_get('site_name', '');
$logo_img = theme('image', array('path' => $theme->page['logo'], 'alt' => check_plain($site_name)));
$vars['logo'] = l($logo_img, '<front>', array('html' => TRUE));

// Vars for content region.
if ($vars['elements']['#region'] == 'content') {
  $vars['tabs'] = render($theme->page['tabs']);
}
