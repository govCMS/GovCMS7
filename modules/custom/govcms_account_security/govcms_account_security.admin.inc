<?php

/**
 * @file
 * Contains admin paths for govCMS Account Security.
 *
 * @codingStandardsIgnoreStart
 *
 * @copyright Copyright(c) 2015 Commonwealth of Australia as represented by Department of Finance
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Department of Finance
 *
 * @codingStandardsIgnoreEnd
 */

/**
 * Settings form for govcms account security.
 */
function govcms_account_security_admin_settings($form, $form_state) {

  $output = '';

  $header = [t('Name'), t('Constraint')];
  $rows = [];

  if (!empty(variable_get('user_failed_login_user_limit'))) {
    $rows[] = [t('Failed login attemps allowed before blocking'), variable_get('user_failed_login_user_limit')];
  }

  if (!empty(variable_get('user_failed_login_user_window'))) {
    $rows[] = [t('After failed login limit is reached, block an account for'), variable_get('user_failed_login_user_window') . ' seconds'];
  }

  $flood_event_identifier = variable_get('user_failed_login_identifier_uid_only') ? 'user ID only' : 'both user ID and IP address';
  $rows[] = [t('Identify a flood event by'), $flood_event_identifier];

  if (module_exists('password_policy')) {
    $policy = password_policy_policy_load(1);
    $output .= check_plain($policy['description']);

    if (!empty($policy['expiration'])) {
      $rows[] = [t('Password expiration'), $policy['expiration'] . ' days'];
    }
    if (!empty($policy['warning'])) {
      $rows[] = [t('Password expiration warning'), check_plain($policy['warning'] . ' days before expiration')];
    }
    if (!empty($policy['policy']['complexity'])) {
      $rows[] = [t('Minimum types of characters a passowrd must contain'), check_plain($policy['policy']['complexity'] . ' of lowercase, uppercase, digit or punctuation')];
    }
    if (!empty($policy['policy']['length'])) {
      $rows[] = [t('Minimum password length'), check_plain($policy['policy']['length'] . ' characters')];
    }
    if (!empty($policy['policy']['alphanumeric'])) {
      $rows[] = [t('Minimum number of alphanumeric characters'), check_plain($policy['policy']['alphanumeric'])];
    }
    if (!empty($policy['policy']['letter'])) {
      $rows[] = [t('Minimum number of letters'), check_plain($policy['policy']['letter'])];
    }
    if (!empty($policy['policy']['lowercase'])) {
      $rows[] = [t('Minimum number of lowercase letters'), check_plain($policy['policy']['lowercase'])];
    }
    if (!empty($policy['policy']['uppercase'])) {
      $rows[] = [t('Minimum number of uppercase letters'), check_plain($policy['policy']['uppercase'])];
    }
    if (!empty($policy['policy']['punctuation'])) {
      $rows[] = [t('Minimum number of punctuation'), check_plain($policy['policy']['punctuation'])];
    }
    if (!empty($policy['policy']['delay'])) {
      $rows[] = [t('Minimum number of hours between password change'), check_plain($policy['policy']['delay'] . ' hours')];
    }
    if (!empty($policy['policy']['history'])) {
      $rows[] = [t('Password history check'), 'last ' . check_plain($policy['policy']['history'] . ' passwords')];
    }
    if (!empty($policy['policy']['username'])) {
      if ($policy['policy']['username'] > 0) {
        $rows[] = [t('Password must not contain user name'), 'enforced'];
      }
    }
  }

  $output .= theme('table', array('header' => $header, 'rows' => $rows));

 $modules = module_list();
 $module_options = array(
   ' - none -',
 );
 foreach ($modules as $key => $m) {
   $module_options[$key] = $key;
 }
  $permissions = user_permission_get_modules();
 $permission_options = array(
   ' - none -'
 );
 foreach ($permissions as $key => $p) {
   $permission_options[$key] = $key;
 }
  $form['vtabs'] = array(
   '#type' => 'vertical_tabs',
 );
  $form['password_report'] = array(
   '#type' => 'fieldset',
   '#title' => t('Password policy report'),
   '#group' => 'vtabs',
 );
  $form['modules'] = array(
   '#type' => 'fieldset',
   '#title' => t('Banned module access'),
   '#group' => 'vtabs',
 );
  $form['permissions'] = array(
   '#type' => 'fieldset',
   '#title' => t('Banned permissions access'),
   '#group' => 'vtabs',
 );
  $form['password_report']['govcms_account_security_policy_report'] = array(
   '#markup' => $output
 );
  $form['modules']['govcms_account_security_policy_report_banned_modules'] = array(
   '#type' => 'select',
   '#title' => t('Modules to remove from applicability'),
   '#options' => $module_options,
   '#size' => '10',
   '#default_value' => variable_get('govcms_account_security_policy_report_banned_modules', array()),
   '#description' => t('Remove the following modules from the modules list page for all users not user 1.'),
   '#multiple' => TRUE
 );
  $form['permissions']['govcms_account_security_policy_report_banned_permissions'] = array(
   '#type' => 'select',
   '#title' => t('Permissions to remove from applicability'),
   '#options' => $permission_options,
   '#size' => '10',
   '#default_value' => variable_get('govcms_account_security_policy_report_banned_permissions', array()),
   '#description' => t('Remove the following permissions from the modules list page for all users not user 1.'),
   '#multiple' => TRUE
 );
  return system_settings_form($form);

}
