<?php

class crumbs_MonoPlugin_SkipItem implements crumbs_MonoPlugin_FindTitleInterface {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->setTitle('Skip this breadcrumb link.');
  }

  /**
   * {@inheritdoc}
   */
  function findTitle($path, $item) {
    return FALSE;
  }
}