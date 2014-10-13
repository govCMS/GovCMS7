<?php

/**
 * @file
 * Contains AcsfDuplicationScrubModuleDisableHandler.
 */

namespace Acquia\Acsf;

/**
 * Disables Drupal modules necessary for the scrubbing process.
 */
class AcsfDuplicationScrubModuleDisableHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));

    $enable_for_scrub = acsf_vget('acsf_duplication_enable_for_scrub', array());
    if (!empty($enable_for_scrub)) {
      require_once DRUPAL_ROOT . '/includes/install.inc';

      // Re-disable modules that were disabled prior to starting the scrubbing
      // process, and enabled only for scrubbing.
      module_disable($enable_for_scrub);

      // Uninstall these modules. Drupal will drop their tables and any orphaned
      // data remaining in them.
      drupal_uninstall_modules($enable_for_scrub);
    }
  }

}
