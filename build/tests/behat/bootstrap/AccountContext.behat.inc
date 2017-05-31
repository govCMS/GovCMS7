<?php

namespace Acquia\govCMSExtension\Context;

use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Hook\Scope\EntityScope;
use Behat\Behat\Definition\Call\Given;
use Behat\Gherkin\Node\PyStringNode;

/**
 * Contains step definitions for working with users.
 */
class AccountContext extends DrupalSubContextBase {

  /**
   * Clean the password state tables for a test user to bypass password policy.
   *
   * Remove any password history, expiration of flag forcing a password change
   * when they next log in.
   *
   * @afterUserCreate
   */
  public function cleanUserPasswordState(EntityScope $scope) {
    // Retrieve the user.
    $user = $scope->getEntity();
    if (!empty($user->uid)) {
      // Remove the records from password policy module tables.
      db_delete('password_policy_force_change')
        ->condition('uid', $user->uid)
        ->execute();
      db_delete('password_policy_expiration')
        ->condition('uid', $user->uid)
        ->execute();
      db_delete('password_policy_history')
        ->condition('uid', $user->uid)
        ->execute();
    }
  }

  /**
   * Helper for creating users.
   *
   * @param string $name
   *   The name to use - random value created if blank.
   * @param string $pass
   *   The password to use - random value created if blank.
   * @param string $roles
   *   A comma delimited list of roles to add to the user.
   */
  private function createUser($name = '', $pass = '', $roles = '') {
    // Basic user data.
    $user = (object) array(
      'name' => empty($name) ? $this->getRandom()->name(8) : $name,
      'pass' => empty($pass) ? $this->getRandom()->name(16) : $pass,
    );
    $user->mail = "{$user->name}@example.com";

    $this->userCreate($user);
    // Assign roles to user.
    if (!empty($roles)) {
      $roles = explode(',', $roles);
      $roles = array_map('trim', $roles);
      foreach ($roles as $role) {
        if (!in_array(strtolower($role), array(
          'authenticated',
          'authenticated user',
        ))
        ) {
          // Only add roles other than 'authenticated user'.
          $this->getDriver()->userAddRole($user, $role);
        }
      }
    }

    return $user;
  }

  /**
   * Creates and authenticates a user with a specific name and given role(s).
   *
   * @Given /^I am logged in as a user named "(?P<username>[^"]*)" with the "(?P<role>[^"]*)" role$/
   */
  public function assertAuthenticatedByRole($username, $role = '') {
    // Check if a user with this role is already logged in.
    if (!$this->loggedInWithRole($role)) {
      // Create user.
      $this->createUser($username, '', $role);

      // Login.
      $this->login();
    }
  }

  /**
   * Creates and authenticates a user with the given permission(s).
   *
   * @param string $permissions
   *   The comma separated list of permissions to provide to the user.
   * @param string $username
   *   Optional parameter for user name to be used for login.
   * @param string $password
   *   Optional parameter for user password to be used for login.
   *
   * @Given /^I am logged in as a user (?:|named )"(?P<username>[^"]*)" with the "(?P<permissions>[^"]*)" permission(?:|s)$/
   * @Given /^I am logged in as a user with the password "(?P<password>[^"]*)" and the "(?P<permissions>[^"]*)" permission(?:|s)$/
   */
  public function assertAuthenticatedWithPermissions($permissions, $username = '', $password = '') {
    // Create user.
    $user = $this->createUser($username, $password);

    // Create and assign a temporary role with given permissions.
    $permissions = explode(',', $permissions);
    $rid = $this->getDriver()->roleCreate($permissions);
    $this->getDriver()->userAddRole($user, $rid);
    $this->roles[] = $rid;

    // Login.
    $this->login();
  }

  /**
   * Creates and authenticates a user with the given set of permissions.
   *
   * @param \Behat\Gherkin\Node\PyStringNode $permissions
   *   The permissions to check for.
   * @param string $username
   *   The user name (a random one is chosen if not supplied).
   * @param string $password
   *   The initial password (a random one is chosen if not supplied).
   *
   * @Given /^I am logged in as a user (?:|named )(?:|"(?P<username>[^"]*)" )(?:|with the password "(?P<password>[^"]*)" )with the following permissions:$/
   */
  public function assertAuthenticatedWithPermissionsList(PyStringNode $permissions, $username = '', $password = '') {
    // Create user.
    $user = $this->createUser($username, $password);

    // Create and assign a temporary role with given permissions.
    // The table parsing might have left whitespace around the text => trim.
    $perms_array = array();
    foreach ($permissions->getStrings() as $permission) {
      array_push($perms_array, trim($permission));
    }
    $rid = $this->getDriver()->roleCreate($perms_array);
    $this->getDriver()->userAddRole($user, $rid);
    $this->roles[] = $rid;

    // Login.
    $this->login();
  }

  /**
   * Log out a user.
   *
   * @Then /^I logout$/
   */
  public function assertLogout() {
    $this->logout();
  }

