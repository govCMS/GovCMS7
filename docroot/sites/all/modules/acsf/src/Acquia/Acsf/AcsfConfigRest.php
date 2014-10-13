<?php

/**
 * @file
 * Creates a config object using our REST API keys.
 */

namespace Acquia\Acsf;

class AcsfConfigRest extends AcsfConfigDefault {

  /**
   * Implements AcsfConfig::loadConfig().
   */
  protected function loadConfig() {
    parent::loadConfig();
    $this->username = $GLOBALS['gardens_site_settings']['conf']['acsf_site_id'];
    $this->password = $GLOBALS['gardens_site_settings']['conf']['site_api_key'];
  }

}
