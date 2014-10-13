<?php

/**
 * @file
 * Provides drush commands to set up a site for Acquia Site Factory.
 */

/**
 * Implements hook_drush_command().
 */
function acsf_init_drush_command() {
  return array(
    'acsf-init' => array(
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
      'callback' => 'drush_acsf_init',
      'description' => dt('Installs/updates the non-standard Drupal components for this repository to be compatible with Acquia Site Factory. This command will update in place, so there is no harm in running it multiple times.'),
    ),
    'acsf-connect-factory' => array(
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
      'callback' => 'drush_acsf_connect_factory',
      'description' => dt('Connect a site to a factory by setting up the right variables in the database.'),
      'aliases' => array('acsf-cf'),
      'options' => array(
        'site-admin-mail' => array(
          'description' => dt('The email address of the Site Factory admin / Gardens admin user. This is typically the "Gardens admin" user on the factory. These email addresses have to match in order for the initial OpenID connection to bind these accounts.'),
          'required' => TRUE,
          'example-value' => 'user3@example.com',
        ),
        'site-owner-name' => array(
          'description' => dt('The name of the site owner.'),
          'required' => TRUE,
          'example-value' => 'John Smith',
        ),
        'site-owner-mail' => array(
          'description' => dt('The email address of the site owner.'),
          'required' => TRUE,
          'example-value' => 'john.smith@example.com',
        ),
        'site-owner-roles' => array(
          'description' => dt('A list of comma-separated roles that should be granted to the site owner (optional).'),
          'example-value' => 'editor, site manager',
        ),
      ),
      'examples' => array(
        'drush acsf-connect-factory --site-admin-mail="user3@example.com" --site-owner-name="John Smith" --site-owner-mail="john.smith@example.com"' => dt('Connect the site to the factory and sets the owner to John Smith.'),
      ),
    ),
    'acsf-init-verify' => array(
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
      'callback' => 'drush_acsf_init_verify',
      'description' => dt('Verifies that acsf-init was successfully run in the current version.'),
    ),
    'acsf-uninstall' => array(
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
      'callback' => 'drush_acsf_uninstall',
      'description' => dt('Uninstalls components for this Drupal repository to be compatible with Acquia Site Factory.'),
    ),
  );
}

/**
 * Command callback: executes the required changes to this repository.
 */
function drush_acsf_init() {
  // Retrieve the path to the acsf module relative to this file.
  $path = dirname(dirname(dirname(__FILE__)));
  $relative_path = str_replace(DRUPAL_ROOT . '/', '', $path);
  $repo_root = str_replace('/docroot', '', DRUPAL_ROOT);
  $lib_path = sprintf('%s/%s/acsf/acsf_init/lib', DRUPAL_ROOT, $relative_path);

  drush_print(dt('Installing ACSF requirements.'));

  // Create the required directories.
  foreach (acsf_init_get_required_dirs($repo_root) as $name => $dir) {
    drush_print(dt('Creating directory for !name at !dir', array(
      '!name' => $name,
      '!dir' => $dir,
    )));
    if (!file_exists($dir)) {
      if (mkdir($dir, 0755, TRUE)) {
        drush_log(dt('Success'), 'success', 'success');
      }
      else {
        drush_log(dt('Error'), 'error', 'error');
      }
    }
    else {
      drush_log(dt('Already Exists'), 'success', 'ok');
    }
  }

  // Copy the required files.
  foreach (acsf_init_get_required_files($repo_root) as $file => $location) {
    $source = sprintf('%s/%s/%s', $lib_path, $location['source'], $file);
    $dest = sprintf('%s/%s', $location['dest'], $file);
    $mod = isset($location['mod']) ? $location['mod'] : FALSE;
    drush_print(dt('Copying !file to !dest.', array(
      '!file' => $source,
      '!dest' => $dest,
    )));
    if (file_exists($dest)) {
      $confirm = drush_confirm(dt('Destination file exists, continue?'));
      if ($confirm === FALSE) {
        continue;
      }
    }
    // Copy the file into the destination.
    if (copy($source, $dest)) {
      drush_log(dt('Copy Success: !file', array('!file' => $file)), 'success', 'success');
    }
    else {
      drush_log(dt('Copy Error: !file', array('!file' => $file)), 'error', 'error');
    }
    // Chmod the file if required.
    if ($mod && chmod($dest, $mod)) {
      drush_log(dt('Chmod Success: !file', array('!file' => $file)), 'success', 'success');
    }
    elseif ($mod) {
      drush_log(dt('Chmod Error: !file', array('!file' => $file)), 'error', 'error');
    }
  }

  // Verify that the files are in sync.
  drush_acsf_init_verify();
}

/**
 * Command callback: Connect a site to a Factory.
 */
