<?php

/**
 * @file
 * Admin page callback file for the Password Policy module.
 *
 * @ignore sniffer_commenting_functioncomment_missingparamtype:file
 * @ignore sniffer_commenting_functioncomment_missingreturntype:file
 */

/****************************************************************************/
/* Password policy admin settings                                           */
/****************************************************************************/

/**
 * Settings form display.
 */
function password_policy_admin_settings() {
  $form['password_policy_force_change_reset'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force password change on reset'),
    '#default_value' => variable_get('password_policy_force_change_reset', 0),
    '#description' => t('When a user requests a one-time login link, this option will require the user to change their password before continuing to browse the site.'),
  );

  $form['expiration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expiration settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['expiration']['password_policy_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Admin (UID=1) password expires.'),
    '#default_value' => variable_get('password_policy_admin', 0),
    '#description' => t('Admin account password will obey expiration policy.'),
  );
  $form['expiration']['password_policy_begin'] = array(
    '#type' => 'radios',
    '#title' => t('Beginning of password expirations'),
    '#default_value' => variable_get('password_policy_begin', 0),
    '#options' => array('0' => t('After expiration time from setting a default policy (all passwords are valid during the expiration time from setting the default policy, and after that older than expiration time passwords expire).'), '1' => t('Setting a default policy (passwords older than expiration time expire after setting the default policy, retroactive behaviour).')),
  );
  $form['expiration']['password_policy_block'] = array(
    '#type' => 'radios',
    '#title' => t('Blocking expired accounts'),
    '#default_value' => variable_get('password_policy_block', 0),
    '#options' => array('0' => t('Expired accounts are blocked. Only administrators can unblock them. Users whose accounts have expired will be forced to change their passwords at next login (after being unblocked).'), '1' => t('Expired accounts are not blocked. Users whose accounts have expired will be forced to change their passwords at next login.')),
  );

  // Visibility.
  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['visibility']['password_policy_show_restrictions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show restrictions on password change page.'),
    '#default_value' => variable_get('password_policy_show_restrictions', 0),
    '#description' => t('Should password restrictions be listed on the password change page. A javascript warning block will be shown anyways if ithe typed in password does not meet the restrictions.'),
  );

  // E-mail notification settings.
  $form['email'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail notification settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['email']['password_policy_warning_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject of warning e-mail'),
    '#default_value' => _password_policy_mail_text('warning_subject'),
    '#maxlength' => 180,
    '#description' => t('Customize the subject of the warning e-mail message, which is sent to remind of password expiration.') . ' ' . t('Available variables are:') . ' !username, !site, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri, !days_left.',
  );
  $form['email']['password_policy_warning_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body of warning e-mail'),
    '#default_value' => _password_policy_mail_text('warning_body'),
    '#rows' => 15,
    '#description' => t('Customize the body of the warning e-mail message, which is sent to remind of password expiration.') . ' ' . t('Available variables are:') . ' !username, !site, !uri, !uri_brief, !mailto, !date, !login_uri, !edit_uri, !days_left.',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  $form['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
  );

  return $form;
}

/**
 * Submit hook for the settings form.
 */
function password_policy_admin_settings_submit($form, &$form_state) {
  $op = $form_state['clicked_button']['#value'];
  switch ($op) {
    case t('Save configuration'):
      variable_set('password_policy_admin', $form_state['values']['password_policy_admin']);
      variable_set('password_policy_begin', $form_state['values']['password_policy_begin']);
      variable_set('password_policy_block', $form_state['values']['password_policy_block']);
      variable_set('password_policy_show_restrictions', $form_state['values']['password_policy_show_restrictions']);
      variable_set('password_policy_warning_subject', $form_state['values']['password_policy_warning_subject']);
      variable_set('password_policy_warning_body', $form_state['values']['password_policy_warning_body']);
      variable_set('password_policy_force_change_reset', $form_state['values']['password_policy_force_change_reset']);
      drupal_set_message(t('The configuration options have been saved.'));
      break;

    case t('Reset to defaults'):
      variable_del('password_policy_admin');
      variable_del('password_policy_begin');
      variable_del('password_policy_block');
      variable_del('password_policy_show_restrictions');
      variable_del('password_policy_warning_subject');
      variable_del('password_policy_warning_body');
      variable_del('password_policy_force_change_reset');
      drupal_set_message(t('The configuration options have been reset to their default values.'));
      break;
  }
}

