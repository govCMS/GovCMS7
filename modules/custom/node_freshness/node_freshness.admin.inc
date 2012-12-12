<?php

/**
 * @file
 * Provides menu callbacks for node_freshness.
 */

/**
 * Page callback for admin config form.
 */
function node_freshness_config() {
  $form = array();

  $defaults = _node_freshness_get();
  $form['node_freshness'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
  );

  // Enter number of units.
  $form['node_freshness']['node_freshness_amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount'),
    '#description' => t('Now long is content determined as fresh.'),
    '#default_value' => $defaults['node_freshness_amount'],
    '#element_validate' => array('element_validate_integer_positive'),
    '#size' => 10,
  );

  // Enter node freshness type.
  $form['node_freshness']['node_freshness_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#description' => t('Now long is content determined as fresh.'),
    '#options' => array(
      'month' => t('Month'),
      'year' => t('Year'),
    ),
    '#default_value' => $defaults['node_freshness_type'],
  );

  return system_settings_form($form);
}
