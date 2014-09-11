<?php

/**
 * @file
 * The password policy password tab page callbacks.
 */

/**
 * Password change form.
 */
function password_policy_password_tab($form, &$form_state, $account) {
  global $user;

  // During initial form build, add the entity to the form state for use during
  // form building and processing. During a rebuild, use what is in the form
  // state.
  if (!isset($form_state['user'])) {
    $form_state['user'] = $account;
  }
  else {
    $account = $form_state['user'];
  }

  if ($user->uid == $account->uid) {
    // To skip the current password field, the user must have logged in via a
    // one-time link and have the token in the URL.
    $pass_reset = isset($_SESSION['pass_reset_' . $account->uid]) && isset($_GET['pass-reset-token']) && ($_GET['pass-reset-token'] == $_SESSION['pass_reset_' . $account->uid]);
    $protected_values = array();
    $current_pass_description = '';
    // The user may only change their own password without their current
    // password if they logged in via a one-time login link.
    if (!$pass_reset) {
      $protected_values['mail'] = t('E-mail address');
      $protected_values['pass'] = t('Password');
      $request_new = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));
      $current_pass_description = t('Enter your current password to change the %pass. !request_new.', array('%pass' => $protected_values['pass'], '!request_new' => $request_new));
    }
    // The user must enter their current password to change to a new one.
    if (isset($protected_values['pass'])) {
      $form['current_pass_required_values'] = array(
        '#type' => 'value',
        '#value' => array('pass' => $protected_values['pass']),
      );

      $form['account']['current_pass'] = array(
        '#type' => 'password',
        '#title' => t('Current password'),
        '#size' => 25,
        '#access' => !empty($protected_values),
        '#description' => $current_pass_description,
        '#weight' => -5,
        '#attributes' => array('autocomplete' => 'off'),
      );

      $form['#validate'][] = 'user_validate_current_pass';
    }
  }

  $form['pass'] = array(
    '#type' => 'password_confirm',
    '#size' => 25,
    '#required' => TRUE,
    '#description' => t('To change the current user password, enter the new password in both fields.'),
  );

  // @TODO Remove this as it supports a D6-style of interacting with a user form
  // In the future, this data should be stored in $form_state.
  $form['#uid'] = $account->uid;
  $form['#user'] = $account;
  $form['_account'] = array('#type' => 'value', '#value' => $account);

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Password change form validation.
 */
function password_policy_password_tab_validate($form, &$form_state) {
  $pass = trim($form_state['values']['pass']);
  if (empty($pass)) {
    form_set_error('pass', t('Your password cannot be empty.'));
  }
}

/**
 * Password change form submit.
 */
function password_policy_password_tab_submit($form, &$form_state) {
  global $user;

  $account = $form['_account']['#value'];
  $account = $form_state['user'];

  user_module_invoke('submit', $form_state['values'], $account, 'account');
  user_save($account, array('pass' => $form_state['values']['pass']));
  drupal_set_message(t('Password has been changed.'));

  if (variable_get('password_policy_password_tab_redirect', '') && !preg_match('/[?&]destination=/', $form['#action'])) {
    $redirect = drupal_parse_url(format_string(variable_get('password_policy_password_tab_redirect', ''), array('%uid' => $user->uid)));
    $opts = array();

    if (!empty($redirect['fragment'])) {
      $opts['fragment'] = $redirect['fragment'];
    }
    if (!empty($redirect['query'])) {
      parse_str($redirect['query'], $params);
      $opts['query'] = $params;
    }
    $form_state['redirect'] = array($redirect['path'], $redirect);
  }
}
