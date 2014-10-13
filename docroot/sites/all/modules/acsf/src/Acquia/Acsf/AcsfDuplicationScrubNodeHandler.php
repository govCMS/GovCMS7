<?php

/**
 * @file
 * Contains AcsfDuplicationScrubNodeHandler.
 */

namespace Acquia\Acsf;

/**
 * Handles the scrubbing of Drupal nodes.
 */
class AcsfDuplicationScrubNodeHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));

    $options = $this->event->context['scrub_options'];
    $limit = $options['batch_node'];

    if ($options['retain_content']) {
      return;
    }

    if ($options['avoid_oom']) {
      if ($nids = $this->getItems($limit)) {
        node_delete_multiple($nids);
        $this->event->dispatcher->interrupt();
      }
    }
    else {
      do {
        $nids = $this->getItems($limit);
        if (empty($nids)) {
          break;
        }
        node_delete_multiple($nids);
      } while (TRUE);
    }
  }

  /**
   * Gets a range of node IDs to be deleted.
   *
   * @param int $limit
   *   The number of records to retrieve.
   *
   * @return array
   *   An indexed array containing the relevant NIDs, or an empty array if there
   *   is no result set.
   */
  protected function getItems($limit) {
    return db_query_range('SELECT nid FROM {node} WHERE uid NOT IN (:uids)', 0, $limit, array(':uids' => $this->getPreservedUsers()))->fetchCol();
  }

  /**
   * Gets a list of user IDs to preserve.
   *
   * @return array
   *   An indexed array of user IDs to preserve.
   */
  protected function getPreservedUsers() {
    // Delete content that isn't owned by a preserved user.
    $preserved_uids = AcsfDuplicationScrubUserHandler::getPreservedUsers();
    // Remove the anonymous user from the list, since we do want to delete that
    // content.
    if (($key = array_search(0, $preserved_uids)) !== FALSE) {
      unset($preserved_uids[$key]);
    }
    return $preserved_uids;
  }

  /**
   * Counts the remaining nodes authored by the anonymous user.
   *
   * @return int
   *   The number of items remaining in the table that were authored by the
   *   anonymous user.
   */
  public function countRemaining() {
    return db_query('SELECT COUNT(*) FROM {node} WHERE uid NOT IN (:uids)', array(':uids' => self::getPreservedUsers()))->fetchField();
  }

}
