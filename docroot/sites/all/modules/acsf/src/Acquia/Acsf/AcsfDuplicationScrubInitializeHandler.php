<?php

/**
 * @file
 * Contains AcsfDuplicationScrubInitializeHandler.
 */

namespace Acquia\Acsf;

/**
 * Handles final operations for the scrub.
 */
class AcsfDuplicationScrubInitializeHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));
    if (!$this->isComplete()) {
      $site = acsf_get_acsf_site();
      $site->clean();
      variable_del('acsf_duplication_scrub_status');
      variable_set('site_name', $this->event->context['site_name']);
      variable_set('install_time', time());
      // As a preparatory step, remove any corrupt file entries that may prevent
      // duplication from succeeding. Specifically, remove any file with an
      // empty URI string.
      db_delete('file_managed')->condition('uri', '')->execute();
      $this->setComplete();
    }
  }

  /**
   * Returns if this step has already completed.
   */
  public function isComplete() {
    return acsf_vget('acsf_site_duplication_step_initialize_complete', FALSE);
  }

  /**
   * Sets a flag to indicate that this step has completed.
   */
  protected function setComplete() {
    acsf_vset('acsf_site_duplication_step_initialize_complete', TRUE, 'acsf_duplication_scrub');
  }

}
