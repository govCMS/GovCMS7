<?php
/**
 * @file
 * govcms_events.features.user_permission.inc
 */

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function govcms_events_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: create event content.
  $permissions['create event content'] = array(
    'name' => 'create event content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any event content.
  $permissions['delete any event content'] = array(
    'name' => 'delete any event content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any event content.
  $permissions['edit any event content'] = array(
    'name' => 'edit any event content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
