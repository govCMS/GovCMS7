<?php

/**
 * This class uses the PluginOperation pattern, but it does not implement any of
 * the PluginOperation interfaces. This is because it is not supposed to be used
 * with the PluginEngine, but rather from a custom function (see above).
 */
class crumbs_PluginOperation_describe {

  //                                                              Collected data
  // ---------------------------------------------------------------------------

  /**
   * @var array
   */
  protected $keys = array('*' => TRUE);

  /**
   * @var array
   */
  protected $keysByPlugin = array();

  /**
   * @var string[][]
   *   Format: $[$key][] = $description
   */
  private $descriptions = array();

  //                                                             State variables
  // ---------------------------------------------------------------------------

  /**
   * @var string
   *   Temporary variable.
   */
  protected $pluginKey;

  /**
   * @var crumbs_InjectedAPI_describeMonoPlugin
   */
  protected $injectedAPI_mono;

  /**
   * @var crumbs_InjectedAPI_describeMultiPlugin
   */
  protected $injectedAPI_multi;

  /**
   * The constructor.
   */
  function __construct() {
    $this->injectedAPI_mono = new crumbs_InjectedAPI_describeMonoPlugin($this);
    $this->injectedAPI_multi = new crumbs_InjectedAPI_describeMultiPlugin($this);
  }

  /**
   * @param crumbs_PluginInterface $plugin
   * @param string $plugin_key
   */
  function invoke($plugin, $plugin_key) {
    $this->pluginKey = $plugin_key;

    if ($plugin instanceof crumbs_MonoPlugin) {
      $result = $plugin->describe($this->injectedAPI_mono);
      if (is_string($result)) {
        $this->setTitle($result);
      }
    }
    elseif ($plugin instanceof crumbs_MultiPlugin) {
      $result = $plugin->describe($this->injectedAPI_multi);
      if (is_array($result)) {
        foreach ($result as $key_suffix => $title) {
          $this->addRule($key_suffix, $title);
        }
      }
    }
  }

  /**
   * To be called from crumbs_InjectedAPI_describeMultiPlugin::addRule()
   *
   * @param string $key_suffix
   * @param string $title
   */
  function addRule($key_suffix, $title) {
    $key = $this->pluginKey . '.' . $key_suffix;
    $this->_addRule($key);
    $this->_addDescription($key, $title );
  }

  /**
   * Add a description at an arbitrary wildcard key.
   * To be called from crumbs_InjectedAPI_describeMultiPlugin::addDescription()
   *
   * @param string $description
   * @param string $key_suffix
   */
  function addDescription($description, $key_suffix) {
    if (isset($key_suffix)) {
      $key = $this->pluginKey . '.' . $key_suffix;
    }
    else {
      $key = $this->pluginKey;
    }
    $this->_addDescription($key, $description);
  }

  /**
   * @param string $key
   * @param string $description
   */
  protected function _addDescription($key, $description) {
    $this->descriptions[$key][] = $description;
  }

  /**
   * To be called from crumbs_InjectedAPI_describeMonoPlugin::setTitle()
   *
   * @param string $title
   */
  function setTitle($title) {
    $this->_addRule($this->pluginKey);
    $this->_addDescription($this->pluginKey, $title);
  }

  /**
   * @param string $key
   */
  protected function _addRule($key) {
    $fragments = explode('.', $key);
    $partial_key = array_shift($fragments);
    while (TRUE) {
      if (empty($fragments)) break;
      $wildcard_key = $partial_key .'.*';
      $this->keys[$wildcard_key] = TRUE;
      $this->keysByPlugin[$this->pluginKey][$wildcard_key] = TRUE;
      $partial_key .= '.'. array_shift($fragments);
    }
    $this->keys[$key] = $key;
    $this->keysByPlugin[$this->pluginKey][$key] = $key;
  }

  /**
   * @return array
   */
  function getKeys() {
    return $this->keys;
  }

  /**
   * @return array
   */
  function getKeysByPlugin() {
    return $this->keysByPlugin;
  }

  /**
   * @param string $key
   * @param int $weight
   */
  function setDefaultWeight($key, $weight) {
    $this->keys[$key] = $key;
  }

  /**
   * @return crumbs_Container_MultiWildcardData
   */
  function collectedInfo() {
    $container = new crumbs_Container_MultiWildcardData($this->keys);
    $container->__set('key', $this->keys);
    $container->descriptions = $this->descriptions;
    return $container;
  }
}
