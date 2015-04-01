<?php
/**
 * @file
 * govcms_media_releases.features.user_permission.inc
 */

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function govcms_media_releases_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: create media_release content.
  $permissions['create media_release content'] = array(
    'name' => 'create media_release content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any media_release content.
  $permissions['delete any media_release content'] = array(
    'name' => 'delete any media_release content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any media_release content.
  $permissions['edit any media_release content'] = array(
    'name' => 'edit any media_release content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
