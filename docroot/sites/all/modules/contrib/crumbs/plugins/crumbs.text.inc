<?php

/**
 * Implements hook_crumbs_plugins().
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function text_crumbs_plugins($api) {
  foreach (field_info_fields() as $field_name => $field_info) {
    if (0
      || 'text' !== $field_info['type']
      || '1' !== '' . $field_info['cardinality']
    ) {
      continue;
    }

    $instances = array();
    foreach ($field_info['bundles'] as $entity_type => $bundles) {
      foreach ($bundles as $bundle_name) {
        $instance_info = field_info_instance($entity_type, $field_name, $bundle_name);
        if (empty($instance_info['settings']['text_processing'])) {
          $instances[$entity_type][] = $bundle_name;
        }
      }
    }

    if (!empty($instances)) {
      $plugin = new crumbs_EntityPlugin_Field_Text($field_name, $instances);
      $api->entityTitlePlugin($field_name, $plugin, array_keys($instances));
    }
  }
  $api->disabledByDefault('*');
}