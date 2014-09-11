<?php

/**
 * @file
 * Field API handler plugin.
 */

$plugin = array(
  'label' => 'FieldAPI',
  'handler' => array(
    'class' => 'draggableviews_handler_fieldapi',
  ),
);

class draggableviews_handler_fieldapi extends draggableviews_handler {
  /**
  * Set default value of field option.
  */
  public function option_definition() {
    return array('field' => '');
  }

  /**
  * Add field options for handler.
  */
  function options_form($field) {
    $form = array();
    $options = array('' => t('- Select -'));

    // Check all the sortings added to a view. Hope there is
    // better way to determine them. Need to research.
    $sorts = $field->view->display_handler->display->display_options['sorts'];
    // If no sorts avaialble for current display, use sorts from default display.
    if (empty($sorts)) {
      $sorts = $field->view->display['default']->display_options['sorts'];
    }
    foreach ($sorts as $sort_option) {
      $field_name = $sort_option['field'];
      // Field should be like "field_name_value".
      if (strpos($field_name, 'field_') === FALSE || strpos($field_name, '_value') === FALSE) {
        continue;
      }

      // Remove "_value" from field name and try to load the field.
      $field_name = drupal_substr($field_name, 0, drupal_strlen($field_name) - 6);
      if ($field_info = field_info_field($field_name)) {
        if ($field_info['type'] == 'number_integer') {
          $views_field_data = field_views_field_default_views_data($field_info);
          $options[$sort_option['table'] . ':' . $sort_option['field']] = filter_xss($views_field_data[$sort_option['table']][$sort_option['field']]['title']);
        }
      }
    }

    // If options are emtpy, show warning message.
    if (count($options) == 1) {
      $form['field_warning'] = array(
        '#markup' => '<div class="messages warning">' . t('Add weight integer field to sorts so it can be selected.') . '</div>',
      );
    }

    $form['field'] = array(
      '#type' => 'select',
      '#title' => t('Field'),
      '#options' => $options,
      '#default_value' => $field->options['draggableviews']['draggableviews_handler_fieldapi']['field'],
      '#description' => t('Please select field that contains weight. It should be integer type and already added to sorts of the view.'),
    );
    return $form;
  }

  function get($field, $index) {
    // Get the name of selected field.
    $field_option = $field->options['draggableviews']['draggableviews_handler_fieldapi']['field'];
    list($field_table, $field_name) = explode(':', $field_option);
    // Current row.
    $row = $field->view->result[$index];
    // Check whether key has table name and field name in it.
    foreach ($row as $key => $value) {
      if (strpos($key, $field_table) !== FALSE && strpos($key, $field_name) !== FALSE) {
        return $value;
      }
    }
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

    $base_table = $view->base_table;
    $entity_info_all = entity_get_info();
    $entity_type = '';
    foreach ($entity_info_all as $entity_name_key => $entity_info) {
      if ($entity_info['base table'] == $view->base_table) {
        $entity_type = $entity_name_key;
        break;
      }
    }

    $options_field = $view->field['draggableviews']->options['draggableviews']['draggableviews_handler_fieldapi']['field'];
    list($field_tabe, $field_column) = explode(':', $options_field);
    // Remove '_value' from column name to get field name.
    $field_name = drupal_substr($field_column, 0, drupal_strlen($field_column) - 6);

    // Save the values of the field.
    foreach ($fv['draggableviews'] as $item) {
      if (isset($item['id']) && isset($item['weight'])) {
        $entity_wrapper = entity_metadata_wrapper($entity_type, $item['id']);
        $entity_wrapper->{$field_name}->set($item['weight']);
        $entity_wrapper->save();
      }
    }
  }
}
