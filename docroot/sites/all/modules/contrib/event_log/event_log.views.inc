<?php

/**
 * @file
 * Provide views data and handlers for event_logs.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 */
function event_log_views_data() {
  $data['event_log']['table']['group'] = t('Event log');

  // Advertise this table as a possible base table
  $data['event_log']['table']['base'] = array(
    'field' => 'lid',
    'title' => t('Logged Events'),
    'weight' => -10,
    'defaults' => array(
      'field' => 'lid',
    ),
  );

  // lid
  $data['event_log']['lid'] = array(
    'title' => t('Log event ID'),
    'help' => t('Log event ID.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // type
  $data['event_log']['type'] = array(
    'title' => t('Type'),
    'help' => t('Event handler type.'),
    'field' => array(
      'field' => 'type',
      'group' => t('Event log'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // operation
  $data['event_log']['operation'] = array(
    'title' => t('Operation'),
    'help' => t('Event handler type.'),
    'field' => array(
      'group' => t('Event log'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // form_id
  $data['event_log']['form_id'] = array(
    'title' => t('Form ID'),
    'help' => t('ID of the submitted form, if available.'),
    'field' => array(
      'group' => t('Event log'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // uid field
  $data['event_log']['uid'] = array(
    'title' => t('User uid'),
    'help' => t('The user that triggered the event.'),
    'relationship' => array(
      'title' => t('Author'),
      'help' => t('Relate search to the user who triggered the event.'),
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('author'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_user_name',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'field' => array(
      'handler' => 'views_handler_field_user',
    ),
  );

  // ip
  $data['event_log']['ip'] = array(
    'title' => t('IP address'),
    'help' => t('IP address of the user that triggered the event.'),
    'field' => array(
      'group' => t('Event log'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // description
  $data['event_log']['description'] = array(
    'title' => t('Description'),
    'help' => t('Description of the event.'),
    'field' => array(
      'group' => t('Event log'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // info
  $data['event_log']['info'] = array(
    'title' => t('Info'),
    'help' => t('Meta information about the event, such as a serialized object.'),
    'field' => array(
      'group' => t('Event log'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // path
  $data['event_log']['path'] = array(
    'title' => t('Path'),
    'help' => t('The active menu link path while the event occurred.'),
    'field' => array(
      'group' => t('Event log'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // created field
  $data['event_log']['created'] = array(
    'title' => t('Event timestamp'),
    'help' => t('The timestamp that the event occurred.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // references
  $data['event_log']['ref_numeric'] = array(
    'title' => t('Numeric reference'),
    'help' => t('The meaning of this reference depends on the event type and operation. You can reference the object by using the correct relationship.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['event_log']['ref_char'] = array(
    'title' => t('Alphabetical reference'),
    'help' => t('The meaning of this reference depends on the event type and operation. You can reference the object by using the correct relationship.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_data_alter().
 * @param $data
 */
function event_log_views_data_alter(&$data) {
  // Combine all event log relationships, per {table,field}.
  $relationships = array();
  $handlers = event_log_get_event_handlers();
  foreach ($handlers as $type => $handler) {
    if (!empty($handler['relationships'])) {
      foreach ($handler['relationships'] as $info) {
        if (!array_key_exists($info['table'], $relationships)) {
          $relationships[$info['table']] = array();
        }
        if (!array_key_exists($info['field'], $relationships[$info['table']])) {
          $relationships[$info['table']][$info['field']] = array(
            'numeric' => !empty($info['numeric']),
            'types' => array()
          );
        }
        $relationships[$info['table']][$info['field']]['types'][$type] = array(
          'operations' => $info['operations'],
        );
      }
    }
  }

  // Add handlers for every referable object.
  foreach ($relationships as $table => $fields) {
    foreach ($fields as $field => $field_info) {

      $ref_field_name = ($field_info['numeric'] ? 'ref_numeric' : 'ref_char');
      $field_key = $ref_field_name . '_' . $table . '_' . $field;

      // Forward reference.
      $types_str = '';
      foreach ($field_info['types'] as $type => $info) {
        if ($types_str != '') {
          $types_str .= ', ';
        }
        $types_str .= $type;
        if ($info['operations'] !== NULL) {
          $types_str .= ' ' . t('(operations: @operations)', array('@operations' => implode(',', $info['operations'])));
        }
      }

      $title = t('Event log record reference to @table.@field', array(
        '@table' => $table,
        '@field' => $field
      ));
      $help = t('This reference works for the following event types: @types_str', array('@types_str' => $types_str));

      $data['event_log'][$field_key] = array(
        'title' => $title,
        'help' => $help,
        'relationship' => array(
          'title' => $title,
          'help' => $help,
          'handler' => 'views_handler_relationship',
          'base' => $table,
          'base field' => $field,
          'label' => $title,
          'relationship field' => $ref_field_name,
        ),
      );

      $extra_str = '';
      foreach ($field_info['types'] as $type => $info) {
        if ($extra_str != '') {
          $extra_str .= ' OR ';
        }
        $extra_str .= '((event_log.type = \'' . $type . '\') AND ';
        if ($info['operations'] !== NULL) {
          $extra_str .= '(event_log.operation IN (\'' . implode('\',\'', $info['operations']) . '\'))';
        }
        else {
          $extra_str .= '1';
        }
        $extra_str .= ')';
      }

      $data['event_log'][$field_key]['relationship']['extra'] = $extra_str;

      // Backward reference.
      $data[$table]['event_log'] = array(
        'title' => t('Reverse: @title', array('@title' => $title)),
        'help' => $help,
        'group' => t('Event log'),
        'relationship' => array(
          'title' => t('Reverse: @title', array('@title' => $title)),
          'help' => $help,
          'handler' => 'views_handler_relationship',
          'base' => 'event_log',
          'base field' => $ref_field_name,
          'label' => t('Reverse: @title', array('@title' => $title)),
          'relationship field' => $field,
          'extra' => str_replace("event_log", "%alias", $extra_str),
        ),
      );
    }
  }
}
