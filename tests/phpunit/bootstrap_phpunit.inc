<?php
/**
 * @file
 * Bootstrap Drupal for PHPUnit testing.
 */

$docroot = __DIR__ . '/../..';
print "Checking drupal dir :: " . $docroot . PHP_EOL;
if (!is_dir($docroot)) {
  echo "No drupal directory found in or above current working directory. Aborting. \n";
  exit(1);
}

$site = 'default';
if (isset($_SERVER['SITE'])) {
  $site = $_SERVER['SITE'];
}
$site_dir = $docroot . '/sites/' . $site;
if (!file_exists($site_dir . '/settings.php')) {
  echo "No configured site found. Aborting.\n";
  exit(1);
}

$_SERVER['HTTP_HOST'] = 'localhost';
$_SERVER['REMOTE_ADDR'] = '127.0.0.1';
$_SERVER['PHPUNIT'] = TRUE;
$_SERVER['PHPUNIT_BACKUP_FILE'] = tempnam('/tmp/', 'phpunit-backup');

define('DRUPAL_ROOT', $docroot);
echo "Running PHPunit tests with Site : " . $site_dir . PHP_EOL;
set_include_path($docroot . PATH_SEPARATOR . get_include_path());

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
