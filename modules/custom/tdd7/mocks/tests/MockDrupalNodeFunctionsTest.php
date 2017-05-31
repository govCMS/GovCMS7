<?php
/**
 * @file
 * @author Edward Murrell <edward@catalyst-au.net>
 * Tests the Mock Drupal Load functions
 */

namespace tdd7\testframework\mocks;

require_once dirname(dirname(__DIR__)). '/basefixtures/BasicTestCase.php';
require_once dirname(__DIR__) . '/MockDrupalNodeFunctions.php';

use tdd7\testframework\BasicTestCase;

define('MOCK_NODE_TEST_NID1', 547545754543);
define('MOCK_NODE_TEST_NID2', 963732177731);
define('MOCK_NODE_TEST_NID3', 342789342789);
define('MOCK_NODE_TEST_NID_TYPE1', 'test_type_one');
define('MOCK_NODE_TEST_NID_TYPE2', 'test_type_two');
define('MOCK_NODE_TEST_NID_TYPE3', 'test_type_three');
define('MOCK_NODE_TEST_NID_TITLE1', 'Testing Title Uno');
define('MOCK_NODE_TEST_NID_TITLE2', 'Testing Title Duo');
define('MOCK_NODE_TEST_NID_TITLE3', 'Testing Title Trio');

