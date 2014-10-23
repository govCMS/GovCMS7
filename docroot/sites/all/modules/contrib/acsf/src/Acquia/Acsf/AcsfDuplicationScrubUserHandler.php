<?php

/**
 * @file
 * Contains AcsfDuplicationScrubUserHandler.
 */

namespace Acquia\Acsf;

/**
 * Handles the scrubbing of Drupal users.
 */
class AcsfDuplicationScrubUserHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));

    $options = $this->event->context['scrub_options'];
    $limit = $options['batch_user'];

    if ($options['retain_users']) {
      return;
    }

    if ($options['avoid_oom']) {
      if ($uids = $this->getItems($limit)) {
        $this->deleteUsers($uids);
        $this->event->dispatcher->interrupt();
      }
    }
    else {
      do {
        $uids = $this->getItems($limit);
        if (empty($uids)) {
          break;
        }
        $this->deleteUsers($uids);
      } while (TRUE);
    }
  }

  /**
   * Gets a range of user IDs excluding those marked as preserved.
   *
   * @param int $limit
   *   The number of records to retrieve.
   *
   * @return array
   *   An indexed array containing the relevant UIDs, or an empty array if there
   *   is no result set.
   */
  protected function getItems($limit = 5000) {
    return db_query_range('SELECT uid FROM {users} WHERE uid NOT IN (:uids)', 0, $limit, array(':uids' => $this->getPreservedUsers()))->fetchCol();
  }

  /**
   * Deletes a given list of users.
   *
   * @param array $uids
   *   An indexed array of user IDs to delete.
   */
  protected function deleteUsers(array $uids = array()) {
    foreach ($uids as $uid) {
      $this->reassignFiles($uid);
      user_delete($uid);
    }
  }

  /**
   * Reassigns files owned by the given user ID to the anonymous user.
   *
   * Prior to deleting the user, re-assign {file_managed}.uid to anonymous.
   * Re-assign files only: allow nodes and comments to be deleted. It would be
   * more proper to call file_load_multiple(), iterate each loaded file entity,
   * set its uid property, and call file_save() (see comment_user_cancel() for a
   * similar example for comments). It would be even more proper if file.module
   * implemented hook_user_cancel(), so we could just call that hook. But for
   * performance, we just update the {file_managed} table directly.
   *
   * @param int $uid
   *   The user ID for which to reassign files.
   */
  protected function reassignFiles($uid) {
    db_update('file_managed')
      ->fields(array(
        'uid' => 0,
      ))
      ->condition('uid', $uid)
      ->execute();
  }

  /**
   * Gets a list of user IDs to preserve.
   *
   * @return array
   *   An indexed array of user IDs to preserve.
   */
  public function getPreservedUsers() {
    $preserved = array_merge(self::getOpenIdAdmins(), self::getSiteAdmins()); // Preserve Open ID and site admins.
    $preserved[] = 0; // Preserve the anonymous user.
    $preserved[] = 1; // Preserve UID 1.
    drupal_alter('acsf_duplication_scrub_preserved_users', $preserved);
    return $preserved;
  }

  /**
   * Gets a list of Open ID admins.
   *
   * @return array
   *   An indexed array of user IDs representing Open ID admins.
   */
  public function getOpenIdAdmins() {
    $uids = array();
    $admin_roles = array(
      variable_get('user_admin_role'),
    );
    drupal_alter('acsf_duplication_scrub_admin_roles', $admin_roles);
    if (!empty($admin_roles)) {
      $uids = db_query('SELECT a.uid FROM {authmap} a INNER JOIN {users_roles} r ON a.uid = r.uid WHERE a.module = :module AND r.rid IN (:admin_roles)', array(':module' => 'openid', ':admin_roles' => $admin_roles))->fetchCol();
    }

    return $uids;
  }

  /**
   * Gets a list of site admins.
   *
   * @return array
   *   An indexed array of user IDs representing site admins.
   */
  public function getSiteAdmins() {
    $uids = array();
    $admin_roles = array(
      variable_get('user_admin_role'),
    );
    drupal_alter('acsf_duplication_scrub_admin_roles', $admin_roles);
    if (!empty($admin_roles)) {
      $uids = db_query('SELECT u.uid FROM {users} u INNER JOIN {users_roles} r ON u.uid = r.uid WHERE r.rid IN (:admin_roles)', array(':admin_roles' => $admin_roles))->fetchCol();
    }

    return $uids;
  }

  /**
   * Counts the remaining users excluding those marked as preserved.
   *
   * @return int
   *   The number of items remaining in the table that do not need to be
   *   preserved.
   */
  public function countRemaining() {
    return db_query('SELECT COUNT(*) FROM {users} WHERE uid NOT IN (:uids)', array(':uids' => self::getPreservedUsers()))->fetchField();
  }

}
