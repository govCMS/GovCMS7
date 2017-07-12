<?php
/**
 * @file
 * @author Edward Murrell <edward@catalyst-au.net>
 * Simple test case to demo use of MockDrupalNodeFunctions.
 *
 * Runs this test by running the following from the command line:
 *  phpunit sites/all/modules/contrib/tdd7/docs/examples/tests/ExampleDrupalNodeMockTest.php
 */

namespace tdd7\example;

require_once __DIR__ . '/../ExampleDrupalNodeMock.inc';
require_once __DIR__ . '/../../../basefixtures/BasicTestCase.php';
require_once __DIR__ . '/../../../mocks/MockDrupalNodeFunctions.php';

use tdd7\testframework\BasicTestCase;
use \tdd7\testframework\mocks\MockDrupalNodeFunctions;

/**
 * We define constants here to make it easier to recognise node IDs in the rest
 * of the unit testing code. Large numbers are used so decrease the likelihood
 * ID collisions and producting false positives and odd interactions with the
 * rest of the Drupal code.
 */
define('TDD7_EXAMPLE_NID1', 457543543);
define('TDD7_EXAMPLE_NID2', 454328904);

/**
 * Define the mock node_load() function for our namespaced production code,
 * instead of the core drupal node_load().
 */
function node_load($nid = NULL, $vid = NULL, $reset = FALSE) {
  return MockDrupalNodeFunctions::node_load($nid, $vid, $reset);
}

class ExampleDrupalNodeMockTest extends BasicTestCase {

  /**
   * This code is run before each testABC() method in this class.
   */
  public function setUp() {
    /**
     * Create a mock node with nid defined in TDD7_EXAMPLE_NID1, type 'page', and a title of 'Expected title'
     */
    MockDrupalNodeFunctions::AddMockNode(TDD7_EXAMPLE_NID1, 'page', 'Expected title');
  }

  /**
   * This code is run after each testABC() method in this class.
   */
  public function tearDown() {
    /**
     * Delete all mock node data, so that test data from one class does not
     * potentially corrupt the next test.
     */
    MockDrupalNodeFunctions::ResetMockData();
  }

  /**
   * Test the get_node_title() returns a title for the right node.
   */
  public function testGet_node_titleReturnsExpectedString() {
    /**
     * Retrieve the results of get_node_title that will call the mocked
     * node_load() function, and assert that this returns the title of the
     * mocked node we created in setUp();
     */
    $this->assertEquals('Expected title', get_node_title(TDD7_EXAMPLE_NID1));

    /**
     * In this function we search for an nid that doesn't exist. According our
     * function documentation, this function should return an empty string if
     * the node isn't found, so we test that.
     */
    $this->assertEquals('', get_node_title(TDD7_EXAMPLE_NID2));
  }
}
