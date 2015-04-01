<?php
/**
 * @file
 * govcms_slideshow.features.user_permission.inc
 */

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function govcms_slideshow_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: create slide content.
  $permissions['create slide content'] = array(
    'name' => 'create slide content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any slide content.
  $permissions['delete any slide content'] = array(
    'name' => 'delete any slide content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any slide content.
  $permissions['edit any slide content'] = array(
    'name' => 'edit any slide content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
