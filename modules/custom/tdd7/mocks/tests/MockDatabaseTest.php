<?php
/**
 * @file Test Drupal Database DatabaseConnection_unittest mock
 */

namespace tdd7\testframework\mocks;

if (!defined("DRUPAL_ROOT")) {
  define('DRUPAL_ROOT', getcwd());
  require_once './includes/bootstrap.inc';
  drupal_override_server_variables();
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
}
require_once dirname(__DIR__) . '/Database.inc';

define ('TABLE1', 'testMockTable1');
define ('TABLE2', 'testMockTable2');

class MockDatabaseTestCase extends \PHPUnit_Framework_TestCase {
  private $db;

  public function setUp() {
    $this->db = DatabaseConnection_unittest::getInstance();

    $this->db->addTestData(TABLE1, array(
      'id'        => 31,
      'firstName' => 'Hans',
      'lastName'  => 'Dülfer',
      'year'      => 1892,
      'email'     => 'hans@example.de.com',
    ));

    $this->db->addTestData(TABLE1, array(
      'id'        => 7854,
      'firstName' => 'Alex',
      'lastName'  => 'Honnold',
      'year'      => 1985,
      'email'     => 'alex@example.com',
    ));

    $this->db->addTestData(TABLE1, array(
      'id'        => 48091,
      'firstName' => 'Hans',
      'lastName'  => 'Florine',
      'year'      => 1964,
      'email'     => 'hans@example.com',
    ));

    $this->db->addTestData(TABLE1, array(
      'id'        => 2391,
      'firstName' => 'Yuji',
      'lastName'  => 'Hirayama',
      'year'      => 1969,
      'email'     => 'yuji@example.jp',
    ));

    $this->db->addTestData(TABLE1, array(
      'id'        => 7593,
      'firstName' => 'Alex',
      'lastName'  => 'Puccio',
      'year'      => 1989,
      'email'     => 'alex.puccio@example.com',
    ));

    $this->db->addTestData(TABLE1, array(
      'id'        => 7981,
      'firstName' => 'Daniel',
      'lastName'  => 'Woods',
      'year'      => 1989,
      'email'     => 'daniel.woods@example.com',
    ));
  }

  public function tearDown() {
    $this->db->resetTestData();
  }

  public function testAddEmptyData() {
    // Use local copy for this test becase we are corrupting it with empty data.
    $db = new DatabaseConnection_unittest('', '', '');

    $this->assertEmpty($db->getTestData(TABLE1));
    $db->addTestData(TABLE1, array());
    $this->assertCount(1, $db->getTestData(TABLE1));

    // Assert that data only is stored in the correct 'table'.
    $this->assertEmpty($db->getTestData(TABLE2));
  }

