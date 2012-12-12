<?php
/**
 * @file
 * Preprocess zone for header background image.
 */

if ($vars['zone'] == 'header') {

  global $theme;
  $repeat = array();
  $custom_css = '';

  $theme_header_background = variable_get($theme . '_header_background');
  $background_image_url = isset($theme_header_background['url']) ? $theme_header_background['url'] : '';

  if (isset($theme_header_background['repeat-x']) && $theme_header_background['repeat-x']) {
    $repeat[] = 'repeat-x';
  }

  if (isset($theme_header_background['repeat-y']) && $theme_header_background['repeat-y']) {
    $repeat[] = 'repeat-y';
  }

  if (empty($repeat)) {
    $repeat[] = 'no-repeat';
  }

  $repeat = implode(', ', $repeat);

  if (isset($theme_header_background['custom_css'])) {
    $custom_css = $theme_header_background['custom_css'];
  }

  if ($background_image_url != '') {
    $vars['attributes_array']['style'] = 'background: url("' . $background_image_url . '") ' . $repeat . ' ' . $custom_css . ' !important;';
  }

}
