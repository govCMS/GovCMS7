<?php

/**
 * @file
 * Creates a config object using our custom INI file.
 */

namespace Acquia\Acsf;

class AcsfConfigDefault extends AcsfConfig {

  /**
   * Keep the values from the config file in a shared static cache.
   *
   * @var stdClass.
   */
  protected static $cacheDefault;

  /**
   * Implements AcsfConfig::loadConfig().
   */
  protected function loadConfig() {
    // If the cache is empty, we haven't loaded the config file yet.
    if (empty(self::$cacheDefault)) {
      self::$cacheDefault = new \stdClass();
      $this->loadIniFile();
    }

    $this->url = self::$cacheDefault->url;
    $this->username = self::$cacheDefault->username;
    $this->password = self::$cacheDefault->password;
    $this->urlSuffix = self::$cacheDefault->urlSuffix;
    $this->sourceUrl = self::$cacheDefault->sourceUrl;
  }

  /**
   * Implements AcsfConfig::loadConfig().
   *
   * The cred file location will match the directory structure of an AH site:
   * /mnt/www/html/[site].[env]/docroot will have a credential file at
   * /mnt/files/[site].[env]/nobackup/sf_shared_creds.ini, using normal INI
   * format:
   *
   * [gardener]
   * url = "http://gardener.[stage].acquia-sites.com"
   * username = "acquiagardensrpc"
   * password = "[password]"
   * url_suffix = "[stage].acquia-sites.com"
   *
   * @throws AcsfConfigMissingCredsException
   */
  protected function loadIniFile() {
    $ini_file = sprintf('/mnt/files/%s.%s/nobackup/sf_shared_creds.ini', $this->ahSite, $this->ahEnv);

    $acsf_shared_creds = parse_ini_file($ini_file, TRUE);

    if (empty($acsf_shared_creds['gardener'])) {
      throw new AcsfConfigMissingCredsException(sprintf('Shared credential file not found in /mnt/files/%s.%s/nobackup/.', $this->ahSite, $this->ahEnv));
    }

    // Set the cached values for subsequent usage.
    self::$cacheDefault->url = $acsf_shared_creds['gardener']['url'];
    self::$cacheDefault->username = $acsf_shared_creds['gardener']['username'];
    self::$cacheDefault->password = $acsf_shared_creds['gardener']['password'];
    if (isset($acsf_shared_creds['gardener']['url_suffix'])) {
      self::$cacheDefault->urlSuffix = $acsf_shared_creds['gardener']['url_suffix'];
    }
    else {
      self::$cacheDefault->urlSuffix = '';
    }
    if (isset($acsf_shared_creds['gardener']['source_url'])) {
      self::$cacheDefault->sourceUrl = $acsf_shared_creds['gardener']['source_url'];
    }
    else {
      self::$cacheDefault->sourceUrl = '';
    }
  }

}
