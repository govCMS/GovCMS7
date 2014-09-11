<?php

/**
 * @file
 * Views hooks implementations.
 */

/**
 * Implements hook_views_data_alter().
 */
function draggableviews_views_data_alter(&$data) {

  $data['draggableviews_structure']['weight'] = array(
    'title' => t('Weight'),
    'help' => t('Sort entities by the draggableviews weight table field.'),
    'group' => t('Draggableviews'),
    'sort' => array(
      'handler' => 'draggableviews_handler_sort',
    ),
  );

  foreach (entity_get_info() as $entity_type => $info) {
    if (isset($info['base table']) && isset($data[$info['base table']]['table'])) {
      $data[$info['base table']]['draggableviews'] = array(
        'title' => $data[$info['base table']]['table']['group'],
        'group' => t('Draggableviews'),
        'help' => t('Provide a draggable functionality.'),
        'real field' => $info['entity keys']['id'],
        'field' => array(
          'handler' => 'draggableviews_handler_field_draggable',
          'click sortable' => FALSE,
        ),
      );

      // Explain to every entity how to join with draggableviews structure table.
      $data['draggableviews_structure']['table']['join'][$info['base table']] = array(
        'handler' => 'draggableviews_join_handler',
        'left_table' => $info['base table'], // Because this is a direct link it could be left out.
        'left_field' => $info['entity keys']['id'],
        'field' => 'entity_id',
      );
    }
  }
}
