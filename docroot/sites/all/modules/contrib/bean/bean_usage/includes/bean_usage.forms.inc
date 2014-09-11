<?php
function bean_usage_settings() {
  $form = array();

  $form['bean_usage_results'] = array(
    '#type' => 'fieldset',
    '#title' => t('Results per page'),
    '#weight' => 0,
    '#collapsible' => FALSE,
  );

  $form['bean_usage_results']['bean_usage_results_per_page'] = array(
    '#title' => t('Results per page'),
    '#description' => t('How many results display per page on the bean usage page'),
    '#type' => 'select',
    '#options' => array(
      '5' => 5,
      '10' => 10,
      '15' => 15,
      '20' => 20,
      '25' => 25,
      '30' => 30,
      '35' => 35,
      '40' => 40,
      '45' => 45,
      '50' => 50,
    ),
    '#default_value' => variable_get('bean_usage_results_per_page', 30),
  );

  return system_settings_form($form);
}

/**
 * Filter form for bean usage view
 *
 * @return array
 */
function bean_usage_filters() {
  $params = drupal_get_query_parameters();
  $filters = empty($params['filter']) ? '' : explode(',', $params['filter']);

  $form = array();

  $form['bean_usage_filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter by bean type'),
    '#weight' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $bean_types = bean_get_types();
  $options = array();
  foreach ($bean_types as $bean) {
    $options[$bean->type] = $bean->type;
  }

  asort($options);
  $multiple = TRUE;

  $form['bean_usage_filter']['bean_usage_filter_type'] = array(
    '#type' => 'select',
    '#prefix' => '<div style="margin-right:10px; position:relative; float:left;">',
    '#suffix' => '</div>',
    '#multiple' => $multiple,
    '#size' => $multiple ? min(4, count($options)) : 0,
    '#title' => t('Filter type'),
    '#description' => t('Choose the bean types to filter the list of results.'),
    '#options' => $options,
    '#default_value' => $filters,
  );

  $form['bean_usage_filter']['actions'] = array(
    '#type' => 'actions',
    '#prefix' => '<div style="position:relative; float:left;">',
    '#suffix' => '</div>',
  );

  $form['bean_usage_filter']['actions']['apply'] = array(
    '#type' => 'submit',
    '#value' => t('Apply'),
  );

  $form['bean_usage_filter']['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
  );

  return $form;
}

/**
 * Submit function for bean_usage_filters()
 *
 * Applies the filter via a redirect back to the bean usage view page with the added filter query param.
 *
 * @param $form
 * @param $form_state
 */
function bean_usage_filters_submit(&$form, &$form_state) {
  // Get the query string parameters minus the drupal url and filter param
  $params = drupal_get_query_parameters($_GET, array('q', 'filter'));

  // add the filter to the query string
  $filters = $form_state['values']['bean_usage_filter_type'];
  if (!empty($filters)) {
    switch (strtolower($form_state['values']['op'])) {
      case 'apply':
        $params['filter'] = join(',', $filters);
        break;
    }
  }

  // Redirect back to bean usage view with added filter query string param
  drupal_goto($_GET['q'], array('query' => $params));
}
