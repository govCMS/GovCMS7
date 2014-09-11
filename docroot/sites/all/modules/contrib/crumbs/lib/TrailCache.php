<?php

/**
 * Class crumbs_Container_LazyTrails
 */
class crumbs_TrailCache {

  /**
   * @var array
   *   Cached data
   */
  protected $data = array();

  /**
   * @var crumbs_TrailFinder
   */
  protected $source;

  /**
   * @todo Add an interface for $source.
   *   Don't restrict it to crumbs_TrailFinder.
   *
   * @param crumbs_TrailFinder $source
   */
  function __construct($source) {
    $this->source = $source;
  }

  /**
   * @param $path
   * @return mixed
   */
  function getForPath($path) {
    if (!isset($this->data[$path])) {
      $this->data[$path] = $this->source->getForPath($path);
    }
    return $this->data[$path];
  }
}
