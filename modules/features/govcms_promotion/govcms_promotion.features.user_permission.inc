<?php
/**
 * @file
 * govcms_promotion.features.user_permission.inc
 */

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function govcms_promotion_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: create footer_teaser content.
  $permissions['create footer_teaser content'] = array(
    'name' => 'create footer_teaser content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any footer_teaser content.
  $permissions['delete any footer_teaser content'] = array(
    'name' => 'delete any footer_teaser content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any footer_teaser content.
  $permissions['edit any footer_teaser content'] = array(
    'name' => 'edit any footer_teaser content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
