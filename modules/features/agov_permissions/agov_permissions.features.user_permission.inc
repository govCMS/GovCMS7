<?php
/**
 * @file
 * agov_permissions.features.user_permission.inc
 */

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function agov_permissions_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: access administration pages.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'system',
  );

  // Exported permission: access comments.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access site in maintenance mode.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'system',
  );

  // Exported permission: access content overview.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'node',
  );

  // Exported permission: access site map.
  $permissions['access site map'] = array(
    'name' => 'access site map',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'site_map',
  );

  // Exported permission: access toolbar.
  $permissions['access toolbar'] = array(
    'name' => 'access toolbar',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'toolbar',
  );

  // Exported permission: access workbench.
  $permissions['access workbench'] = array(
    'name' => 'access workbench',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench',
  );

  // Exported permission: add media from remote sources.
  $permissions['add media from remote sources'] = array(
    'name' => 'add media from remote sources',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'media_internet',
  );

  // Exported permission: administer comments.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: administer content types.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: administer files.
  $permissions['administer files'] = array(
    'name' => 'administer files',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: administer maintenance mode.
  $permissions['administer maintenance mode'] = array(
    'name' => 'administer maintenance mode',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'maintenance_mode_permissions',
  );

  // Exported permission: administer nodes.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'node',
  );

  // Exported permission: administer scheduler.
  $permissions['administer scheduler'] = array(
    'name' => 'administer scheduler',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'scheduler',
  );

  // Exported permission: 'administer theme settings'.
  $permissions['administer theme settings'] = array(
    'name' => 'administer theme settings',
    'roles' => array(
      'Site editor' => 'Site editor',
      'administrator' => 'administrator',
    ),
    'module' => 'agov_appearance',
  );

  // Exported permission: administer workbench moderation.
  $permissions['administer workbench moderation'] = array(
    'name' => 'administer workbench moderation',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: bypass node access.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'node',
  );

  // Exported permission: bypass workbench moderation.
  $permissions['bypass workbench moderation'] = array(
    'name' => 'bypass workbench moderation',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: create any basic_content bean.
  $permissions['create any basic_content bean'] = array(
    'name' => 'create any basic_content bean',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'bean',
  );

  // Exported permission: create any image_and_text bean.
  $permissions['create any image_and_text bean'] = array(
    'name' => 'create any image_and_text bean',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'bean',
  );

  // Exported permission: delete any basic_content bean.
  $permissions['delete any basic_content bean'] = array(
    'name' => 'delete any basic_content bean',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'bean',
  );

  // Exported permission: delete any image_and_text bean.
  $permissions['delete any image_and_text bean'] = array(
    'name' => 'delete any image_and_text bean',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'bean',
  );

  // Exported permission: edit any basic_content bean.
  $permissions['edit any basic_content bean'] = array(
    'name' => 'edit any basic_content bean',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'bean',
  );

  // Exported permission: edit any image_and_text bean.
  $permissions['edit any image_and_text bean'] = array(
    'name' => 'edit any image_and_text bean',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'bean',
  );

  // Exported permission: edit own comments.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: moderate content from draft to needs_review.
  $permissions['moderate content from draft to needs_review'] = array(
    'name' => 'moderate content from draft to needs_review',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from needs_review to draft.
  $permissions['moderate content from needs_review to draft'] = array(
    'name' => 'moderate content from needs_review to draft',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: moderate content from needs_review to published.
  $permissions['moderate content from needs_review to published'] = array(
    'name' => 'moderate content from needs_review to published',
    'roles' => array(
      'Content approver' => 'Content approver',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: override default scheduler time.
  $permissions['override default scheduler time'] = array(
    'name' => 'override default scheduler time',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'scheduler_workbench',
  );

  // Exported permission: post comments.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: revert revisions.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'node',
  );

  // Exported permission: schedule (un)publishing of nodes.
  $permissions['schedule (un)publishing of nodes'] = array(
    'name' => 'schedule (un)publishing of nodes',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'scheduler',
  );

  // Exported permission: search content.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: skip comment approval.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'comment',
  );

  // Exported permission: use text format rich_text.
  $permissions['use text format rich_text'] = array(
    'name' => 'use text format rich_text',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'filter',
  );

  // Exported permission: use workbench_moderation my drafts tab.
  $permissions['use workbench_moderation my drafts tab'] = array(
    'name' => 'use workbench_moderation my drafts tab',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: use workbench_moderation needs review tab.
  $permissions['use workbench_moderation needs review tab'] = array(
    'name' => 'use workbench_moderation needs review tab',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view all unpublished content.
  $permissions['view all unpublished content'] = array(
    'name' => 'view all unpublished content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view any basic_content bean.
  $permissions['view any basic_content bean'] = array(
    'name' => 'view any basic_content bean',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'bean',
  );

  // Exported permission: view any image_and_text bean.
  $permissions['view any image_and_text bean'] = array(
    'name' => 'view any image_and_text bean',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'bean',
  );

  // Exported permission: view any unpublished content.
  $permissions['view any unpublished content'] = array(
    'name' => 'view any unpublished content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: view bean page.
  $permissions['view bean page'] = array(
    'name' => 'view bean page',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'bean',
  );

  // Exported permission: view bean page.
  $permissions['assign all roles'] = array(
    'name' => 'assign all roles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: view moderation history.
  $permissions['view moderation history'] = array(
    'name' => 'view moderation history',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view moderation messages.
  $permissions['view moderation messages'] = array(
    'name' => 'view moderation messages',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'node',
  );

  // Exported permission: view revisions.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'node',
  );

  // Exported permission: view the administration theme.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'system',
  );

  // Create webform content.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'webform',
  );

  // Edit any webform content.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'webform',
  );

  // Delete any webform content.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: access all webform results.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: access own webform results.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: edit own webform submissions.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'webform',
  );

  // Exported permission: delete own webform submissions.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'webform',
  );

  // Edit meta tags.
  $permissions['edit meta tags'] = array(
    'name' => 'edit meta tags',
    'roles' => array(
      'Content approver' => 'Content approver',
      'Content editor' => 'Content editor',
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'metatag',
  );

  // Exported permission: administer google analytics.
  $permission['administer google analytics'] = array(
    'name' => 'administer google analytics',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'googleanalytics',
  );

  // Exported permission: administer google analytics reports.
  $permission['administer google analytics reports'] = array(
    'name' => 'administer google analytics reports',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'google_analytics_report',
  );

  // Exported permission: access google analytics reports.
  $permission['access google analytics reports'] = array(
    'name' => 'access google analytics reports',
    'roles' => array(
      'administrator' => 'administrator',
      'Site editor' => 'Site editor',
    ),
    'module' => 'google_analytics_report',
  );

  // Additional site-editor permissions.
  $additional_permissions = array(
    'access bean overview' => 'bean',
    'access broken links report' => 'linkchecker',
    'access contextual links' => 'contextual',
    'access event log' => 'event_log',
    'access own broken links report' => 'linkchecker',
    'access site reports' => 'system',
    'access user profiles' => 'user',
    'administer beans' => 'bean',
    'administer blocks' => 'block',
    'administer contact forms' => 'contact',
    'administer google analytics' => 'googleanalytics',
    'administer menu' => 'menu',
    'administer redirects' => 'redirect',
    'administer search' => 'search',
    'administer search_api' => 'search_api',
    'administer shield' => 'shield',
    'administer url aliases' => 'path',
    'administer users' => 'user',
    'assign Content approver role' => 'role_delegation',
    'assign Content editor role' => 'role_delegation',
    'assign Site editor role' => 'role_delegation',
    'bypass file access' => 'file_entity',
    'create url aliases' => 'path',
    'delete all webform submissions' => 'webform',
    'delete terms in 1' => 'taxonomy',
    'edit all webform submissions' => 'webform',
    'edit terms in 1' => 'taxonomy',
    'force password change' => 'password_policy',
    'set webform_clear times' => 'webform_clear',
    'unblock expired accounts' => 'password_policy',
    'use panels in place editing' => 'panels',
    'view bean revisions' => 'bean',
  );
  foreach ($additional_permissions as $permission => $module) {
    $permissions[$permission] = array(
      'name' => $permission,
      'roles' => array(
        'administrator' => 'administrator',
        'Site editor' => 'Site editor',
      ),
      'module' => $module,
    );
  }

  return $permissions;
}
