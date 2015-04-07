<?php

/**
 * @file
 * Prints a drush-compatible uri, given a site, env and db_role.
 */

$site = $argv[1];
$env = $argv[2];
$db_role = $argv[3];

// Get the db connection.
require dirname(__FILE__) . '/../acquia/db_connect.php';
$link = get_db($site, $env, $db_role);

// Get the site name from the database.
$result = mysql_query('SELECT value FROM acsf_variables WHERE name = "acsf_site_data"');
$value = mysql_result($result, 0);
mysql_close($link);
$site_data = unserialize($value);
$standard_domain = $site_data['standard_domain'];

echo "$standard_domain";
