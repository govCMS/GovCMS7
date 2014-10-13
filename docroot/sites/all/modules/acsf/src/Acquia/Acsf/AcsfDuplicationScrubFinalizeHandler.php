<?php

/**
 * @file
 * Contains AcsfDuplicationScrubFinalizeHandler.
 */

namespace Acquia\Acsf;

/**
 * Handles final operations for the scrub.
 */
class AcsfDuplicationScrubFinalizeHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));

    // Clear the theme field so all users will use the default theme.
    db_update('users')
      ->fields(array(
        'theme' => 0,
      ))
      ->execute();

    // Clear any in-progress multistep forms that are not normally wiped during
    // cache-clear. The other caches are expected to be cleared externally from
    // this process.
    cache_clear_all('*', 'cache_form', TRUE);

    // Clean up ACSF variables.
    $acsf_variables = acsf_vget_group('acsf_duplication_scrub');
    foreach ($acsf_variables as $name => $value) {
      acsf_vdel($name);
    }

    // Begin the site without any watchdog records. This should happen right at
    // the end of the scubbing process to remove any log entries added by the
    // scrubbing process itself.
    if (db_table_exists('watchdog')) {
      db_delete('watchdog')->execute();
    }

    // Mark the entire scrubbing process as complete.
    variable_set('acsf_duplication_scrub_status', 'complete');
  }

}
