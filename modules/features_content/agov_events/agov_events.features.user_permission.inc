<?php
/**
 * @file
 * agov_events.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function agov_events_user_default_permissions() {
  $permissions = array();

  // Exported permission: create event content.
  $permissions['create event content'] = array(
    'name' => 'create event content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'Site administrator' => 'Site administrator',
      'Site builder' => 'Site builder',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any event content.
  $permissions['delete any event content'] = array(
    'name' => 'delete any event content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own event content.
  $permissions['delete own event content'] = array(
    'name' => 'delete own event content',
    'roles' => array(
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
      'Site administrator' => 'Site administrator',
      'Site builder' => 'Site builder',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own event content.
  $permissions['edit own event content'] = array(
    'name' => 'edit own event content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'Site administrator' => 'Site administrator',
      'Site builder' => 'Site builder',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
