<?php


/**
 * Injected API object for the describe() method of multi plugins.
 */
class crumbs_InjectedAPI_describeMultiPlugin {

  /**
   * @var crumbs_PluginOperation_describe
   */
  protected $pluginOperation;

  /**
   * @param crumbs_PluginOperation_describe $plugin_operation
   */
  function __construct($plugin_operation) {
    $this->pluginOperation = $plugin_operation;
  }

  /**
   * @param string $key_suffix
   * @param bool $title
   */
  function addRule($key_suffix, $title = TRUE) {
    $this->pluginOperation->addRule($key_suffix, $title);
  }

  /**
   * @param string $key_suffix
   * @param string $title
   * @param string $label
   */
  function ruleWithLabel($key_suffix, $title, $label) {
    $this->addRule($key_suffix, t('!key: !value', array(
      '!key' => $label,
      '!value' => $title,
    )));
  }

  /**
   * @param string $description
   * @param string $key_suffix
   */
  function addDescription($description, $key_suffix = '*') {
    $this->pluginOperation->addDescription($description, $key_suffix);
  }

  /**
   * @param array $paths
   * @param string $key_suffix
   *
   * @deprecated
   *   This method has no effect.
   */
  function setRoutes(array $paths, $key_suffix = '*') {
    // This method has no effect.
  }

  /**
   * @param string $description
   * @param string $label
   * @param string $key_suffix
   */
  function descWithLabel($description, $label, $key_suffix = '*') {
    $this->addDescription(t('!key: !value', array(
      '!key' => $label,
      '!value' => $description,
    )), $key_suffix);
  }
}
