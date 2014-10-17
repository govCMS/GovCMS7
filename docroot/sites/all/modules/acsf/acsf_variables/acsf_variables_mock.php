<?php

/**
 * @file
 * Mocks the acsf_variables interface for testing.
 */

/**
 * Mocks acsf_vget_group for testing.
 */
function acsf_vget_group($group, $default = array()) {
  $return = $default;
  foreach (acsf_variable_storage() as $name => $data) {
    if (isset($data['group']) && $data['group'] == $group) {
      $return[$name] = $data['value'];
    }
  }

  return $return;
}

/**
 * Mocks acsf_vget for testing.
 */
function acsf_vget($name, $default = NULL) {
  $storage = acsf_variable_storage();

  if (isset($storage[$name]['value'])) {
    return $storage[$name]['value'];
  }

  return $default;
}

/**
 * Mocks acsf_vset for testing.
 */
function acsf_vset($name, $value, $group = NULL) {
  acsf_variable_storage($name, $value, $group);
}

/**
 * Mocks acsf_vdel for testing.
 */
function acsf_vdel($name) {
  acsf_variable_storage($name, NULL, NULL, TRUE);
}

/**
 * Creates an in-memory storage for acsf_variables to simulate a db.
 *
 * @param string $name
 *   The name of the variable to store.
 * @param mixed $value
 *   The value of the variable to store.
 * @param string $group
 *   The group name of the variable to store.
 * @param bool $delete
 *   Whether or not to delete the specified variable.
 */
function acsf_variable_storage($name = NULL, $value = NULL, $group = NULL, $delete = FALSE) {
  static $storage;

  if (empty($storage)) {
    $storage = array();
  }

  if (isset($value)) {
    $storage[$name] = array(
      'value' => $value,
    );
  }

  if (!empty($group)) {
    $storage[$name]['group'] = $group;
  }

  if ($delete) {
    unset($storage[$name]);
  }

  return $storage;
}
