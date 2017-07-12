<?php

namespace tdd7\example;

/**
 * Return all active people with a matching last name.
 * 
 * @param string $last_name;
 *
 * @return array
 *  An array of matching record objects with id, first name, last name and
 *  student ID.
 */
function search_by_last_name($last_name) {
  $res = db_select('students')
    ->fields('students', array('id', 'lastName'))
    ->condition('lastName', $last_name)
    ->execute();

  $results = array();
  while ($record = $res->fetchObject()) {
    $results[] = $record;
  }
  return $results;
}