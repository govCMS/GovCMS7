<?php
/** 
 * @file Test Drupal Database DatabaseConnection_unittest mock can update
 *  database rows.
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

class MockDatabaseTestInssertCase extends \PHPUnit_Framework_TestCase {
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
 }

  public function tearDown() {
    $this->db->resetTestData();
  }

  /**
   * Assert that our db_select returns the object it's supposed t.
   */
  public function testDb_insertReturnsObject() {
    $query = db_insert('foo');
    $this->assertInstanceOf('\tdd7\testframework\mocks\MockInsertQuery', $query);
  }

  public function testDB_insertSingle() {
    $fields = array(
      'id' => '42',
      'firstName' => 'Jane',
      'lastName' => 'Hill',
      'year' => 1956,
      'email' => 'jane@example.de.com',
    );
    $nid = db_insert(TABLE1)
      ->fields($fields)
      ->execute();

    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'year'))
      ->condition('id', 42)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals('Jane', $record->firstName);
    $this->assertEquals(1956, $record->year);
  }
}