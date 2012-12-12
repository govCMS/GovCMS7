<?php
/**
 * @file
 * agov_promotion.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function agov_promotion_user_default_permissions() {
  $permissions = array();

  // Exported permission: create footer_teaser content.
  $permissions['create footer_teaser content'] = array(
    'name' => 'create footer_teaser content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'Site administrator' => 'Site administrator',
      'Site builder' => 'Site builder',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any footer_teaser content.
  $permissions['delete any footer_teaser content'] = array(
    'name' => 'delete any footer_teaser content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own footer_teaser content.
  $permissions['delete own footer_teaser content'] = array(
    'name' => 'delete own footer_teaser content',
    'roles' => array(
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
      'Site administrator' => 'Site administrator',
      'Site builder' => 'Site builder',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own footer_teaser content.
  $permissions['edit own footer_teaser content'] = array(
    'name' => 'edit own footer_teaser content',
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
