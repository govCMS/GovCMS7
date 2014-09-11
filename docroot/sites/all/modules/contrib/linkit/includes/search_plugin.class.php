<?php
/**
 * @file
 * Linkit Search plugin interface.
 *
 * Provides an interface and classes to implement Linkit search plugins.
 */

/**
 * Defines a common interface for a Linkit search plugin.
 */
interface LinkitSearchPluginInterface {

  /**
   * Search plugin factory method.
   *
   * @param $plugin
   *   A search plugin object.
   *
   * @param LinkitProfile $profile
   *   (optional) A LinkitProfile object.
   *
   * @return
   *   An instance of the search plugin class or an instance of the
   *   LinkitSearchPluginBroken class.
   */
  public static function factory($plugin, LinkitProfile $profile);

  /**
   * Return a string representing this handler's name in the UI.
   */
  public function ui_title();

  /**
   * Return a string representing this handler's description in the UI.
   */
  public function ui_description();

  /**
   * Fetch search results based on the $search_string.
   *
   * @param $search_string
   *   A string that contains the text to search for.
   *
   * @return
   *   An associative array whose values are an
   *   associative array containing:
   *   - title: A string to use as the search result label.
   *   - description: (optional) A string with additional information about the
   *     result item.
   *   - path: The URL to the item.
   *   - group: (optional) A string with the group name for the result item.
   *     Best practice is to use the plugin name as group name.
   *   - addClass: (optional) A string with classes to add to the result row..
   */
  public function fetchResults($search_string);
}

/**
 * Base class for Linkit search plugins.
 */
abstract class LinkitSearchPlugin implements LinkitSearchPluginInterface {

  /**
   * The plugin definition for this instance.
   *
   * @var array
   */
  protected $plugin;

  /**
   * The profile instance for this instance.
   *
   * @var LinkitProfile object
   */
  protected $profile;

  /**
   * Initialize this search plugin with the search plugin and the profile.
   *
   * @param $plugin
   *   A search plugin object.
   *
   * @param LinkitProfile $profile
   *   A LinkitProfile object.
   */
  public function __construct($plugin, LinkitProfile $profile) {
    $this->plugin = $plugin;
    $this->profile = $profile;
  }

  /**
   * Implements LinkitSearchPluginInterface::factory().
   */
  public static function factory($plugin, LinkitProfile $profile) {
    ctools_include('plugins');

    // Make sure that the handler class exists and that it has this class as one
    // of its parents.
    if (class_exists($plugin['handler']['class']) && is_subclass_of($plugin['handler']['class'], __CLASS__)) {
      return new $plugin['handler']['class']($plugin, $profile);
    }
    else {
      // The plugin handler class is defined but it cannot be found, so lets
      // instantiate the LinkitSearchPluginBroken instead.
      return new LinkitSearchPluginBroken($plugin, $profile);
    }
  }

  /**
   * Implements LinkitSearchPluginInterface::ui_title().
   */
  public function ui_title() {
    if (!isset($this->plugin['ui_title'])) {
      return check_plain($this->plugin['module'] . ':' . $this->plugin['name']);
    }
    return check_plain($this->plugin['ui_title']);
  }

  /**
   * Implements LinkitSearchPluginInterface::ui_description().
   */
  public function ui_description() {
    if (isset($this->plugin['ui_description'])) {
      return check_plain($this->plugin['ui_description']);
    }
  }

  /**
   * Generate a settings form for this handler.
   * Uses the standard Drupal FAPI.
   *
   * @return
   *   An array containing any custom form elements to be displayed in the
   *   profile editing form
   */
  public function buildSettingsForm() {}

  /**
   * Determine if the handler is considered 'broken', meaning it's a
   * a placeholder used when a handler can't be found.
   */
  public function broken() { }
}

/**
 * A special handler to take the place of missing or broken Linkit search
 * plugin handlers.
 */
class LinkitSearchPluginBroken extends LinkitSearchPlugin {

  /**
   * Overrides LinkitSearchPlugin::ui_title().
   */
  public function ui_title() { return t('Broken/missing handler'); }

  /**
   * Overrides LinkitSearchPlugin::ui_description().
   */
  public function ui_description() {}

  /**
   * Implements LinkitSearchPluginInterface::fetchResults().
   */
  public function fetchResults($search_string) {}

  /**
   * Overrides LinkitSearchPlugin::broken().
   */
  public function broken() { return TRUE; }
}