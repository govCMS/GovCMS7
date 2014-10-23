<?php

/**
 * @file
 * This simple interface defines the way that responses are constructed.
 */

namespace Acquia\Acsf;

abstract class AcsfMessageResponse {

  // The endpoint on the remote service.
  public $endpoint;

  // The response code from the remote call.
  public $code;

  // The body of the response.
  public $body;

  /**
   * Constructor.
   *
   * @param string $endpoint
   *   The endpoint on the remote service.
   * @param mixed $code
   *   The response code from the remote call.
   * @param mixed $body
   *   The body of the response.
   */
  public function __construct($endpoint, $code, $body) {
    if (empty($endpoint) || $code === NULL || $body === NULL) {
      throw new AcsfMessageMalformedResponseException('A response must contain an endpoint, a return code and a response body.');
    }

    $this->endpoint = $endpoint;
    $this->code = $code;
    $this->body = $body;
  }

  /**
   * Defines whether or not the call failed.
   *
   * Client code needs to analyze the response and determine failure.
   */
  abstract public function failed();
}
