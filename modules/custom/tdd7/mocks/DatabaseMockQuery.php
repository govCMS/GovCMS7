<?php

namespace tdd7\testframework\mocks;

class MockQuery {
  protected $conditions;
  protected $fields;

  public function condition($field, $value = NULL, $operator = NULL) {
    if (empty($operator)) {
      $operator = '=';
    }
    $this->conditions[] = array('field' => $field, 'value' => $value, 'operator' => $operator);
    return $this;
  }

  public function &conditions() {
  }

  /**
   * Tests if $row matches SQL LIKE $key
   * @param $row Value to test against
   * @param $key Search string: eg; '%test%';
   * @return boolean TRUE if $row matches $key
   */
  protected function confirmLikeRow($row, $key) {
    $test_str = str_replace(
      array('%%', '%', '?'),
      array('%', '.*', '.'),
      $key);
    $test_str = "/^{$test_str}$/";
    $result = preg_match($test_str, $row);
    return (bool)$result;
  }

  /**
   * Ugly function decide if fields match conditons or not
   */
  protected function confirmMatch($row) {
  if(!isset($this->conditions)) {
    return TRUE;
  }
    foreach ($this->conditions as $cond) {
      $field = $cond['field'];
      switch ($cond['operator']) {
        case null :
        case '='  :
        case '==' :
          if ($row[$field] != $cond['value']) {
            return FALSE;
          }
          break;
        case 'LIKE':
          if ($this->confirmLikeRow($row[$field], $cond['value']) == FALSE) {
            return FALSE;
          }
          break;
        case 'IN':
          if(!in_array($row[$field],$cond['value'])) {
            return FALSE;
          }

        default:
          break;
      }
    }
    return TRUE;
  }

  /**
   * Filters the given row down to only the fields expected. If the fields are
   * not supplied, they a null value will be created. If an empty array has been
   * supplied for fields, then all fields will be returned.
   * @param array $row
   * @return array The same row, with only the fields expected
   */
  protected function filterFields($tablename, array $row) {
    if (empty($this->fields[$tablename])) {
      return $row;
    }
    $new = array();
    foreach ($this->fields[$tablename] as $field) {
      if (array_key_exists($field, $row)) {
        $new[$field] = $row[$field];
      }
    }
    return $new;
  }
}
