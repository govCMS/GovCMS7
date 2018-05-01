<?php

use Drupal\DrupalExtension\Context\MinkContext;
use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Mink\Driver\Selenium2Driver;
use Behat\Behat\Hook\Scope\AfterStepScope;
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
   * Set default browser window size to maximum.
   *
   * @BeforeScenario
   */
  public function maximizeWindow() {
    $driver = $this->getSession()->getDriver();
    if (!($driver instanceof Selenium2Driver)) {
      return;
    }
    $this->getSession()->getDriver()->maximizeWindow();
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
   * Actions to take after a step has run.
   *
   * @AfterStep
   */
  public function takeScreenShotAfterFailedStep(AfterStepScope $scope) {
    if (99 === $scope->getTestResult()->getResultCode()) {
      $driver = $this->getSession()->getDriver();
      if (!($driver instanceof Selenium2Driver)) {
        return;
      }
      $this->getSession()->resizeWindow(1440, 900, 'current');
      file_put_contents(__DIR__ . '../../screenshot-fail.png', $this->getSession()->getDriver()->getScreenshot());
    }
  }

  /**
   * Takes a screenshot for debugging purposes.
   *
   * @param string $filename
   *   The name of the screenshot file.
   *
   * @When I take a screenshot named :filename
   */
  public function takeScreenshot($filename) {
    $screenshot = $this->getSession()->getDriver()->getScreenshot();
    // If this file is in tests/features/bootstrap, the screenshot be in tests.
    file_put_contents(__DIR__ . '../../' . $filename . '.png', $screenshot);
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
