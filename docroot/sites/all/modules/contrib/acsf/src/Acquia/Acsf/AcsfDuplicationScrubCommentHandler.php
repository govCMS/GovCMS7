<?php

/**
 * @file
 * Contains AcsfDuplicationScrubCommentHandler.
 */

namespace Acquia\Acsf;

/**
 * Handles the scrubbing of Drupal comments.
 */
class AcsfDuplicationScrubCommentHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));

    $options = $this->event->context['scrub_options'];
    $limit = $options['batch_comment'];

    if ($options['retain_content'] || !module_exists('comment')) {
      return;
    }

    if ($options['avoid_oom']) {
      // Orphaned comments, that is comments by an authenticated user or
      // attached to a node that no longer exists, cannot be deleted by
      // comment_delete_multiple. Handle these items first.
      if ($cids = $this->getOrphanedItems($limit)) {
        $orphaned = TRUE;
      }
      elseif ($cids = $this->getItems($limit)) {
        $orphaned = FALSE;
      }

      if (!empty($cids)) {
        $this->deleteItems($cids, $orphaned);
        $this->event->dispatcher->interrupt();
      }
    }
    else {
      do {
        if ($cids = $this->getOrphanedItems($limit)) {
          $orphaned = TRUE;
        }
        elseif ($cids = $this->getItems($limit)) {
          $orphaned = FALSE;
        }
        else {
          break;
        }

        $this->deleteItems($cids, $orphaned);
      } while (TRUE);
    }

  }

  /**
   * Gets a range of comment IDs.
   *
   * @param int $limit
   *   The number of records to retrieve.
   *
   * @return array
   *   An indexed array containing the relevant comment IDs, or an empty array
   *   if there is no result set.
   */
  protected function getItems($limit) {
    return db_query_range('SELECT cid FROM {comment}', 0, $limit)->fetchCol();
  }

  /**
   * Gets a range of orphaned comment IDs.
   *
   * Orphaned comments are those which are associated with an user and / or node
   * that for some reason no longer exist on the site
   *
   * @param int $limit
   *   The number of records to retrieve.
   *
   * @return array
   *   An indexed array containing the relevant comment IDs, or an empty array
   *   if there is no result set.
   */
  protected function getOrphanedItems($limit) {
    return db_query_range('
      SELECT cid FROM {comment} c
      LEFT JOIN {users} u ON c.uid = u.uid
      LEFT JOIN {node} n ON c.nid = n.nid
      WHERE u.uid IS NULL OR n.nid IS NULL', 0, $limit)->fetchCol();
  }

  /**
   * Deletes comments.
   *
   * @param array $cids
   *   An indexed array of comment IDs to delete.
   * @param bool $orphaned
   *   Optional. Whether or not the comments are orphans, since these need to be
   *   deleting differently.
   */
  protected function deleteItems(array $cids, $orphaned = FALSE) {
    if ($orphaned) {
      db_delete('comment')->condition('cid', $cids, 'IN')->execute();
    }
    else {
      comment_delete_multiple($cids);
    }
  }

  /**
   * Counts the remaining comments.
   *
   * @return int
   *   The number of items remaining in the table.
   */
  public function countRemaining() {
    if (!module_exists('comment')) {
      return 0;
    }
    return db_query('SELECT COUNT(*) FROM {comment}')->fetchField();
  }

}
