<?php

/**
 * @file
 * Acquia Site Factory OpenID related admin functions.
 */

/**
 * Form constructor for the user invitation form.
 *
 * @see acsf_openid_admin_invite_people_form_validate()
 * @see acsf_openid_admin_invite_people_form_submit()
 *
 * @ingroup forms
 */
function acsf_openid_admin_invite_people_form($form, &$form_state) {
  $threshold = acsf_openid_admin_invite_people_threshold_get();
  $window = acsf_openid_admin_invite_people_window_get();
  if (empty($_POST) && !flood_is_allowed('acsf_openid_admin_invite_people', $threshold, $window)) {
    drupal_set_message(t('You are only allowed to send @number_per_day invitations per day and have already reached your limit. You will not be able to submit this form until later.', array('@number_per_day' => $threshold)), 'warning');
  }

  $form['email_addresses'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter e-mail addresses for people you would like to invite'),
    '#description' => t('Separate e-mail addresses with commas. Invitations are limited to @threshold a day.', array('@threshold' => $threshold)),
  );
  $form['invitation_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Invitation message'),
    '#description' => t('Available variables are: @tokens.', array('@tokens' => implode(', ', acsf_openid_admin_invite_people_tokens()))),
    '#default_value' => _user_mail_text('register_admin_created_body', NULL, array(), FALSE),
    '#rows' => 9,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'acsf_openid') . '/acsf_openid.invite.js'),
    ),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send invitations'),
  );

  return $form;
}

/**
 * Form validation handler for acsf_openid_admin_invite_people_form().
 */
function acsf_openid_admin_invite_people_form_validate($form, &$form_state) {
  // There must be at least one e-mail address.
  $address_list = trim($form_state['values']['email_addresses']);
  if (empty($address_list)) {
    form_set_error('email_addresses', t('You must enter at least one email address.'));
  }

  // All email addresses must be valid.
  $addresses = array_unique(array_map('trim', explode(',', $address_list)));
  $invalid_addresses = array();
  foreach ($addresses as $address) {
    // We store these email addresses in the database, so make sure they are
    // also within the maximum length.
    if (!valid_email_address($address) || drupal_strlen($address) > EMAIL_MAX_LENGTH) {
      $invalid_addresses[] = $address;
    }
  }
  $number_invalid = count($invalid_addresses);
  if ($number_invalid) {
    $message = format_plural($number_invalid, 'The email address %addresses is invalid.', 'The following email addresses are invalid: %addresses', array('%addresses' => implode(', ', $invalid_addresses)));
    form_set_error('email_addresses', $message);
  }

  // The number of email addresses must not put us over the flood control limit.
  $number_of_addresses = count($addresses);
  $threshold = acsf_openid_admin_invite_people_threshold_get();
  $limit = $threshold - $number_of_addresses + 1;
  $window = acsf_openid_admin_invite_people_window_get();
  // Iterate to find out how many events we have left. (A direct database query
  // would be more efficient, but also more fragile in terms of not using the
  // flood API.)
  while (!flood_is_allowed('acsf_openid_admin_invite_people', $limit, $window) && $number_of_addresses > 0) {
    $number_of_addresses--;
    $limit++;
    $flood_error = TRUE;
  }
  if (!empty($flood_error)) {
    if ($number_of_addresses) {
      form_set_error('email_addresses', format_plural($number_of_addresses, 'You are only allowed to invite 1 user at this time. (You can send a total of @number_per_day invitations per day.)', $number_of_addresses < $threshold ? 'You are only allowed to invite @count users at this time. (You can send a total of @number_per_day invitations per day.)' : 'You are only allowed to invite @count users per day.', array('@number_per_day' => $threshold)));
    }
    else {
      form_set_error('email_addresses', t('You are only allowed to send @number_per_day invitations per day and have already reached your limit. Try again later.', array('@number_per_day' => $threshold)));
    }
  }
}

