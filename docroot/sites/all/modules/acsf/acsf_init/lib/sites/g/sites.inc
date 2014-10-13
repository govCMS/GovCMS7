<?php

/**
 * @file
 * Configuration file for Drupal's multi-site directory aliasing feature.
 */

// Bail out if we're not on an Acquia server.
if (function_exists('is_acquia_host') && !is_acquia_host()) {
  return;
}

// Make sure to use require_once() so this file is never loaded more than
// once per page.
define('GARDENS_SITE_DATA_USE_APC', (get_cfg_var('gardens.disable_apc_for_sites_php') != 1));
// TTL set to 30 minutes to allow a cron to run full refreshes.
define('GARDENS_SITE_DATA_TTL', 1800);

// Populate $_ENV if we are running cli.
if ((!isset($_ENV['AH_SITE_NAME']) || !isset($_ENV['AH_SITE_GROUP']) || !isset($_ENV['AH_SITE_ENVIRONMENT'])) && file_exists('/var/www/site-scripts/site-info.php')) {
  require_once '/var/www/site-scripts/site-info.php';
  list($name, $group, $stage, $secret) = ah_site_info();
  if (!isset($_ENV['AH_SITE_NAME'])) {
    $_ENV['AH_SITE_NAME'] = $name;
  }
  if (!isset($_ENV['AH_SITE_GROUP'])) {
    $_ENV['AH_SITE_GROUP'] = $group;
  }
  if (!isset($_ENV['AH_SITE_ENVIRONMENT'])) {
    $_ENV['AH_SITE_ENVIRONMENT'] = $stage;
  }
}

/**
 * Returns the sites data structure.
 *
 * @return bool|mixed
 *   An array of sites data on success, or FALSE on failure to load or parse the
 *   file.
 */
function gardens_site_data_load_file() {
  $json = @file_get_contents(gardens_site_data_get_filepath());
  if ($json) {
    // Get the map as arrays.
    return json_decode($json, TRUE);
  }
  return FALSE;
}

/**
 * Returns the location of the sites data json file.
 *
 * We rely on the existence of the files-private directory that's created in
 * /mnt/files next to the public files directory.
 *
 * @return string
 *   The json file location.
 */
function gardens_site_data_get_filepath() {
  // Use the "real" path here rather than the canonical hosting path
  // to minimize symlink traversal.
  return "/mnt/files/{$_ENV['AH_SITE_GROUP']}.{$_ENV['AH_SITE_ENVIRONMENT']}/files-private/sites.json";
}

/**
 * Fully refreshes the APC cached site/domain data, rewriting every key.
 */
function gardens_site_data_refresh_all() {
  if ($map = gardens_site_data_load_file()) {
    foreach ($map['sites'] as $domain => $site) {
      $data = gardens_site_data_build_data($site, $map);
      gardens_site_data_cache_set($domain, $data);
    }
  }
}

/**
 * Returns the data structure for a single site.
 *
 * @param array $site
 *   An array of information about a specific site, containing keys including
 *   'conf', 'flags', 'name' etc.
 * @param array $map
 *   An array containing global information that applies to all sites (site,
 *   env, memcache_inc).
 *
 * @return array
 *   A data structure containing information about a single site.
 */
function gardens_site_data_build_data(array $site, array $map) {
  // All sites use a conventional public file path.
  $db_name = $site['conf']['acsf_db_name'];
  $site['conf']['file_public_path'] = 'sites/g/files/' . $db_name . '/f';

  return array(
    'dir' => "g/files/{$site['name']}",
    // Put some settings into a global used in settings.php.
    'gardens_site_settings' => array(
      'site' => $map['cloud']['site'],
      'env' => $map['cloud']['env'],
      'memcache_inc' => !empty($map["memcache_inc"]) ? $map["memcache_inc"] : '',
      'flags' => !empty($site['flags']) ? $site['flags'] : array(),
      'conf' => !empty($site['conf']) ? $site['conf'] : array(),
    ),
  );
}

