<?php

namespace tdd7\testframework\mocks;

require_once 'DatabaseMockQuery.php';

class MockSelectQuery extends MockQuery implements \SelectQueryInterface {
  private $database;
  private $tablename;
  private $order = array();

  private $countQuery;

  function __construct(DatabaseConnection_unittest $db, $tablename) {
    $this->database = $db;
    $this->tablename = $tablename;
    $this->countQuery = FALSE;
  }

  public function __clone() {
  }

  public function addExpression($expression, $alias = NULL, $arguments = array()) {
  }

  public function addField($table_alias, $field, $alias = NULL) {
  }

  public function addJoin($type, $table, $alias = NULL, $condition = NULL, $arguments = array()) {
  }

  public function addMetaData($key, $object) {
  }

  public function addTag($tag) {
  }

  public function arguments() {
  }

  public function compile(\DatabaseConnection $connection, \QueryPlaceholderInterface $queryPlaceholder) {
  }

  public function compiled() {
  }

  public function countQuery() {
    $this->countQuery = TRUE;
    return $this;
  }

  public function distinct($distinct = TRUE) {
    return $this;
  }

  public function exists(\SelectQueryInterface $select) {
  }

  public function extend($extender_name) {
  }

  public function fields($table_alias, array $fields = array()) {
    $this->fields[$table_alias] = $fields;
    return $this;
  }

  public function forUpdate($set = TRUE) {
  }

  public function getArguments(\QueryPlaceholderInterface $queryPlaceholder = NULL) {
  }

  public function &getExpressions() {
  }

  public function &getFields() {
  }

  public function &getGroupBy() {
  }

  public function getMetaData($key) {
  }

  public function &getOrderBy() {
  }

  public function &getTables() {
  }

  public function &getUnion() {
  }

  public function groupBy($field) {
  }

  public function hasAllTags() {
  }

  public function hasAnyTag() {
  }

  public function hasTag($tag) {
  }

  public function havingCondition($field, $value = NULL, $operator = NULL) {
  }

  public function innerJoin($table, $alias = NULL, $condition = NULL, $arguments = array()) {
  }

  public function isNotNull($field) {
  }

  public function isNull($field) {
  }

  public function isPrepared() {
  }

  public function join($table, $alias = NULL, $condition = NULL, $arguments = array()) {
  }

  public function leftJoin($table, $alias = NULL, $condition = NULL, $arguments = array()) {
  }

  public function nextPlaceholder() {
  }

  public function notExists(\SelectQueryInterface $select) {
  }

  public function orderBy($field, $direction = 'ASC') {
    // Only allow ASC and DESC, default to ASC.
    $direction = strtoupper($direction) == 'DESC' ? 'DESC' : 'ASC';
    $this->order[$field] = $direction;
    return $this;
  }

  public function orderRandom() {
  }

  public function preExecute(\SelectQueryInterface $query = NULL) {
  }

  public function range($start = NULL, $length = NULL) {
  }

  public function rightJoin($table, $alias = NULL, $condition = NULL, $arguments = array()) {
  }

  public function union(\SelectQueryInterface $query, $type = '') {
  }

  public function uniqueIdentifier() {
  }

  public function where($snippet, $args = array()) {
  }

  public function execute() {
    $results = array();
    foreach ($this->database->getTestData($this->tablename) as $row) {
      if ($this->confirmMatch($row)) {
        $results[] = $this->filterFields($this->tablename, $row);
      }
    }
    //Unsure what happens if multiple order by fields are defined.
    if (!empty($this->order)) {
      foreach ($this->order as $field => $direction) {
        usort($results, function ($a,$b) use ($field,$direction) {
          if($direction == 'ASC') {
            return strcmp($a[$field], $b[$field]);
          }
          else
          {
            return strcmp($b[$field], $a[$field]);
          }
        });
      }
    }
    if ($this->countQuery) {
      $results = array(array('count' => count($results)));
    }

    return new MockQueryResult($this->database, $this, $results);
  }
}
