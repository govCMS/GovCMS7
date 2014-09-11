<?php

/**
 * Represents a position in the wildcard tree, either at a leaf (candidate)
 * or at a node (wildcard).
 *
 * @property array $basicMethods
 * @property array $routeMethods
 * @property array $routes
 * @property array $descriptions
 */
class crumbs_Container_MultiWildcardDataOffset {

  /**
   * @var crumbs_Container_MultiWildcardData
   */
  protected $container;

  /**
   * @var string
   */
  protected $key;

  /**
   * @param crumbs_Container_MultiWildcardData $container
   * @param string $key
   *   Key identifying a position in the wildcard tree, e.g. 'menu.hierarchy.*'.
   */
  function __construct($container, $key) {
    $this->container = $container;
    $this->key = $key;
  }

  /**
   * @param string $key
   * @return mixed
   */
  function __get($key) {
    return $this->container->__get($key)->valueAtKey($this->key);
  }

  /**
   * @param string $key
   * @return array
   */
  function getAll($key) {
    return $this->container->__get($key)->getAll($this->key);
  }

  /**
   * @param string $key
   * @return array
   */
  function getAllMerged($key) {
    return $this->container->__get($key)->getAllMerged($this->key);
  }

}
