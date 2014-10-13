<?php

require_once __DIR__ . '/../vendor/autoload.php';

class AcsfMessageUnitTestFailure extends \Acquia\Acsf\AcsfMessage {

  /**
   * Implements AcsfMessage::sendMessage().
   */
  protected function sendMessage($url, $method, $endpoint, array $parameters, $username, $password) {
    return new AcsfMessageResponseUnitTest('unit.test.endpoint', 1, 'response body');
  }

}

