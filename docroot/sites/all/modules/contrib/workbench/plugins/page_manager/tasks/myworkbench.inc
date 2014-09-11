<?php

/**
 * Specialized implementation of hook_page_manager_task_tasks(). See api-task.html for
 * more information.
 */
function workbench_myworkbench_page_manager_tasks() {

  return array(
    // This is a 'page' task and will fall under the page admin UI
    'task type' => 'page',

    'title' => t('My Workbench'),
    'admin title' => t('The Workbench landing page.'),
    'admin description' => t('When enabled, this overrides the default Workbench page for <em>admin/workbench</em>. If no variant is selected, the default "My Workbench" will be shown. See http://drupal.org/node/1226174 for more information.'),
    'admin path' => 'admin/workbench',

    // Menu hooks so that we can alter the node/%node menu entry to point to us.
    'hook menu alter' => 'workbench_myworkbench_menu_alter',

    // This is task uses 'context' handlers and must implement these to give the
    // handler data it needs.
    'handler type' => 'context',

    // Allow this to be enabled or disabled:
    'disabled' => variable_get('workbench_myworkbench_disabled', TRUE),
    'enable callback' => 'workbench_myworkbench_enable',
  );
}

/**
 * Callback defined by workbench_myworkbench_page_manager_tasks().
 *
 * Alter menu item so that admin/workbench comes here.
 */
function workbench_myworkbench_menu_alter(&$items, $task) {

  if (variable_get('workbench_myworkbench_disabled', TRUE)) {
    return;
  }

  $callback = $items['admin/workbench']['page callback'];
  // Override the node edit handler for our purpose.
  if ($callback == 'workbench_content' || variable_get('page_manager_override_anyway', FALSE)) {
    $items['admin/workbench']['page callback'] = 'workbench_myworkbench';
    $items['admin/workbench']['file path'] = $task['path'];
    $items['admin/workbench']['file'] = $task['file'];
  }

  else {
    //variable_set('workbench_myworkbench_disabled', TRUE);
    if (!empty($GLOBALS['page_manager_enabling_workbench'])) {
      drupal_set_message(t('Page manager module is unable to enable Workbench because some other module already has overridden with %callback.', array('%callback' => $callback)), 'warning');
    }
    return;
  }
}

/**
 * Entry point for our overridden My Workbench.
 *
 * This function asks its assigned handlers who, if anyone, would like
 * to run with it. If no one does, it passes through to the main My Workbench.
 */
function workbench_myworkbench() {
  // Load my task plugin
  $task = page_manager_get_task('myworkbench');

  ctools_include('context');
  ctools_include('context-task-handler');
  $output = ctools_context_handler_render($task, '', array(), array());
  if ($output !== FALSE) {
    return $output;
  }

  module_load_include('inc', 'workbench', 'workbench.pages');
  $function = 'workbench_content';
  foreach (module_implements('page_manager_override') as $module) {
    $call = $module . '_page_manager_override';
    if (($rc = $call('workbench')) && function_exists($rc)) {
      $function = $rc;
      break;
    }
  }

  // Otherwise, fall back.
  return $function();
}

/**
 * Callback to enable/disable the page from the UI.
 */
function workbench_myworkbench_enable($cache, $status) {
  variable_set('workbench_myworkbench_disabled', $status);
  // Set a global flag so that the menu routine knows it needs
  // to set a message if enabling cannot be done.
  if (!$status) {
    $GLOBALS['page_manager_enabling_workbench'] = TRUE;
  }
}