function drush_acsf_connect_factory() {
  // Preliminary validation before starting to modify the database.
  $site_admin_mail = trim(drush_get_option('site-admin-mail'));
  $site_owner_name = trim(drush_get_option('site-owner-name'));
  $site_owner_mail = trim(drush_get_option('site-owner-mail'));
  $site_owner_roles = drush_get_option_list('site-owner-roles');

  $site_owner_account = user_load_by_mail($site_owner_mail);
  // Validate email addresses.
  if (!valid_email_address($site_admin_mail)) {
    return drush_set_error(dt('The site-admin-mail value is not a valid email address.'));
  }
  if (!valid_email_address($site_owner_mail)) {
    return drush_set_error(dt('The site-owner-mail value is not a valid email address.'));
  }
  // Make sure there is no regular user account with the admin email address.
  $site_admin_mail_account = user_load_by_mail($site_admin_mail);
  if ($site_admin_mail_account && $site_admin_mail_account->uid > 1) {
    return drush_set_error(dt('Unable to sync the admin account, the email address @mail is already used by the user account @uid.', array(
      '@mail' => $site_admin_mail,
      '@uid' => $site_admin_mail_account->uid,
    )));
  }
  // Make sure there is no user with the same name before creating a new user.
  if (empty($site_owner_account) && user_load_by_name($site_owner_name)) {
    return drush_set_error(dt('Unable to create the site owner account, there is already a user account with the name @site-owner-name but with a different email address.', array(
      '@site-owner-name' => $site_owner_name,
    )));
  }
  // Make sure the name isn't used by another user with a different email.
  $conflicting_account = user_load_by_name($site_owner_name);
  if ($conflicting_account && $site_owner_account->uid !== $conflicting_account->uid) {
    return drush_set_error(dt('Unable to update the site owner account, uid @uid is already using the name @site-owner-name but with a different email address.', array(
      '@uid' => $conflicting_account->uid,
      '@site-owner-name' => $site_owner_name,
    )));
  }
  // If a list of roles was specified, make sure they all exist.
  foreach ($site_owner_roles as $role) {
    if (!user_role_load_by_name($role)) {
      return drush_set_error(dt('The role @role does not exist.', array('@role' => $role)));
    }
  }

  // Clear all caches ahead of time so Drupal has a chance to rebuild
  // registries.
  drupal_flush_all_caches();
  acsf_build_registry();
  drush_log(dt('Cleared all caches.'), 'ok');

  // Set default settings for user accounts.
  $default_account_edit = array();
  $default_account_edit['status'] = 1;
  // Set login to non-zero to avoid e-mail verification needed error.
  $default_account_edit['login'] = 1;

  // Take over uid 1 with our Gardens admin user.
  $admin_account = user_load(1);
  // Create a new user if uid 1 doesn't exist.
  if (empty($admin_account)) {
    $admin_account = new stdClass();
    $admin_account->uid = 1;
    $admin_account->is_new = TRUE;
  }
  $admin_account_edit = $default_account_edit;
  if (variable_get('user_admin_role', 0)) {
    $admin_account_edit['roles'][variable_get('user_admin_role', 0)] = 1;
  }
  user_save($admin_account, array(
    'name' => 'Gardens admin',
    'pass' => user_password(),
    'mail' => $site_admin_mail,
  ) + $admin_account_edit);

  // Create or update site owner account.
  // Prepare roles for site owner.
  $site_owner_account_edit = $default_account_edit;
  foreach ($site_owner_roles as $role) {
    $rid = user_role_load_by_name($role)->rid;
    $site_owner_account_edit['roles'][$rid] = 1;
  }
  // Site owners also get the administrator role.
  if (variable_get('user_admin_role', 0)) {
    $site_owner_account_edit['roles'][variable_get('user_admin_role', 0)] = 1;
  }
  user_save($site_owner_account, array(
    'name' => $site_owner_name,
    'pass' => user_password(),
    'mail' => $site_owner_mail,
  ) + $site_owner_account_edit);
  drush_log(dt('Synched Gardens admin and site owner accounts.'), 'ok');

  // Remove all traces of openid.
  if (module_exists('openid')) {
    db_truncate('authmap')->execute();
    db_truncate('openid_association')->execute();
    db_truncate('openid_nonce')->execute();
    drush_log(dt('Removed all openid associations and endpoints.'), 'ok');
  }

  // Remove acsf variables so that they can be repopulated with the right values
  // on the next acsf-site-sync. We don't truncate the entire table in case a
  // custom module has stored custom variables in acsf_variables.
  acsf_vdel('acsf_site_info');

  // Reset the local site data and run acsf-site-sync to fetch factory data
  // about the site.
  $site = acsf_get_acsf_site();
  $site->clean();
  drush_acsf_site_sync();
  drush_log(dt('Executed acsf-site-sync to gather site data from factory and reset all acsf variables.'), 'ok');

  // Clear all caches.
  drupal_flush_all_caches();
  drush_log(dt('Cleared all caches.'), 'ok');

  // Send a theme event notification to the Factory.
  $notify = acsf_theme_notification();
  $notify->sendNotification('site', 'create');
}

/**
 * Command callback: Verify that acsf-init was run against the current version.
 */