  /**
   * Check that a user account with a particular name and role exists.
   *
   * @Given /^a user named "(?P<username>[^"]*)" with role "(?P<role>[^"]*)" exists$/
   */
  public function assertAccountCreated($username, $role) {
    // Create the user.
    $user = $this->createUser($username, '', $role);
    if (empty($user)) {
      throw new \Exception('Failed to create the user with the name "%s"', $username);
    }
  }

  /**
   * Ensure that a user account is deleted.
   *
   * @When /^a user named "(?P<username>[^"]*)" is deleted$/
   */
  public function assertAccountDeleted($username) {
    // Find the user.
    $user = user_load_by_name($username);
    // If such user exists then delete it.
    if (!empty($user)) {
      $this->getDriver()->userDelete($user);
    }
    else {
      throw new \Exception('No such user');
    }
  }

  /**
   * Set the last logged in time for a user.
   *
   * @When /^the user named "(?P<username>[^"]*)" has not logged in for "(?P<lastlogin>[^"]*)" days$/
   */
  public function setUserSuspension($username, $lastlogin) {
    // Find the user.
    $user = user_load_by_name($username);
    // If such user exists then delete it.
    if (!empty($user)) {
      // Load current settings for suspension rules.
      $rule = rules_config_load('rules_suspend_account_after_inactivity');
      foreach ($rule->actions() as $action) {
        if ($action->settings['identifier'] = 'Suspend Account [account:uid]') {
          $settings = $action->settings;
        }
      }
      if (!empty($settings)) {
        // Override the rules scheduled review time.
        // By default the scheduler will 60 days from now, but we need to
        // dynamically offset that by the number of inactivity days.
        $component = 'rules_suspend_account';
        $task_identifier = "Suspend Account {$user->uid}";
        $timestamp = strtotime(sprintf('-%s days', $lastlogin), strtotime($settings['date']));

        rules_action('schedule', ['component' => $component])->executeByArgs([
          'date' => is_numeric($timestamp) ? $timestamp : strtotime('now'),
          'identifier' => $task_identifier,
          'param_suspend_account_user' => $user,
        ]);
      }
    }
    else {
      throw new \Exception("No such user {$username}");
    }
  }

  /**
   * Test whether a user account can be blocked.
   *
   * @Given /^I should be able to block the user$/
   */
  public function iShouldBeAbleToBlockTheUser() {
    $this->assertSession()->elementExists('css', 'input[name=status]');
  }

  /**
   * Confirm that a user account may not be blocked.
   *
   * @Given /^I should not be able to block the user$/
   */
  public function iShouldNotBeAbleToBlockTheUser() {
    $this->assertSession()->elementNotExists('css', 'input[name=status]');
  }

  /**
   * Test visiting an account cancel page.
   *
   * @Given /^I visit the user cancel page for "(?P<username>[^"]*)"$/
   */
  public function iShouldNotBeAbleToCancelTheAccount($username) {
    $account = user_load_by_name($username);
    return new Given('I visit "/user/' . $account->uid . '/cancel"', function () {
    });
  }

  /**
   * Test that an account can be cancelled.
   *
   * @Then /^I should be able to cancel the account "(?P<username>[^"]*)"$/
   */
  public function iShouldBeAbleToCancelTheAccount($username) {
    $this->selectUserVBOCheckbox($username);
    $this->getSession()->getPage()->fillField('operation', 'action::views_bulk_operations_user_cancel_action');
    $this->getSession()->getPage()->pressButton('edit-submit--2');
    $this->assertSession()->elementExists('css', 'input[value=Next][type=submit]');
    return new Given('I should not see "is protected from cancellation, and was not cancelled."');
  }

  /**
   * Selects a user in the VBO list.
   *
   * @param string $username
   *   The username to select.
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
   * Access the user edit page.
   *
   * @Given /^I visit the user edit page for "(?P<username>[^"]*)"$/
   */
  public function iVisitTheUserEditPageFor($username) {
    $account = user_load_by_name($username);
    if (!empty($account->uid)) {
      $this->getSession()->visit($this->locatePath('/user/' . $account->uid . '/edit'));
    }
    else {
      throw new \Exception('No such user');
    }
  }

  /**
   * Check that the roles for a user can be modified.
   *
   * @Then /^I should be able to change the "(?P<role_name>[^"]*)" role$/
   */
  public function iShouldBeAbleToChangeTheRole($role_name) {
    $administrator_role = user_role_load_by_name($role_name);
    $this->assertSession()->elementExists('css', '#edit-roles-change-' . $administrator_role->rid);
  }

  /**
   * Check that the roles for a user may not be modified.
   *
   * @Then /^I should not be able to change the "(?P<role_name>[^"]*)" role$/
   */
  public function iShouldNotBeAbleToChangeTheRole($role_name) {
    $administrator_role = user_role_load_by_name($role_name);
    $this->assertSession()->elementNotExists('css', '#edit-roles-change-' . $administrator_role->rid);
  }

}
