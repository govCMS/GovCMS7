<?php

class crumbs_MultiPlugin_EntityTitle extends crumbs_MultiPlugin_EntityFindSomething implements crumbs_MultiPlugin_FindTitleInterface {

  /**
   * {@inheritdoc}
   */
  function findTitle($path, $item) {
    return $this->find($path, $item);
  }
}
