<?php

/**
 * @file
 * Native handler sort.
 */

/**
 * Sort handler for ordering by weight.
 */
class draggableviews_handler_sort extends views_handler_sort {
  function query() {
    $this->ensure_my_table();
    // If new items should be placed in the bottom.
    if ($this->options['draggableviews_setting_new_items_bottom_list']) {
      // ORDER BY COALESCE(weight, 10000)
      // New items will get big default instead of NULL
      $as = $this->table_alias . '_' . $this->real_field;
      $as = $this->query->add_field($this->table_alias, $this->real_field, $as, array());
      $this->query->orderby[] = array(
        'field' => 'COALESCE(' . $as . ', 10000)',
        'direction' => drupal_strtoupper($this->options['order'])
      );
    }
    else {
      // New items will be placed at the top as have NULL value.
      $this->query->add_orderby($this->table_alias, $this->real_field);
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    // This handler invokes few times for one view,
    // in the first time the $this->view->name is empty,
    // so we need this check.
    if (is_object($this->view)) {
      $options['draggableviews_setting_view'] = array('default' => $this->view->name);
    }
    else {
      $options['draggableviews_setting_view'] = array('default' => 'self');
    }

    $options['draggableviews_setting_arguments'] = array('default' => 'all');
    $options['draggableviews_setting_arguments_php'] = array('default' => '');
    $options['draggableviews_setting_new_items_bottom_list'] = array('default' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['expose_button']['#access'] = FALSE;
    $form['order']['#description'] = t('Please remember to override settings of the sort criterion if you have display that sets weights and you choose descendling order.');

    // Check whether current views display doesn't have draggableviews field.
    // If it has, it means that this is setting view so we should set
    // option draggableviews_setting_view to 'self'
    $view_clone = clone $this->view;
    $view_clone->build($view_clone->current_display);
    $options = 'self';
    // Check whether field exists. If not it is displaying view so lets show
    // all options of other setting views.
    if (!isset($view_clone->field['draggableviews'])) {
      // Get list of all enabled views.
      $views_list = views_get_enabled_views();
      $options = array();

      // Convert list of objects to options for the form.
      foreach ($views_list as $view_name => $view_object) {
        foreach ($view_object->display as $display_name => $display) {
          if ($display_name == 'default') {
            continue;
          }
          // Clone view and build it so we can see all the fields.
          $view_clone = clone $view_object;
          $view_clone->build($display_name);

          // If draggableviews field attached, show this view in options.
          if (isset($view_clone->field['draggableviews'])) {
            $options[$view_name . ':' . $display_name] = $view_object->human_name . ' (' . $display->display_title . ')';
          }
        }
      }
    }

    // If it is setting view.
    if (!is_array($options)) {
      $form['order']['#access'] = FALSE;
      $options = isset($this->options['draggableviews_setting_view']) ? $this->options['draggableviews_setting_view'] : 'self';
      $form['draggableviews_setting_view'] = array(
        '#type' => 'value',
        '#value' => $options,
      );
    }
    else {
      $form['draggableviews_setting_view'] = array(
        '#type' => 'select',
        '#title' => t('Display sort as'),
        '#default_value' => $this->options['draggableviews_setting_view'],
        '#options' => $options,
        '#description' => t('Please choose the view and display that sets the order.')
      );
      // If there is no setting views available, show error message.
      if (empty($options)) {
        drupal_set_message(t('First you should create a view that sets sorting order.'), 'error');
      }
    }

    $form['draggableviews_setting_arguments'] = array(
      '#title' => t('Arguments handling'),
      '#type' => 'radios',
      '#options' => array(
        'all' => t('Use all arguments'),
        'none' => t('Do not use any arguments (use empty arguments)'),
        'php' => t('Prepare arguments with PHP code'),
      ),
      '#default_value' => $this->options['draggableviews_setting_arguments'],
      '#description' => t('When sorting order is saved all arguments passed are saved with order. In display view we can choose how to use these arguments.')
    );
    $form['draggableviews_setting_arguments_php'] = array(
      '#title' => t('PHP code to prepare arguments'),
      '#type' => 'textarea',
      '#default_value' => $this->options['draggableviews_setting_arguments_php'],
      '#states' => array(
        'visible' => array(
          'input[name="options[draggableviews_setting_arguments]"]' => array('value' => 'php'),
        ),
      ),
    );
    $form['draggableviews_setting_new_items_bottom_list'] = array(
      '#type' => 'checkbox',
      '#title' => t('New items appear bottom of the list'),
      '#description' => t('New items means elements (for example nodes) that do not have saved weight (newly created).'),
      '#default_value' => $this->options['draggableviews_setting_new_items_bottom_list'],
    );
  }
}
