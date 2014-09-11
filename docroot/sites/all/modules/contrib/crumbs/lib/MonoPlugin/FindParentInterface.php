<?php

interface crumbs_MonoPlugin_FindParentInterface extends crumbs_MonoPlugin {

  /**
   * Find candidates for the parent path.
   *
   * @param string $path
   *   The path that we want to find a parent for.
   * @param array $item
   *   Item as returned from crumbs_get_router_item()
   *
   * @return string
   *   Parent path candidate.
   */
  function findParent($path, $item);
}