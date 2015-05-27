<?php

/**
 * @file
 * Common permissions.
 *
 * The original foundation for the govCMS distribution is aGov; the Drupal distribution created by PreviousNext to provide a core set of elements, functionality and features that can be used to develop government websites
 *
 * @copyright Copyright(c) 2015 Commonwealth of Australia as represented by Department of Finance
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Department of Finance
 */

/**
 * Return base govcms permissions.
 *
 * PHPMD things this function is too long...
 * @SuppressWarnings(PHPMD)
 *
 * @return array
 *   An array of permissions.
 */
function govcms_permissions_base_permissions() {
  return array(
    'system' => array(
      'access administration pages' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'access site in maintenance mode' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'view the administration theme' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
      'access site reports' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'administer actions' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'administer themes' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'comment' => array(
      'access comments' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ),
      ),
      'administer comments' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
      'edit own comments' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ),
      ),
      'post comments' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ),
      ),
      'skip comment approval' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
    ),
    'contextual' => array(
      'access contextual links' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ),
      ),
    ),
    'node' => array(
      'access content' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ),
      ),
      'access content overview' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'administer content types' => array(
        'roles' => array(
          0 => 'Site builder',
          1 => 'administrator',
        ),
      ),
      'administer nodes' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ),
      ),
      'bypass node access' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ),
      ),
      'revert revisions' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'view own unpublished content' => array(
        'roles' => array(
          0 => 'authenticated user',
          1 => 'Content approver',
          2 => 'Content editor',
          3 => 'administrator',
          4 => 'Site editor',
          5 => 'Site builder',
        ),
      ),
      'view revisions' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
    ),
    'site_map' => array(
      'access site map' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'Site builder',
          4 => 'authenticated user',
        ),
      ),
    ),
    'toolbar' => array(
      'access toolbar' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ),
      ),
    ),
    'workbench' => array(
      'access workbench' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
    ),
    'media_internet' => array(
      'add media from remote sources' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ),
      ),
    ),
    'file_entity' => array(
      'administer files' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ),
      ),
      'bypass file access' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'maintenance_mode_permissions' => array(
      'administer maintenance mode' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ),
      ),
    ),
    'scheduler' => array(
      'administer scheduler' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ),
      ),
      'schedule (un)publishing of nodes' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ),
      ),
    ),
    'govcms_appearance' => array(
      'administer theme settings' => array(
        'roles' => array(
          0 => 'Site editor',
          1 => 'Site builder',
          2 => 'administrator',
        ),
      ),
    ),
    'workbench_moderation' => array(
      'administer workbench moderation' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ),
      ),
      'bypass workbench moderation' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ),
      ),
      'moderate content from draft to needs_review' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ),
      ),
      'moderate content from needs_review to draft' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ),
      ),
      'moderate content from needs_review to published' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'administrator',
          2 => 'Site editor',
        ),
      ),
      'use workbench_moderation my drafts tab' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'use workbench_moderation needs review tab' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'view all unpublished content' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'view moderation history' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
      'view moderation messages' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
    ),
    'bean' => array(
      'create any basic_content bean' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'create any image_and_text bean' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'delete any basic_content bean' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'delete any image_and_text bean' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'edit any basic_content bean' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'edit any image_and_text bean' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'view any basic_content bean' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'Site builder',
          4 => 'authenticated user',
        ),
      ),
      'view any image_and_text bean' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'Site builder',
          4 => 'authenticated user',
        ),
      ),
      'view bean page' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'access bean overview' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'administer beans' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'edit bean view mode' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'view bean revisions' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'administer bean types' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
        ),
      ),
      'administer bean settings' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
        ),
      ),
    ),
    'scheduler_workbench' => array(
      'override default scheduler time' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
    ),
    'search' => array(
      'search content' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'Site builder',
          4 => 'authenticated user',
        ),
      ),
      'administer search' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'filter' => array(
      'use text format rich_text' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
    ),
    'view_unpublished' => array(
      'view any unpublished content' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
    ),
    'role_delegation' => array(
      'assign all roles' => array(
        'roles' => array(
          0 => 'administrator',
        ),
      ),
      'assign Content approver role' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
      'assign Content editor role' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
      'assign Site editor role' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
      'assign Site builder role' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
    ),
    'webform' => array(
      'create webform content' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
      'edit any webform content' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
      'delete any webform content' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
      'access all webform results' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
      'access own webform results' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'access own webform submissions' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ),
      ),
      'edit own webform submissions' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ),
      ),
      'delete own webform submissions' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ),
      ),
      'delete all webform submissions' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'edit all webform submissions' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'metatag' => array(
      'edit meta tags' => array(
        'roles' => array(
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ),
      ),
      'administer meta tags' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'user_action_report' => array(
      'view user actions' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'quicktabs' => array(
      'administer quicktabs' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'linkchecker' => array(
      'access broken links report' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'access own broken links report' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'draggableviews' => array(
      'access draggableviews' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'event_log' => array(
      'access event log' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'user' => array(
      'access user profiles' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'administer users' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'block' => array(
      'administer blocks' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'contact' => array(
      'administer contact forms' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'googleanalytics' => array(
      'administer google analytics' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'menu' => array(
      'administer menu' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'redirect' => array(
      'administer redirects' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'search_api' => array(
      'administer search_api' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'shield' => array(
      'administer shield' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'taxonomy' => array(
      'administer taxonomy' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'delete terms in 1' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'edit terms in 1' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'path' => array(
      'administer url aliases' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'create url aliases' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'password_policy' => array(
      'force password change' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'unblock expired accounts' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'webform_clear' => array(
      'set webform_clear times' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'panels' => array(
      'use panels in place editing' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'use panels dashboard' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'view pane admin links' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'administer pane access' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'change layouts in place editing' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'administer advanced pane settings' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'use panels caching features' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'use panels locks' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'use ipe with page manager' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'page_manager' => array(
      'use page manager' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'views' => array(
      'administer views' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
      'access all views' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'xmlsitemap' => array(
      'administer xmlsitemap' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ),
      ),
    ),
    'shortcut' => array(
      'administer shortcuts' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
      'customize shortcut links' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
      'switch shortcut sets' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site editor',
        ),
      ),
    ),
    'crumbs' => array(
      'administer crumbs' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
        ),
      ),
    ),
    'ds' => array(
      'admin_display_suite' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
        ),
      ),
    ),
    'image' => array(
      'administer image styles' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
        ),
      ),
    ),
    'service_links' => array(
      'access service links' => array(
        'roles' => array(
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
          3 => 'Content approver',
          4 => 'Content editor',
          5 => 'authenticated user',
          6 => 'anonymous user',
        ),
      ),
    ),
  );
}
