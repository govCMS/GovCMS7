<?php

/**
 * @file
 * Definition of the 'block' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('System block'),
  'description' => t('Display the pane as a system block; this is more restrictive than the default.'),
  'render pane' => 'panels_block_style_render_pane',
  'weight' => -10,
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panels_block_style_render_pane($vars) {
  $content = $vars['content'];
  $pane = $vars['pane'];

  if (empty($content->content)) {
    return;
  }

  $block = clone($content);

  if (!empty($block->title)) {
    $block->subject = $block->title;
  }
  if (!isset($block->subject)) {
    $block->subject = '';
  }

  $block->region = $pane->panel;
  if (!isset($block->module)) {
    $block->module = $block->type;
  }
  if (!isset($block->delta)) {
    $block->delta = $block->subtype;
  }

  $build = $block->content;
  if (is_string($build)) {
    $build = array('#markup' => $build);
  }

  $build['#block'] = $block;
  $build['#theme_wrappers'][] = 'block';

  // If using per pane classes, $block->css_class will need to be added in your
  // preprocess or template, along with any other Panels specific field you
  // might want to utilize.
  return drupal_render($build);
}

