#!/usr/bin/env php
<?php

/**
 * @file
 * Scrubs a site after its database has been copied.
 */

if (empty($argv[3])) {
  echo "Error: Not enough arguments.\n";
  exit(1);
}

$site    = $argv[1]; // AH site group.
$env     = $argv[2]; // AH site env.
$db_role = $argv[3]; // Database name.

fwrite(STDERR, sprintf("Scrubbing site database: site: %s; env: %s; db_role: %s;\n", $site, $env, $db_role));

// Get a database connection.
require dirname(__FILE__) . '/../../acquia/db_connect.php';
$link = get_db($site, $env, $db_role);

// Get the site name from the database.
$result = database_query_result("SELECT value FROM acsf_variables WHERE name = 'acsf_site_info'");
$site_info = unserialize($result);
$site_name = $site_info['site_name'];
if (empty($site_name)) {
  error('Could not retrieve the site name from the database.');
}
fwrite(STDERR, "Site name: $site_name;\n");

// Get the location of acsf module from the system table.
$result = database_query_result("SELECT filename FROM system WHERE name = 'acsf' AND status = 1");
$acsf_dir = dirname($result);
if (empty($acsf_dir)) {
  error('Could not locate the ACSF module.');
}
$docroot = sprintf('/var/www/html/%s.%s/docroot', $site, $env);
$acsf_location = "$docroot/$acsf_dir";
fwrite(STDERR, "ACSF location: $acsf_location;\n");

mysql_close($link);

// Get the Factory creds using acsf-get-factory-creds.
$command = sprintf(
  'AH_SITE_GROUP=%1$s AH_SITE_ENVIRONMENT=%2$s drush5 @%1$s.%2$s -r %4$s -i %3$s acsf-get-factory-creds --pipe',
  escapeshellarg($site),
  escapeshellarg($env),
  escapeshellarg($acsf_location),
  escapeshellarg($docroot)
);
fwrite(STDERR, "Executing: $command;\n");
$creds = json_decode(trim(shell_exec($command)));

// Get the target URL suffix from the Factory.
$url_suffix = $creds->url_suffix;
if (empty($url_suffix)) {
  error('Could not retrieve Site Factory URL suffix.');
}

// Create a new standard domain name.
$new_domain = "$site_name.$url_suffix";

// Execute the scrub.
$command = sprintf(
  'drush5 @%s.%s -r /var/www/html/%s.%s/docroot -l %s -y acsf-site-scrub',
  escapeshellarg($site),
  escapeshellarg($env),
  escapeshellarg($site),
  escapeshellarg($env),
  escapeshellarg($new_domain)
);
fwrite(STDERR, "Executing: $command;\n");
$result = shell_exec($command);
print $result;

// @todo Exit with an error status code if scrubbing failed.

function database_query_result($query) {
  $result = mysql_query($query);
  if (!$result) {
    error('Query failed: ' . $query);
  }
  return mysql_result($result, 0);
}
