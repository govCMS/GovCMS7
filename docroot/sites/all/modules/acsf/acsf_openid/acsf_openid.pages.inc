<?php

/**
 * @file
 * Site Factory OpenID related pages.
 */

/**
 * Page callback: Process an OpenID authentication.
 *
 * Custom replacement for openid_authentication_page() to address some issues:
 *  - faster authentication,
 *  - allow invited users to register via OpenID when the site does not allow
 *    registrations,
 *  - allow content managers who has registered locally to be still be able to
 *    log in via OpenID.
 *
 * @see acsf_openid_menu_alter()
 * @see openid_authentication_page()
 */
function acsf_openid_authentication_page() {
  module_load_include('inc', 'openid');

  // We have hard coded claimed_id in $_SESSION to
  // http://specs.openid.net/auth/2.0/identifier_select so that a call to the
  // factory can tell us which OpenID to work with. At this point
  // open_id.claimed_id will be something like:
  // http://<factory domain>/user/<uid>/identity.
  //
  // This causes openid_complete() to run openid_discover() due to:
  // OpenID Authentication, section 11.2:
  // If the returned Claimed Identifier is different from the one sent
  // to the OpenID Provider, we need to do discovery on the returned
  // identififer to make sure that the provider is authorized to
  // respond on behalf of this.
  //
  // Only one provider is allowed - the factory, so as long as the request comes
  // from there, it is possible to bypass this check (which saves us 2 HTTP
  // requests and full page renders on the factory).
  if (!empty($_SESSION['openid'])) {
    $response = _openid_response();
    $factory_url = acsf_factory_url();
    if (isset($response['openid.claimed_id'])) {
      $factory_domain = parse_url($factory_url, PHP_URL_HOST);
      $openid_domain = parse_url($response['openid.claimed_id'], PHP_URL_HOST);
      if ($factory_domain && $openid_domain && $factory_domain == $openid_domain) {
        $_SESSION['openid']['claimed_id'] = $response['openid.claimed_id'];
      }
    }
  }

  $response = openid_complete();
  if ($response['status'] == 'success') {
    // If the site does not allow open registrations, temporarily allow them if
    // the user who is trying to register was invited by a site owner.
    acsf_openid_allow_open_user_registrations_if_user_was_invited($response);

    // Make sure email verification is turned off for the remainder of this
    // request. (We need it off for OpenID registrations, but the site may have
    // it on in general if local user logins are allowed.)
    $GLOBALS['conf']['user_email_verification'] = FALSE;

    // Need to allow content managers who create local accounts to be able to
    // still log in from the factory. Merge OpenID accounts with local accounts
    // if needed. Attempt to load the user based on the OpenID first.
    $identity = $response['openid.claimed_id'];
    $account_by_openid = user_external_load($identity);
    if (!isset($account_by_openid->uid)) {
      // If we did not find the user by OpenID, look the user up by email.
      $sreg_values = openid_extract_namespace($response, OPENID_NS_SREG, 'sreg');
      if (!empty($sreg_values['email'])) {
        $account_by_email = user_load_by_mail($sreg_values['email']);
        if ($account_by_email) {
          // If this user was found by email but not by OpenID, make sure the
          // account does not have another OpenID assigned (in case factory
          // email address changes that are not yet propagated). One account
          // should only have at most one OpenID (factory user) assigned in
          // the Site Factory.
          $user_already_has_openid = db_query("SELECT 1 FROM {authmap} WHERE module = 'openid' AND uid = :uid", array(':uid' => $account_by_email->uid))->fetchField();
          if (!$user_already_has_openid) {
            // If no OpenID is assigned to this user, then at this point we
            // should add the current OpenID.
            user_set_authmaps($account_by_email, array('authname_openid' => $identity));
          }
        }
      }
    }

    // Now perform the OpenID authentication.
    return openid_authentication($response);
  }
  else {
    drupal_set_message(t('Your login could not be completed successfully, due to an internal error. Try again later.'), 'error');

    module_load_include('inc', 'openid');
    $sreg_values = openid_extract_namespace($response, OPENID_NS_SREG, 'sreg');

    // Elaborate on why session data is missing.
    if (empty($_SESSION)) {
      if (empty($_COOKIE[session_name()])) {
        $message = 'Session cookie missing, no session data found.';
      }
      else {
        $message = 'Session cookie found, session was empty.';
      }
    }

    // We put this in syslog() directly since site owners don't need to see it.
    watchdog('acsf_openid', 'OpenID login failed: result: "@status"; user: @name (@mail); site: @url; openid: @openid; browser: @browser', array(
      '@status' => $response['status'] . (isset($message) ? ' ' . $message : ''),
      '@name' => $sreg_values['nickname'],
      '@mail' => $sreg_values['email'],
      '@url' => $GLOBALS['base_url'],
      '@openid' => $response['openid.claimed_id'],
      '@browser' => $_SERVER['HTTP_USER_AGENT'],
    ));

    drupal_goto();
  }
}

