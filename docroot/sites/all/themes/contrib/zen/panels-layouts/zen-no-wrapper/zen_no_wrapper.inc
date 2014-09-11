<?php

/**
 * Implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title'       => t('No wrapper'),
  'category'    => t('Columns: 1'),
  'icon'        => 'icon.png',

  'theme'       => 'zen_no_wrapper',

  'regions'     => array(
    'main'      => t('Main'),
  ),

  'settings form'     => 'zen_no_wrapper_settings_form',
  'settings validate' => 'zen_no_wrapper_settings_validate',
  'settings submit'   => 'zen_no_wrapper_settings_submit',
);

/**
 * Form for layout settings.
 */
function zen_no_wrapper_settings_form(&$display, $layout, $settings) {
  $form = array();

  $form['layout_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout settings'),
    '#description' => t('Note: if this setting is used, a wrapper div will be added to accomodate the needed classes.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  // Create a classes text field for each region in the layout.
  foreach ($layout['regions'] as $region => $label) {
    $form['layout_settings'][$region . '_classes'] = array(
      '#type' => 'textfield',
      '#title' => t('Classes for the “@region” region', array('@region' => $label)),
      '#default_value' => isset($settings[$region . '_classes']) ? $settings[$region . '_classes'] : '',
      '#description' => t('CSS class (or classes) to apply to the @region region in the layout. This may be blank.', array('@region' => $label)),
    );
  }

  return $form;
}

/**
 * Form validation for layout settings.
 */
function zen_no_wrapper_settings_validate(&$form_state, $form, &$display, $layout, $settings) {
  // Since we allow underscores, change the css filter from Drupal's default.
  $filter = array(' ' => '-', '/' => '-', '[' => '-', ']' => '');
  foreach (array_keys($layout['regions']) as $region) {
    // Ensure that each class is valid.
    foreach (explode(' ', $form_state['layout_settings'][$region . '_classes']) as $class) {
      $cleaned_class = drupal_clean_css_identifier($class, $filter);
      // CSS identifiers can't start with a number or a dash and a number.
      $cleaned_class = preg_replace('/^\-?\d+/', '', $cleaned_class);
      if ($class != $cleaned_class) {
        form_set_error($region . '_classes', t('The class "@class" is invalid. Here’s an alternative class name that is valid: @alternate', array('@class' => $class, '@alternate' => $cleaned_class)));
      }
    }
  }
}

/**
 * Form submit handler for layout settings.
 */
function zen_no_wrapper_settings_submit(&$form_state, &$display, $layout, $settings) {
  // Move the settings out of the 'layout_settings' array.
  foreach (array_keys($form_state['layout_settings']) as $key) {
    $form_state[$key] = $form_state['layout_settings'][$key];
  }
  unset($form_state['layout_settings']);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function template_preprocess_zen_no_wrapper(&$variables, $hook) {
  foreach (array_keys($variables['layout']['regions']) as $region) {
    // Pull out the region classes to easy-to-handle variables.
    $variables[$region . '_classes'] = !empty($variables['settings'][$region . '_classes']) ? ' ' . $variables['settings'][$region . '_classes'] : '';
  }
}
