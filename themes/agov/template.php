<?php

/**
 * Implements template_preprocess_html().
 */
function agov_preprocess_html(&$vars) {
  /* Adds HTML5 placeholder shim */
  drupal_add_js(libraries_get_path('html5placeholder') . "/jquery.html5-placeholder-shim.js", 'file');
}

/**
 * Implements hook_form_alter().
 */
function agov_form_alter(&$form, &$form_state, $form_id) {
  if($form_id == 'search_block_form') {
    $form['search_block_form']['#attributes']['placeholder'] = 'Enter keywords...';
  }
}