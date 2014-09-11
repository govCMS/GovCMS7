<?php

/**
 * Theme callback for form elements with "#type" = "crumbs_weights_tabledrag".
 *
 * @param array &$vars
 * @return string
 *   Rendered HTML
 */
function theme_crumbs_weights_tabledrag(&$vars) {

  $element = $vars['element'];

  $table = new crumbs_Admin_WeightsTable($element['#crumbs_plugin_info']);

  foreach (element_children($element) as $key) {
    $child = $element[$key];
    $table->addElement($key, $child);
  }

  $rows = $table->getRows();

  drupal_add_tabledrag('crumbs_weights_tabledrag', 'order', 'sibling', 'crumbs-weight-element');

  return theme('table', array(
    'rows' => $rows,
    'attributes' => array('id' => 'crumbs_weights_tabledrag'),
  ));
}