/**
 * Parses the entire JSON sites file and returns a result for a single domain.
 *
 * @param string $domain
 *   A domain name to search for in the JSON.
 *
 * @return array
 *   A gardens site data structure, or zero if the domain was not found.
 */
function gardens_site_data_get_site_from_file($domain) {
  $map = gardens_site_data_load_file();
  if (!empty($map['sites'][$domain])) {
    return gardens_site_data_build_data($map['sites'][$domain], $map);
  }
  else {
    return 0;
  }
}

/**
 * Returns data for a single domain directly from the JSON file.
 *
 * Optionally also stores the data in APC.
 *
 * @param string $domain
 *   The domain name to look up in the JSON file.
 *
 * @return array|int
 *   An array of site data, or 0 if no site was found for the given domain.
 */
function gardens_site_data_refresh_one($domain) {
  $data = gardens_site_data_refresh_domains(array($domain));
  return $data[$domain];
}

/**
 * Returns data for the specified domains directly from the JSON file.
 *
 * Optionally also stores the data in APC.
 *
 * @param array $domains
 *   The domain names to look up in the JSON file.
 *
 * @return array
 *   An array keyed by the specified domains, whose values are site data arrays
 *   or 0 if no site was found for the given domain.
 */
function gardens_site_data_refresh_domains(array $domains) {
  $location = gardens_site_data_get_filepath();
  $data = array();
  foreach ($domains as $domain) {
    // Shell out to grep to find the relevant line of the json file.
    $result = shell_exec(sprintf("grep %s %s --no-filename --color=never --context=0", escapeshellarg($domain), escapeshellarg($location)));

    if (empty($result)) {
      // Log an explicit fail in APC if we cannot find the domain, so that we
      // can take advantage of APC caching the "fail" also. To do this, cache an
      // integer literal zero for any failed domain.
      $data[$domain] = 0;
    }
    else {
      // $result is in the form of
      // "example.com": {"name": "g123", "flags": {}},
      // (with or without the trailing comma).
      $matches = array();
      $pattern = '@^\s*"' . preg_quote($domain, '@') . '": ({.+}),?$@';
      if (preg_match($pattern, trim($result), $matches)) {
        $found_site = json_decode($matches[1], TRUE);
      }

      // Retrieve the first line of the JSON file, which contains the global
      // site settings data.
      $f = fopen($location, 'r');
      $json = fgets($f);
      fclose($f);
      $json = rtrim($json, ",\n");
      $json .= "}";
      $global_map_data = json_decode($json, TRUE);

      if (empty($found_site) || empty($global_map_data)) {
        // This will happen if the domain appears in the JSON file, but the
        // format of the file has changed such that the grep-based single-line
        // parsing no longer works.
        // TODO: Log the error in such a way that it will squawk loudly.
        $map = gardens_site_data_load_file();
        $data[$domain] = gardens_site_data_build_data($map['sites'][$domain], $map);
      }
      else {
        $data[$domain] = gardens_site_data_build_data($found_site, $global_map_data);
      }
    }
    // Update the current record in place *if* we are using APC.
    if (GARDENS_SITE_DATA_USE_APC) {
      gardens_site_data_cache_set($domain, $data[$domain]);
    }
  }
  return $data;
}

/**
 * Stores site info for a given domain in APC.
 *
 * @param string $domain
 *   The domain name used in the cache key to store.
 * @param mixed $data
 *   An array of data about the site/domain containing keys 'dir' and
 *   'gardens_site_settings'. If the domain was not found in the sites.json then
 *   a scalar 0.
 */
function gardens_site_data_cache_set($domain, $data) {
  if (function_exists('apc_store')) {
    $domain_key = "gardens_domain:$domain";
    apc_store($domain_key, $data, GARDENS_SITE_DATA_TTL);
  }
}

/**
 * Retrieves cached site info from APC for a given domain.
 *
 * @return mixed
 *   An object containing information about the site on success, or FALSE if no
 *   cached data was found for the domain.
 */
function gardens_site_data_cache_get($domain) {
  if (function_exists('apc_fetch')) {
    $domain_key = "gardens_domain:$domain";
    return apc_fetch($domain_key);
  }
}
