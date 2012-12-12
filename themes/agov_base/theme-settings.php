<?php
/**
 * @file
 * Theme settings overrides.
 */

/**
 * Implements hook_form_BASE_FORM_ID_alter().
 */
function agov_base_form_system_theme_settings_alter(&$form, &$form_state) {
  $path = '';

  $form['header'] = array(
    '#type' => 'fieldset',
    '#title' => t('Header'),
    '#description' => t('Upload header background image and set display options.'),
  );

  $header_background = variable_get($form_state['theme'] . '_header_background');

  if (isset($header_background['uri'])) {
    $path = str_replace(file_default_scheme() . '://', "", $header_background['uri']);
  }
  $form['header']['header_background_image_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to header background'),
    '#default_value' => $path,
  );

  $form['header']['header_background_image'] = array(
    '#type' => 'file',
    '#title' => t('Upload a header background'),
    '#description' => t('Upload a heading background image.'),
  );

  $form['header']['header_background_repeat_x'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat horizontally'),
    '#default_value' => isset($header_background['repeat-x']) && $header_background['repeat-x'] ? TRUE : FALSE,
  );

  $form['header']['header_background_repeat_y'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat vertically'),
    '#default_value' => isset($header_background['repeat-y']) && $header_background['repeat-y'] ? TRUE : FALSE,
  );

  $form['header']['header_background_custom_css'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom CSS'),
    '#description' => t('Any additional shorthand CSS to be placed after the background: url() element. E.g. center or 25% 50%'),
    '#default_value' => isset($header_background['custom_css']) ? $header_background['custom_css'] : '',
  );

  $form['#submit'][] = 'agov_base_form_system_theme_settings_alter_submit';

}

/**
 * Submit handler.
 * @ingroup forms
 */
function agov_base_form_system_theme_settings_alter_submit(&$form, &$form_state) {

  $header_background = variable_get($form_state['theme'] . '_header_background', array());

  $validators = array('file_validate_is_image' => array());
  $file = file_save_upload('header_background_image', $validators, file_default_scheme() . '://');

  // Set file variables.
  if ($file) {
    $header_background['uri'] = file_unmanaged_copy($file->uri);
    $header_background['url'] = file_create_url($file->uri);
  }
  elseif (!empty($form_state['values']['header_background_image_uri'])) {
    $user_image_path = check_plain($form_state['values']['header_background_image_uri']);
    $file_uri = file_default_scheme() . '://' . $user_image_path;
    if (file_exists($file_uri)) {
      $header_background['uri'] = $file_uri;
      $header_background['url'] = file_create_url($file_uri);
    }
    else {
      form_set_error('header][header_background_image_uri', 'The header background image path is not valid.');
    }
  }
  else {
    $header_background['uri'] = '';
    $header_background['url'] = '';
  }

  // Set the repeat and css variables.
  $header_background['repeat-x'] = $form_state['values']['header_background_repeat_x'];
  $header_background['repeat-y'] = $form_state['values']['header_background_repeat_y'];
  $header_background['custom_css'] = check_plain($form_state['values']['header_background_custom_css']);

  variable_set($form_state['theme'] . '_header_background', $header_background);

}
