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

class MockDatabaseTestUpdateCase extends \PHPUnit_Framework_TestCase {
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
  }

  public function tearDown() {
    $this->db->resetTestData();
  }

  /**
   * Assert that our db_select returns the object it's supposed t.
   */
  public function testDb_updateReturnsObject() {
    $query = db_update('foo');
    $this->assertInstanceOf('\tdd7\testframework\mocks\MockUpdateQuery', $query);
  }

  public function testDB_updateSingleRow() {
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'year'))
      ->condition('id', 2391)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals('Yuji', $record->firstName);
    $this->assertEquals(1969,   $record->year);

    $update = db_update(TABLE1)
      ->fields(array('year' => 1970))
      ->condition('id',2391)
      ->execute();

    $this->assertEquals(1,$update);

    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'year'))
      ->condition('id', 2391)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals('Yuji', $record->firstName);
    $this->assertEquals(1970,   $record->year);

    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'year'))
      ->condition('id', 48091)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals('Hans', $record->firstName);
    $this->assertEquals(1964,   $record->year);
  }

  public function testDB_updateFieldthatDoesntExist() {

    $update = db_update(TABLE1)
      ->fields(array('year' => 1971,'foo' => 'Bar'))
      ->condition('id',2391)
      ->execute();

    $this->assertEquals(1,$update);

    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'year','foo'))
      ->condition('id', 2391)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals('Yuji', $record->firstName);
    $this->assertEquals(1971,   $record->year);
    /**
     * @TODO: This is wrong. When the following issue is fixed, the function
     * assertObjectHasAttribute should be changed to assertObjectNotHasAttribute
     * and an Exception attached to the execute() function run on non-existent
     * columns.
     * http://git.syd.catalyst-au.net/edward/tdd7/issues/2
     */
    $this->assertObjectHasAttribute('foo',$record);
  }

  public function testDB_updateMultipleRows() {
    // Update the birthdate of all people called Hans to 1970
    $update = db_update(TABLE1)
      ->fields(array('year' => 1970))
      ->condition('firstName','Hans')
      ->execute();

    $this->assertEquals(2,$update);

    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'year','id'))
      ->condition('firstName', 'Hans')
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals('Hans', $record->firstName);
    $this->assertEquals(31,   $record->id);
    $this->assertEquals(1970,   $record->year);
    $record = $res->fetchObject();
    $this->assertEquals('Hans', $record->firstName);
    $this->assertEquals(48091,     $record->id);
    $this->assertEquals(1970,   $record->year);

    // Confirm that no other records were edited.
    $res = db_select(TABLE1)
      ->fields(TABLE1, array('firstName', 'year'))
      ->condition('id', 7593)
      ->execute();
    $record = $res->fetchObject();
    $this->assertEquals('Alex', $record->firstName);
    $this->assertEquals(1989,   $record->year);
  }

}