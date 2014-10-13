<?php

/**
 * @file
 * Contains \Acquia\Acsf\AcsfThemeNotify.
 */

namespace Acquia\Acsf;

class AcsfThemeNotify {

  /**
   * Sends a theme notification to the Factory.
   *
   * This is going to contact the Factory, so it qualifies as a third-party
   * call, therefore calling it during a normal page load is not advisable. A
   * possibly safer solution could be executing this via a menu callback called
   * through an asynchronous JavaScript call.
   *
   * If the request does not succeed (and $store_failed_notification is truthy),
   * the notification will be stored so that we may try again later when cron
   * runs.
   *
   * @param string $scope
   *   The scope. Either "theme", "site", "group", or "global".
   * @param string $event
   *   The type of theme event that occurred. Either "create", "modify", or
   *   "delete".
   * @param int $nid
   *   The node ID associated with the scope. Only required for "group" scope
   *   notifications. If empty, it will be filled in automatically for "theme"
   *   and "site" scope notifications.
   * @param string $theme
   *   The system name of the theme the event relates to. Only relevant for
   *   "theme" scope notifications.
   * @param int $timestamp
   *   The timestamp when the notification was created.
   * @param bool $store_failed_notification
   *   Optional variable to disable storing a notification when the sending
   *   fails. Should be only used in case of notifications which have been
   *   already added to the pending notification table.
   *
   * @return array
   *   The message response body and code.
   */
  public function sendNotification($scope, $event, $nid = NULL, $theme = NULL, $timestamp = NULL, $store_failed_notification = TRUE) {
    if (!$this->isEnabled()) {
      return array(
        'code' => 500,
        'data' => array('message' => t('The theme change notification feature is not enabled.')),
      );
    }

    try {
      if (empty($nid) && in_array($scope, array('theme', 'site'))) {
        $site = acsf_get_acsf_site();
        $nid = $site->site_id;
      }
      $parameters = array(
        'scope' => $scope,
        'event' => $event,
        'nid' => $nid,
      );
      if ($theme) {
        $parameters['theme'] = $theme;
      }
      if ($timestamp) {
        $parameters['timestamp'] = $timestamp;
      }
      $message = new AcsfMessageRest('POST', 'site-api/v1/theme/notification', $parameters);
      $message->send();
      $response = array(
        'code' => $message->getResponseCode(),
        'data' => $message->getResponseBody(),
      );
    }
    catch (\Exception $e) {
      $error_message = t('AcsfThemeNotify failed with error: @message.', array('@message' => $e->getMessage()));
      syslog(LOG_ERR, $error_message);

      // Send a log message to the Factory.
      $acsf_log = new AcsfLog();
      $acsf_log->log('theme_notify', $error_message, LOG_ERR);

      $response = array(
        'code' => 500,
        'data' => array('message' => $error_message),
      );
    }

    if ($store_failed_notification && $response['code'] !== 200) {
      $this->addNotification($event, $theme);
    }

    return $response;
  }

  /**
   * Resends failed theme notifications.
   *
   * @param int $limit
   *   The number of notification that should be processed.
   *
   * @return int
   *   Returns the number of successfully sent notifications. If none of the
   *   pending notifications managed to get sent then the return will be -1.
   */
  public function processNotifications($limit) {
    if (!$this->isEnabled()) {
      return -1;
    }

    $notifications = $this->getNotifications($limit);

    // If there were no pending notifications then we can consider this process
    // successful.
    $success = 0;

    foreach ($notifications as $notification) {
      // If this is a notification for an event that is not supported, it will
      // never get a 200 response so we need to remove it from storage.
      if (!in_array($notification->event, array('create', 'modify', 'delete'))) {
        $this->removeNotification($notification);
        continue;
      }

      // Increment the count of attempts on this notification. At the first pass
      // through this function, this notification has already been attempted
      // once.
      $this->incrementNotificationAttempts($notification);

      // Remove notification and handle if it exceeds the maximum allowed
      // attempts (default 3). The assumption behind the >= comparison here is
      // that the notification was already tried once before it was stored in
      // the table.
      if ($notification->attempts >= acsf_vget('acsf_theme_notification_max_attempts', 3)) {
        $this->removeNotification($notification);
        // @todo Any additional handling needed? DG-11826
      }
      // Only "site" or "theme" notifications get stored. Any notification with
      // a non-empty theme field is assumed to be a theme notification,
      // otherwise it is a site notification.
      $scope = !empty($notification->theme) ? 'theme' : 'site';
      // Try to send the notification but if it fails do not store it again.
      $response = $this->sendNotification($scope, $notification->event, NULL, $notification->theme, $notification->timestamp, FALSE);
      if ($response['code'] === 200) {
        $this->removeNotification($notification);
        $success++;
      }
    }

    return $success == 0 && !empty($notifications) ? -1 : $success;
  }

  /**
   * Removes a pending notification from the database.
   */
  public function removeNotification($notification) {
    db_query('DELETE FROM {acsf_theme_notifications} WHERE id = :id', array(
      ':id' => $notification->id,
    ));
  }

  /**
   * Indicates whether theme notifications are enabled.
   *
   * If this method returns FALSE, theme notifications will not be sent to the
   * Site Factory.
   *
   * @return bool
   *   TRUE if notifications are enabled; FALSE otherwise.
   */
  public function isEnabled() {
    return acsf_vget('acsf_theme_enabled', TRUE);
  }

  /**
   * Gets a list of stored notifications to be resent.
   *
   * @param int $limit
   *   The number of notifications to fetch.
   *
   * @return object[]
   *   An array of theme notification objects.
   */
  public function getNotifications($limit) {
    return db_query_range('SELECT id, event, theme, timestamp, attempts FROM {acsf_theme_notifications} ORDER BY timestamp ASC', 0, $limit)->fetchAll();
  }

  /**
   * Stores a theme notification for resending later.
   *
   * If the initial request to send the notification to the Factory fails, we
   * store it and retry later on cron.
   *
   * @param string $event
   *   The type of theme event that occurred.
   * @param string $theme
   *   The system name of the theme the event relates to.
   */
  public function addNotification($event, $theme) {
    db_query('INSERT INTO {acsf_theme_notifications} (timestamp, event, theme, attempts) VALUES(:timestamp, :event, :theme, 1)', array(
      ':timestamp' => time(),
      ':event' => $event,
      ':theme' => $theme,
    ));
  }

  /**
   * Increments the stored number of attempts for a notification.
   *
   * @param object $notification
   *   A notification object, equivalent to a row loaded from DB table
   *   acsf_theme_notifications.
   */
  public function incrementNotificationAttempts($notification) {
    db_query('UPDATE {acsf_theme_notifications} set attempts = :attempt WHERE id = :id', array(':id' => $notification->id, ':attempt' => ++$notification->attempts));
  }

}
