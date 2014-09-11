<?php

class crumbs_MonoPlugin_ParentPathCallback implements crumbs_MonoPlugin_FindParentInterface {

  /**
   * @var callback
   */
  protected $callback;

  /**
   * @var string
   */
  protected $module;

  /**
   * @var string
   */
  protected $key;

  /**
   * @param callback $callback
   * @param string $module
   * @param string $key
   */
  function __construct($callback, $module, $key) {
    $this->callback = $callback;
    $this->module = $module;
    $this->key = $key;
  }

  /**
   * @return string[]
   *   Names of properties that should be remembered on serialize().
   *   It should be noted that "callback" is not one of them, because this could
   *   be an anonymous function.
   */
  function __sleep() {
    return array('module', 'key');
  }

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t('Callback result.'), t('Parent'));
  }

  /**
   * {@inheritdoc}
   */
  function findParent($path, $item) {
    if (!isset($this->callback)) {
      // Restore the callback after serialization.
      $this->callback = crumbs()->callbackRestoration->restoreCallback($this->module, $this->key, 'routeParent');
    }
    if (!empty($this->callback)) {
      return call_user_func($this->callback, $path, $item);
    }

    return NULL;
  }

}
