<?php

/**
 * @file
 * Provides PHPUnit tests for AcsfConfig.
 */

class AcsfConfigTest extends PHPUnit_Framework_TestCase {

  public function setUp() {
    $files = array(
      __DIR__ . '/../vendor/autoload.php',
      __DIR__ . '/AcsfConfigUnitTest.inc',
      __DIR__ . '/AcsfConfigUnitTestMissingPassword.inc',
      __DIR__ . '/AcsfConfigUnitTestMissingUrl.inc',
      __DIR__ . '/AcsfConfigUnitTestMissingUsername.inc',
      __DIR__ . '/AcsfConfigUnitTestIncompatible.inc',
      __DIR__ . '/AcsfMessageUnitTestSuccess.inc',
      __DIR__ . '/AcsfMessageUnitTestFailure.inc',
      __DIR__ . '/AcsfMessageUnitTestFailureException.inc',
      __DIR__ . '/AcsfMessageUnitTestMissingEndpoint.inc',
      __DIR__ . '/AcsfMessageUnitTestMissingResponse.inc',
      __DIR__ . '/AcsfMessageResponseUnitTest.inc',
    );
    foreach ($files as $file) {
      require_once $file;
    }
  }

  /**
   * Tests that a PHP error is thrown when no constructor params are provided.
   *
   * @expectedException PHPUnit_Framework_Error_Notice
   * @expectedExceptionMessage AH_SITE_GROUP
   */
  public function testAcsfConfigMissingParameters() {
    // Intentionally avoid providing the required constructor parameters to
    // check that the environment variables are used.
    new AcsfConfigUnitTest();
  }

  /**
   * Tests that a PHP error is thrown when not enough params are provided.
   *
   * @expectedException PHPUnit_Framework_Error_Notice
   * @expectedExceptionMessage AH_SITE_ENVIRONMENT
   */
  public function testAcsfConfigMissingEnvironment() {
    new AcsfConfigUnitTest('ah_site_group');
  }

  /**
   * Tests that a PHP error is thrown when not enough params are provided.
   *
   * @expectedException PHPUnit_Framework_Error_Notice
   * @expectedExceptionMessage AH_SITE_GROUP
   */
  public function testAcsfConfigMissingSiteGroup() {
    new AcsfConfigUnitTest(null, 'ah_site_environment');
  }

  /**
   * Tests no PHP error is thrown when the necessary parameters are provided.
   */
  public function testAcsfConfigNoMissing() {
    try {
      $no_error = TRUE;
      // Provide bot the $ah_site and $ah_env parameters to ensure no errors are
      // triggered for missing environment variables.
      $config = new AcsfConfigUnitTest('ah_site_group', 'ah_site_environment');
    }
    catch (PHPUnit_Framework_Error_Notice $e) {
      $no_error = FALSE;
    }
    $this->assertTrue($no_error);
  }

  /**
   * Tests that a missing password triggers an exception.
   *
   * @expectedException \Acquia\Acsf\AcsfConfigIncompleteException
   */
  public function testAcsfConfigMissingPassword() {
    new AcsfConfigUnitTestMissingPassword('unit_test_site', 'unit_test_env');
  }

  /**
   * Tests that a missing username triggers an exception.
   *
   * @expectedException \Acquia\Acsf\AcsfConfigIncompleteException
   */
  public function testAcsfConfigMissingUsername() {
    new AcsfConfigUnitTestMissingUsername('unit_test_site', 'unit_test_env');
  }

  /**
   * Tests that a missing URL triggers an exception.
   *
   * @expectedException \Acquia\Acsf\AcsfConfigIncompleteException
   */
  public function testAcsfConfigMissingUrl() {
    new AcsfConfigUnitTestMissingUrl('unit_test_site', 'unit_test_env');
  }

  /**
   * Tests getPassword() works as expected.
   */
  public function testAcsfConfigGetPassword() {
    $config = new AcsfConfigUnitTest('unit_test_site', 'unit_test_env');
    $this->assertSame($config->getPassword(), 'Un1tT35t');
  }

  /**
   * Tests getUrl() works as expected.
   */
  public function testAcsfConfigGetUrl() {
    $config = new AcsfConfigUnitTest('unit_test_site', 'unit_test_env');
    $this->assertSame($config->getUrl(), 'http://gardener.unit.test');
  }

  /**
   * Tests getUsername() works as expected.
   */
  public function testAcsfConfigGetUsername() {
    $config = new AcsfConfigUnitTest('unit_test_site', 'unit_test_env');
    $this->assertSame($config->getUsername(), 'gardener_unit_test');
  }

}

/**
 * Fake version of variable_get to make the tests pass.
 */
function variable_get($name, $default = NULL) {
  return FALSE;
}

