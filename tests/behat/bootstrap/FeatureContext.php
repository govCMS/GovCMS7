<?php

namespace GovCMS\govCMSExtension\Context;

use Drupal\DrupalExtension\Context\MinkContext;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Drupal\DrupalExtension\Hook\Scope\EntityScope;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

  /**
   * Keep track of all users that are created.
   *
   * @var array
   */
  protected $userLog = array();

  /**
   * Initializes context.
   *
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   */
  public function __construct() {
  }

  /**
   * Log the user IDs created during the tests.
   *
   * Collect user IDs later to be used for cleaning up processes.
   *
   * @afterUserCreate
   */
  public function logUsers(EntityScope $scope) {
    // Retrieve the user.
    $user = $scope->getEntity();
    if (!empty($user->uid)) {
      $this->userLog[$user->uid] = $user->uid;
    };
  }

  /**
   * Schedules a node for publication.
   *
   * @param string $when
   *   The date and time at which to publish the node, in the format
   *   YYYY-MM-DD HH:MM:SS.
   *
   * @When I schedule the node to be published at :when
   */
  public function schedulePublication($when) {
    $mink = new MinkContext();
    $mink->setMink($this->getMink());
    $mink->clickLink('Scheduling options');
    $mink->iWaitForAjaxToFinish();

    list ($date, $time) = explode(' ', $when, 2);
    $date_field = $this->getSession()->getPage()->findField("publish_on[date]");
    $time_field = $this->getSession()->getPage()->findField("publish_on[time]");

    $date_field->setValue($date);
    $time_field->setValue($time);
  }

  /**
   * Clean up files that were created during the tests.
   *
   * @AfterScenario @api
   */
  public function cleanUpFiles() {
    // Get UIDs of users created during this scenario.
    if (!empty($this->userLog)) {
      // Select all beans created by the scenario users.
      $file_ids = db_select('file_managed', 'f')
        ->fields('f', array('fid'))
        ->condition('uid', $this->userLog, 'IN')
        ->execute()
        ->fetchAll();

      // Loop through all files that were found and delete them.
      if (!empty($file_ids)) {
        foreach ($file_ids as $fid) {
          $file = file_load($fid->fid);
          file_delete($file);
        }
      }
    }
  }

  /**
   * Clean up bean entities that were created during the tests.
   *
   * @AfterScenario @beans
   */
  public function cleanUpBeans() {
    // Get UIDs of users created during this scenario.
    if (!empty($this->userLog)) {
      // Select all beans created by the scenario users.
      $query = new EntityFieldQuery();
      $result = $query->entityCondition('entity_type', 'bean')
        ->propertyCondition('uid', $this->userLog, 'IN')
        ->execute();
      // Loop through all beans that were found and delete them.
      if (isset($result['bean'])) {
        $bids = array_keys($result['bean']);
        foreach ($bids as $bid) {
          $bean = bean_load($bid);
          bean_delete($bean);
        }
      }
    }
  }

  /**
   * Clean up all the test users that were logged during the scenario.
   *
   * @AfterScenario @api
   */
  public function cleanUpUsers() {
    $this->userLog = array();
  }

}
