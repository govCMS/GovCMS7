<?php

require_once __DIR__ . '/../vendor/autoload.php';

class AcsfConfigUnitTestMissingUsername extends \Acquia\Acsf\AcsfConfig {

  /**
   * Implements AcsfConfig::loadConfig().
   */
  protected function loadConfig() {
    $this->url = 'http://gardener.unit.test';
    $this->password = 'Un1tT35t';
  }

}

