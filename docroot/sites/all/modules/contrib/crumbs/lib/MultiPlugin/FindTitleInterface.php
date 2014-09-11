<?php

interface crumbs_MultiPlugin_FindTitleInterface extends crumbs_MultiPlugin {

  /**
   * Find candidates for the parent path.
   *
   * @param string $path
   *   The path that we want to find a parent for.
   * @param array $item
   *   Item as returned from crumbs_get_router_item()
   *
   * @return string[]
   *   Title candidates
   */
  function findTitle($path, $item);
}
