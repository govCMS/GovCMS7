#!/usr/bin/php
<?php

/**
 * @file
 * This script is responsible for deploying theme files on each webnode.
 *
 * When a webnode is launched, this script is called by Acquia Hosting with
 * the sitegroup name and environment name as arguments.
 *
 * If the themes are already deployed on this webnode, this script exits
 * as quickly as possible.
 *
 * Otherwise, this script sends a request to the Site Factory indicating which
 * webnode needs a theme deployment and then monitors that Wip task until it
 * has completed.
 *
 * If theme deployment fails, we will retry a number of times before giving
 * up.
 *
 * If a webnode is launched while Wip is paused, this script will effectively
 * hang indefinitely.  This is probably the correct behavior because the new
 * webnode cannot correctly respond to web requests until the theme files have
 * been deployed.
 *
 * If VCS theming has not been configured for the specified sitegroup, the
 * Site Factory will not start a task.
 */

/**
 * Constant for the Site Factory WIP task status for completion without error.
 */
define('WIP_STATUS_COMPLETED', 16);

global $argv, $argc;
main($argv, $argc);

/**
 * The entry point into the script.
 *
 * Determines whether there are theme files, and request them from the Site
 * Factory if needed.
 *
 * @param string $argv
 *   The command line arguments.
 * @param int $argc
 *   The number of command line arguments.
 */
function main($argv, $argc) {
  if ($argc < 3) {
    printf("Must provide the sitegroup name and environment name.\n");
    exit(1);
  }
  $site = $argv[1];
  $env = $argv[2];
  $verbose = FALSE;
  if (in_array('-v', $argv) || in_array('--verbose', $argv)) {
    $verbose = TRUE;
  }
  $force = FALSE;
  if (in_array('-f', $argv) || in_array('--force', $argv)) {
    $force = TRUE;
  }
  $deployed = has_theme_files($site, $env);
  if ($force || !$deployed) {
    $webnode = gethostname();
    if ($verbose) {
      if (!$deployed) {
        printf("Theme files have not been deployed on %s for %s.%s\n", $webnode, $site, $env);
      }
      else {
        printf("Forcing theme deployment on %s for %s.%s\n", $webnode, $site, $env);
      }
    }

    // Assume we will fail until proven otherwise.
    $success = FALSE;
    // Send Site Factory request.
    $attempts = 3;
    do {
      $response = request_theme_files($site, $env, $webnode);
      if ($verbose) {
        printf("Sent request to the Site Factory for themes: %s\n", print_r($response, TRUE));
      }
      // Poll waiting for theme deployment.
      if ($response->code == 200) {
        $task_id = $response->body['task_id'];
        if ($task_id == 'NA') {
          printf("VCS theming is not configured for %s.%s\n", $site, $env);
          exit;
        }

        // Wait here until the themes are deployed.
        do {
          sleep(10);
          $task_info = get_wip_task_status($site, $env, $task_id);
          $task = $task_info->body['wip_task'];
          if ($verbose) {
            printf("Wip task status: %s\n", print_r($task, TRUE));
          }
        } while ($task['status'] < WIP_STATUS_COMPLETED);

        // Note: STATUS_WARNING is 144, which has the 16 (STATUS_COMPLETED) bit
        // set, so checking against 16 will be true for both completed, and
        // warning.
        if ($task['status'] & WIP_STATUS_COMPLETED) {
          $success = TRUE;
          break;
        }
      }
    } while ($attempts-- > 0);

    if (!$success) {
      // Failed to deploy the theme files.
      printf("Failed to deploy theme files to %s for %s.%s\n", $webnode, $site, $env);
      exit(1);
    }
  }
}

/**
 * Indicates whether theme files have been deployed.
 *
 * @param string $site
 *   The sitegroup name.
 * @param string $env
 *   The environment name.
 *
 * @return bool
 *   TRUE if this webnode has theme files; FALSE otherwise.
 */
function has_theme_files($site, $env) {
  $result = FALSE;
  $path = get_theme_directory($site, $env);
  if (file_exists($path) && is_dir($path)) {
    $result = TRUE;
  }
  return $result;
}

/**
 * Returns the shared credentials.
 *
 * @param string $site
 *   The hosting sitegroup name.
 * @param string $env
 *   The hosting environment name.
 *
 * @return SimpleRestCreds
 *   The credentials.
 *
 * @throws Exception
 *   If the credentials cannot be read for any reason.
 */
function get_shared_creds($site, $env) {
  $path = sprintf('/mnt/files/%s.%s/nobackup', $site, $env);
  $shared = sprintf('%s/sf_shared_creds.ini', $path);
  if (file_exists($shared)) {
    $data = parse_ini_file($shared, TRUE);
    if (!empty($data) && !empty($data['gardener'])) {
      return new SimpleRestCreds($data['gardener']['username'],
        $data['gardener']['password'],
        $data['gardener']['url']);
    }
  }
  throw new Exception(sprintf('Unable to read credentials from %s', $shared));
}

/**
 * Returns the path to the theme repository.
 *
 * @param string $site
 *   The sitegroup name.
 * @param string $env
 *   The environment name.
 *
 * @return string
 *   The theme repo path.
 */
function get_theme_directory($site, $env) {
  return sprintf('/mnt/tmp/%s.%s/theme_repo/live/', $site, $env);
}

/**
 * Sends the request to deploy themes on the specified webnode.
 *
 * @param string $site
 *   The hosting site group name.
 * @param string $env
 *   The hosting environment name.
 * @param string $webnode
 *   The fully qualified webnode name.
 *
 * @return SimpleRestResponse
 *   The response.
 */
