<?php
/**
 * @file
 * Linkit Entity Search Plugin.
 */

/**
 * Plugin structure is an associative array containing:
 * - ui_title: The title of the plugin used in the admin UI.
 * - ui_description: A description used in the admin UI.
 * - entity_type: (Only required if the plugin extends LinkitPluginEntity) The
 *     entity type this plugin will be used for.
 * - handler: Describes the class to be used for this plugin.
 */
$plugin = array(
  'get child' => 'linkit_entity_ctools_linkit_get_child',
  'get children' => 'linkit_entity_ctools_linkit_get_children',
  'handler' => array(
    'class' => 'LinkitSearchPluginEntity',
    'file' => 'entity.class.php',
  ),
);

/**
 * Get a single Linkit search plugin.
 */
function linkit_entity_ctools_linkit_get_child($plugin, $parent, $child) {
  $plugins = linkit_entity_ctools_linkit_get_children($plugin, $parent);
  return $plugins[$parent . ':' . $child];
}

/**
 * Get all child Linkit search plugins.
 */
function linkit_entity_ctools_linkit_get_children($plugin, $parent) {
  $entities = entity_get_info();
  $plugins = array();

  // The alternative plugins is extensions of the provided
  // LinkitSearchPluginEntity class provided by Linkit.
  $alternative_plugins = array(
    'entity:node',
    'entity:user',
    'entity:taxonomy_term',
    'entity:file',
  );

  foreach ($entities as $entity_type => $entity) {
    // The entity must have an URI CALLBACK defined.
    if (!isset($entity['uri callback'])) {
      continue;
    }

    $plugin['ui_title'] = $entity['label'];
    $plugin['ui_description'] = t('Extend Linkit with @entity support.', array('@entity' => $entity_type));
    $plugin['name'] = $parent . ':' . $entity_type;
    $plugin['entity_type'] = $entity_type;

    // If there is an alternative search class for this entity, change the handler.
    if (in_array('entity:' . $entity_type, $alternative_plugins)) {
      $handler = array(
        'class' => 'LinkitSearchPlugin' . drupal_ucfirst($entity_type),
        'file' => $entity_type . '.class.php',
      );
      $plugin['handler'] = $handler;
    }
    drupal_alter('linkit_search_plugin_entity', $plugin, $entity);
    $plugins[$parent . ':' . $entity_type] = $plugin;
  }

  drupal_alter('linkit_search_plugin_entities', $plugins);

  // Test the plugins.
  foreach ($plugins as $plugin_name => $plugin) {
    // In some cases the plugins isn't auto loaded. Ctools handle this for us.
    // This is typical when installing Linkit.
    if (!class_exists($plugin['handler']['class'])) {
      continue;
    }

    $tested_plugin = new $plugin['handler']['class']($plugin, new LinkitProfile());
    if (isset($tested_plugin->unusable) && $tested_plugin->unusable) {
      unset($plugins[$plugin_name]);
    }
  }

  return $plugins;
}
