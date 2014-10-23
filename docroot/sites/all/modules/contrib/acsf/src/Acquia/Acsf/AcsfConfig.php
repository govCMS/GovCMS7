<?php

/**
 * @file
 * Provides an interface to define how our message configuration should work.
 */

namespace Acquia\Acsf;

abstract class AcsfConfig {

  // The URL of the remote service.
  protected $url;

  // The username of the remote service.
  protected $username;

  // The password of the remote service.
  protected $password;

  // The signup suffix of the Factory.
  protected $urlSuffix;

  // The source URL of the Factory this was staged from.
  protected $sourceUrl;

  // An optional Acquia Hosting sitegroup.
  protected $ahSite;

  // An optional Acquia Hosting environment.
  protected $ahEnv;

  /**
   * Constructor.
   *
   * @param string $ah_site
   *   (Optional) Acquia Hosting sitegroup.
   * @param string $ah_env
   *   (Optional) Acquia Hosting environment.
   *
   * @throws AcsfConfigIncompleteException
   */
  public function __construct($ah_site = NULL, $ah_env = NULL) {
    if (function_exists('is_acquia_host') && !is_acquia_host()) {
      return;
    }

    // If none specified, pick the site group and environment from $_ENV.
    if (empty($ah_site)) {
      $ah_site = $_ENV['AH_SITE_GROUP'];
    }
    if (empty($ah_env)) {
      $ah_env = $_ENV['AH_SITE_ENVIRONMENT'];
    }

    $this->ahSite = $ah_site;
    $this->ahEnv = $ah_env;
    $this->loadConfig();

    // Require the loadConfig implementation to set required values.
    foreach (array('url', 'username', 'password') as $key) {
      if (empty($this->{$key})) {
        throw new AcsfConfigIncompleteException(sprintf('The ACSF configuration was incomplete, no value was found for %s.', $key));
      }
    }
  }

  /**
   * Retrieves the config username.
   */
  public function getUsername() {
    return $this->username;
  }

  /**
   * Retrieves the config password.
   */
  public function getPassword() {
    return $this->password;
  }

  /**
   * Retrieves the config URL.
   */
  public function getUrl() {
    return $this->url;
  }

  /**
   * Retrieves the config URL suffix.
   */
  public function getUrlSuffix() {
    return $this->urlSuffix;
  }

  /**
   * Retrieves the source URL.
   */
  public function getSourceUrl() {
    return $this->sourceUrl;
  }

  /**
   * Loads the configuration.
   *
   * Client code MUST populate the url, username and password properties.
   */
  abstract protected function loadConfig();

}
