<?php

/**
 * @file
 * Defines a response from AcsfMessageRest.
 */

namespace Acquia\Acsf;

class AcsfMessageResponseRest extends AcsfMessageResponse {

  /**
   * Implements AcsfMessageResponse::failed().
   */
  public function failed() {
    if ($this->code >= 400) {
      return TRUE;
    }
    return FALSE;
  }
}
