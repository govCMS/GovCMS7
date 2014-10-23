<?php

require_once __DIR__ . '/../vendor/autoload.php';

class AcsfMessageUnitTestSuccess extends \Acquia\Acsf\AcsfMessage {

  /**
   * Implements AcsfMessage::sendMessage().
   */
  protected function sendMessage($url, $method, $endpoint, array $parameters, $username, $password) {
    $response = json_encode(array(
      'url' => $url,
      'method' => $method,
      'endpoint' => $endpoint,
      'parameters' => $parameters,
      'username' => $username,
      'password' => $password,
    ));
    return new AcsfMessageResponseUnitTest($endpoint, 0, $response);
  }

}

