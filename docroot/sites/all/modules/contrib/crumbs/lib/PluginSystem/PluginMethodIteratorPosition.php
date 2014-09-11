<?php


class crumbs_PluginSystem_PluginMethodIteratorPosition {

  /**
   * The plugin key at the current iterator position.
   *
   * @var string|false
   */
  private $pluginKey;

  /**
   * The plugin method at the current iterator position.
   *
   * @var string
   */
  private $pluginMethod;

  /**
   * The plugin at the current iterator position.
   *
   * @var crumbs_PluginInterface
   */
  private $plugin;

  /**
   * @param string $pluginKey
   * @param string $pluginMethod
   *   Either 'findParent' or 'findTitle'.
   * @param crumbs_PluginInterface $plugin
   */
  function __construct($pluginKey, $pluginMethod, $plugin) {
    $this->pluginKey = $pluginKey;
    $this->pluginMethod = $pluginMethod;
    $this->plugin = $plugin;
  }

  /**
   * @return bool
   *   TRUE, if the current plugin is a multi plugin.
   */
  function isMultiPlugin() {
    return $this->plugin instanceof crumbs_MultiPlugin;
  }

  /**
   * @return bool
   *   TRUE, if the current plugin is a mono plugin.
   */
  function isMonoPlugin() {
    return $this->plugin instanceof crumbs_MonoPlugin;
  }

  /**
   * @param mixed[] $args
   *   E.g. array($path, $item, $breadcrumb) for findTitle().
   *
   * @return mixed
   */
  function invokeFinderMethod(array $args) {
    return call_user_func_array(array($this->plugin, $this->pluginMethod), $args);
  }

}
