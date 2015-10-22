<?php

/**
 * @file
 * Custom prepend file for PHP unserver for govCMS. Used to provide Drupal
 * with the correct information when Drush cannot be used.
 *
 * @TODO Remove and reimplement when the upstream Drush bug is fixed in
 * https://github.com/drush-ops/drush/pull/1699
 */

/**
 * Determine the URI to use for this server.
 */
function runserver_uri($uri) {
  $drush_default = array(
    'host' => '127.0.0.1',
    'port' => '8888',
    'path' => '',
  );
  $uri = runserver_parse_uri($uri);
  if (is_array($uri)) {
    // Populate defaults.
    $uri = $uri + $drush_default;
    if (ltrim($uri['path'], '/') == '-') {
      // Allow a path of a single hyphen to clear a default path.
      $uri['path'] = '';
    }
    // Determine and set the new URI.
    $uri['addr'] = $uri['host'];
  }
  return $uri;
}

/**
 * Parse a URI or partial URI (including just a port, host IP or path).
 *
 * @param string $uri
 *   String that can contain partial URI.
 *
 * @return array
 *   URI array as returned by parse_url.
 */
function runserver_parse_uri($uri) {
  if (empty($uri)) {
    return array();
  }
  if ($uri[0] == ':') {
    // ':port/path' shorthand, insert a placeholder hostname to allow parsing.
    $uri = 'placeholder-hostname' . $uri;
  }
  // FILTER_VALIDATE_IP expects '[' and ']' to be removed from IPv6 addresses.
  // We check for colon from the right, since IPv6 addresses contain colons.
  $to_path = trim(substr($uri, 0, strpos($uri, '/')), '[]');
  $to_port = trim(substr($uri, 0, strrpos($uri, ':')), '[]');
  if (filter_var(trim($uri, '[]'), FILTER_VALIDATE_IP) || filter_var($to_path, FILTER_VALIDATE_IP) || filter_var($to_port, FILTER_VALIDATE_IP)) {
    // 'IP', 'IP/path' or 'IP:port' shorthand, insert a schema to allow parsing.
    $uri = 'http://' . $uri;
  }
  $uri = parse_url($uri);
  if (empty($uri)) {
    return drush_set_error('RUNSERVER_INVALID_ADDRPORT', dt('Invalid argument - should be in the "host:port/path" format, numeric (port only) or non-numeric (path only).'));
  }
  if (count($uri) == 1 && isset($uri['path'])) {
    if (is_numeric($uri['path'])) {
      // Port only shorthand.
      $uri['port'] = $uri['path'];
      unset($uri['path']);
    }
  }
  if (isset($uri['host']) && $uri['host'] == 'placeholder-hostname') {
    unset($uri['host']);
  }
  return $uri;
}

// Override the default PHP server handling for routed paths with periods in.
$url = parse_url($_SERVER["REQUEST_URI"]);
if (file_exists('.' . $url['path'])) {
  // Serve the requested resource as-is.
  return FALSE;
}

// Populate the "q" query key with the path, skip the leading slash.
$_GET['q'] = $_REQUEST['q'] = substr($url['path'], 1);

// We set the base_url so that Drupal generates correct URLs for runserver
// (e.g. http://127.0.0.1:8888/...), but can still select and serve a specific
// site in a multisite configuration (e.g. http://mysite.com/...).
$uri = runserver_uri($_SERVER["REQUEST_URI"]);

// Remove any leading slashes from the path, since that is what url() expects.
$path = ltrim($uri['path'], '/');

// $uri['addr'] is a special field set by runserver_uri()
$hostname = $uri['host'];
$addr = $uri['addr'];

// We set the effective base_url, since we have now detected the current site,
// and need to ensure generated URLs point to our runserver host.
// We also pass in the effective base_url to our auto_prepend_script via the
// CGI environment. This allows Drupal to generate working URLs to this http
// server, whilst finding the correct multisite from the HTTP_HOST header.
$base_url = 'http://' . $addr . ':' . $uri['port'];
$env['RUNSERVER_BASE_URL'] = $base_url;

// Include the main index.php and let core take over.
chdir(dirname(dirname(dirname(dirname(__FILE__)))) . '/docroot');
include 'index.php';