/**
 * Form submit handler for acsf_openid_admin_invite_people_form().
 */
function acsf_openid_admin_invite_people_form_submit($form, &$form_state) {
  // Set the submitted invitation message to be used from now on.
  variable_set('user_mail_register_admin_created_body', $form_state['values']['invitation_message']);

  $address_list = trim($form_state['values']['email_addresses']);
  $addresses = array_map('trim', explode(',', $address_list));
  $window = acsf_openid_admin_invite_people_window_get();
  $successes = array();
  $failures = array();
  $original_addresses = $addresses;
  $addresses = array_unique($addresses);
  $has_duplicates = count($addresses) != count($original_addresses);
  foreach ($addresses as $address) {
    // Send mail to the address. Pass in an fake 'account' variable so we can
    // use the [user:mail] token, but make sure it has most standard user
    // object properties to avoid PHP notices.
    $account = (object) array_merge((array) drupal_anonymous_user(), db_query("SELECT * FROM {users} WHERE uid = 0")->fetchAssoc());
    $account->mail = $address;
    $message = drupal_mail('user', 'register_admin_created', $address, language_default(), array('account' => $account));
    if ($message['result']) {
      $successes[] = $address;
      // Register the event with the flood control API.
      flood_register_event('acsf_openid_admin_invite_people', $window);
      // Store a record of this invitation.
      acsf_openid_admin_user_invite_save($address);
    }
    else {
      $failures[] = $address;
    }
  }
  if ($number_of_failures = count($failures)) {
    drupal_set_message(format_plural($number_of_failures, 'Mail could not be sent to the following address: %addresses', 'Mail could not be sent to the following addresses: %addresses', array('%addresses' => implode(', ', $failures))), 'error');
  }
  if ($number_of_successes = count($successes)) {
    if ($has_duplicates) {
      drupal_set_message(format_plural($number_of_successes, '1 site registration invitation was sent (duplicate emails were removed). After an invitee registers, they will show up in the list below.', '@count site registration invitations were sent (duplicate emails were removed). After an invitee registers, they will show up in the list below.'));
    }
    else {
      drupal_set_message(format_plural($number_of_successes, '1 site registration invitation was sent. After an invitee registers, they will show up in the list below.', '@count site registration invitations were sent. After an invitee registers, they will show up in the list below.'));
    }
  }
  $form_state['redirect'] = 'admin/people';
}

/**
 * Saves an invited email address to the database.
 *
 * @param string $email
 *   The email address to save.
 *
 * @return bool
 *   TRUE if an invitation was created; FALSE if did not need to be created
 *   because the e-mail address was already invited.
 */
function acsf_openid_admin_user_invite_save($email) {
  $status = db_merge('acsf_openid_invited_users')
    ->key(array('mail' => $email))
    ->execute();

  return $status == MergeQuery::STATUS_INSERT;
}

/**
 * Returns the number of invites that can be sent out in a certain window.
 *
 * @see acsf_openid_admin_invite_people_window_get()
 */
function acsf_openid_admin_invite_people_threshold_get() {
  return variable_get('acsf_openid_invite_people_threshold', 25);
}

/**
 * Returns the window (in seconds) over which site invites are limited.
 *
 * @see acsf_openid_admin_invite_people_threshold_get()
 */
function acsf_openid_admin_invite_people_window_get() {
  // The window is equal to one day. (Note that if we ever change this, there
  // is a lot of text in the form that would need to be changed also.)
  return variable_get('acsf_openid_invite_people_window', 86400);
}

/**
 * Returns an array of tokens for the message inviting users to a site.
 */
function acsf_openid_admin_invite_people_tokens() {
  return array(
    '[site:name]',
    '[site:url]',
    '[site:register-url]',
    '[site:url-brief]',
    '[user:mail]',
    '[site:service-name]',
    '[site:factory-account-url]',
  );
}

/**
 * Form constructor to configure acsf_openid behaviour.
 *
 * @see acsf_openid_admin_settings_form_submit()
 *
 * @ingroup forms
 */
