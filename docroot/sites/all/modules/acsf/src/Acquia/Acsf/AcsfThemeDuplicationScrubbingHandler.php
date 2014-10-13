<?php

/**
 * @file
 * Contains \Acquia\Acsf\AcsfThemeDuplicationScrubbingHandler.
 */

namespace Acquia\Acsf;

/**
 * Truncates the pending theme notification table.
 */
class AcsfThemeDuplicationScrubbingHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));
    db_query('TRUNCATE {acsf_theme_notifications}');
  }

}
