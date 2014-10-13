<?php

/**
 * @file
 * Provides drush commands for theme change notifications.
 */

/**
 * Implements hook_drush_command().
 */
function acsf_theme_drush_command() {
  return array(
    'acsf-theme-notify' => array(
      'description' => dt('Sends a notification to the Factory that a theme event has occurred.'),
      'arguments' => array(
        'scope' => dt('The scope of the repository to send a notification for. Possible values are "theme", "site", "group", or "global".'),
      ),
      'options' => array(
        'event' => dt('The type of theme event to notify the Factory about. Possible values are "create", "modify", or "delete". Defaults to "modify".'),
        'theme' => dt('The system name of the theme the event relates to. Only relevant for "theme" scope notifications.'),
        'nid' => dt('The node ID of the entity on the Factory the theme change is associated with. The node ID for "site" and "theme" scope notifications is automatically derived from the current site. Explicitly passing the --nid option for "site" and "theme" notifications overrides the one from the current site and should match the site node ID on the Factory. For "group" scope notifications, the nid cannot be automatically derived and is therefore required.'),
      ),
    ),
  );
}

/**
 * Command callback: Sends a theme change notification to the Factory.
 */
function drush_acsf_theme_notify($scope) {
  $event = drush_get_option('event', 'modify');
  $nid = drush_get_option('nid');
  $theme = drush_get_option('theme');

  // Do most of the validation locally to avoid depending on the validation at
  // the endpoint.
  if (empty($scope)) {
    return drush_set_error(dt('The scope argument is required. Possible values are "theme", "site", "group", or "global".'));
  }
  if (!in_array($scope, array('theme', 'site', 'group', 'global'))) {
    return drush_set_error(dt('The scope argument must be either "theme", "site", "group", or "global".'));
  }
  if (!in_array($event, array('create', 'modify', 'delete'))) {
    return drush_set_error(dt('Event type not supported. Possible values are "create", "modify", or "delete".'));
  }
  if ($scope === 'theme' && empty($theme)) {
    return drush_set_error(dt('The --theme option must be passed for "theme" scope notifications.'));
  }
  if ($scope === 'group' && empty($nid)) {
    return drush_set_error(dt('The --nid option must be passed for "group" scope notifications.'));
  }

  $response = acsf_theme_notification()->sendNotification($scope, $event, $nid, $theme, NULL, FALSE);
  // AcsfMessageRest always returns a 500 error code if there was a problem
  // calling the REST API.
  if ($response['code'] === 500) {
    drush_log($response['data']['message'], 'error');
  }
  else {
    drush_log($response['data']['message'], 'success');
  }
}
