<?php

/**
 * @file
 * Theme file stub for Workbench.
 */

/**
 * Generic theme function for use with Render API.
 *
 * Renders the #title and #attributes properties if they are present.
 */
function theme_workbench_element($variables) {
  $element = $variables['element'];

  // Use the #title attribute.
  $title = '';
  if (!empty($element['#title'])) {
    $title = '<h3>' . check_plain($element['#title']) . '</h3>';
  }

  $contextual = '';
  if (!empty($element['contextual_links'])) {
    $contextual = drupal_render($element['contextual_links']);
    $element['#attributes']['class'][] = 'contextual-links-region';
  }

  // Use #attributes to customize a wrapper <div>.
  $attributes = '';
  if (!empty($element['#attributes'])) {
    $attributes = drupal_attributes($element['#attributes']);
  }

  // Render any child items.
  if (!$element['#children']) {
    $element['#children'] = drupal_render_children($element);
  }

  // Build simple output.
  $output = "<div{$attributes}>{$title}{$contextual}{$element['#children']}</div>";
  return $output;
}
