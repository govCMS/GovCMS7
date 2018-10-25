<?php

/**
 * @file
 * Common permissions.
 *
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 *
 * aGov
 * @copyright Copyright(c) 2014 PreviousNext
 * @author Chris Skene chris at previousnext dot com dot au
 *
 * govCMS (Forked on 1 April 2015 - http://cgit.drupalcode.org/govcms/commit/?id=64b602dcc7ddde0992c5c7cf5f3c4a795e5be08a)
 * The original foundation for the govCMS distribution is aGov; the Drupal distribution created by PreviousNext to provide a core set of elements, functionality and features that can be used to develop government websites
 * @copyright Copyright(c) 2015 Commonwealth of Australia as represented by Department of Finance
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
  return [
    'system' => [
      'access administration pages' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'access site in maintenance mode' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'view the administration theme' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
      'access site reports' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'administer actions' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'administer themes' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'comment' => [
      'access comments' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ],
      ],
      'administer comments' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
      'edit own comments' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ],
      ],
      'post comments' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ],
      ],
      'skip comment approval' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
    ],
    'contextual' => [
      'access contextual links' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ],
      ],
    ],
    'node' => [
      'access content' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'authenticated user',
        ],
      ],
      'access content overview' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'administer content types' => [
        'roles' => [
          0 => 'Site builder',
          1 => 'administrator',
        ],
      ],
      'administer nodes' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ],
      ],
      'bypass node access' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ],
      ],
      'revert revisions' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'view own unpublished content' => [
        'roles' => [
          0 => 'authenticated user',
          1 => 'Content approver',
          2 => 'Content editor',
          3 => 'administrator',
          4 => 'Site editor',
          5 => 'Site builder',
        ],
      ],
      'view revisions' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
    ],
    'site_map' => [
      'access site map' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'Site builder',
          4 => 'authenticated user',
        ],
      ],
    ],
    'superfish' => [
      'administer superfish' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'toolbar' => [
      'access toolbar' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ],
      ],
    ],
    'workbench' => [
      'access workbench' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
    ],
    'media' => [
      'administer media browser' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'access media browser' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
    ],
    'media_internet' => [
      'add media from remote sources' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
    ],
    'media_wysiwyg' => [
      'use media wysiwyg' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
    ],
    'file_entity' => [
      'administer files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'bypass file access' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'create files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'edit any image files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'delete any image files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'download any image files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'edit any video files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'delete any video files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'download any video files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'edit any audio files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'delete any audio files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'download any audio files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'edit any document files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'delete any document files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
      'download any document files' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'Site builder',
          3 => 'administrator',
          4 => 'Site editor',
        ],
      ],
    ],
    'linkit' => [
      'administer linkit' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ],
      ],
    ],
    'maintenance_mode_permissions' => [
      'administer maintenance mode' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ],
      ],
    ],
    'scheduler' => [
      'administer scheduler' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ],
      ],
      'schedule (un)publishing of nodes' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ],
      ],
    ],
    'govcms_appearance' => [
      'administer theme settings' => [
        'roles' => [
          0 => 'Site editor',
          1 => 'Site builder',
          2 => 'administrator',
        ],
      ],
    ],
    'workbench_moderation' => [
      'administer workbench moderation' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ],
      ],
      'bypass workbench moderation' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
        ],
      ],
      'moderate content from draft to needs_review' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ],
      ],
      'moderate content from needs_review to draft' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ],
      ],
      'moderate content from needs_review to published' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'administrator',
          2 => 'Site editor',
        ],
      ],
      'use workbench_moderation my drafts tab' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'use workbench_moderation needs review tab' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'view all unpublished content' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'view moderation history' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
      'view moderation messages' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
    ],
    'bean' => [
      'create any basic_content bean' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'create any image_and_text bean' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'delete any basic_content bean' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'delete any image_and_text bean' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'edit any basic_content bean' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'edit any image_and_text bean' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'view any basic_content bean' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'Site builder',
          4 => 'authenticated user',
        ],
      ],
      'view any image_and_text bean' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'Site builder',
          4 => 'authenticated user',
        ],
      ],
      'view bean page' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'access bean overview' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'administer beans' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'edit bean view mode' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'view bean revisions' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'administer bean types' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
        ],
      ],
      'administer bean settings' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
        ],
      ],
    ],
    'scheduler_workbench' => [
      'override default scheduler time' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
    ],
    'search' => [
      'search content' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'anonymous user',
          3 => 'Site builder',
          4 => 'authenticated user',
        ],
      ],
      'administer search' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'filter' => [
      'administer filters' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'use text format rich_text' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
    ],
    'view_unpublished' => [
      'view any unpublished content' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
    ],
    'role_delegation' => [
      'assign all roles' => [
        'roles' => [
          0 => 'administrator',
        ],
      ],
      'assign Content approver role' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
      'assign Content editor role' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
      'assign Site editor role' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
      'assign Site builder role' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
    ],
    'webform' => [
      'create webform content' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
      'edit any webform content' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
      'delete any webform content' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
      'access all webform results' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
      'access own webform results' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'access own webform submissions' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site builder',
          4 => 'Site editor',
        ],
      ],
      'edit own webform submissions' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ],
      ],
      'delete own webform submissions' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
        ],
      ],
      'delete all webform submissions' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'edit all webform submissions' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'metatag' => [
      'edit meta tags' => [
        'roles' => [
          0 => 'Content approver',
          1 => 'Content editor',
          2 => 'administrator',
          3 => 'Site editor',
          4 => 'Site builder',
        ],
      ],
      'administer meta tags' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'user_action_report' => [
      'view user actions' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'quicktabs' => [
      'administer quicktabs' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'linkchecker' => [
      'access broken links report' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'access own broken links report' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'draggableviews' => [
      'access draggableviews' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'event_log' => [
      'access event log' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'user' => [
      'access user profiles' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'administer users' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'block' => [
      'administer blocks' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'contact' => [
      'administer contact forms' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'googleanalytics' => [
      'administer google analytics' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'honeypot' => [
      'administer honeypot' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'bypass honeypot protection' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'menu' => [
      'administer menu' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'redirect' => [
      'administer redirects' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'search_api' => [
      'administer search_api' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'shield' => [
      'administer shield' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'taxonomy' => [
      'administer taxonomy' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'delete terms in 1' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'edit terms in 1' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'path' => [
      'administer url aliases' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'create url aliases' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'pathauto' => [
      'administer pathauto' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'password_policy' => [
      'force password change' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'unblock expired accounts' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'webform_clear' => [
      'set webform_clear times' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'panels' => [
      'use panels in place editing' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'use panels dashboard' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'view pane admin links' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'administer pane access' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'change layouts in place editing' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'administer advanced pane settings' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'use panels caching features' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'use panels locks' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'use ipe with page manager' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'page_manager' => [
      'use page manager' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'views' => [
      'administer views' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
      'access all views' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'xmlsitemap' => [
      'administer xmlsitemap' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
          2 => 'Site builder',
        ],
      ],
    ],
    'shortcut' => [
      'administer shortcuts' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
      'customize shortcut links' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
      'switch shortcut sets' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site editor',
        ],
      ],
    ],
    'crumbs' => [
      'administer crumbs' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
        ],
      ],
    ],
    'ds' => [
      'admin_display_suite' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
        ],
      ],
    ],
    'image' => [
      'administer image styles' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
        ],
      ],
    ],
    'service_links' => [
      'access service links' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
          2 => 'Site editor',
          3 => 'Content approver',
          4 => 'Content editor',
          5 => 'authenticated user',
          6 => 'anonymous user',
        ],
      ],
    ],
    'field' => [
      'administer fields' => [
        'roles' => [
          0 => 'administrator',
          1 => 'Site builder',
        ],
      ],
    ],
  ];
}
