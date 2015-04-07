<?php

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

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
    * Creates and authenticates a user with the given role via Drush.
    *
    * @Given /^I am logged in as a user with the "(?P<role>[^"]*)" role that doesn't force password change$/
   */
  public function assertAuthenticatedByRole($role) {

    $user = (object) array(
      'name'  => $this->getRandom()->name(8),
      'pass'  => $this->getRandom()->name(16),
      'role'  => $role,
      'roles' => array($role),
    );
    $user->mail = "{$user->name}@example.com";
    // Create a new user.
    $this->userCreate($user);

    // Find the user
    $account = user_load_by_name($user->name);

    // Remove the "Force password change on next login" record.
    db_delete('password_policy_force_change')
      ->condition('uid', $account->uid)
      ->execute();
    db_delete('password_policy_expiration')
      ->condition('uid', $account->uid)
      ->execute();

    $this->login();

  }

}