/**
 * Page callback: logs the current user out, and redirects to the home page.
 *
 * Override for user_logout(), because when users log out of a site, they need
 * to be logged out of the factory as well.
 *
 * Theoretically hook_user_logout() would allow us to set the destination GET
 * parameter to get the same result, but drupal_goto() would not accept an
 * external URL in GET for security reasons.
 *
 * @see user_logout()
 * @see acsf_openid_menu_alter()
 */
function acsf_openid_custom_user_logout() {
  global $user;

  // Save a copy of the account (before the logout happens and $user is
  // destroyed) so we can use it below.
  $account = $user;

  // COPIED code from user_logout(). Keep in sync as D7 changes.
  watchdog('user', 'Session closed for %name.', array('%name' => $user->name));
  module_invoke_all('user_logout', $user);
  // Destroy the current session, and reset $user to the anonymous user.
  session_destroy();

  // Customized code starts here. If the current user is registered with OpenID
  // then redirect to the factory logout path.
  $factory_url = acsf_factory_url();
  if (!empty($factory_url) && acsf_openid_registered_with_openid($account)) {
    $url_fragments = parse_url($GLOBALS['base_url']);
    $site_host = $url_fragments['host'];
    if (isset($url_fragments['port'])) {
      $site_host .= '/' . $url_fragments['port'];
    }
    drupal_goto($factory_url . '/sf-openid-logout/' . $site_host);
  }
  else {
    drupal_goto();
  }
}

/**
 * Page callback: shows user registration page.
 *
 * @see acsf_openid_menu_alter()
 */
function acsf_openid_user_register_page() {
  // If we are redirected to user/register in the middle of an OpenID
  // registration, it's because the programmatic submission of the registration
  // form failed (probably because there are profile fields that need to be
  // filled out). In that case, show the user a modified version of the form
  // that focuses on the profile fields and hides other distractions.
  if ($response = acsf_openid_user_registration_response()) {
    // If the site does not allow open registrations, temporarily allow them if
    // the user who is trying to register was invited by a site owner. This
    // allows the form below to be submitted successfully and the invited user
    // to be registered right away.
    acsf_openid_allow_open_user_registrations_if_user_was_invited($response);

    // Make sure email verification is turned off for the remainder of this
    // request. (We need it off for OpenID registrations, but the site may have
    // it on in general if local user logins are allowed.)
    $GLOBALS['conf']['user_email_verification'] = FALSE;

    // Set a custom page title. We use a different title depending on whether
    // we are inside or outside the overlay, since inside the overlay the user
    // is not "inside" the site yet so it makes sense to refer to it in the
    // third person, but outside the overlay it doesn't.
    if (module_exists('overlay') && variable_get('acsf_openid_overlay_for_registration', 1)) {
      drupal_set_title(t('The site %site-name wants to know more about you.', array('%site-name' => acsf_openid_site_name_or_domain())), PASS_THROUGH);
    }
    else {
      drupal_set_title(t('Complete your registration'));
    }

    // Remove breadcrumb.
    drupal_set_breadcrumb(array());

    // Clear messages from previous request. On submission in this request, the
    // error message will show proper, if fields are still not properly set.
    // This is to avoid the errors showing up from OpenID module trying to
    // submit this form in the previous request and failing (that is why we are
    // here at the first place).
    drupal_get_messages();

    $form = drupal_get_form('user_register_form');
    // Hide user name, password and OpenID URL info.
    $form['account']['#access'] = FALSE;
    $form['openid_display']['#access'] = FALSE;

    // Add CSS to make the page content look more like the pages from Factory.
    if (module_exists('overlay') && variable_get('acsf_openid_overlay_for_registration', 1)) {
      $form['#attached']['css'][] = drupal_get_path('module', 'acsf_openid') . '/acsf_openid.register.css';
    }

    return $form;
  }
  elseif (!acsf_openid_force_openid()) {
    // If we're not in the middle of an OpenID registration, display the normal
    // user registration page if local logins are allowed.
    return drupal_get_form('user_register_form');
  }
  else {
    // Display the centralized login message, if local logins are not allowed.
    return acsf_openid_login_message();
  }
}