/**
 * Lists roles to which a policy applies.
 *
 * @param $pid
 *   Policy id.
 *
 * @return
 *   Array of role names.
 */
function _password_policy_admin_list_roles($pid) {
  $roles = array();
  $query = db_select('role', 'r', array('target' => 'slave'));
  $query->innerJoin('password_policy_role', 'p', 'p.rid = r.rid');
  $result = $query->fields('r', array('name'))
    ->condition('p.pid', $pid)
    ->execute();
  foreach ($result as $row) {
    $roles[] = $row->name;
  }
  return $roles;
}

/**
 * The list of the password policies.
 */
function password_policy_admin_list($form) {
  $options = array();
  $enabled = array();

  // @ignore sniffer_array_array_longlinedeclaration:2
  $result = db_select('password_policy', 'p', array('fetch' => PDO::FETCH_ASSOC, 'target' => 'slave'))
      ->fields('p', array('pid', 'name', 'enabled', 'description', 'created', 'weight'))
      ->orderBy('weight')
      ->execute();

  $form['#tree'] = TRUE;
  foreach ($result as $row) {
    $pid = $row['pid'];
    $options[$pid] = $row['enabled'] ? format_date($row['created'], 'medium') : '';
    if ($row['enabled']) {
      $enabled[] = $pid;
    }

    $form['policies'][$pid]['name'] = array(
      '#markup' => check_plain($row['name']),
    );
    $form['policies'][$pid]['roles'] = array(
      '#markup' => theme('item_list', array('items' => _password_policy_admin_list_roles($pid))),
    );
    $form['policies'][$pid]['enabled'] = array(
      '#type' => 'checkbox',
      '#default_value' => $row['enabled'],
    );
    $form['policies'][$pid]['view'] = array(
      '#type' => 'link',
      '#title' => 'view',
      '#href' => 'admin/config/people/password_policy/' . $pid,
    );
    $form['policies'][$pid]['edit'] = array(
      '#type' => 'link',
      '#title' => 'edit',
      '#href' => 'admin/config/people/password_policy/' . $pid . '/edit',
    );
    $form['policies'][$pid]['delete'] = array(
      '#type' => 'link',
      '#title' => 'delete',
      '#href' => 'admin/config/people/password_policy/' . $pid . '/delete',
    );
    $form['policies'][$pid]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight for @title', array('@title' => $row['name'])),
      '#title_display' => 'invisible',
      '#default_value' => $row['weight'],
    );
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );
  return $form;
}

/**
 * Submit hook for the form on the default list view.
 */
function password_policy_admin_list_submit($form, &$form_state) {
  foreach ($form_state['values']['policies'] as $pid => $policy) {
    db_query("UPDATE {password_policy} SET weight = :weight WHERE pid = :pid", array(':weight' => $policy['weight'], ':pid' => $pid));
    // Ensure we don't reset the timestamp on policies that are already enabled.
    if ($policy['enabled']) {
      db_query("UPDATE {password_policy} SET enabled = 1, created = :time WHERE pid = :pid AND enabled = 0", array(':time' => time(), ':pid' => $pid));
    }
    else {
      db_query("UPDATE {password_policy} SET enabled = 0 WHERE pid = :pid", array(':pid' => $pid));
    }
  }

  drupal_set_message(t('The changes have been saved.'));
}

/**
 * Returns HTML for the password policy administration list.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 * @see theme_filter_admin_overview()
 */
