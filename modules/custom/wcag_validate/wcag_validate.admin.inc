<?php

/**
 * @file
 * Provides admin pages for wcag_validate module.
 */

/**
 * Create our config form.
 */
function wcag_validate_admin_form() {

  $form['wcag_validate_auth_user'] = array(
    '#type' => 'textfield',
    '#title' => t('HTTP Auth User'),
    '#default_value' => variable_get('wcag_validate_auth_user', ''),
    '#description' => t("If the validation server is behind HTTP Auth, enter the username"),
  );

  $form['wcag_validate_auth_pass'] = array(
    '#type' => 'password',
    '#title' => t('HTTP Auth Pass'),
    '#default_value' => variable_get('wcag_validate_auth_pass', ''),
    '#description' => t("If the validation server is behind HTTP Auth, enter the password"),
  );

  $form['wcag_validate_server_base'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Base URL'),
    '#default_value' => variable_get('wcag_validate_server_base', wcag_validate_get_config('wcag_validate_server_base')),
  );

  $form['wcag_validate_server_process'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Process Path'),
    '#description' => t('ie, /process'),
    '#default_value' => variable_get('wcag_validate_server_process', wcag_validate_get_config('wcag_validate_server_process')),
  );

  $form['wcag_validate_server_view'] = array(
    '#type' => 'textfield',
    '#title' => t('Service View Path'),
    '#description' => t('ie, /view'),
    '#default_value' => variable_get('wcag_validate_server_view', wcag_validate_get_config('wcag_validate_server_view')),
  );

  $form['wcag_validate_report_redirect'] = array(
    '#type' => 'checkbox',
    '#title' => 'Redirect to report?',
    '#default_value' => variable_get('wcag_validate_report_redirect', wcag_validate_get_config('wcag_validate_report_redirect')),
    '#description' => t('This will redirect to the report rather than rendering it in the module'),
  );

  $form['visibility'] = array(
    '#markup' => t('Visibility of the button can be configured !link.',
      array('!link' => l(t('here'), 'admin/structure/block/manage/wcag_validate/wcag_validate/configure'))
    ),
    '#access' => 'administer blocks',
  );


  return system_settings_form($form);
}
