<?php

/**
 * @property crumbs_Container_WildcardData|array $basicMethods
 * @property crumbs_Container_WildcardData|array $routeMethods
 * @property crumbs_Container_WildcardData|array $routes
 * @property crumbs_Container_WildcardData|array $descriptions
 */
class crumbs_Container_MultiWildcardData implements ArrayAccess, IteratorAggregate {

  /**
   * @var array
   */
  protected $keys;

  /**
   * @var array
   */
  protected $containers = array();

  /**
   * @param array $keys
   */
  function __construct($keys) {
    $this->keys = $keys;
  }

  /**
   * @param string $key
   * @return crumbs_Container_WildcardData
   */
  function __get($key) {
    if (!isset($this->containers[$key])) {
      $this->containers[$key] = new crumbs_Container_WildcardData();
    }
    return $this->containers[$key];
  }

  /**
   * @param string $key
   * @param array $data
   */
  function __set($key, $data) {
    $this->containers[$key] = new crumbs_Container_WildcardData($data);
  }

  /**
   * @return crumbs_Container_MultiWildcardDataIterator
   */
  function getIterator() {
    return new crumbs_Container_MultiWildcardDataIterator($this, $this->keys);
  }

  /**
   * @param string $key
   * @return crumbs_Container_MultiWildcardDataOffset
   */
  function offsetGet($key) {
    return new crumbs_Container_MultiWildcardDataOffset($this, $key);
  }

  /**
   * @param string $key
   * @param mixed $value
   * @throws Exception
   */
  function offsetSet($key, $value) {
    throw new Exception("offsetSet not supported.");
  }

  /**
   * @param string $key
   * @return bool
   */
  function offsetExists($key) {
    return isset($this->keys[$key]);
  }

  /**
   * @param string $key
   * @throws Exception
   */
  function offsetUnset($key) {
    throw new Exception("offsetUnset not supported.");
  }
}