function theme_password_policy_admin_list($variables) {
  $form = $variables['form'];

  $rows = array();
  if (isset($form['policies']) && count($form['policies'])) {
    foreach (element_children($form['policies']) as $id) {
      $form['policies'][$id]['weight']['#attributes']['class'] = array('password-policy-order-weight');
      $rows[] = array(
        'data' => array(
          drupal_render($form['policies'][$id]['name']),
          drupal_render($form['policies'][$id]['roles']),
          drupal_render($form['policies'][$id]['enabled']),
          drupal_render($form['policies'][$id]['weight']),
          drupal_render($form['policies'][$id]['view']),
          drupal_render($form['policies'][$id]['edit']),
          drupal_render($form['policies'][$id]['delete']),
        ),
        'class' => array('draggable'),
      );
    }
  }
  if (empty($rows)) {
    unset($form['actions']['submit']);
  }
  $header = array(
    t('Name'),
    t('Roles'),
    t('Enabled'),
    t('Weight'),
    array(
      'data' => t('Operations'),
      'colspan' => 3,
    ),
  );
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'password-policy-order'),
    'empty' => t('There are currently no policies. <a href="!url">Add a new one</a>.',
      array('!url' => url('admin/config/people/password_policy/add'))),
  ));
  $output .= drupal_render_children($form);

  drupal_add_tabledrag('password-policy-order', 'order', 'sibling', 'password-policy-order-weight');

  return $output;
}

/**
 * The default view for the password policy.
 */
function password_policy_admin_view($policy) {
  $output = check_plain($policy['description']);
  $header = array(t('Name'), t('Constraint'));
  $rows = array();

  $roles = _password_policy_admin_list_roles($policy['pid']);
  if (!empty($roles)) {
    $rows[] = array(t('Roles'), theme('item_list', array('items' => $roles)));
  }
  if (!empty($policy['expiration'])) {
    $rows[] = array(t('Expiration'), $policy['expiration']);
  }
  if (!empty($policy['warning'])) {
    $rows[] = array(t('Warning'), check_plain($policy['warning']));
  }

  foreach ($policy['policy'] as $key => $val) {
    $desc = _password_policy_constraint_description($key);
    $rows[] = array($desc['name'], $val);
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No policies defined.'), 'colspan' => 2));
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows));

  return $output;
}

/**
 * Form display for new or to be edited password policies.
 */
function password_policy_admin_form($form, &$form_state, $policy = NULL) {
  $form['policy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Policy'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['policy']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($policy['name']) ? $policy['name'] : '',
    '#maxlength' => 64,
    '#required' => TRUE,
  );
  $form['policy']['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#default_value' => isset($policy['description']) ? $policy['description'] : '',
    '#size' => 128,
    '#maxlength' => 255,
  );

  $form['roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Roles'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['roles']['roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#options' => user_roles(TRUE),
    '#default_value' => isset($policy['roles']) ? $policy['roles'] : array(),
    '#description' => t("Select the roles that this policy will apply to."),
  );

  $form['expiration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expiration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['expiration']['expiration'] = array(
    '#type' => 'textfield',
    '#title' => t('Password Expiration'),
    '#default_value' => isset($policy['expiration']) ? $policy['expiration'] : '0',
    '#size' => 5,
    '#maxlength' => 5,
    '#description' => t("The passwords will expire after this number of days. The users with expired passwords will be blocked. Setting this field to 0 will not put any password expiration constraints."),
  );
  $form['expiration']['warning'] = array(
    '#type' => 'textfield',
    '#title' => t('Password Expiration Warning'),
    '#default_value' => isset($policy['warning']) ? $policy['warning'] : '',
    '#size' => 10,
    '#description' => t("The comma separated list of days. The warning about expiration of the password will be sent out on those days before the expiration. Leaving this field empty won't send out or display any warnings."),
  );

  $form['constraints'] = array(
    '#type' => 'fieldset',
    '#title' => t('Constraints'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  foreach (_password_policy_constraints() as $constraint) {
    $desc = _password_policy_constraint_description($constraint);
    $form['constraints']['constraint_' . $constraint] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#default_value' => isset($policy['policy'][$constraint]) ? $policy['policy'][$constraint] : NULL,
      '#maxlength' => 3,
      '#title' => filter_xss($desc['name']),
      '#description' => filter_xss($desc['description']),
    );
  }

  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => is_array($policy) ? t('Save') : t('Create'),
  );

  if ($policy) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
    $form['actions']['pid'] = array(
      '#type' => 'hidden',
      '#value' => isset($policy['pid']) ? $policy['pid'] : '',
    );
  }

  return $form;
}

