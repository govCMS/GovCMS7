<?php
/**
 * @file
 * agov_page.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function agov_page_user_default_permissions() {
  $permissions = array();
  
  // Exported permission: create page content.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      0 => 'Content approver',
      1 => 'Content editor',
      2 => 'Site administrator',
      3 => 'Site builder',
      4 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any page content.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own page content.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any page content.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      0 => 'Content approver',
      1 => 'Content editor',
      2 => 'Site administrator',
      3 => 'Site builder',
      4 => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own page content.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      0 => 'Content approver',
      1 => 'Content editor',
      2 => 'Site administrator',
      3 => 'Site builder',
      4 => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
