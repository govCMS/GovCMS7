<?php
/**
 * @file
 * MockCurlService.php
 *
 * Wraps up and mocks out the Curl Service.
 */

namespace tdd7\testframework\mocks;

/**
 * Class MockCurlService
 *
 * @package tdd7\services
 */
class MockCurlService {
  public $url = NULL;

  /**
   * Wrapper for curl_init.
   *
   * @param string $url
   *   The url to init to.
   */
  public function init($url) {
    $this->url = $url;
    $this->options[CURLOPT_URL] = $url;
  }

  public $options = array();

  /**
   * Wrapper for curl_setopt.
   *
   * @param resource $curl_object
   *   The curl object to operate on.
   * @param int $opt
   *   The curl option to set.
   * @param mixed $val
   *   The value of the option.
   */
  public function setopt($curl_object, $opt, $val) {
    $this->options[$opt] = $val;
  }

  public $exec_return = NULL;

  /**
   * Wrapper for curl_exec.
   *
   * @param resource $curl_object
   *   The curl object to operate on.
   *
   * @return string|mixed
   *   The results of the operation.
   */
  public function exec($curl_object) {
    return $this->exec_return;
  }

  public $return_http_code = 200;

  /**
   * Wrapper for curl_getinfo.
   *
   * @param resource $curl_object
   *   The curl object to operate on.
   *
   * @return array
   *   An array of curl info.
   */
  public function getinfo($curl_object) {
    return array("http_code" => $this->return_http_code);
  }
}
