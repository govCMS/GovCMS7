<?php
/**
 * @file Drupal Database layer mock functions and classes
 */

namespace tdd7\testframework\mocks;

require_once 'DatabaseSelect.php';
require_once 'DatabaseInsert.php';
require_once 'DatabaseUpdate.php';
require_once 'DatabaseDelete.php';
require_once 'DatabaseMockQuery.php';

/**
 * Returns a new mocked up SelectQuery object for the active database.
 *
 *
 * @param $table
 *   The base table for this query. May be a string or another SelectQuery
 *   object. If a query object is passed, it will be used as a subselect.
 * @param $alias
 *   The alias for the base table of this query.
 * @param $options
 *   An array of options to control how the query operates.
 *
 * @return SelectQuery
 *   A new SelectQuery object for this connection.
 */
function db_select($table, $alias = NULL, array $options = array()) {
  return \tdd7\testframework\mocks\DatabaseConnection_unittest::getInstance()->select($table, $alias, $options);
}

/**
 * Returns a new UpdateQuery object for the active database.
 *
 * @param $table
 *   The table to update.
 * @param $options
 *   An array of options to control how the query operates.
 *
 * @return UpdateQuery
 *   A new UpdateQuery object for this connection.
 */
function db_update($table, array $options = array()) {
  return \tdd7\testframework\mocks\DatabaseConnection_unittest::getInstance()->update($table, $options);
}


/**
 * Returns a new InsertQuery object for the active database.
 *
 * @param $table
 *   The table to update.
 * @param $options
 *   An array of options to control how the query operates.
 *
 * @return UpdateQuery
 *   A new UpdateQuery object for this connection.
 */
function db_insert($table, array $options = array()) {
  return \tdd7\testframework\mocks\DatabaseConnection_unittest::getInstance()->insert($table, $options);
}

/**
 * Returns a new MockDeleteQuery object for the active database.
 *
 * @param $table
 *   The table to delete from.
 * @param $options
 *   An array of options to control how the query operates.
 *
 * @return MockDeleteQuery
 *   A new MockDeleteQuery object for this connection.
 */
function db_delete($table, array $options = array()) {
  return \tdd7\testframework\mocks\DatabaseConnection_unittest::getInstance()->delete($table, $options);
}

class DatabaseConnection_unittest extends \DatabaseConnection {
  static $instance = null;

  private $data = array();

  function __construct($dsn, $username, $password, $driver_options = array()) {
  }

  public function databaseType() {
    return "mock_sql";
  }

  public function driver() {
    return "mock_sql";
  }

  public function mapConditionOperator($operator) {
  }

  public function nextId($existing_id = 0) {
  }

  public function queryRange($query, $from, $count, array $args = array(), array  $options = array()) {
  }

  public function queryTemporary($query,  array $args = array(), array $options = array()) {
  }

  public function select($table, $alias = NULL, array $options = array()) {
    return new MockSelectQuery($this, $table);
  }

  public function update($table, array $options = array()) {
    return new MockUpdateQuery($this, $table,$options);
  }

  public function insert($table, array $options = array()) {
    return new MockInsertQuery($this, $table,$options);
  }

  public function delete($table, array $options = array()) {
    return new MockDeleteQuery($this, $table,$options);
  }

  /**
   * Returns a staticly stored instance of this class. Creates a new instance
   *  if required.
   * @return DatabaseConnection_unittest
   */
  public static function getInstance() {
    if (DatabaseConnection_unittest::$instance == null) {
      DatabaseConnection_unittest::$instance = new DatabaseConnection_unittest('test_db','username','password');
    }
    return DatabaseConnection_unittest::$instance;
  }

  /**
   * Add test data to a table
   * @param type $table
   * @param array $data
   */
  public function addTestData($table, array $data) {
    $this->data[$table][] = $data;
  }

  /**
   * Returns test data for specified table. If no data is available, an empty
   *  array will be returned.
   * @param type $table
   * @return array Data added to test tables so far, may be empty.
   */
  public function &getTestData($table) {
    if (array_key_exists($table, $this->data)) {
      return $this->data[$table];
    }
    else {
      return array();
    }
  }

  /**
   * Replace all test data.
   */
  public function resetTestData() {
    $this->data = array();
  }
}


/**
 * Mock database return result
 */
class MockQueryResult {
  private $database;
  private $query;
  private $results;

  /**
   * Create a result set from the a mock database and query
   * @param \tdd7\testframework\mocks\DatabaseConnection_unittest $db
   * @param \tdd7\testframework\mocks\MockSelectQuery $qy
   * @param type $results Array of results MockSelectQuery execute()
   */
  function __construct(DatabaseConnection_unittest $db, MockSelectQuery $qy, $results) {
    $this->database = $db;
    $this->query    = $qy;
    $this->results  = $results;
  }

  /**
   * Returns a stdObject() pointing to the row of the next result
   * @return stdClass or FALSE
   */
  public function fetchObject() {
    if (!empty($this->results)) {
      $res = array_shift($this->results);
      return (object) $res;
    } else {
      return FALSE;
    }
  }

  /**
   * Returns a single field from the next record of a result set.
   *
   * @param int $index
   *   Column index of row
   *
   * @return mixed (string or numeric number)
   *   Value of the column
   */
  public function fetchField($index = 0) {
    $ret = FALSE;
    if (!empty($this->results)) {
      $res = array_shift($this->results);
      if ($index < count($res) && $index >= 0) {
        // Get all values with numeric index.
        $res = array_values($res);
        $ret = $res[$index];
      }
    }

    return $ret;
  }
}



