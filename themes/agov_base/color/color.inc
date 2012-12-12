<?php
/**
 * @file
 * Defines color.module settings.
 */

$info = array(
  // Available colors and color labels used in theme.
  'fields' => array(
    'base' => t('Header background'), // Includes footer & block title backgrounds.
    'base_text' => t('Header text'), // Includes footer & block title text.
    'menu' => t('Menu background'),
    'menu_text' => t('Menu text'),
    'bg' => t('Main background'),
    'page' => t('Page background'),
    'text' => t('Text color'),
    'link' => t('Link color'),
  ),
  // Pre-defined color schemes.
  'schemes' => array(
    'default' => array(
      'title' => t('Barton (default)'),
      'colors' => array(
        'base' => '#1d4873',
        'base_text' => '#ffffff',
        'menu' => '#9E1C27',
        'menu_text' => '#ffffff',
        'bg' => '#efeee9',
        'page' => '#ffffff',
        'text' => '#5F5F5F',
        'link' => '#9E1C27',
      ),
    ),
    // @todo Give the Deakin scheme some different colours.
    'deakin' => array(
      'title' => t('Deakin'),
      'colors' => array(
        'base' => '#560703',
        'base_text' => '#323234',
        'menu' => '#454545',
        'menu_text' => '#f1f1f1',
        'bg' => '#e6e6e6',
        'page' => '#ffffff',
        'text' => '#6b6b6b',
        'link' => '#2a7094',
      ),
    ),

    'watson' => array(
      'title' => t('Watson'),
      'colors' => array(
        'base' => '#005162',
        'base_text' => '#b4b4b4',
        'menu' => '#181818',
        'menu_text' => '#f1f1f1',
        'bg' => '#eeebe6',
        'page' => '#ffffff',
        'text' => '#5e5e5e',
        'link' => '#cb2c02',
      ),
    ),    

    'reid' => array(
      'title' => t('Reid'),
      'colors' => array(
        'base' => '#1b1b27',
        'base_text' => '#1e1d2f',
        'menu' => '#646464',
        'menu_text' => '#f1f1f1',
        'bg' => '#e4e4e6',
        'page' => '#ffffff',
        'text' => '#606060',
        'link' => '#c63300',
      ),
    ),

  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'css/global.css',
    'css/retina.css',
    // @todo Clean these stylesheets to exclusively contain layout CSS.
    'css/australian-government-alpha-default-narrow.css',
    'css/australian-government-alpha-default-normal.css',
    'css/australian-government-alpha-default.css',
  ),

  // Preview files.
  // @todo Make the preview more useful.
  // @see themes/bartik/color/preview.html
  'preview_html' => 'color/preview.html',
  'preview_css' => 'color/preview.css',
  // 'preview_js' => 'color/preview.js',

  // Files to copy.
  'copy' => array(),

  // Gradient definitions.
  'gradients' => array(),

  // Color areas to fill (x, y, width, height).
  'fill' => array(),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Base file for image generation.
  'base_image' => 'color/base.png',
);
