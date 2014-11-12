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
  $variables['footer'] = '<div id="footer">' . t('!aGov is developed by !PreviousNext', array(
    '!aGov' => l(t('aGov'), 'http://agov.com.au'),
    '!PreviousNext' => l(t('PreviousNext'), 'http://previousnext.com.au'),
  )) . '</div>';
}

/**
 * Implements hook_preprocess_node().
 */
function agov_zen_preprocess_node(&$variables) {
  if ('slide' == $variables['type']) {
    if (!empty($variables['field_read_more'][0]['url'])) {
      $variables['title_link'] = l($variables['title'], $variables['field_read_more'][0]['url']);
    }
    else {
      $variables['title_link'] = check_plain($variables['title']);
    }
  }
}

/**
 * Overrides zen_status_messages to fix a small bug with output.
 *
 * @deprecated
 *
 * @todo: This can be removed when http://drupal.org/node/2344165 is fixed.
 */
function agov_zen_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"messages--$type messages $type\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul class=\"messages__list\">\n";
      foreach ($messages as $message) {

        // Fix is for this line only.
        $output .= '  <li class="messages__item">' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Implements theme_form_required_marker().
 */
function agov_zen_form_required_marker($variables) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();
  $attributes = array(
    'class' => 'form-required',
    'title' => $t('This field is required.'),
  );
  return '<span' . drupal_attributes($attributes) . '>(required)</span>';
}
