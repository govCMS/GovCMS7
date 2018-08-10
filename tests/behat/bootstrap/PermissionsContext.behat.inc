<?php

namespace GovCMS\govCMSExtension\Context;

use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Behat\Gherkin\Node\PyStringNode;
use Drupal\DrupalExtension\Context\MinkContext;
use Behat\Mink\Exception\Exception;

/**
 * Contains step definitions for working with users.
 */
class PermissionsContext extends DrupalSubContextBase {

  /**
   * Converts a role name to an rid if required.
   *
   * @param mixed $rid
   *   The role ID or name.
   *
   * @return int
   *   The role ID
   */
  private function roleToRid($rid) {
    if (is_numeric($rid)) {
      return $rid;
    }

    return array_search($rid, user_roles());
  }

  /**
   * Asserts that a role has a set of permissions.
   *
   * @param string $rid
   *   The role ID.
   * @param \Behat\Gherkin\Node\PyStringNode $permissions
   *   The permissions to check for.
   *
   * @Then the :role role should have permissions:
   * @Then the :role role should have permission to:
   */
  public function assertPermissions($rid, PyStringNode $permissions) {
    $rid = self::roleToRid($rid);
    foreach ($permissions->getStrings() as $permission) {
      $this->assertPermission($rid, trim($permission), TRUE);
    }
  }

  /**
   * Asserts that a role does NOT have a set of permissions.
   *
   * @param string $rid
   *   The role ID.
   * @param \Behat\Gherkin\Node\PyStringNode $permissions
   *   The permissions to check for.
   *
   * @Then the :role role should not have permissions:
   * @Then the :role role should not have permission to:
   */
  public function assertNoPermissions($rid, PyStringNode $permissions) {
    $rid = self::roleToRid($rid);
    foreach ($permissions->getStrings() as $permission) {
      $this->assertNoPermission($rid, trim($permission), TRUE);
    }
  }

  /**
   * Asserts that a role has a specific permission.
   *
   * @param string $rid
   *   The role ID.
   * @param string $permission
   *   The permission to check for.
   * @param bool $assertPath
   *   Whether we should check the path.
   *
   * @Given the :role role has the :permission permission
   * @Given the :role role has permission to :permission
   *
   * @Then the :role role should have the :permission permission
   * @Then the :role role should have permission to :permission
   */
  public function assertPermission($rid, $permission, $assertPath = TRUE) {
    $rid = self::roleToRid($rid);
    if ($assertPath) {
      $mink = new MinkContext();
      $mink->setMink($this->getMink());
      $mink->assertAtPath('/admin/people/permissions/' . $rid);
    }
    $this->assertSession()->checkboxChecked($rid . '[' . $permission . ']');
  }

  /**
   * Asserts that a role does not have a specific permission.
   *
   * @param string $rid
   *   The role ID.
   * @param string $permission
   *   The permission to check for.
   * @param bool $assertPath
   *   Whether we should check the path.
   *
   * @Given the :role role does not have the :permission permission
   * @Given the :role role does not have permission to :permission
   *
   * @Then the :role role should not have the :permission permission
   * @Then the :role role should not have permission to :permission
   */
  public function assertNoPermission($rid, $permission, $assertPath = TRUE) {
    $rid = self::roleToRid($rid);
    if ($assertPath) {
      $mink = new MinkContext();
      $mink->setMink($this->getMink());
      $mink->assertAtPath('/admin/people/permissions/' . $rid);
    }
    $field = $rid . '[' . $permission . ']';
    try {
      $this->assertSession()->fieldNotExists($field);
    }
    catch (Exception $e) {
      $this->assertSession()->checkboxNotChecked($field);
    }
  }

}
