<?php

/**
 * @file
 * Contains AcsfMessage.
 *
 * AcsfMessage defines a basic message interface between a Drupal site and the
 * Site Factory. It is composed of a AcsfConfig compatible object which defines
 * the location and credentials required to communicate with the Site Factory.
 * There is one abstract method, which client code must implement:
 * sendMessage(). This method is responsible for implementing the communication
 * and returning an AcsfResponse object. This ensures that the client code has
 * predictable input and output.
 *
 * Invocation is simple, the following shows a working example of communicating
 * via REST (using the AcsfMessageRest concrete class). Construction can be as
 * simple as providing a method, endpoint and parameters. Additional arguments
 * may be provided to customize the behavior - namely locating a special config
 * file or providing an anonymous callback function.
 *
 * $m = new AcsfMessageRest('GET', 'site-api/v1/sync/', array('site_id' => 406));
 * $m->send();
 * $m->getResponseCode();
 * $m->getResponseBody();
 */

namespace Acquia\Acsf;

abstract class AcsfMessage {

  // The message endpoint on the remote server.
  protected $endpoint;

  // An unstructured list of parameters to send with the request.
  protected $parameters;

  // The AcsfMessageResponse object.
  protected $response;

  // An optional Acquia Hosting sitegroup.
  protected $ahSite;

  // An optional Acquia Hosting environment.
  protected $ahEnv;

  // An optional AcsfConfig object.
  private $config;

  /**
   * Constructor.
   *
   * @param string $method
   *   The request method. e.g. POST, GET, PUT, etc.
   * @param string $endpoint
   *   The endpoint to contact on the remote server.
   * @param array $parameters
   *   The list of parameters to send with the request.
   * @param AcsfConfig $config
   *   (Optional) The configuration option.
   * @param string $ah_site
   *   (Optional) The Acquia Hosting sitegroup.
   * @param string $ah_env
   *   (Optional) The Acquia Hosting environment.
   * @param Closure $callback
   *   (Optional) An anonymous callback function.
   */
  public function __construct($method, $endpoint, array $parameters = NULL, AcsfConfig $config = NULL, $ah_site = NULL, $ah_env = NULL, Closure $callback = NULL) {

    // Use our default config if not specified.
    if (empty($config)) {
      $config = new AcsfConfigDefault($ah_site, $ah_env);
    }

    // Ensure that the config class is compatible.
    if (!is_subclass_of($config, '\Acquia\Acsf\AcsfConfig')) {
      throw new AcsfMessageMissingCredsException('The config argument must contain an AcsfConfig compatible class file.');
    }

    $this->config = $config;
    $this->method = $method;
    $this->endpoint = $endpoint;
    $this->parameters = $parameters;
    $this->ahSite = $ah_site;
    $this->ahEnv = $ah_env;
    $this->callback = $callback;
  }

  /**
   * Sends the message to the remote server.
   */
  public function send() {
    if (function_exists('is_acquia_host') && !is_acquia_host()) {
      return;
    }

    $this->response = $this->sendMessage($this->config->getUrl(), $this->method, $this->endpoint, $this->parameters, $this->config->getUsername(), $this->config->getPassword());

    // Don't allow empty responses.
    if (empty($this->response)) {
      throw new AcsfMessageEmptyResponseException(sprintf('The message to %s resulted in an empty response.', $this->endpoint));
    }

    // Only allow AcsfMessageResponse compatible responses.
    if (!is_subclass_of($this->response, '\Acquia\Acsf\AcsfMessageResponse')) {
      throw new AcsfMessageMalformedResponseException(sprintf('The message to %s resulted in a malformed response. It should be an AcsfMessageResponse object.', $this->endpoint));
    }

    // If the response failed, throw an exception.
    if ($this->response->failed()) {
      // The REST API returns error descriptions in the "message" field of the
      // response body.
      if (!empty($this->response->body['message'])) {
        $error_message = sprintf('The request to %s failed with HTTP error: %s %s.', $this->endpoint, $this->response->code, $this->response->body['message']);
      }
      else {
        $error_message = sprintf('The request to %s failed.', $this->endpoint);
      }
      throw new AcsfMessageFailedResponseException($error_message);
    }

    // Allow the implementer to respond right away.
    $this->receiveResponse($this->response);

    // Allow an anonymous callback.
    if (!empty($this->callback)) {
      try {
        $callback = $this->callback;
        $callback($this->response);
      }
      catch (\Exception $e) {
        // @todo log here?
      }
    }
  }

  /**
   * Allows client code to optionally run logic after the response is received.
   */
  protected function receiveResponse(AcsfMessageResponse $response) {

  }

  /**
   * Retrieves the response body.
   */
  public function getResponseBody() {
    if (empty($this->response)) {
      return FALSE;
    }
    return $this->response->body;
  }

  /**
   * Retrieves the response code.
   */
  public function getResponseCode() {
    if (empty($this->response)) {
      return FALSE;
    }
    return $this->response->code;
  }

  /**
   * Sends a message to a remote server and implements a response object.
   *
   * @param string $url
   *   The URL of the remote service.
   * @param string $method
   *   The request method. e.g. POST, GET, PUT, etc.
   * @param string $endpoint
   *   The endpoint to call on the remote service.
   * @param array $parameters
   *   Parameters to send with the request.
   * @param string $username
   *   The remote username.
   * @param string $password
   *   The remote password.
   *
   * @return AcsfMessageResponse
   *   The message response instance.
   */
  abstract protected function sendMessage($url, $method, $endpoint, array $parameters, $username, $password);

}
