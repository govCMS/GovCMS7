<?php

/**
 * @file
 * This event handler populates the site information after the installation.
 */

namespace Acquia\Acsf;

class AcsfSiteInfoHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    $site = acsf_get_acsf_site();
    $site->refresh();

    // Notify the user to verify their email address.
    $site->verification_status['last_updated'] = time();

    $site->save();
  }

}
