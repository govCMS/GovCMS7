<?php

/**
 * @file
 * Views field handler. Contains all relevant Draggableviews
 * options and related logic.
 * Implements the Views Form API.
 */

class draggableviews_handler_field_draggable extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();

    $options['draggableviews'] = array(
      'contains' => array(
        'handler' => array('default' => 'draggableviews_handler_native'),
        'save_button_label' => array('default' => 'Save'),
        'ajax' => array('default' => FALSE),
      ),
    );

    // Populate default values of form elements provided by handlers.
    foreach (draggableviews_get_handlers() as $handler_id => $handler_object) {
      $options['draggableviews']['contains'][$handler_id] = array('default' => $handler_object->option_definition());
    }
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove not needed settings options.
    $form['alter']['#access'] = FALSE;
    $form['style_settings']['#access'] = FALSE;
    $form['empty_field_behavior']['#access'] = FALSE;

    $form['draggableviews'] = array(
      '#type' => 'fieldset',
      '#title' => t('Draggable Views'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $handler_options = array();
    $handler_forms = array();
    foreach (draggableviews_get_handlers() as $handler_id => $handler_object) {
      $handler = ctools_get_plugins('draggableviews', 'handler', $handler_id);
      $handler_options[$handler_id] = filter_xss($handler['label']);
      $handler_forms[$handler_id] = $handler_object->options_form($this);
    }

    $form['draggableviews']['handler'] = array(
      '#type' => 'select',
      '#title' => t('Handler'),
      '#options' => $handler_options,
      '#default_value' => $this->options['draggableviews']['handler'],
    );

    // Add handler's form element as fielset that
    // is active only if handler selected.
    foreach ($handler_forms as $handler_id => $handler_form_element) {
      // Skip empty handler's form elements.
      if (empty($handler_form_element)) {
        continue;
      }
      $form['draggableviews'][$handler_id] = array(
        '#type' => 'fieldset',
        '#title' => check_plain($form['draggableviews']['handler']['#options'][$handler_id]),
        '#collapsible' => FALSE,
        '#states' => array(
          'visible' => array(
            'select[name="options[draggableviews][handler]"]' => array('value' => $handler_id),
          ),
        ),
      );
      foreach ($handler_form_element as $key => $form_element) {
        $form['draggableviews'][$handler_id][$key] = $form_element;
      }
    }

    $form['draggableviews']['save_button_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom Save button label'),
      '#description' => t("Allow to change Save button Label."),
      '#default_value' => $this->options['draggableviews']['save_button_label'],
    );

    $form['draggableviews']['ajax'] = array(
      '#type' => 'checkbox',
      '#title' => t('Ajax'),
      '#description' => t('Use ajax in draggable form.'),
      '#default_value' => $this->options['draggableviews']['ajax'],
    );
  }

  function render($values) {
    if (user_access('access draggableviews')) {
      return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
    }
  }

  /**
   * The form which replaces the placeholder from render().
   */
  function views_form(&$form, &$form_state) {
    // The view is empty, abort.
    if (empty($this->view->result)) {
      return;
    }

    $form[$this->options['id']] = array(
      '#tree' => TRUE,
    );
    $range = count($this->view->result);
    // At this point, the query has already been run, so we can access the results
    // in order to get the base key value (for example, nid for nodes).
    foreach ($this->view->result as $row_index => $row) {
      $entity_id = $this->get_value($row);

      $form[$this->options['id']][$row_index] = array(
        '#tree' => TRUE,
      );

      $handler_object = draggableviews_get_handler_class($this->options['draggableviews']['handler']);

      // Weight field selectbox.
      $form[$this->options['id']][$row_index]['weight'] = array(
        '#type' => 'select',
        '#options' => range(-$range, $range),
        '#attributes' => array('class' => array('draggableviews-weight')),
        '#default_value' => $handler_object->get($this, $row_index),
      );
      // Item to keep id of the entity.
      $form[$this->options['id']][$row_index]['id'] = array(
        '#type' => 'hidden',
        '#value' => $this->view->result[$row_index]->{$this->field_alias},
      );
    }
  }
}