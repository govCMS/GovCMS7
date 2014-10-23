<?php

/**
 * @file
 * Contains AcsfDuplicationScrubTemporaryFilesHandler.
 */

namespace Acquia\Acsf;

/**
 * Handles the scrubbing of Drupal temporary files.
 */
class AcsfDuplicationScrubTemporaryFilesHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));
    // Remove all temporary files. This code is copied from system_cron() so see
    // that function for more details. Some highlights:
    // - It's unclear if the status field can ever be anything other than 0
    //   (temporary) or 1 (permanenet), but system_cron() uses the bitwise &
    //   operator, so apparently, it thinks additional status bit fields are
    //   possible.
    // - It's unclear why <> is used instead of != for ("not equal").
    // - Separate placeholders are used instead of a single ":permanent" due to
    //   a bug in some PHP versions (see system_cron() for the d.o. issue link).
    $fids = db_query('SELECT fid FROM {file_managed} WHERE status & :permanent1 <> :permanent2 LIMIT 1000', array(
      ':permanent1' => FILE_STATUS_PERMANENT,
      ':permanent2' => FILE_STATUS_PERMANENT,
    ))->fetchCol();
    foreach ($fids as $fid) {
      if ($file = file_load($fid)) {
        file_delete($file);
      }
    }
  }

}
