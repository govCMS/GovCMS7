<?php

use Behat\Behat\Context\ClosuredContextInterface,
    Behat\Behat\Context\TranslatedContextInterface,
    Behat\Behat\Exception\PendingException;
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

}
