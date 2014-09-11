<?php
/**
 * @file
 * Feeds mapping implementation for the Metatag module.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 */
function metatag_feeds_processor_targets_alter(&$targets, $entity_type, $bundle) {
  if (metatag_entity_supports_metatags($entity_type)) {
    $info = metatag_get_info();
    foreach ($info['tags'] as $name => $tag) {
      $targets['meta_' . $name] = array(
        'name' => 'Meta tag: ' . check_plain($tag['label']),
        'callback' => 'metatag_feeds_set_target',
        'description' => $tag['description'],
      );
    }
  }
}

/**
 * Callback function to set value of a metatag tag.
 */
function metatag_feeds_set_target($source, $entity, $target, $value) {
  // Don't do anything if we weren't given any data.
  if (empty($value)) {
    return;
  }

  // Strip the prefix that was added above.
  $name = str_replace('meta_', '', $target);

  // Assign the value.
  $entity->metatags[$name]['value'] = $value;
}