class MockDrupalNodeFunctionsTest extends \tdd7\testframework\BasicTestCase {
  /**
   * GIVEN AddMockNode() is called.
   * AND NID is provided
   * THEN a stdClass is returned
   * WITH nid set, type set.
   */
  public function testNode_loadReturnsClassWithType() {
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1);
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID2, MOCK_NODE_TEST_NID_TYPE2, MOCK_NODE_TEST_NID_TITLE2);
    $node2 = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID2);
    $node1 = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID1);
    $this->assertEquals(547545754543,        $node1->nid);
    $this->assertEquals('test_type_one',     $node1->type);
    $this->assertEquals('Testing Title Uno', $node1->title);

    $this->assertEquals(963732177731,        $node2->nid);
    $this->assertEquals('test_type_two',     $node2->type);
    $this->assertEquals('Testing Title Duo', $node2->title);
  }

  /**
   * GIVEN AddMockNode() is called.
   * AND ResetMockData() is called.
   * THEN node_load() return FALSE;
   */
  public function testResetMockDataEmptiesMockNodeData() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1);
    // Some version of phpunit do have assertNotFalse, so check assert !empty().
    $loadresults = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID1);
    $isempty = empty($loadresults);
    $this->assertFalse($isempty);
    $this->assertFalse(MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID2));
    MockDrupalNodeFunctions::ResetMockData();
    $this->assertFalse(MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID1));
    $this->assertFalse(MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID2));
  }

  /**
   * Given AddMockNode() with no anguage set.
   * THEN node_load() returns a language set as 'und', known as LANGUAGE_NONE.
   */
  public function testAddmocknodeSetsDefaultLanguageToNone() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1);
    $node = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID1);
    $this->assertEquals(LANGUAGE_NONE, $node->language);
    $this->assertEquals('und',         $node->language);
  }

  /**
   * Given AddMockNode() with a language set.
   * THEN node_load() returns that node with language set.
   */
  public function testAddmocknodeSetsLanguageOnNode() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1, 'testlang');
    $node = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID1);
    $this->assertEquals('testlang', $node->language);
  }

  /**
   * Given AddNodeAttribute is called.
   * THEN node_load returns a node with that attribute set.
   */
  public function testAddnodeattributeSetsFieldsOnMockNodeObjects() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1);
    MockDrupalNodeFunctions::AddNodeAttribute(MOCK_NODE_TEST_NID1, 'uid', -123);
    $node = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID1);
    $this->assertEquals(-123, $node->uid);
  }

  /**
   * Given AddNodeAttribute is called with an invalid nid.
   * THEN AddNodeAttribute generates an exception.
   * @expectedException Exception
   * @expectedExceptionMessage Mock node does not exist.
   */
  public function testAddnodeattributeOnInvalidObject() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddNodeAttribute(MOCK_NODE_TEST_NID1, 'uid', -123);
    $node = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID1);
  }

  /**
   * Given AddNodeAttribute is called with an invalid attribute.
   * THEN AddNodeAttribute generates an exception.
   * @expectedException Exception
   * @expectedExceptionMessage Attribute name is invalid.
   */
  public function testAddnodeattributeWithInvalidAttribute() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1);
    MockDrupalNodeFunctions::AddNodeAttribute(MOCK_NODE_TEST_NID1, 'field_foo', -123);
  }

  /**
   * Given AddNodeField is called.
   * THEN node_load returns a node with that field set.
   */
  public function testAddnodeFieldDataSetsFieldsOnMockNodeObjects() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1);
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID1, 'field_test', array('value' => 'test value'));
    $node = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID1);
    $this->assertEquals('test value', $node->field_test[LANGUAGE_NONE][0]['value']);

    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID1, 'field_test', array('value' => 'test value2'), 5);
    $this->assertEquals('test value2', $node->field_test[LANGUAGE_NONE][5]['value']);
  }

  /**
   * Given AddNodeField is called with an invalid attribute.
   * THEN AddNodeField generates an exception.
   * @expectedException Exception
   * @expectedExceptionMessage Mock node does not exist.
   */
  public function testAddnodefieldWithInvalidNid() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1);
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID2, 'field_test', array('value' => 'test value'));
  }

  /**
   * Given mock nodes exist
   * THEN node_load_multiple will return only those requested.
   */
  public function testNodeloadmultipleReturnsRequestedNodes () {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID_TYPE1, MOCK_NODE_TEST_NID_TITLE1);
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID2, MOCK_NODE_TEST_NID_TYPE2, MOCK_NODE_TEST_NID_TITLE2);
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID3, MOCK_NODE_TEST_NID_TYPE3, MOCK_NODE_TEST_NID_TITLE3);
    $nodes = MockDrupalNodeFunctions::node_load_multiple(array(MOCK_NODE_TEST_NID1, MOCK_NODE_TEST_NID3));
    $this->assertArrayHasKey(MOCK_NODE_TEST_NID1, $nodes);
    $this->assertArrayNotHasKey(MOCK_NODE_TEST_NID2, $nodes);
    $this->assertArrayHasKey(MOCK_NODE_TEST_NID3, $nodes);

    $node1 = $nodes[MOCK_NODE_TEST_NID1];
    $node3 = $nodes[MOCK_NODE_TEST_NID3];
    $this->assertEquals(MOCK_NODE_TEST_NID_TITLE1, $node1->title);
    $this->assertEquals(MOCK_NODE_TEST_NID_TITLE3, $node3->title);
  }

  /**
   * GIVEN AddNodeField is called on body more than once with a languge set.
   * THEN node_load returns a node with all the language fields.
   */
  public function testAddnodeFieldDataSetsLanguageFieldsOnMockNodeObjects() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID2, MOCK_NODE_TEST_NID_TYPE2, MOCK_NODE_TEST_NID_TITLE2, 'lang_default');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID2, 'field_test', array('value' => 'test value'));
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID2, 'field_test', array('value' => 'test1 value'), NULL, 'lang_altern');

    $node = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID2);
    $this->assertEquals('test value', $node->field_test['lang_default'][0]['value']);
    $this->assertEquals('test1 value', $node->field_test['lang_altern'][0]['value']);
  }

  /**
   * GIVEN AddNodeField is called on a field with multiple times w/h langauges.
   * THEN node_load returns a node with all the language fields and all deltas.
   */
  public function testAddnodeFieldDataSetsLanguageMultipleFieldsOnMockNodeObjects() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID3, MOCK_NODE_TEST_NID_TYPE3, MOCK_NODE_TEST_NID_TITLE3, 'lang_default');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'test-A value'));
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'test1-A value'), NULL, 'lang_alt1');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'test2-A value'), NULL, 'lang_alt2');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'test3-A value'), NULL, 'lang_alt3');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'test1-B value'), NULL, 'lang_alt1');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'test2-B value'), NULL, 'lang_alt2');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'test3-B value'), NULL, 'lang_alt3');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'test-B value'));

    $node = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID3);
    $this->assertEquals('test-A value', $node->field_test['lang_default'][0]['value']);
    $this->assertEquals('test-B value', $node->field_test['lang_default'][1]['value']);
    $this->assertEquals('test1-A value', $node->field_test['lang_alt1'][0]['value']);
    $this->assertEquals('test2-A value', $node->field_test['lang_alt2'][0]['value']);
    $this->assertEquals('test3-A value', $node->field_test['lang_alt3'][0]['value']);
    $this->assertEquals('test1-B value', $node->field_test['lang_alt1'][1]['value']);
    $this->assertEquals('test2-B value', $node->field_test['lang_alt2'][1]['value']);
    $this->assertEquals('test3-B value', $node->field_test['lang_alt3'][1]['value']);
  }

  /**
   * GIVEN AddNodeField is called w/h deltas on a field with multiple times w/h langauges.
   * THEN node_load returns a node with all the language fields and all deltas.
   */
  public function testAddnodeFieldDataSetsLanguageMultipleDeltaFieldsOnMockNodeObjects() {
    MockDrupalNodeFunctions::ResetMockData();
    MockDrupalNodeFunctions::AddMockNode(MOCK_NODE_TEST_NID3, MOCK_NODE_TEST_NID_TYPE3, MOCK_NODE_TEST_NID_TITLE3, 'lang_default');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'testlang1 delt1 value'), 1, 'lang_alt1');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'testlang2 delt2 value'), 2, 'lang_alt2');
    MockDrupalNodeFunctions::AddNodeField(MOCK_NODE_TEST_NID3, 'field_test', array('value' => 'testlang3 delt2 value'), 2, 'lang_alt3');

    $node = MockDrupalNodeFunctions::node_load(MOCK_NODE_TEST_NID3);
    $this->assertEquals('testlang1 delt1 value', $node->field_test['lang_alt1'][1]['value']);
    $this->assertEquals('testlang2 delt2 value', $node->field_test['lang_alt2'][2]['value']);
    $this->assertEquals('testlang3 delt2 value', $node->field_test['lang_alt3'][2]['value']);
  }
}
