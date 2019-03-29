<?php

namespace GovCMS\govCMSExtension\Context;

use Behat\Gherkin\Node\PyStringNode;
use Behat\Mink\Exception\Exception;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\MinkContext;

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
  protected function roleToRid($rid) {
    if (is_numeric($rid)) {
      return $rid;
    }

    return array_search($rid, user_roles());
  }

  /**
   * Check that we are on the role's permission setting page.
   *
   * @param string $rid
   *   Role id.
   *
   * @throws \Behat\Mink\Exception\UnsupportedDriverActionException
   */
  protected function assertPermissionPagePath($rid) {
    $base_url = $this->getMinkParameter('base_url');
    $page = '/admin/people/permissions/' . $rid;
    $path = !empty($base_url) ? $base_url . $page : $page;
    $mink = new MinkContext();
    $mink->setMink($this->getMink());
    $mink->assertAtPath($path);
  }

  /**
   * Asserts that a role has a set of permissions.
   *
   * @param string $role
   *   The role name.
   * @param \Behat\Gherkin\Node\PyStringNode $permissions
   *   The permissions to check for.
   *
   * @Then the :role role should have permissions:
   * @Then the :role role should have permission to:
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   * @throws \Behat\Mink\Exception\UnsupportedDriverActionException
   */
  public function assertPermissions($role, PyStringNode $permissions) {
    $rid = self::roleToRid($role);
    try {
      self::assertPermissionPagePath($rid);
    }
    catch (\Exception $e) {
      throw new \Exception(sprintf('Invalid permission page path for role "%s"', $role));
    }
    foreach ($permissions->getStrings() as $permission) {
      $this->assertPermission($rid, trim($permission));
    }
  }

  /**
   * Asserts that a role does NOT have a set of permissions.
   *
   * @param string $role
   *   The role ID.
   * @param \Behat\Gherkin\Node\PyStringNode $permissions
   *   The permissions to check for.
   *
   * @Then the :role role should not have permissions:
   * @Then the :role role should not have permission to:
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   */
  public function assertNoPermissions($role, PyStringNode $permissions) {
    $rid = self::roleToRid($role);
    try {
      self::assertPermissionPagePath($rid);
    }
    catch (\Exception $e) {
      throw new \Exception(sprintf('Invalid permission page path for role "%s"', $role));
    }
    foreach ($permissions->getStrings() as $permission) {
      $this->assertNoPermission($rid, trim($permission));
    }
  }

  /**
   * Asserts that a role has a specific permission.
   *
   * @param string $rid
   *   The role ID.
   * @param string $permission
   *   The permission to check for.
   *
   * @Given the :role role has the :permission permission
   * @Given the :role role has permission to :permission
   *
   * @Then the :role role should have the :permission permission
   * @Then the :role role should have permission to :permission
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   */
  public function assertPermission($rid, $permission) {
    $this->assertSession()->checkboxChecked($rid . '[' . $permission . ']');
  }

  /**
   * Asserts that a role does not have a specific permission.
   *
   * @param string $rid
   *   The role ID.
   * @param string $permission
   *   The permission to check for.
   *
   * @Given the :role role does not have the :permission permission
   * @Given the :role role does not have permission to :permission
   *
   * @Then the :role role should not have the :permission permission
   * @Then the :role role should not have permission to :permission
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   */
  public function assertNoPermission($rid, $permission) {
    $field = $rid . '[' . $permission . ']';
    try {
      $this->assertSession()->fieldNotExists($field);
    }
    catch (Exception $e) {
      $this->assertSession()->checkboxNotChecked($field);
    }
  }

}
