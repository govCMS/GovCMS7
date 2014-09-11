<?php

class crumbs_Container_WildcardData {

  /**
   * @var array
   */
  protected $data;

  /**
   * @var mixed
   */
  protected $fallback;

  /**
   * @param array $data
   *   Array keyed with wildcard keys.
   */
  function __construct(array $data = array()) {
    $this->data = $data;
    $this->fallback = isset($this->data['*']) ? $this->data['*'] : NULL;
  }

  /**
   * Determine the values for the key and all wildcard parents.
   *
   * @param string $key
   *   The key
   *
   * @return array
   *   The values, e.g.
   *     aaa.bbb.ccc.ddd => 5
   *     aaa.bbb.ccc.* => 77
   *     aaa.* => 21
   *     * => 9
   */
  function getAll($key) {
    $fragments = explode('.', $key);
    $partial_key = array_shift($fragments);
    $values = array();
    while (!empty($fragments)) {
      $wildcard_key = $partial_key . '.*';
      if (isset($this->data[$wildcard_key])) {
        $values[$wildcard_key] = $this->data[$wildcard_key];
      }
      $partial_key .= '.'. array_shift($fragments);
    }
    if (isset($this->data[$key])) {
      $values[$key] = $this->data[$key];
    }
    return array_reverse($values);
  }

  /**
   * If the values are arrays, then this one merges the array values for the key
   * and all wildcard parents.
   *
   * @param string $key
   *   The key
   *
   * @return array
   *   The merged arrays, e.g.
   *   Starting from
   *     aaa.bbb.ccc.ddd => array(5, 55)
   *     aaa.bbb.ccc.* => array(77)
   *     aaa.* => array(21)
   *     * => array(9, 99, 999)
   *  Merged:
   *     array(5, 55, 77, 21, 9, 99, 999)
   */
  function getAllMerged($key) {
    $merged = array();
    foreach ($this->getAll($key) as $values) {
      if (is_array($values)) {
        $merged = array_merge($merged, $values);
      }
    }
    return $merged;
  }

  /**
   * Determine the value for the rule specified by the key.
   *
   * @param string $key
   *   Key that we are looking for.
   *
   * @return mixed
   *   The value for this key.
   */
  function valueAtKey($key) {
    if (isset($this->data[$key])) {
      // Look for explicit setting.
      return $this->data[$key];
    }
    // Try wildcards.
    return $this->wildcardValue($key);
  }

  /**
   * Helper: Actually build the prefixed container.
   *
   * @param string $prefix
   *   Prefix, as above.
   *
   * @return crumbs_Container_WildcardData
   *   The prefixed container.
   */
  protected function buildPrefixedData($prefix) {
    $data = array();
    $k = strlen($prefix);
    $data[''] = $data['*'] = $this->wildcardValue($prefix);
    if (isset($this->data[$prefix])) {
      $data[''] = $this->data[$prefix];
    }
    if (isset($this->data[$prefix .'.*'])) {
      $data['*'] = $this->data[$prefix .'.*'];
    }
    foreach ($this->data as $key => $value) {
      if (strlen($key) > $k && substr($key, 0, $k+1) === ($prefix .'.')) {
        $data[substr($key, $k+1)] = $value;
      }
    }
    return $data;
  }

  /**
   * Helper: Resolve wildcards..
   *
   * @param string $key
   *   Key that we are looking for.
   *
   * @return mixed
   *   The value for this key.
   */
  protected function wildcardValue($key) {
    $fragments = explode('.', $key);
    $partial_key = array_shift($fragments);
    $value = $this->fallback;
    while (!empty($fragments)) {
      if (isset($this->data[$partial_key .'.*'])) {
        $value = $this->data[$partial_key .'.*'];
      }
      $partial_key .= '.'. array_shift($fragments);
    }
    return $value;
  }
}
