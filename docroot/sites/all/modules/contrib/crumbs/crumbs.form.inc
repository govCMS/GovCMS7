<?php

/**
 * Implements hook_element_info()
 */
function crumbs_element_info() {
  $types = array();
  // Nice documentation to be found in
  // http://api.drupal.org/api/drupal/includes%21form.inc/function/form_builder/7
  $common = array(
    '#input' => TRUE,
    '#value_callback' => '_crumbs_element_value_callback',
    '#process' => array('_crumbs_element_process'),
    '#after_build' => array('_crumbs_element_after_build'),
    '#element_validate' => array('_crumbs_element_validate'),
    '#pre_render' => array('_crumbs_element_pre_render'),
    '#tree' => TRUE,
  );
  $types['crumbs_weights_tabledrag'] = array(
    '#theme' => 'crumbs_weights_tabledrag',
  ) + $common;
  $types['crumbs_weights_textual'] = array(
    '#theme' => 'crumbs_weights_textual',
  ) + $common;
  $types['crumbs_weights_expansible'] = array(
    '#theme' => 'crumbs_weights_expansible',
  ) + $common;
  return $types;
}
