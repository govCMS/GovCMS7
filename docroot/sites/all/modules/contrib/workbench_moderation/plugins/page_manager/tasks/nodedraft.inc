<?php

/**
 * Specialized implementation of hook_page_manager_task_tasks(). See api-task.html for
 * more information.
 */
function workbench_moderation_nodedraft_page_manager_tasks() {

  return array(
    // This is a 'page' task and will fall under the page admin UI
    'task type' => 'page',

    'title' => t('Node draft'),
    'admin title' => t('The draft page for moderated nodes.'),
    'admin description' => t('When enabled, this overrides the default node view at node/%node/draft'),
    'admin path' => 'node/%node/draft',

    // Menu hooks so that we can alter the node/%node menu entry to point to us.
    'hook menu alter' => 'workbench_moderation_nodedraft_menu_alter',

    // This is task uses 'context' handlers and must implement these to give the
    // handler data it needs.
    'handler type' => 'context',
    'get arguments' => 'workbench_moderation_nodedraft_get_arguments',
    'get context placeholders' => 'workbench_moderation_nodedraft_get_contexts',

    // Allow this to be enabled or disabled:
    'disabled' => variable_get('workbench_moderation_nodedraft_disabled', TRUE),
    'enable callback' => 'workbench_moderation_nodedraft_enable',
  );
}

/**
 * Callback defined by workbench_moderation_nodedraft_page_manager_tasks().
 *
 * Alter menu item so that admin/workbench comes here.
 */
function workbench_moderation_nodedraft_menu_alter(&$items, $task) {

  if (variable_get('workbench_moderation_nodedraft_disabled', TRUE)) {
    return;
  }

  $callback = $items['node/%node/draft']['page callback'];
  // Override the node edit handler for our purpose.
  if ($callback == 'workbench_moderation_node_view_draft' || variable_get('page_manager_override_anyway', FALSE)) {
    $items['node/%node/draft']['page callback'] = 'workbench_moderation_nodedraft';
    $items['node/%node/draft']['file path'] = $task['path'];
    $items['node/%node/draft']['file'] = $task['file'];
  }

  else {
    //variable_set('workbench_moderation_nodedraft_disabled', TRUE);
    if (!empty($GLOBALS['page_manager_enabling_workbench'])) {
      drupal_set_message(t('Page manager module is unable to enable Workbench Moderation Draft Node because some other module already has overridden with %callback.', array('%callback' => $callback)), 'warning');
    }
    return;
  }
}

/**
 * Entry point for our overridden My Workbench.
 *
 * This function asks its assigned handlers who, if anyone, would like
 * to run with it. If no one does, it passes through to the main node draft page.
 */
function workbench_moderation_nodedraft($node) {
  // Load my task plugin
  $task = page_manager_get_task('nodedraft');

  // Get the most recent revision to pass to the task handler.
  $current_node = workbench_moderation_node_current_load($node);

  // Load the node into a context.
  ctools_include('context');
  ctools_include('context-task-handler');
  $contexts = ctools_context_handler_get_task_contexts($task, '', array($current_node));

  $output = ctools_context_handler_render($task, '', $contexts, array($current_node->nid));
  if ($output !== FALSE) {
    return $output;
  }

  module_load_include('inc', 'workbench_moderation', 'workbench_moderation.node');
  $function = 'workbench_moderation_node_view_draft';
  foreach (module_implements('page_manager_override') as $module) {
    $call = $module . '_page_manager_override';
    if (($rc = $call('workbench')) && function_exists($rc)) {
      $function = $rc;
      break;
    }
  }

  // Otherwise, fall back.
  return $function($node);
}

/**
 * Callback to enable/disable the page from the UI.
 */
function workbench_moderation_nodedraft_enable($cache, $status) {
  variable_set('workbench_moderation_nodedraft_disabled', $status);
  // Set a global flag so that the menu routine knows it needs
  // to set a message if enabling cannot be done.
  if (!$status) {
    $GLOBALS['page_manager_enabling_workbench'] = TRUE;
  }
}

/**
 * Callback to get arguments provided by this task handler.
 *
 * Since this is the node view and there is no UI on the arguments, we
 * create dummy arguments that contain the needed data.
 */
function workbench_moderation_nodedraft_get_arguments($task, $subtask_id) {
  return array(
    array(
      'keyword' => 'node',
      'identifier' => t('Node draft being viewed'),
      'id' => 1,
      'name' => 'entity_id:node',
      'settings' => array(),
    ),
  );
}

/**
 * Callback to get context placeholders provided by this handler.
 */
function workbench_moderation_nodedraft_get_contexts($task, $subtask_id) {
  return ctools_context_get_placeholders_from_argument(page_manager_node_view_get_arguments($task, $subtask_id));
}
