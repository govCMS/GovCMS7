<?php
/**
 * @file
 * Linkit Profile class.
 */

/**
 * Linkit Profile class implementation.
 */
class LinkitProfile {

  /**
   * The profile data (settings).
   *
   * @var array
   */
  public $data;

  /**
   * All enabled attributes for this profile.
   *
   * @var array
   */
  protected $enabled_attribute_plugins;

  /**
   * All enabled search plugins for this profile.
   *
   * @var array
   */
  protected $enabled_search_plugins;

  /**
   * Set all enabled attribure plugins.
   */
  public function setEnabledAttributePlugins() {
    foreach ($this->data['attribute_plugins'] as $attribute_name => $attribute) {
      if ($attribute['enabled']) {
        // Load the attribute plugin.
        $attribute_plugin = linkit_attribute_plugin_load($attribute_name);

        // Call the callback to get the FAPI element.
        if (isset($attribute_plugin['callback']) && function_exists($attribute_plugin['callback'])) {
          $attribute_html = $attribute_plugin['callback']($attribute_plugin, $attribute);
          // Add Linkit specific class, this is used by the editor JS scripts.
          $attribute_html['#attributes']['class'][] = 'linkit-attribute';

          $this->enabled_attribute_plugins[$attribute_name] = $attribute_html;
        }
      }
    }
  }

  /**
   * Set all enabled search plugins.
   */
  public function setEnabledsearchPlugins() {
    // Sort plugins by weight.
    uasort($this->data['search_plugins'], 'linkit_sort_plugins_by_weight');

    foreach ($this->data['search_plugins'] as $plugin_name => $plugin) {
      if ($plugin['enabled']) {
        // Load plugin definition.
        $plugin_definition = linkit_search_plugin_load($plugin_name);

        // Get a Linkit search plugin object.
        $search_plugin = LinkitSearchPlugin::factory($plugin_definition, $this);

        // Only register none broken plugins.
        if ($search_plugin->broken() !== TRUE) {
          $this->enabled_search_plugins[$plugin_name] = $search_plugin;
        }
      }
    }
  }

  /**
   * Construct an array with all the enabled attribute plugins for this profile.
   *
   * @return
   *   An array with all enabled attribute plugins for this profile.
   */
  public function getEnabledAttributePlugins() {
    if (!isset($this->enabled_attribute_plugins)) {
      $this->setEnabledAttributePlugins();
    }
    return $this->enabled_attribute_plugins;
  }

  /**
   * Construct an array with all enabled search plugins for this profile.
   *
   * @return
   *   An array with all enabled search plugins for this profile.
   */
  public function getEnabledsearchPlugins() {
    if (!isset($this->enabled_search_plugins)) {
      $this->setEnabledsearchPlugins();
    }
    return $this->enabled_search_plugins;
  }
}