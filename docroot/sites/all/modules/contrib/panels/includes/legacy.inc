<?php

/**
 * Legacy state manager for Panels.
 *
 * Checks all possible ways (using discovery of patterned method names) in which
 * Panels may need to operate in legacy mode,
 * sets variables as appropriate, and returns an informational
 *
 */
class PanelsLegacyState {
  var $legacy = NULL;

  function t() {
    $func = get_t();
    $args = func_get_args();
    return call_user_func_array($func, $args);
  }

  function getStatus() {
    if (!isset($this->legacy)) {
      $this->determineStatus();
    }
    return $this->legacy;
  }

  /**
   * Run all compatibility checks.
   */
  function determineStatus() {
    $this->legacy = array();
    foreach(get_class_methods($this) as $method) {
      if (strtolower(substr($method, 0, 5)) == 'check') {
        $this->legacy[$method] = $this->$method();
      }
    }
    $this->legacy = array_filter($this->legacy);
  }

  // At this time there are no legacy checks.
}