/**
 * Form validation hook for new or edited password policies.
 */
function password_policy_admin_form_validate($form, &$form_state) {
  $roles = array_filter($form_state['values']['roles']);
  if (empty($roles)) {
    form_set_error('roles', t('You must select at least one role for a policy to apply to.'));
  }
  if (!empty($form_state['values']['warning']) && !preg_match("/^[0-9,]+$/", $form_state['values']['warning'])) {
    form_set_error('warning', t('Warning must only contain digits and commas'));
  }
}

/**
 * Form submission hook for new or edited password policies.
 */
function password_policy_admin_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];

  if ($op == t('Delete')) {
    drupal_goto('admin/config/people/password_policy/delete/' . $form_state['values']['pid']);
  }

  $policy = array();
  foreach ($form_state['values'] as $key => $value) {
    // If we have no form value, then we have no constraint to set.
    if (!is_array($value)) {
      // Dodge issues with roles array.
      $value = trim($value);
      if ($value != "" && preg_match("/^constraint_/", $key)) {
        $policy[substr($key, 11)] = $value;
      }
    }
  }

  $expiration = intval($form_state['values']['expiration']);
  // If we have an pid, update, else save.
  if (isset($form_state['values']['pid']) && $form_state['values']['pid']) {
    db_update('password_policy')
      ->fields(array(
        'name' => $form_state['values']['name'],
        'description' => $form_state['values']['description'],
        'policy' => serialize($policy),
        'expiration' => !empty($expiration) ? $expiration : 0,
        'warning' => str_replace(' ', '', $form_state['values']['warning']),
      ))
      ->condition('pid', $form_state['values']['pid'])
      ->execute();
    drupal_set_message(t('Policy %name has been updated.', array('%name' => $form_state['values']['name'])));
    watchdog('password_policy', 'Policy %name updated.', array('%name' => $form_state['values']['name']), WATCHDOG_NOTICE, l(t('edit'), 'admin/config/people/password_policy/' . $form_state['values']['pid'] . '/edit'));
    $pid = $form_state['values']['pid'];
    db_delete('password_policy_role')
      ->condition('pid', $pid)
      ->execute();
  }
  else {
    $pid = db_insert('password_policy')
      ->fields(array(
        'name' => $form_state['values']['name'],
        'description' => $form_state['values']['description'],
        'enabled' => 0,
        'policy' => serialize($policy),
        'expiration' => !empty($expiration) ? $expiration : 0,
        'warning' => str_replace(' ', '', $form_state['values']['warning']),
      ))
      ->execute();
    drupal_set_message(t('Policy %name has been created.', array('%name' => $form_state['values']['name'])));
    watchdog('password_policy', 'New policy %name created.', array('%name' => $form_state['values']['name']), WATCHDOG_NOTICE, l(t('edit'), 'admin/config/people/password_policy/' . $pid . '/edit'));
  }

  foreach (array_filter($form_state['values']['roles']) as $rid => $enabled) {
    db_insert('password_policy_role')
      ->fields(array(
        'pid' => $pid,
        'rid' => $rid,
      ))
      ->execute();
  }

  $form_state['redirect'] = 'admin/config/people/password_policy/list';
}

/**
 * Confirmation form for the deletion of a password policy.
 *
 * Deletion takes place in password_policy_admin_delete_submit().
 */
