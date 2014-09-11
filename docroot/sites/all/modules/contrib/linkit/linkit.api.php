<?php

/**
 * Implements hook_linkit_plugin_entities_alter().
 *
 * The default behavior for entities is that they will use the default entity
 * search plugin class, which will provide them with the basic methods they
 * need.
 *
 * Tho there can be some search plugins that will extend those basic method with
 * more advanced once, therefore the handlers for those plugins will have to be
 * changed.
 *
 * Make sure that your classes is included in the regisrty.
 * The easiest way to do this is by define them as
 *
 * <code> files[] = plugins/linkit_search/my_custom_plugin.class.php </code>
 *
 * @param $plugins
 *   An array of all search plugins processed within Linkit entity plugin.
 */
function hook_linkit_search_plugin_entities_alter(&$plugins) {
  $path = drupal_get_path('module', 'mymodule') . '/plugins/linkit_search';
  if (isset($plugins['my_custom_plugin'])) {
    $handler = array(
      'class' => 'MyCustomPlugin',
      'file' => 'my_custom_plugin.class.php',
      'path' => $path,
    );
    $plugins['my_custom_plugin']['handler'] = $handler;
  }
}