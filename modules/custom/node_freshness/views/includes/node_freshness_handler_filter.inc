<?php
// @codingStandardsIgnoreFile
/**
 * @file
 * Provides node_freshness views handler implementation.
 */

/**
 * Custom filter handler for views, that handles DATETIME
 */
class node_freshness_handler_filter extends views_handler_filter_date {

  /**
   * Add our node_freshness option.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['value'] = array(
      'contains' => array(
        'node_freshness' => array('default' => '>'),
      ),
    );

    return $options;
  }

  /**
   * Add our node_freshness operator.
   */
  function operators() {
    $operators = parent::operators();

    $operators += array(
      'node_freshness' => array(
        'title' => t('Node freshness'),
        'short' => t('node_freshness'),
        'method' => 'op_node_freshness',
      ),
    );

    return $operators;
  }

  /**
   * Add a node_freshness type to the date handler.
   */
  function value_form(&$form, &$form_state) {
    // Get the parents form.
    parent::value_form($form, $form_state);

    $form['value']['node_freshness'] = array(
      '#type' => 'radios',
      '#title' => t('Node Freshness'),
      '#options' => array(
        '>' => t('Is greater than node freshness.'),
        '<' => t('Is less than node freshness.'),
      ),
      '#default_value' => $this->value['node_freshness'],
      '#dependency' => array(
        'edit-options-operator' => array(
          'node_freshness',
        ),
      ),
    );

    // Get a list of dependancies and remove node_freshness.
    $deps = $form['operator']['#options'];
    unset($deps['node_freshness']);

    // Set dependancies for value types.
    $form['value']['type']['#dependency']['edit-options-operator'] = array_keys($deps);
  }

  /**
   * Custom method for node freshness.
   */
  function op_node_freshness($field) {
    if (!empty($this->value['node_freshness'])) {
      // Get the node_freshness value.
      $values = _node_freshness_get();
      $value = $values['value'];
      $condition = $this->value['node_freshness'];
      $this->query->add_where_expression($this->options['group'], "$field $condition '$value'");
    }
  }
}
