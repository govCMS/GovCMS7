<?php

/**
 * @file
 * Theme settings
 */

/**
 * Implements hook_form_system_theme_settings_alter().
 */
function agov_base_form_system_theme_settings_alter(&$form, &$form_state) {
  // Add CSS & JS.
  drupal_add_css(drupal_get_path('theme', 'agov_base') . '/css/theme-settings.css', array('group' => CSS_THEME, 'weight' => 100));
  drupal_add_js(drupal_get_path('theme', 'agov_base') . '/js/theme-settings.js');

  // Create aGov settings tab group.
  $form['design_settings'] = array(
    '#type' => 'vertical_tabs',
    '#weight' => -20,
    '#prefix' => t('<h3>Design configuration</h3>'),
  );

  // Create colour config tab.
  $form['design_settings']['colour'] = array(
    '#type' => 'fieldset',
    '#weight' => -10,
    '#title' => t('Colour scheme'),
  );

  // Enable colour options.
  $form['design_settings']['colour']['colour_toggle'] = array(
    '#type' => 'checkbox',
    '#weight' => -10,
    '#title' => t('Enable colour scheme choices'),
    '#default_value' => theme_get_setting('colour_toggle'),
    '#description' => t("Enabling this will allow you to choose one of aGov's included colour schemes. If you want to design your own colour scheme, disable this option and edit the") . ' <em>' . t('theme-colour.scss') . '</em> ' . t('file within the sass directory of your sub theme.'),
  );

  // Colour scheme options.
  $colour_options = array(
    'barton' => t('Barton'),
    'cook' => t('Cook'),
    'deakin' => t('Deakin'),
    'fisher' => t('Fisher'),
    'hughes' => t('Hughes'),
    'reid' => t('Reid'),
    'watson' => t('Watson'),
  );
  $form['design_settings']['colour']['colour_scheme'] = array(
    '#type' => 'radios',
    '#weight' => -9,
    '#title' => t('Choose a colour scheme'),
    '#default_value' => theme_get_setting('colour_scheme'),
    '#options' => $colour_options,
    '#states' => array(
      'visible' => array(
        ':input[name="colour_toggle"]' => array('checked' => TRUE),
      ),
    ),
  );

  $path = '';

  $form['design_settings']['header'] = array(
    '#type' => 'fieldset',
    '#title' => t('Header'),
    '#description' => t('Upload header background image and set display options.'),
  );

  $header_background = variable_get($form_state['theme'] . '_header_background');

  if (isset($header_background['uri'])) {
    $path = str_replace(file_default_scheme() . '://', "", $header_background['uri']);
  }
  $form['design_settings']['header']['header_background_image_uri'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to header background'),
    '#default_value' => $path,
  );

  $form['design_settings']['header']['header_background_image'] = array(
    '#type' => 'file',
    '#title' => t('Upload a header background'),
    '#description' => t('Upload a heading background image.'),
  );

  $form['design_settings']['header']['header_background_repeat_x'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat horizontally'),
    '#default_value' => isset($header_background['repeat-x']) && $header_background['repeat-x'] ? TRUE : FALSE,
  );

  $form['design_settings']['header']['header_background_repeat_y'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat vertically'),
    '#default_value' => isset($header_background['repeat-y']) && $header_background['repeat-y'] ? TRUE : FALSE,
  );

  $form['design_settings']['header']['header_background_custom_css'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom CSS'),
    '#description' => t('Any additional shorthand CSS to be placed after the background: url() element. E.g. center or 25% 50%'),
    '#default_value' => isset($header_background['custom_css']) ? $header_background['custom_css'] : '',
  );

  $form['#submit'][] = 'agov_base_form_system_theme_settings_alter_submit';

  // Rearrange visual settings into design config tabs group
  $form['design_settings']['logo'] = $form['logo'];
  $form['design_settings']['logo']['#title'] = t('Logo');
  unset($form['logo']);
  unset($form['design_settings']['logo']['#attributes']);
  
  $form['design_settings']['favicon'] = $form['favicon'];
  $form['design_settings']['favicon']['#title'] = t('Favicon');
  unset($form['favicon']);
  
  $form['design_settings']['theme_settings'] = $form['theme_settings'];
  unset($form['theme_settings']);

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
