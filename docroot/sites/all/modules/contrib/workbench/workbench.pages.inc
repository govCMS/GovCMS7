<?php

/**
 * @file
 * Workbench page callbacks.
 */

/**
 * Page callback for the workbench content page.
 *
 * Note that we add Views information to the array and render
 * the Views as part of the alter hook provided here.
 *
 * @see hook_workbench_content_alter()
 *
 * @return
 *  A Render API array of content creation options.
 */
function workbench_content() {
  $output = array();

  // Allow other modules to add content here.
  $output['#attributes'] = array('class' => array('admin', 'my-workbench'));
  $output['#attached'] = array(
    'css' => array(drupal_get_path('module', 'workbench') . '/css/workbench.my-workbench.css'),
  );
  $output['#theme'] = 'workbench_element';
  // This left column is given a width of 35% by workbench.myworkbench.css.
  $output['workbench_current_user'] = array(
    '#title' => t('My Profile'),
    '#view' => 'workbench_current_user',
    '#view_display' => 'block_1',
    '#attributes' => array('class' => array('left', 'clearfix')),
    '#theme' => 'workbench_element',
  );
  // This right column is given a width of 65% by workbench.myworkbench.css.
  $output['workbench_edited'] = array(
    '#view' => 'workbench_edited',
    '#view_display' => 'block_1',
    '#attributes' => array('class' => array('right', 'clearfix')),
    '#theme' => 'workbench_element',
  );
  $output['workbench_recent_content'] = array(
    '#view' => 'workbench_recent_content',
    '#view_display' => 'block_1',
    '#attributes' => array('class' => array('clearfix'), 'style' => array('clear: both;')),
    '#theme' => 'workbench_element',
  );

  // Allow other modules to alter the default page.
  drupal_alter('workbench_content', $output);

  // Transform the Views into markup.
  // @see views_embed_view()
  foreach (element_children($output) as $key) {
    if (isset($output[$key]['#view']) && $view = views_get_view($output[$key]['#view'])) {
      $output[$key] += array('#markup' => '', '#view_display' => 'default');
      $display_id = $output[$key]['#view_display'];

      // Build contextual links.
      if (module_exists('contextual')) {
        $output[$key] += contextual_element_info();
        views_add_contextual_links($output[$key]['contextual_links'], 'block', $view, $display_id);
      }

      if ($view->access($display_id)) {
        $output[$key]['#markup'] .= $view->preview($display_id, array());
        if ($title = $view->get_title()) {
          $output[$key]['#title'] = $title;
        }
      }
      $view->destroy();
    }
  }

  return $output;
}

/**
 * Simple page to show list of content type to create.
 *
 * @see hook_workbench_create_alter()
 *
 * @return
 *  A Render API array of content creation options.
 */
function workbench_create() {
  $output = array();
  $output['workbench_create_default'] = _workbench_create();

  // Allow other modules to add content here.
  drupal_alter('workbench_create', $output);

  return $output;
}

/**
 * Emulate node/add to return content creation list.
 *
 * @return
 *  A Render API array of content creation options.
 */
function _workbench_create() {
  $output = array();
  $output['#markup'] = '<h3>' . t('Create content') . '</h3>';

  $item = menu_get_item('node/add');
  $content = system_admin_menu_block($item);

  if (!empty($content)) {
    // Theme the arrray of content type creation links.
    $output['#markup'] .= theme('node_add_list', array('content' => $content));
  }
  else {
    $output['#markup'] .= t('You cannot create any new content. Please contact the site administrator.');
  }

  return $output;
}
