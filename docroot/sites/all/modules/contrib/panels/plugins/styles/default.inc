<?php

/**
 * @file
 * Definition of the 'default' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('No style'),
  'description' => t('The default panel rendering style; displays each pane with a separator.'),
  'render region' => 'panels_default_style_render_region',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_default_style_render_region($vars) {
  $output = '';
//  $output .= '<div class="region region-' . $vars['region_id'] . '">';
  $output .= implode('<div class="panel-separator"></div>', $vars['panes']);
//  $output .= '</div>';
  return $output;
}