function request_theme_files($site, $env, $webnode) {
  $endpoint = 'site-api/v1/theme/deploy';
  try {
    $parameters = array(
      'sitegroup' => $site,
      'webnode' => $webnode,
    );
    $creds = get_shared_creds($site, $env);
    $message = new SimpleRestMessage($site, $env);
    $response = $message->send('POST', $endpoint, $parameters, $creds);
  }
  catch (Exception $e) {
    $error_message = sprintf('Theme deploy failed with error: %s', $e->getMessage());
    syslog(LOG_ERR, $error_message);
    $response = new SimpleRestResponse($endpoint, 500, array('message' => $error_message));
  }
  return $response;
}

/**
 * Requests status of a particular wip task.
 *
 * @param string $site
 *   The hosting site group name.
 * @param string $env
 *   The hosting environment name.
 * @param int $task_id
 *   The Wip task id.
 *
 * @return SimpleRestResponse
 *   The response.
 */
function get_wip_task_status($site, $env, $task_id) {
  $endpoint = sprintf('site-api/v1/wip/task/%s/status', $task_id);
  try {
    $parameters = array();
    $creds = get_shared_creds($site, $env);
    $message = new SimpleRestMessage($site, $env);
    $response = $message->send('GET', $endpoint, $parameters, $creds);
  }
  catch (Exception $e) {
    $error_message = sprintf('Wip task status failed with error: %s', $e->getMessage());
    $file = __FILE__;
    syslog(LOG_ERR, "Error in cloud hook pre-web-activate/$file: $error_message");
    $response = new SimpleRestResponse($endpoint, 500, array('message' => $error_message));
  }
  return $response;
}

/**
 * Class SimpleRestCreds.
 *
 * Contains the REST credentials that will be used when making Site Factory
 * requests.
 */
class SimpleRestCreds {
  public $name;
  public $password;
  public $url;

  /**
   * Creates a new instance of SimpleRestCreds.
   *
   * @param string $name
   *   The username to be used to contact Site Factory.
   * @param string $password
   *   The password to be used to contact Site Factory.
   * @param string $url
   *   The url of the Site Factory.
   */
  public function __construct($name, $password, $url) {
    $this->name = $name;
    $this->password = $password;
    $this->url = $url;
  }
}

/**
 * Class SimpleRestMessage.
 *
 * A simple class used to send REST requests to the Site Factory.
 */
class SimpleRestMessage {
  private $retryMax = 3;
  private $retryWait = 5;
  private $site;
  private $env;

  /**
   * Creates a new instance of SimpleRestMessage.
   *
   * @param string $site
   *   The hosting site name.
   * @param string $env
   *   The hosting environment name.
   */
  public function __construct($site, $env) {
    $this->site = $site;
    $this->env = $env;
  }

  /**
   * Sends a request.
   *
   * @param string $method
   *   The request method.  Either 'POST' or 'GET'.
   * @param string $endpoint
   *   The request endpoint.
   * @param array $parameters
   *   Any required parameters for the request. Note: parameters are currently
   *   only implemented for POST requests. To add support for GET parameters
   *   would require changes in this method.
   * @param SimpleRestCreds $creds
   *   The credentials to use for the Site Factory request.
   *
   * @throws Exception
   *   If the request fails.
   *
   * @return \SimpleRestResponse
   *   The response.
   */
  public function send($method, $endpoint, array $parameters, SimpleRestCreds $creds) {
    $error = '';
    $user_agent = sprintf('%s.%s %s', $this->site, $this->env, gethostname());
    $curl = curl_init();

    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_USERAGENT, $user_agent);
    curl_setopt($curl, CURLOPT_HEADER, 0);
    curl_setopt($curl, CURLOPT_USERPWD, $creds->name . ":" . $creds->password);
    curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);

    // If it is not a GET request, set the method here.
    if ($method != 'GET') {
      curl_setopt($curl, CURLOPT_CUSTOMREQUEST, $method);
    }

    // If we are sending parameters, set the query string or POST fields here.
    $query_string = '';
    if ($method != 'GET' && !empty($parameters)) {
      $data_string = json_encode($parameters);
      curl_setopt($curl, CURLOPT_POSTFIELDS, $data_string);
      curl_setopt($curl, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($data_string),
      ));
    }

    $full_url = sprintf('%s/%s%s', $creds->url, $endpoint, $query_string);
    curl_setopt($curl, CURLOPT_URL, $full_url);

    $attempts = 0;
    $response = FALSE;

    while (!$response && ++$attempts <= $this->retryMax) {
      $response = curl_exec($curl);
      if (!$response) {
        $error = curl_error($curl);
        sleep($this->retryWait);
      }
    }

    if (!$response) {
      throw new Exception(sprintf('Error reaching url "%s" with method "%s." Returned error "%s."', $full_url, $method, $error));
    }

    $response_code = curl_getinfo($curl, CURLINFO_HTTP_CODE);
    curl_close($curl);

    $response_body = json_decode($response, TRUE);

    return new SimpleRestResponse($endpoint, $response_code, $response_body);
  }

}

/**
 * Class SimpleRestResponse.
 *
 * Holds the response.
 */
class SimpleRestResponse {
  /**
   * The request endpoint.
   *
   * @var string
   */
  public $endpoint;

  /**
   * The response code.
   *
   * @var string
   */
  public $code;

  /**
   * The response body.
   *
   * @var array
   */
  public $body;

  /**
   * Constructs a new instance of SimpleRestResponse.
   *
   * @param string $endpoint
   *   The request endpoint.
   * @param string $response_code
   *   The response code.
   * @param array $response_body
   *   The response body.
   */
  public function __construct($endpoint, $response_code, array $response_body) {
    $this->endpoint = $endpoint;
    $this->code = $response_code;
    $this->body = $response_body;
  }
}
