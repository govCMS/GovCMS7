<?php

/**
 * @file
 * Features module hooks
 */

/**
 * Implements hook_features_pipe_MODULE_alter().
 */
function bean_admin_ui_features_pipe_bean_type_alter(&$pipe, $data, $export) {
  if (isset($export['features']['bean_type'])) {
    foreach ($export['features']['bean_type'] as $type_name) {
      $fields = field_info_instances('bean', $type_name);
      foreach ($fields as $name => $field) {
        $pipe['field'][] = "bean-{$field['bundle']}-{$field['field_name']}";
      }
    }
  }
}

/**
 * Implements {component}_features_revert().
 */
function bean_type_features_revert($module, $component) {
  ctools_component_features_revert($component, $module);
  bean_reset();
}
