<?php

/**
 * @file
 * This file regenerates the APC cache from JSON sites data.
 *
 * @see https://confluence.acquia.com/x/kBre for usage instructions.
 */

$file = "/mnt/files/{$_ENV['AH_SITE_GROUP']}.{$_ENV['AH_SITE_ENVIRONMENT']}/files-private/sites.json";
if (!file_exists($file)) {
  syslog(LOG_ERR, sprintf('APC cache update could not be executed, as the JSON file [%s] is missing.', $file));
  header($_SERVER['SERVER_PROTOCOL'] . ' 404 Not Found');
  die('Missing sites file.');
}

// We also pass some info about the source file for minimal authentication.
$file_contents = file_get_contents($file);
$token = sha1($file_contents);
if (empty($_GET['token']) || $_GET['token'] !== $token) {
  syslog(LOG_ERR, sprintf('APC cache update verification parameter [%s] does not match actual data [%s].', $_GET['token'], $token));
  header($_SERVER['SERVER_PROTOCOL'] . ' 401 Unauthorized');
  die('Invalid.');
}

require_once dirname(__FILE__) . '/sites.inc';

if (!empty($_GET['domains'])) {
  $domains = explode(',', $_GET['domains']);
  gardens_site_data_refresh_domains($domains);
  syslog(LOG_INFO, sprintf('Updated APC cache for [%s].', $_GET['domains']));
}
else {
  gardens_site_data_refresh_all();
  syslog(LOG_INFO, 'Updated APC cache for all domains.');
}
