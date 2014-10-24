<?php

/**
 * @file
 * The 'Event log' module admin pages.
 *
 * @author Bas van Meurs
 * @copyright Cipix Internet
 */

/**
 * Menu callback.
 * @return array|mixed
 */
function event_log_overview_page() {
  $form_state = array('method' => 'get');
  $_GET['form_id'] = 'event_log_overview_page_form';
  $form = drupal_build_form('event_log_overview_page_form', $form_state);
  unset($form['form_build_id']);
  return $form;
}

/**
 * Page callback that shows all logged events.
 */
function event_log_overview_page_form($form, &$form_state) {

  $form['#method'] = 'get';
  $form['#action'] = url('admin/reports/events');

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('Filters'),
    '#description' => t('Filter the events.'),
  );

  $handlers = event_log_get_event_handlers();

  // Add type filter.
  $options = array();
  foreach ($handlers as $type => $handler) {
    $options[$type] = $handler['title'];
  }

  $form['filters']['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t('Event type'),
    '#options' => array('' => 'Select a type') + $options,
    '#ajax' => array(
      'event' => 'change',
      'wrapper' => 'operation-dropdown-replace',
      'path' => 'admin/reports/events/ajax-get-operations',
      'method' => 'replace',
    ),
  );

  $form['filters']['operation'] = _event_log_overview_page_form_get_operations(empty($form_state['input']['type']) ? '' : $form_state['input']['type']);

  // Add reference filters.
  $form['filters']['id'] = array(
    '#type' => 'textfield',
    '#size' => 5,
    '#title' => t('ID'),
    '#prefix' => '<br />',
    '#description' => t('The id of the subject (numeric).'),
  );

  $form['filters']['name'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#title' => t('Name'),
    '#description' => t('The (machine) name of the subject.'),
  );

  $form['filters']['path'] = array(
    '#type' => 'textfield',
    '#size' => 30,
    '#title' => t('Path'),
    '#description' => t('The full path.'),
  );

  $form['filters']['keyword'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#title' => t('Keyword'),
    '#description' => t('Search in the description.'),
  );

  $form['filters']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Apply'),
  );

  // Make fieldset expanded if one of the filters is entered.
  $form['filters']['#collapsed'] = TRUE;
  foreach ($form['filters'] as $name => $item) {
    if ($name == 'submit') {
      continue;
    }

    if (!empty($form_state['values'][$name])) {
      $form['filters']['#collapsed'] = FALSE;
    }
  }

  if (!empty($form_state['submitted'])) {
    // Add results.
    $table = array(
      '#theme' => 'table',
      '#header' => array(
        array('data' => 'created', 'field' => 'created', 'sort' => 'desc'),
        array('data' => 'type', 'field' => 'type'),
        array('data' => 'operation', 'field' => 'operation'),
        array('data' => 'path', 'field' => 'path'),
        array('data' => 'form id', 'field' => 'form_id'),
        array('data' => 'description', 'field' => 'description'),
        array('data' => 'user', 'field' => 'uid'),
        array('data' => 'ip', 'field' => 'ip'),
        array('data' => 'ID', 'field' => 'ref_numeric'),
        array('data' => 'Name', 'field' => 'ref_char'),
        array('data' => 'info'),
      ),
      '#rows' => array(),
    );

    $query = db_select('event_log', 'c')
      ->fields('c')
      ->extend('TableSort')
      ->orderByHeader($table['#header'])
      ->extend('PagerDefault')
      ->limit(50);

    // Apply filters.
    if (!empty($form_state['values']['type'])) {
      $query->condition('type', $form_state['values']['type']);
      if (!empty($form_state['values']['operation'])) {
        $query->condition('operation', $form_state['values']['operation']);
      }
    }
    if (!empty($form_state['values']['id'])) {
      $query->condition('ref_numeric', $form_state['values']['id']);
    }
    if (!empty($form_state['values']['name'])) {
      $query->condition('ref_char', $form_state['values']['name']);
    }
    if (!empty($form_state['values']['path'])) {
      $query->condition('path', $form_state['values']['path']);
    }
    if (!empty($form_state['values']['keyword'])) {
      $query->condition('description', '%' . db_like($form_state['values']['keyword']) . '%', 'LIKE');
    }

    $total = $query->countQuery()->execute()->fetchField();
    $table['#caption'] = t('@total events found', array('@total' => $total));

    $result = $query->execute();

    foreach ($result as $record) {
      if (!empty($record->uid)) {
        $account = user_load($record->uid);
      }
      else {
        $account = NULL;
      }
      $table['#rows'][] = array(
        array('data' => check_plain(date("Y-m-d H:i:s", $record->created))),
        array('data' => check_plain($record->type)),
        array('data' => check_plain($record->operation)),
        array('data' => check_plain($record->path)),
        array('data' => check_plain($record->form_id)),
        array('data' => $record->description),
        array('data' => (empty($account) ? '' : l($account->name, 'user/' . $account->uid))),
        array('data' => check_plain($record->ip)),
        array('data' => check_plain($record->ref_numeric)),
        array('data' => check_plain($record->ref_char)),
        array('data' => (empty($record->info) ? '' : '<div class="event-log-info"><pre>' . check_plain($record->info) . '</pre></div>')),
      );
    }

    $render = array(
      'table' => $table,
      'pager' => array('#theme' => 'pager'),
    );

    drupal_add_js(drupal_get_path('module', 'event_log') . '/js/event_log.admin.js');

    $form['results'] = $render;
  }

  // No token checking and/or caching.
  unset($form['#token']);
  $form_state['no_cache'] = TRUE;

  return $form;
}

/**
 * Returns the form element for the operations based on the event log type.
 * @param $type
 * @return
 *   A form element.
 */
function _event_log_overview_page_form_get_operations($type) {
  $element = array(
    '#type' => 'select',
    '#name' => 'operation',
    '#title' => t('Operation'),
    '#description' => t('The entity operation.'),
    '#options' => array('' => t('Choose an operation')),
    '#prefix' => '<div id="operation-dropdown-replace">',
    '#suffix' => '</div>',
  );

  if ($type) {
    $query = db_select('event_log', 'e')
      ->fields('e', array('operation'))
      ->condition('type', $type)
      ->groupBy('operation');
    $query->addExpression('COUNT(e.lid)', 'c');
    $query->distinct(TRUE);
    $results = $query->execute()->fetchAllKeyed(0);
    $operations = array();
    foreach ($results as $name => $count) {
      $operations[$name] = $name . ' (' . $count . ')';
    }
    $element['#options'] += $operations;
  }

  return $element;
}

function event_log_overview_page_form_submit($form, &$form_state) {
  // Prevent infinite recursion error.
  $form_state['redirect'] = FALSE;

  // Rebuild to show data.
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for the operations options.
 */
function event_log_overview_page_form_get_operations() {
  return _event_log_overview_page_form_get_operations($_REQUEST['type']);
}