/**
 * Page callback: starts OpenID login / registration process.
 *
 * Starts OpenID login /registration process on the site then redirect to
 * Factory.
 *
 * @see acsf_openid_menu()
 */
function acsf_openid_factory_login_page($user_operation = 'login') {
  // Initialized variables for extra OpenID information.
  $is_overlay = FALSE;

  // Allow initiating the login process both in and outside the overlay.
  $destination = isset($_GET['destination']) ? $_GET['destination'] : variable_get('site_frontpage', 'node');
  if (module_exists('overlay') && overlay_get_mode() == 'child') {
    if (!user_is_anonymous()) {
      // User left a tab open with login, but is already logged in via another
      // tab. Close the overlay now.
      acsf_openid_close_overlay('<front>');
      return '';
    }
    if (module_exists('overlay') && variable_get('acsf_openid_overlay_for_login', 1)) {
      $query = array(
        'render' => 'overlay',
        'destination' => $destination . '?render=overlay',
      );
      $is_overlay = TRUE;
    }
  }
  else {
    $query = array('destination' => $destination);
  }

  // Simplified copy of openid_begin() to avoid spending HTTP requests on OpenID
  // discovery. We hardwire the known details of the provider.
  module_load_include('inc', 'openid');

  // Use identifier_select, so the server tells us the identity, we don't know.
  $claimed_id = $identity = 'http://specs.openid.net/auth/2.0/identifier_select';
  $options = array(
    'absolute' => TRUE,
    'query' => $query,
  );
  // Allow other modules to tweak the OpenID return url's parameters, for
  // example ensuring that the return page will be themed as an overlay, or that
  // the return page will be served on https.
  $current_page = $_GET['q'];
  $factory_url = acsf_factory_url();
  drupal_alter('acsf_openid_factory_return_page_options', $options, $current_page);
  $return_to = url('openid/authenticate', $options);
  $service = array(
    'types' => array('http://specs.openid.net/auth/2.0/server', 'http://openid.net/srv/ax/1.0'),
    'uri' => $factory_url . '/openid/provider',
    // Pretend we got anonymous info from the server.
    'identity' => FALSE,
    'version' => 2,
  );

  // Store discovered information in the users' session so we don't have to
  // rediscover.
  $_SESSION['openid']['service'] = $service;
  $_SESSION['openid']['claimed_id'] = $claimed_id;
  // Store the login form values so we can pass them to user_exteral_login().
  $_SESSION['openid']['user_login_values'] = array();

  // If a math library is present, then create an association. This will
  // potentially do an HTTP request and store data in the local DB. Used to get
  // data to be able to sign the request for the provider.
  $assoc_handle = '';
  $math_library = _openid_get_math_library();
  if ('gmp' === $math_library || 'bcmath' === $math_library) {
    $assoc_handle = openid_association($service['uri']);
  }

  // Prepare our data to be sent.
  $request = openid_authentication_request($claimed_id, $identity, $return_to, $assoc_handle, $service);
  $request += array(
    'acsf_openid.is_overlay' => isset($options['query']['render']) && $options['query']['render'] == 'overlay',
    'acsf_openid.user_operation' => $user_operation,
  );

  // Output a mock HTML file with a self-submitting form to redirect the user.
  openid_redirect($service['uri'], $request);
}

