<?php
/** 
 * @file Test DrupalTaxonomyMock functions
 */

namespace tdd7\testframework\mocks;

if (!defined("DRUPAL_ROOT")) {
  define('DRUPAL_ROOT', getcwd());
  require_once './includes/bootstrap.inc';
  drupal_override_server_variables();
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
}

require_once dirname(dirname(__DIR__)). '/basefixtures/BasicTestCase.php';
require_once dirname(__DIR__) . '/MockDrupalTaxonomyFunctions.php';

define ('VOCAB1_VID', 789789789789123123);
define ('VOCAB2_VID', 489789789789123124);
define ('VOCAB1_MACHNAME', 'test_vocab_1');
define ('VOCAB2_MACHNAME', 'test_vocab_2');
define ('VOCAB1_TITLE', 'Test Taxonomy Vocab One');
define ('VOCAB2_TITLE', 'Test Taxonomy Vocab Two');

define ('TERM1_TID', 888889999999991111);
define ('TERM2_TID', 888889999999992222);
define ('TERM3_TID', 888889999999993333);
define ('TERM1_TITLE', 'Taxo test term 1');
define ('TERM2_TITLE', 'Taxo test two');
define ('TERM3_TITLE', 'Taxo test third');

define ('NODE1_NID', 334345555545555555);
define ('NODE2_NID', 111348885545555555);

class MockDrupalTaxonomyFunctionsTest extends \tdd7\testframework\BasicTestCase  {
  public function testAddingTestDataToTaxonomyIsReturned() {
    MockDrupalTaxonomyFunctions::ResetMockData();
    MockDrupalTaxonomyFunctions::AddMockTerm(0, TERM1_TID, TERM1_TITLE);
    MockDrupalTaxonomyFunctions::AddMockTerm(0, TERM2_TID, TERM2_TITLE);
    $term = MockDrupalTaxonomyFunctions::taxonomy_term_load(TERM2_TID);
    $this->assertEquals(TERM2_TITLE, $term->name);
  }

  public function testRetrievingDataByMockTaxonomy_get_treeFunction() {
    MockDrupalTaxonomyFunctions::ResetMockData();
    MockDrupalTaxonomyFunctions::AddMockTerm(1, TERM1_TID, TERM1_TITLE);
    MockDrupalTaxonomyFunctions::AddMockTerm(2, TERM2_TID, TERM2_TITLE);
    MockDrupalTaxonomyFunctions::AddMockTerm(3, TERM3_TID, TERM3_TITLE);
    $tree = MockDrupalTaxonomyFunctions::taxonomy_get_tree(2);
    $this->assertEquals(TERM2_TITLE, $tree[0]->name);

    $emptytree = MockDrupalTaxonomyFunctions::taxonomy_get_tree(8);
    $this->assertEmpty(0, $emptytree);
  }

  public function testTaxonomy_select_nodesReturnsEmptyArrayWithNoMockData() {
    MockDrupalTaxonomyFunctions::ResetMockData();
    $this->assertEquals(array(),MockDrupalTaxonomyFunctions::taxonomy_select_nodes(TERM3_TID));
  }

  public function testTaxonomy_select_nodesReturnsNodeMapFromMockData() {
    MockDrupalTaxonomyFunctions::ResetMockData();
    MockDrupalTaxonomyFunctions::AddMockTermToNode(TERM3_TID,NODE1_NID);
    $expected_result = array(NODE1_NID);
    $this->assertEquals($expected_result, MockDrupalTaxonomyFunctions::taxonomy_select_nodes(TERM3_TID));
    $this->assertEquals(array(),MockDrupalTaxonomyFunctions::taxonomy_select_nodes(TERM2_TID));
  }
  public function testTaxonomy_select_nodesReturnsSingleInstanceOfNodeWhenMappingMockData() {
    MockDrupalTaxonomyFunctions::ResetMockData();
    MockDrupalTaxonomyFunctions::AddMockTermToNode(TERM3_TID,NODE1_NID);
    MockDrupalTaxonomyFunctions::AddMockTermToNode(TERM3_TID,NODE1_NID);
    MockDrupalTaxonomyFunctions::AddMockTermToNode(TERM3_TID,NODE2_NID);
    $expected_result = array(NODE1_NID,NODE2_NID);
    $this->assertEquals($expected_result, MockDrupalTaxonomyFunctions::taxonomy_select_nodes(TERM3_TID));
  }

  /**
   * Call MockDrupalTaxonomyFunctions with non existing machine name to enforce
   *  returning FALSE when no such mock data exists.
   */
  public function testTaxonomy_vocabulary_machine_name_loadReturnsFalseWhenVocabIsNotFound() {
    $result = MockDrupalTaxonomyFunctions::taxonomy_vocabulary_machine_name_load('fake_machine_name_that_doesnt_exist');
    $this->assertFalse($result);
  }

  /**
   * Call MockDrupalTaxonomyFunctions with previously added machine name to
   *  and test that it returns the same element.
   */
  public function testTaxonomy_vocabulary_machine_name_loadReturnsSameNameAndVid() {
    MockDrupalTaxonomyFunctions::AddSimpleVocab(VOCAB1_VID,VOCAB1_MACHNAME, VOCAB1_TITLE);
    MockDrupalTaxonomyFunctions::AddSimpleVocab(VOCAB2_VID,VOCAB2_MACHNAME, VOCAB2_TITLE);
    $result = MockDrupalTaxonomyFunctions::taxonomy_vocabulary_machine_name_load(VOCAB1_MACHNAME);
    $this->assertNotEmpty($result);
    $this->assertEquals(VOCAB1_VID,      $result->vid);
    $this->assertEquals(VOCAB1_TITLE,    $result->title);
    $this->assertEquals(VOCAB1_MACHNAME, $result->name);
  }

  /**
   * Test that ResetMockData() removes Mock vocabs data.
   */
  public function testResetMockDataCleansMockVocab() {
    MockDrupalTaxonomyFunctions::AddSimpleVocab(VOCAB1_VID,VOCAB1_MACHNAME, VOCAB1_TITLE);
    MockDrupalTaxonomyFunctions::ResetMockData();
    $result = MockDrupalTaxonomyFunctions::taxonomy_vocabulary_machine_name_load(VOCAB1_MACHNAME);
    $this->assertFalse($result);
  }
}