function password_policy_admin_delete($form, $form_state, $policy) {
  $form['pid'] = array('#type' => 'hidden', '#value' => $policy['pid']);

  return confirm_form($form, t('Are you sure you want to delete the policy %name?', array('%name' => $policy['name'])), 'admin/config/people/password_policy/list', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

/**
 * Submit hook for the delete policy operation.
 */
function password_policy_admin_delete_submit($form, &$form_state) {
  $pid = $form_state['values']['pid'];
  $policy = _password_policy_load_policy_by_pid($pid);

  db_delete('password_policy')
    ->condition('pid', $pid)
    ->execute();
  db_delete('password_policy_role')
    ->condition('pid', $pid)
    ->execute();  drupal_set_message(t('Password policy %policy was deleted.', array('%policy' => $policy['name'])));
  watchdog('password_policy', 'Policy %name was deleted.', array('%name' => $policy['name']), WATCHDOG_NOTICE);
  drupal_goto('admin/config/people/password_policy/list');
}

/**
 * Forced password change form.
 */
function password_policy_password_change_settings() {
  $form = array();

  $form['password_policy_new_login_change'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force password change on first-time login'),
    '#default_value' => variable_get('password_policy_new_login_change', 0),
  );
  $roles = user_roles(TRUE);
  $form['password_policy_force_change_roles'] = array(
    '#type' => 'checkboxes',
    '#options' => $roles,
    '#title' => t('Force users in the following roles to change their password'),
    '#description' => t('Users who are not logged in will be required to change their password immediately upon login. Users who are currently logged in will be required to change their password upon their next page request, but after changing their password will be redirected back to the page they were attempting to access.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );

  return $form;
}

/**
 * Submit hook for forced password change form.
 */
function password_policy_password_change_settings_submit($form, &$form_state) {
  global $user;
  $selected_roles = array();
  variable_set('password_policy_new_login_change', $form_state['values']['password_policy_new_login_change']);
  if ($form_state['values']['password_policy_new_login_change'] == 1) {
    watchdog('password_policy', 'New user accounts must change password on new login enabled by !admin', array('!admin' => $user->name), WATCHDOG_NOTICE);
  }
  ($form_state['values']['password_policy_new_login_change']) ? drupal_set_message(t('New users will be required to change their password on first-time login.')) : drupal_set_message(t('New users will not be required to change their pasword on first-time login.'));
  foreach ($form_state['values']['password_policy_force_change_roles'] as $role) {
    // Skip over null values returned by unselected roles.
    if ($role == 0) {
      continue;
    }
    $uids = array();
    // Special handling for authenticated users role, since this role makes no
    // entries in the users_roles table.
    if ($role == 2) {
      // No point in flagging anonymous since they can't log in anyway.
      $db_uids = db_query('SELECT uid FROM {users} WHERE uid <> 0')->fetchCol();
    }
    else {
      $db_uids = db_query('SELECT uid FROM {users_roles} WHERE rid = :rid', array('rid' => $role))->fetchCol();
    }
    foreach ($db_uids as $uid) {
      if (($uid == 1 && variable_get('password_policy_admin', 0)) || $uid > 1) {
        $uids[] = $uid;
      }
    }
    if (!empty($uids)) {
      db_update('password_policy_force_change')
        ->fields(array(
          'force_change' => 1,
        ))
        ->condition('uid', $uids, 'IN')
        ->execute();
    }
    $selected_roles[] = $role;
  }
  if (count($selected_roles)) {
    $roles = user_roles(TRUE);
    $list = array();
    foreach ($selected_roles as $sr) {
      $list[] = $roles[$sr];
    }
    $list = implode(', ', $list);
    drupal_set_message(t('Users in the following roles will be required to immediately change their password: %list', array('%list' => $list)), 'status');
    watchdog('password_policy', '!admin has flagged users in the following roles to immediately change their password: %list', array('%list' => $list, '!admin' => $user->name), WATCHDOG_NOTICE);
  }
  else {
    drupal_set_message(t('No roles were selected.'));
  }
}
