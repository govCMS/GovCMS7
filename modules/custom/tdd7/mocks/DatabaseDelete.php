<?php

namespace tdd7\testframework\mocks;

require_once 'DatabaseMockQuery.php';

/**
 * General class for an abstracted INSERT query.
 */
class MockDeleteQuery extends MockQuery {

  private $tablename;
  private $database;

  /**
   * The condition object for this query.
   *
   * Condition handling is handled via composition.
   *
   * @var DatabaseCondition
   */
  protected $condition;

  function __construct(DatabaseConnection_unittest $db, $tablename) {
    $this->database = $db;
    $this->tablename = $tablename;
  }

  /**
   * Executes the DELETE query.
   *
   * @return
   *   The number of rows affected by the delete.
   */
  public function execute() {
    $results = array();
    $tabledata = &$this->database->getTestData($this->tablename);
    $rows_deleted = 0;
    foreach ($tabledata as $row_id => &$row) {
      if ($this->confirmMatch($row)) {
        unset($tabledata[$row_id]);
        $rows_deleted++;
      }
    }

    return $rows_deleted;
  }
}
