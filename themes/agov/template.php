<?php

/**
 * Implements template_preprocess_html().
 */
function agov_preprocess_html(&$vars) {
  /* Adds HTML5 placeholder shim */
  drupal_add_js(libraries_get_path('html5placeholder') . "/jquery.html5-placeholder-shim.js", 'file');

  /* Adds HTML5 placeholder shim */
  drupal_add_js(libraries_get_path('ResponsiveSlides.js-1.32') . "/responsiveslides.js", 'file');
}

/**
 * Implements hook_form_alter().
 */
function agov_form_alter(&$form, &$form_state, $form_id) {
  if($form_id == 'search_block_form') {
    $form['search_block_form']['#attributes']['placeholder'] = 'Enter keywords...';
  }
}

/**
 * Override or insert variables into the page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function agov_preprocess_page(&$variables, $hook) {
  unset($variables['breadcrumb']);
}


/**
 * Implements hook_preprocess_maintenance_page().
 */
function agov_preprocess_maintenance_page(&$variables) {
  $variables['footer'] = t('!aGov is developed by !PreviousNext', array(
    '!aGov' => l(t('aGov'), 'http://agov.com.au'),
    '!PreviousNext' => l(t('PreviousNext'), 'http://previousnext.com.au'),
  ));
}