  // Test that a simple record request by unique ID works
  public function testGetSingleRecord() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'year'))
      ->condition('id', 2391)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals('Yuji', $record->firstName);
    $this->assertEquals(1969,   $record->year);

    // Check that only one record was returned.
    $this->assertFalse($res->fetchObject());
  }

  // Test that a simple .* record request by unique ID works
  public function testGetSingleRecordWithAllFields() {
    $res = db_select(TABLE1)
      ->fields(TABLE1)
      ->condition('id', 7981)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals(7981,                       $record->id);
    $this->assertEquals('Daniel',                   $record->firstName);
    $this->assertEquals('Woods',                    $record->lastName);
    $this->assertEquals(1989,                       $record->year);
    $this->assertEquals('daniel.woods@example.com', $record->email);

    // Check that only one record was returned.
    $this->assertFalse($res->fetchObject());
  }

  // Test that a simple record unique two overlapping id
  public function testSingleMultiMatchRecord() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'firstName', 'lastName'))
      ->condition('firstName', 'Alex')
      ->condition('year', 1989)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals(7593,     $record->id);
    $this->assertEquals('Alex',   $record->firstName);
    $this->assertEquals('Puccio', $record->lastName);

    // Check that only one record was returned.
    $this->assertFalse($res->fetchObject());
  }

  // Test that we get all instances of records that match
  public function testMulipleReturnRecord() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'firstName', 'lastName'))
      ->condition('firstName', 'Alex')
      ->execute();

    $record = $res->fetchObject();
    $this->assertEquals(7854,     $record->id);
    $record = $res->fetchObject();
    $this->assertEquals(7593,     $record->id);

    // Check that only one record was returned.
    $this->assertFalse($res->fetchObject());
  }

  /**
   * Test that we can retrieve only the fields we want, using a different field
   * to retreieve.
   */
  public function testCorrectFieldsReturned() {
        $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'lastName'))
      ->condition('year', 1964)
      ->execute();
    $record = $res->fetchObject();
    $this->assertObjectHasAttribute('firstName', $record);
    $this->assertEquals('Hans',      $record->firstName);
    $this->assertObjectHasAttribute('lastName', $record);
    $this->assertEquals('Florine',   $record->lastName);

    $this->assertObjectNotHasAttribute('year', $record);

    $this->assertFalse($res->fetchObject());
  }

  // Test that the LIKE keyword works
  public function testLikeMatches() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'lastName'))
      ->condition('email', '%example.com', 'LIKE')
      ->execute();

    $record = $res->fetchObject();
    $this->assertEquals(7854,      $record->id);
    $this->assertEquals('Honnold',   $record->lastName);
    $record = $res->fetchObject();
    $this->assertEquals(48091,      $record->id);
    $this->assertEquals('Florine',  $record->lastName);
    $record = $res->fetchObject();
    $this->assertEquals(7593,     $record->id);
    $this->assertEquals('Puccio', $record->lastName);
    $record = $res->fetchObject();
    $this->assertEquals(7981,      $record->id);
    $this->assertEquals('Woods',  $record->lastName);
    $this->assertFalse($res->fetchObject());
  }

  // Test that the LIKE keyword works with single chars
  public function testLikeSingleMatches() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'lastName'))
      ->condition('email', '%example.??', 'LIKE')
      ->execute();

    $record = $res->fetchObject();
    $this->assertEquals(2391,       $record->id);
    $this->assertEquals('Hirayama', $record->lastName);
    $this->assertFalse($res->fetchObject());
  }

  // Test that the Like and == conditions work properly together
  public function testCombinedConditonMatches() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'lastName'))
      ->condition('email',    '%@example.com', 'LIKE')
      ->condition('lastName', '?????',         'LIKE')
      ->condition('year',     1989,            '==')
      ->execute();

    $record = $res->fetchObject();
    $this->assertEquals(7981,       $record->id);
    $this->assertEquals('Woods',    $record->lastName);
    $this->assertObjectNotHasAttribute('firstName', $record);
    $this->assertObjectNotHasAttribute('year', $record);
    $this->assertFalse($res->fetchObject());
  }

  // Test that adding a second condition on the same field doesn't overwrite the
  // older condition.
  public function testSelectMultipleConditionsSingleField() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'lastName'))
      ->condition('email',    '%@example.de.com', 'LIKE')
      ->condition('email',    'hans%', 'LIKE')
      ->execute();

    $record = $res->fetchObject();
    $this->assertEquals(31,       $record->id);
    $this->assertEquals('Dülfer', $record->lastName);
    $this->assertFalse($res->fetchObject());
  }

  /**
   * test fetchField returns a single field from the next record.
   */
  public function testFetchFieldReturnsSingleFieldFromNextRecord() {
    $result = db_select(TABLE1)
      ->fields(TABLE1, array('id'))
      ->execute()
      ->fetchField();
    $this->assertEquals(31, $result);
  }

  /**
   * test countQuery() returns expected output.
   */
  public function testCountQuery() {
    $result = db_select(TABLE1)
      ->fields(TABLE1, array('id'))
      ->condition('id', 7593)
      ->countQuery()
      ->execute()
      ->fetchField();

    $this->assertEquals(1, $result);
  }

  // Test that multiple conditionals default to using AND.
  public function testMultiConditionalUsesBooleanAndToMatchRecord() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'firstName', 'lastName'))
      ->condition('firstName', 'Alex')
      ->condition('year', 1892)
      ->execute();
    $this->assertFalse($res->fetchObject());
  }

  /**
  * Test the orde of the results comes back as requested.
  */
  public function testOrderSelect() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'firstName', 'lastName'))
      ->condition('firstName', 'Alex')
      ->orderBy('id','ASC')
      ->execute();

    $record = $res->fetchObject();
    $this->assertEquals(7593,     $record->id);
    $record = $res->fetchObject();
    $this->assertEquals(7854,     $record->id);

    // Check that only one record was returned.
    $this->assertFalse($res->fetchObject());
  }

  // Test that we get all instances of records that match
  public function testOrderSelectDESC() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id', 'firstName', 'lastName'))
      ->condition('firstName', 'Alex')
      ->orderBy('id','DESC')
      ->execute();

    $record = $res->fetchObject();
    $this->assertEquals(7854,     $record->id);
    $record = $res->fetchObject();
    $this->assertEquals(7593,     $record->id);

    // Check that only one record was returned.
    $this->assertFalse($res->fetchObject());
  }

}
