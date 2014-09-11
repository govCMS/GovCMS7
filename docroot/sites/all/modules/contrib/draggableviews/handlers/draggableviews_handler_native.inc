<?php

/**
 * @file
 * Native handler plugin.
 */

$plugin = array(
  'label' => 'Native',
  'handler' => array(
    'class' => 'draggableviews_handler_native',
  ),
);

class draggableviews_handler_native extends draggableviews_handler {
  public function get($field, $index) {
    $row = $field->view->result[$index];
    return (isset($row->draggableviews_structure_weight)) ? $row->draggableviews_structure_weight : 0;
  }

  function set($form_state) {
    $fv = $form_state['values'];
    $view = $form_state['build_info']['args'][0];
    $view_name = $view->name;
    $view_display = $view->current_display;
    // View arguments.
    $arguments = $view->args;
    if (isset($view->exposed_raw_input)) {
      $arguments += $view->exposed_raw_input;
      ksort($arguments);
      // Redirect view to the same page with exposed filters set.
      $form_state['redirect'] = array(current_path(), array('query' => $view->exposed_raw_input));
    }

    // Give other modules a chance to alter saved arguments.
    drupal_alter('draggableviews_handler_native_arguments', $arguments, $view, $fv['draggableviews']);

    $args_string = json_encode($arguments);

    // Save records to our custom table.
    foreach ($fv['draggableviews'] as $item) {
      // Make sure id is available.
      if (!isset($item['id'])) {
        continue;
      }
      // Delete previous order record.
      db_delete('draggableviews_structure')
        ->condition('view_name', $view_name)
        ->condition('view_display', $view_display)
        ->condition('args', $args_string)
        ->condition('entity_id', $item['id'])
        ->execute();

      // Create new order record.
      $record = array(
        'view_name' => $view_name,
        'view_display' => $view_display,
        'args' => $args_string,
        'entity_id' => $item['id'],
        'weight' => $item['weight'],
      );
      drupal_write_record('draggableviews_structure', $record);
    }
  }
}
