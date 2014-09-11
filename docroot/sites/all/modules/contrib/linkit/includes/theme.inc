<?php
/**
 * @file
 * Linkit theme functions.
 */

/**
 * Theme callback for the search/attribute plugins in linkit_profiles_form.
 */
function theme_linkit_plugin_form_table($variables) {
  $form = $variables['form'];
  $has_description = FALSE;
  $rows = array();

  // Iterate over each element.
  foreach (element_children($form) as $id) {
    $form[$id]['weight']['#attributes']['class'] = array('weight');
    $fields = array(
      drupal_render($form[$id]['name']),
      drupal_render($form[$id]['weight']),
      drupal_render($form[$id]['enabled']),
    );

    if (isset($form[$id]['description'])) {
      $has_description = TRUE;
      $fields[] = drupal_render($form[$id]['description']);
    }

    $rows[$id]['data'] = $fields;
    $rows[$id]['class'] = array('draggable');
  }

  drupal_add_tabledrag('linkit-search-plugins', 'order', 'sibling', 'weight');

  $header = array(
    t('Name'),
    t('Weight'),
    t('Enabled'),
  );

  if ($has_description) {
    $header[] = t('Description');
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'linkit-search-plugins'), 'sticky' => FALSE));
}