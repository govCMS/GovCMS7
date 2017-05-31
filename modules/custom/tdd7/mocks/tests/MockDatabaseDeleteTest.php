<?php
/**
 * @file Test Drupal Database DatabaseConnection_unittest mock can delete rows.
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

class MockDatabaseDeleteTestCase extends \PHPUnit_Framework_TestCase {
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

  public function testDeleteReturnsObject() {
    $query = db_delete('foo');
    $this->assertInstanceOf('\tdd7\testframework\mocks\MockDeleteQuery', $query);
  }

  public function testDeleteSingleRow() {
    $query = db_delete(TABLE1);
    $query->condition('id', 7981);
    $delete = $query->execute();

    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName'))
      ->condition('id', 7981)
      ->execute();

    // Assert empty record.
    $record = $res->fetchObject();
    $this->assertEquals('', $record->firstName);
    // Assert 1 row deleted.
    $this->assertEquals(1, $delete);
  }

  public function testDeleteMultipleRows() {
    $query = db_delete(TABLE1);
    $query->condition('firstName', 'Alex');
    $delete = $query->execute();

    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName'))
      ->condition('id', 7593)
      ->condition('id', 7854)
      ->execute();

    // Assert empty record.
    $record = $res->fetchObject();
    $this->assertEquals('', $record->firstName);
    // Assert 2 rows deleted.
    $this->assertEquals(2, $delete);
  }

  public function testDeleteWholeTable() {
    //  Find out the total number of original records
    $count = db_select(TABLE1)->countQuery()->execute()->fetchField();

    // Delete all from TABLE1
    $query = db_delete(TABLE1);
    $delete = $query->execute();

    // Select all from TABLE1
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName'))
      ->execute();

    // Assert empty record.
    $record = $res->fetchObject();
    $this->assertEquals('', $record->firstName);
    // Assert all rows deleted.
    $this->assertEquals($count, $delete);
  }

  /**
   * Test that deletes using two conditionals on two different columns works
   *  as a boolean AND.
   */
  public function testDeleteUsingConditionalTwice() {
    $query = db_delete(TABLE1);
    $query->condition('firstName', 'Alex');
    $query->condition('year',      1989);
    $delete = $query->execute();

    $res = db_select(TABLE1)
      ->fields(TABLE1, array('id'))
      ->condition('firstName', 'Alex')
      ->execute();

    // Assert that Alex Honnold (id 7854) is still in the DB
    $record = $res->fetchObject();
    $this->assertEquals(7854, $record->id);
    $this->assertEquals(1, $delete);
  }
}
