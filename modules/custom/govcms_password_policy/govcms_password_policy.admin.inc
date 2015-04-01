<?php

/**
 * @file
 * Contains admin paths for govCMS Password Policy
 *
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Chris Skene chris at previousnext dot com dot au
 * @copyright Copyright(c) 2014 Previous Next Pty Ltd
 */

/**
 * Settings form for govcms password policy.
 */
function govcms_password_policy_admin_settings() {

  $form = array();

  $form['govcms_password_policy_ready'] = array(
    '#type' => 'select',
    '#title' => t('Hide the ASD password warning'),
    '#options' => array(
      '0' => t('Visible'),
      '1' => t('Hidden'),
    ),
    '#default_value' => variable_get('govcms_password_policy_ready', 0),
  );

  return system_settings_form($form);
}
