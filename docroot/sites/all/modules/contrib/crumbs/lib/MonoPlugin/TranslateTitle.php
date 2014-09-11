<?php

class crumbs_MonoPlugin_TranslateTitle implements crumbs_MonoPlugin_FindTitleInterface {

  /**
   * @var string
   */
  protected $title;

  /**
   * @param string $title
   */
  function __construct($title) {
    $this->title = $title;
  }

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel("t('" . $this->title . "')", t('Title'));
  }

  /**
   * {@inheritdoc}
   */
  function findTitle($path, $item) {
    return t($this->title);
  }
}