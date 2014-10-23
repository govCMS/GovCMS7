<?php

require_once __DIR__ . '/../vendor/autoload.php';

class AcsfMessageResponseUnitTest extends \Acquia\Acsf\AcsfMessageResponse {

  public function failed() {
    if ($this->code) {
      return TRUE;
    }
    return FALSE;
  }

}

