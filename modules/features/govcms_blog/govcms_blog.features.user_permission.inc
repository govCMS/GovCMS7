<?php
/**
 * @file
 * govcms_blog.features.user_permission.inc
 */

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function govcms_blog_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: create blog_article content.
  $permissions['create blog_article content'] = array(
    'name' => 'create blog_article content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any blog_article content.
  $permissions['delete any blog_article content'] = array(
    'name' => 'delete any blog_article content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any blog_article content.
  $permissions['edit any blog_article content'] = array(
    'name' => 'edit any blog_article content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
