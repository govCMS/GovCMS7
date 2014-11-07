<?php
/**
 * @file
 * user_action_report.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function user_action_report_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'admin_user_actions';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'event_log';
  $view->human_name = 'Administration: User Actions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'User Actions';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view user actions';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'name' => 'name',
    'operation' => 'operation',
    'description' => 'description',
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operation' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'description' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Event log: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'event_log';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Event log: Event log record reference to node.nid */
  $handler->display->display_options['relationships']['ref_numeric_node_nid']['id'] = 'ref_numeric_node_nid';
  $handler->display->display_options['relationships']['ref_numeric_node_nid']['table'] = 'event_log';
  $handler->display->display_options['relationships']['ref_numeric_node_nid']['field'] = 'ref_numeric_node_nid';
  /* Field: Event log: Event timestamp */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'event_log';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Timestamp';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Event log: Operation */
  $handler->display->display_options['fields']['operation']['id'] = 'operation';
  $handler->display->display_options['fields']['operation']['table'] = 'event_log';
  $handler->display->display_options['fields']['operation']['field'] = 'operation';
  /* Field: Event log: Description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'event_log';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['exclude'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'ref_numeric_node_nid';
  $handler->display->display_options['fields']['title']['empty'] = '[description]';
  /* Sort criterion: Event log: Event timestamp */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'event_log';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'OR',
    2 => 'AND',
  );
  /* Filter criterion: Event log: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'event_log';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = 'node';
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Event log: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'event_log';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = 'authentication';
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  /* Filter criterion: Event log: Operation */
  $handler->display->display_options['filters']['operation']['id'] = 'operation';
  $handler->display->display_options['filters']['operation']['table'] = 'event_log';
  $handler->display->display_options['filters']['operation']['field'] = 'operation';
  $handler->display->display_options['filters']['operation']['operator'] = '!=';
  $handler->display->display_options['filters']['operation']['value'] = 'view';
  $handler->display->display_options['filters']['operation']['group'] = 2;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 2;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'User';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    3 => 0,
  );
  /* Filter criterion: Event log: Event timestamp */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'event_log';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['operator'] = '>=';
  $handler->display->display_options['filters']['created']['group'] = 2;
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Timestamp';
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    3 => 0,
  );
  /* Filter criterion: Event log: Type */
  $handler->display->display_options['filters']['type_2']['id'] = 'type_2';
  $handler->display->display_options['filters']['type_2']['table'] = 'event_log';
  $handler->display->display_options['filters']['type_2']['field'] = 'type';
  $handler->display->display_options['filters']['type_2']['value'] = 'user';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/reports/user-actions';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'User Actions';
  $handler->display->display_options['menu']['description'] = 'Provides a report of user actions.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $export['admin_user_actions'] = $view;

  return $export;
}
