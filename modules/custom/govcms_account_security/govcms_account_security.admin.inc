<?php

/**
 * @file
 * Contains admin paths for govCMS Account Security
 *
 *
 * @copyright Copyright(c) 2015 Commonwealth of Australia as represented by Department of Finance
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Department of Finance
 */

/**
 * Settings form for govcms account security.
 */
function govcms_account_security_admin_settings() {

  $form = array();

  drupal_set_message(t("Settings are for review only and cannot be changed."), 'warning');

  $form['govcms_account_security_user_failed_login_user_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of failed login attemps allowed before blocking an account:'),
    '#options' => array(
      '0' => t(variable_get('user_failed_login_user_limit')),
    ),
    '#default_value' => variable_get('user_failed_login_user_limit'),
    '#disabled' => TRUE,
  );

  $form['govcms_account_security_user_failed_login_user_window'] = array(
    '#type' => 'textfield',
    '#title' => t('Block an account for after failed login limit is reached:'),
    '#options' => array(
      '0' => t(variable_get('user_failed_login_user_window').' seconds'),
    ),
    '#default_value' => variable_get('user_failed_login_user_window').' seconds',
    '#disabled' => TRUE,
  );

  $form['govcms_account_security_user_failed_login_identifier_uid_only'] = array(
    '#type' => 'select',
    '#title' => t('Flood control event identifer:'),
    '#options' => array(
      '0' => t(variable_get('user_failed_login_identifier_uid_only')?'User ID only':'Both user ID and IP address'),
    ),
    '#default_value' => variable_get('user_failed_login_identifier_uid_only')?'User ID only':'Both user ID and IP address',
    '#disabled' => TRUE,
  );

  $form['govcms_account_security_user_profile_page_code_anonymous_visit'] = array(
    '#type' => 'select',
    '#title' => t('HTTP code return to anonymous visits on user profile pages:'),
    '#options' => array(
      '0' => t(variable_get('govcms_account_security_user_profile_page_code_anonymous_visit')),
    ),
    '#default_value' => variable_get('govcms_account_security_user_profile_page_code_anonymous_visit'),
    '#disabled' => TRUE,
  );

  return $form;
}
