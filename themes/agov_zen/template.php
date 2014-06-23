<?php

/**
 * @file
 * Template file for aGov zen.
 */

/**
 * Implements template_preprocess_html().
 */
function agov_zen_preprocess_html(&$vars) {

  /* Adds HTML5 placeholder shim */
  drupal_add_js(libraries_get_path('html5placeholder') . "/jquery.placeholder.js", 'file');
}

/**
 * Implements hook_form_alter().
 */
function agov_zen_form_alter(&$form, &$form_state, $form_id) {

  if ($form_id == 'search_block_form') {
    $form['search_block_form']['#attributes']['placeholder'] = 'Enter keywords...';
  }
}

/**
 * Implements hook_preprocess_page().
 */
function agov_zen_preprocess_page(&$variables) {
  unset($variables['breadcrumb']);
}

/**
 * Implements hook_preprocess_region().
 */
function agov_zen_preprocess_region(&$variables) {

}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function agov_zen_preprocess_maintenance_page(&$variables) {
  $variables['footer'] = t('!aGov is developed by !PreviousNext', array(
    '!aGov' => l(t('aGov'), 'http://agov.com.au'),
    '!PreviousNext' => l(t('PreviousNext'), 'http://previousnext.com.au'),
  ));
}
