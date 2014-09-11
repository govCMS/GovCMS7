<?php

class crumbs_MultiPlugin_EntityParent extends crumbs_MultiPlugin_EntityFindSomething implements crumbs_MultiPlugin_FindParentInterface {

  /**
   * {@inheritdoc}
   */
  function findParent($path, $item) {
    return $this->find($path, $item);
  }
}