function acsf_openid_admin_settings_form($form, $form_state) {
  $factory_name = acsf_factory_name();

  $form['overlay_status'] = array(
    '#type' => 'fieldset',
    '#weight' => -10,
    '#title' => t('Overlay'),
  );

  if (!module_exists('overlay')) {
    $form['overlay_status']['#description'] = t('You cannot configure any overlay-related settings until you enable the Overlay module.');
  }

  if (acsf_openid_force_openid()) {
    $title = t('Use the overlay for custom user fields during registration');
    $description = t("During registration, account fields are always displayed in the overlay. If enabled, custom fields will use the overlay also, instead of the site's page.");
  }
  else {
    $title = t('Use the overlay for custom user fields during !service_name_long account registration', array(
      '!service_name_long' => $factory_name,
    ));
    $description = t("When a user registers with a !service_name_long account, fields provided by !service_name_long are always displayed in the overlay. If enabled, custom fields will use the overlay also, instead of the site's page.", array(
      '!service_name_long' => $factory_name,
    ));
  }
  $form['overlay_status']['acsf_openid_overlay_for_registration'] = array(
    '#type' => 'checkbox',
    '#title' => $title,
    '#description' => $description,
    '#default_value' => variable_get('acsf_openid_overlay_for_registration', 1),
    '#disabled' => !module_exists('overlay'),
  );

  $form['overlay_status']['acsf_openid_overlay_for_login'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the overlay for OpenID sign-in pages'),
    '#default_value' => variable_get('acsf_openid_overlay_for_login', 1),
    '#disabled' => !module_exists('overlay'),
  );

  $form['overlay_status']['acsf_openid_overlay_for_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the overlay for administration pages'),
    '#default_value' => variable_get('acsf_openid_overlay_for_admin', 1),
    '#disabled' => !module_exists('overlay'),
  );

  $form['generic'] = array(
    '#title' => t('Advanced Settings'),
    '#type' => 'fieldset',
  );
  $form['generic']['acsf_openid_global_logout'] = array(
    '#type' => 'checkbox',
    '#title' => t('Global sign out'),
    '#description' => t('When users sign out from this website they will also be signed out of the Acquia Cloud Site Factory.'),
    '#default_value' => variable_get('acsf_openid_global_logout', 1),
  );
  $form['generic']['acsf_openid_registration_handling'] = array(
    '#type' => 'checkbox',
    '#title' => t('Registration override'),
    '#description' => t('Use OpenID for invited users, even if new account creation is not allowed.'),
    '#default_value' => variable_get('acsf_openid_registration_handling', 1),
  );

  // Since some of these flags may require us to rebuild menu, we have to ensure
  // that our submit function gets executed after the variable_set, this is why
  // we are adding our submit function after system_settings_form().
  $form = system_settings_form($form);
  $form['#submit'][] = 'acsf_openid_admin_settings_form_submit';

  return $form;
}

/**
 * Form submit handler for acsf_openid_admin_settings_form().
 */
function acsf_openid_admin_settings_form_submit(&$form, &$form_state) {
  // Some flags may have changed affecting some of the menu items.
  menu_rebuild();

  if (empty($form_state['values']['acsf_openid_overlay_for_admin'])) {
    if (module_exists('overlay') && !empty($form['overlay_status']['acsf_openid_overlay_for_admin']['#default_value'])) {
      // If we were in the overlay and the overlay was disabled, we need to
      // close it down and prevent the form redirect.
      acsf_openid_close_overlay('admin/config/user-interface/overlay');
      $form_state['redirect'] = '';
    }
  }
  elseif (empty($form['overlay_status']['acsf_openid_overlay_for_admin']['#default_value'])) {
    // Going to the overlay from the non-overlay admin. Since the admin
    // pages will not activate the overlay, we need to redirect out from
    // there (to the front page).
    $form_state['redirect'] = '';
  }
}