function drush_acsf_init_verify() {
  $drupal_root = rtrim(DRUPAL_ROOT, '/.');
  // Retrieve the path to the acsf module relative to this file.
  $path = dirname(dirname(dirname(__FILE__)));
  $relative_path = str_replace($drupal_root . '/', '', $path);
  $repo_root = str_replace('/docroot', '', $drupal_root);
  $lib_path = sprintf('%s/%s/acsf/acsf_init/lib', $drupal_root, $relative_path);

  $error = FALSE;
  foreach (acsf_init_get_required_files($repo_root) as $file => $location) {
    $source = sprintf('%s/%s/%s', $lib_path, $location['source'], $file);
    $dest = sprintf('%s/%s', $location['dest'], $file);
    if (!file_exists($dest)) {
      $error = TRUE;
      drush_set_error('FILE MISSING', dt('The file !file is missing.', array(
        '!file' => $file,
      )));
    }
    elseif (md5_file($source) != md5_file($dest)) {
      $error = TRUE;
      drush_set_error('FILE OUT OF DATE', dt('The file !file is out of date.', array(
        '!file' => $file,
      )));
    }
  }

  if ($error) {
    drush_print(dt('Please run drush acsf-init to correct these problems and commit the resulting code changes.'));
  }
  else {
    drush_log(dt('acsf-init required files ok'), 'success');
  }
}

/**
 * Command callback: Uninstalls ACSF files from the code base.
 */
function drush_acsf_uninstall() {
  drush_print('Removing ACSF requirements.');

  foreach (acsf_init_get_required_files($repo_root) as $file => $location) {
    $dest = sprintf('%s/%s', $location['dest'], $file);
    if (file_exists($dest)) {
      $confirm = drush_confirm(dt('Delete !file?', array('!file' => $dest)));
      if ($confirm === FALSE) {
        continue;
      }
      if (unlink($dest)) {
        drush_log(dt('Success'), 'success', 'success');
      }
      else {
        drush_log(dt('Error'), 'error', 'error');
      }
    }
  }
}

/**
 * Lists all required directories to create.
 */
function acsf_init_get_required_dirs($repo_root) {
  return array(
    'cloud hooks' => sprintf('%s/hooks/common/post-db-copy', $repo_root),
    'cloud hook deploy' => sprintf('%s/hooks/common/pre-web-activate', $repo_root),
    'acquia hook dir' => sprintf('%s/hooks/acquia', $repo_root),
    'cloud hook samples' => sprintf('%s/hooks/samples', $repo_root),
    'site config logic' => sprintf('%s/sites/g', DRUPAL_ROOT),
  );
}

/**
 * Lists all required files to create/delete.
 */
function acsf_init_get_required_files($repo_root) {
  return array(
    'README.md' => array(
      'source' => 'cloud_hooks',
      'dest' => sprintf('%s/hooks', $repo_root),
    ),
    '000-acquia_required_scrub.php' => array(
      'source' => 'cloud_hooks/common/post-db-copy',
      'dest' => sprintf('%s/hooks/common/post-db-copy', $repo_root),
      'mod' => 0751,
    ),
    '000-acquia-deployment.php' => array(
      'source' => 'cloud_hooks/common/pre-web-activate',
      'dest' => sprintf('%s/hooks/common/pre-web-activate', $repo_root),
      'mod' => 0751,
    ),
    'db_connect.php' => array(
      'source' => 'cloud_hooks/acquia',
      'dest' => sprintf('%s/hooks/acquia', $repo_root),
    ),
    'uri.php' => array(
      'source' => 'cloud_hooks/acquia',
      'dest' => sprintf('%s/hooks/acquia', $repo_root),
    ),
    'acquia-cloud-site-factory-post-db.sh' => array(
      'source' => 'cloud_hooks/samples',
      'dest' => sprintf('%s/hooks/samples', $repo_root),
    ),
    'hello-world.sh' => array(
      'source' => 'cloud_hooks/samples',
      'dest' => sprintf('%s/hooks/samples', $repo_root),
    ),
    'post-code-deploy.tmpl' => array(
      'source' => 'cloud_hooks/samples',
      'dest' => sprintf('%s/hooks/samples', $repo_root),
    ),
    'sites.php' => array(
      'source' => 'sites',
      'dest' => sprintf('%s/sites', DRUPAL_ROOT),
    ),
    'apc_rebuild.php' => array(
      'source' => 'sites/g',
      'dest' => sprintf('%s/sites/g', DRUPAL_ROOT),
    ),
    '.gitignore' => array(
      'source' => 'sites/g',
      'dest' => sprintf('%s/sites/g', DRUPAL_ROOT),
    ),
    'settings.php' => array(
      'source' => 'sites/g',
      'dest' => sprintf('%s/sites/g', DRUPAL_ROOT),
    ),
    'sites.inc' => array(
      'source' => 'sites/g',
      'dest' => sprintf('%s/sites/g', DRUPAL_ROOT),
    ),
  );

}
