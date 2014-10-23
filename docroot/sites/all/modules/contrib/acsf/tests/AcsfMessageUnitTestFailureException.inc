<?php

require_once __DIR__ . '/../vendor/autoload.php';

class AcsfMessageUnitTestFailureException extends \Acquia\Acsf\AcsfMessage {

  /**
   * Implements AcsfMessage::sendMessage().
   */
  protected function sendMessage($url, $method, $endpoint, array $parameters, $username, $password) {
    throw new \Acquia\Acsf\AcsfMessageFailureException('error message');
  }

}