/**
 * Page callback: provides HTTP GET based OpenID login endpoint.
 *
 * Awaits OpenID in GET 'openid' and attempts to start OpenID login with that,
 * finally redirecting the user to the 'node' page (unless a 'destination'
 * query string is already set).
 *
 * @see acsf_openid_menu()
 */
function acsf_openid_site_login_page() {
  if (user_is_anonymous()) {
    if (!empty($_GET['openid'])) {
      $factory_url = acsf_factory_url();
      $factory_host = parse_url($factory_url, PHP_URL_HOST);
      $openid_host = parse_url($_GET['openid'], PHP_URL_HOST);
      if (!$factory_host || !$openid_host || $factory_host !== $openid_host) {
        drupal_set_message(t('Invalid OpenID used for login. Only internal OpenIDs are supported.'), 'error');
      }
      else {
        $options = array(
          'absolute' => TRUE,
          'query' => array('destination' => isset($_REQUEST['destination']) ? $_REQUEST['destination'] : variable_get('site_frontpage', 'node')),
        );
        // Allow other modules to tweak the OpenID return url's parameters, for
        // example ensuring that the return page will be served on https.
        $current_page = $_GET['q'];
        drupal_alter('acsf_openid_factory_return_page_options', $options, $current_page);
        $return_to = url('openid/authenticate', $options);
        openid_begin($_GET['openid'], $return_to, array());
      }
      // openid_begin() should have ended with openid_redirect_http() or
      // openid_redirect() if it went well, both of which drupal_exit(), so
      // if we are here, the OpenID login did not go well and the user will
      // get a message about the invalid OpenID. Although they should not even
      // be aware we use OpenID, this should only ever happen if their domain
      // is bugged somehow, so we at least expose a tracable error message
      // instead of a whitescreen.
      drupal_goto();
    }
  }
  else {
    // User already logged in, just go to the front page.
    drupal_goto(variable_get('site_frontpage', 'node'));
  }
}

/**
 * Page callback: provides a user page when OpenID is forced.
 *
 * Direct to centralized login form.
 *
 * @see acsf_openid_menu_alter()
 */
function acsf_openid_user_page() {
  if ($GLOBALS['user']->uid) {
    menu_set_active_item('user/' . $GLOBALS['user']->uid);
    return menu_execute_active_handler(NULL, FALSE);
  }
  else {
    return acsf_openid_login_message();
  }
}

/**
 * Page callback: provides a centralized login page when OpenID is forced.
 *
 * Override of /user/login and /user/password (and sometimes /user/register).
 *
 * @see acsf_openid_menu_alter()
 */
function acsf_openid_login_message() {
  // This function may be called when an anonymous visitor loads the /user path,
  // and in that case we have to override the page title.
  $site = acsf_get_acsf_site();
  $factory_name = acsf_factory_name();

  drupal_set_title(t('Log in or sign up'));
  $links = acsf_openid_block_view('login');
  $build = array(
    'wrapper' => array(
      '#type' => 'container',
      '#attributes' => array(),
      'title' => array(
        '#markup' => t('This site is hosted on the !service_name_long service.', array('!service_name_long' => $factory_name)),
      ),
      'links' => array(
        '#markup' => ' ' . $links['content'],
      ),
    ),
  );
  return $build;
}

/**
 * Page callback: handles URL redirection back to the factory user pages.
 *
 * Emails on password request and registration use this to open the respective
 * pages through an overlay on the site.
 */
function acsf_openid_factory_redirection_page() {
  // Get all arguments to pass on to the factory.
  $args = func_get_args();
  $factory_url = acsf_factory_url();
  // Redirect to user URL on the factory with these arguments.
  drupal_goto($factory_url . '/user/' . implode('/', $args), array('query' => array('render' => 'overlay')));
}
