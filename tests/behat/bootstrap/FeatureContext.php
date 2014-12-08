<?php

use Behat\Behat\Context\ClosuredContextInterface,
    Behat\Behat\Context\TranslatedContextInterface,
    Behat\Behat\Exception\PendingException;
use Behat\Behat\Context\Step\Given;
use Behat\Gherkin\Node\PyStringNode,
    Behat\Gherkin\Node\TableNode;
use Drupal\DrupalExtension\Context\DrupalContext;

/**
 * Features context.
 */
class FeatureContext extends DrupalContext {

  /**
   * @Given /^an "([^"]*)" user named "([^"]*)"$/
   */
  public function anUserNamed($role_name, $username) {
    // Create user (and project)
    $user = (object) array(
      'name' => $username,
      'pass' => $this->getDrupal()->random->name(16),
      'role' => $role_name,
    );
    $user->mail = "{$user->name}@example.com";

    // Create a new user.
    $this->getDriver()->userCreate($user);

    $this->users[$user->name] = $user;
    $this->getDriver()->userAddRole($user, $role_name);
  }

  /**
   * @Given /^I visit the user edit page for "([^"]*)"$/
   */
  public function iVisitTheUserEditPageFor($name) {
    $account = user_load_by_name($name);
    if (!empty($account->uid)) {
      $this->getSession()->visit($this->locatePath('/user/' . $account->uid . '/edit'));
    }
    else {
      throw new \Exception('No such user');
    }
  }

  /**
   * @Then /^I "([^"]*)" be able to change the "([^"]*)" role$/
   */
  public function iBeAbleToChangeTheRole($state, $role_name) {
    $administrator_role = user_role_load_by_name($role_name);
    if (strtolower($state) == 'should') {
      $this->assertElementOnPage('#edit-roles-change-' . $administrator_role->rid);
    }
    else {
      $this->assertElementNotOnPage('#edit-roles-change-' . $administrator_role->rid);
    }
  }

  /**
   * @Given /^I "([^"]*)" be able to block the user$/
   */
  public function iShouldNotBeAbleToBlockTheUser($state) {
    if (strtolower($state) == 'should') {
      $this->assertElementOnPage('input[name=status]');
    }
    else {
      $this->assertElementNotOnPage('input[name=status]');
    }
  }

  /**
   * @Given /^I visit the user list page$/
   */
  public function iVisitTheUserListPage() {
    return new Given('I visit "/admin/people"');
  }

  /**
   * @Given /^I should not be able to cancel the account "([^"]*)"$/
   */
  public function iShouldNotBeAbleToCancelTheAccount($username) {
    $this->selectUserVBOCheckbox($username);
    $this->getSession()->getPage()->fillField('operation', 'action::views_bulk_operations_delete_item');
    $this->getSession()->getPage()->pressButton('edit-submit--2');
    $this->assertElementNotOnPage('input[value=Confirm][type=submit]');
    return new Given('I should see "is protected from cancellation, and was not cancelled."');
  }

  /**
   * @Given /^I should be able to cancel the account "([^"]*)"$/
   */
  public function iShouldBeAbleToCancelTheAccount($username) {
    $this->selectUserVBOCheckbox($username);
    $this->getSession()->getPage()->fillField('operation', 'action::views_bulk_operations_delete_item');
    $this->getSession()->getPage()->pressButton('edit-submit--2');
    $this->assertElementOnPage('input[value=Confirm][type=submit]');
    return new Given('I should not see "is protected from cancellation, and was not cancelled."');
  }

  /**
   * Selects a user in the VBO list.
   *
   * @param string $username
   *
   * @throws \InvalidArgumentException
   *   When no such username exists or the checkbox can't be found.
   */
  protected function selectUserVBOCheckbox($username) {
    if ($account = user_load_by_name($username)) {
      if ($checkbox = $this->getSession()->getPage()->find('css', 'input[value=' . $account->uid . ']')) {
        $checkbox->check();
      }
      else {
        throw new \InvalidArgumentException(sprintf('No such checkbox %s', $username));
      }
    }
    else {
      throw new \InvalidArgumentException(sprintf('No such username %s', $username));
    }
  }

  /**
   * @Then /^I should be logged out$/
   */
  public function assertLoggedOut() {
    if ($this->loggedIn()) {
      throw new \Exception('Logged in.');
    }
  }

  protected function getSuspendAccountTime() {
    $id = 'Suspend Account ' . $this->user->uid;
    $result = db_select('rules_scheduler', 'r')
      ->fields('r', array('tid', 'date'))
      ->condition('identifier', $id, '=')
      ->execute()
      ->fetchAssoc();
    return $result['date'];
  }

  /**
   * @Then /^account should be scheduled to be blocked$/
   */
  public function accountShouldBeScheduledToBeBlocked() {
    $now = time();
    if ($this->getSuspendAccountTime() <= $now) {
      throw new \Exception('Account not scheduled to be blocked.');
    }
  }

  /**
   * @Then /^adjust scheduled suspend date to now$/
   */
  public function adjustScheduledSuspendDateToNow() {
    $now = time();
    $id = 'Suspend Account ' . $this->user->uid;
    db_update('rules_scheduler')
      ->fields(array(
        'date' => $now,
      ))
      ->condition('identifier', $id, '=')
      ->execute();
  }

  /**
   * @Then /^account should be blocked$/
   */
  public function accountShouldBeBlocked() {
    $user = user_load($this->user->uid, TRUE);
    if ($user->status) {
      throw new \Exception('User is not blocked.');
    }
  }

  /**
   * @Then /^relogin adjust suspend account to later$/
   */
  public function reloginAdjustSuspendAccountToLater() {
    if (!isset($this->user)) {
      return FALSE;
    }
    $initial = $this->getSuspendAccountTime();
    $this->logout();
    $this->login();
    $later = $this->getSuspendAccountTime();
    if ($later <= $initial) {
      throw new \Exception('Scheduled suspend not changed to later.');
    }
  }

}
