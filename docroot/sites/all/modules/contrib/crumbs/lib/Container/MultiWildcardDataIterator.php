<?php

class crumbs_Container_MultiWildcardDataIterator extends ArrayIterator {

  /**
   * @var crumbs_Container_MultiWildcardData
   */
  protected $container;

  /**
   * @param crumbs_Container_MultiWildcardData $container
   * @param array $keys
   */
  function __construct($container, array $keys) {
    $this->container = $container;
    parent::__construct($keys);
  }

  /**
   * @return crumbs_Container_MultiWildcardDataOffset
   */
  function current() {
    return new crumbs_Container_MultiWildcardDataOffset($this->container, $this->key());
  }
}
