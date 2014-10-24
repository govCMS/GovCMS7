<?php
/**
 * @file
 * Admin page callbacks for the Search pages module.
 */

/**
 * Displays an overview of all defined search pages.
 */
function search_api_page_admin_overview() {
  $base_path = drupal_get_path('module', 'search_api') . '/';
  drupal_add_css($base_path . 'search_api.admin.css');

  $header = array(t('Status'), t('Configuration'), t('Name'), t('Path'), t('Index'), t('Operations'));

  $rows = array();
  $t_enabled['data'] = array(
    '#theme' => 'image',
    '#path' => $base_path . 'enabled.png',
    '#alt' => t('enabled'),
    '#title' => t('enabled'),
  );
  $t_enabled['class'] = array('search-api-status');
  $t_disabled['data'] = array(
    '#theme' => 'image',
    '#path' => $base_path . 'disabled.png',
    '#alt' => t('disabled'),
    '#title' => t('disabled'),
  );
  $t_disabled['class'] = array('search-api-status');
  $t_edit = t('edit');
  $pre = 'admin/config/search/search_api/page/';
  $pre_index = 'admin/config/search/search_api/index/';

  foreach (search_api_page_load_multiple() as $page) {
    $index = search_api_index_load($page->index_id);
    $rows[] = array(
      $page->enabled ? $t_enabled : $t_disabled,
      theme('entity_status', array('status' => $page->status)),
      l($page->name, $page->path),
      l($page->path, $page->path),
      l($index->name, $pre_index . $index->machine_name),
      l($t_edit, $pre . $page->machine_name),
    );
  }

  return array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no search pages defined yet.'),
  );
}

/**
 * Displays a form for adding a search page.
 */
function search_api_page_admin_add(array $form, array &$form_state) {
  $form = array();
  if (empty($form_state['step_one'])) {
    $indexes = search_api_index_load_multiple(FALSE);
    if (!$indexes) {
      drupal_set_message(t('There are no searches indexes which can be searched. Please <a href="@url">create an index</a> first.', array('@url' => url('admin/config/search/search_api/add_index'))), 'warning');
      return array();
    }
    $index_options = array();
    foreach ($indexes as $index) {
      if ($index->enabled) {
        $index_options[$index->machine_name] = $index->name;
      }
    }
    foreach ($indexes as $index) {
      if (!$index->enabled) {
        $index_options[$index->machine_name] = $index->name . ' (' . t('disabled') . ')';
      }
    }

    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Search name'),
      '#maxlength' => 50,
      '#required' => TRUE,
    );
    $form['machine_name'] = array(
      '#type' => 'machine_name',
      '#maxlength' => 32,
      '#machine_name' => array(
        'exists' => 'search_api_page_load',
      ),
    );
    $form['index_id'] = array(
      '#type' => 'select',
      '#title' => t('Index'),
      '#description' => t('Select the index this page should search. This cannot be changed later.'),
      '#options' => $index_options,
      '#required' => TRUE,
    );
    $form['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enabled'),
      '#description' => t('This will only take effect if the selected index is also enabled.'),
      '#default_value' => TRUE,
    );
    $form['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Search description'),
    );
    $form['path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path'),
      '#description' => t('Set the path under which the search page will be accessible, when enabled.'),
      '#maxlength' => 50,
      '#required' => TRUE,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create page'),
    );

    return $form;
  }

  $index = search_api_index_load($form_state['step_one']['index_id']);

  if ($index->enabled) {
    $modes = array();
    foreach ($index->query()->parseModes() as $mode => $info) {
      $modes[$mode] = $info['name'];
    }
  }
  else {
    $modes = array();
    $modes['direct'] = t('Direct query');
    $modes['single'] = t('Single term');
    $modes['terms'] = t('Multiple terms');
  }
  $form['mode'] = array(
    '#type' => 'select',
    '#title' => t('Query type'),
    '#description' => t('Select how the query will be parsed.'),
    '#options' => $modes,
    '#default_value' => 'terms',
  );

  $fields = array();
  $index_fields = $index->getFields();
  foreach ($index->getFulltextFields() as $name) {
    $fields[$name] = $index_fields[$name]['name'];
  }
  if (count($fields) > 1) {
    $form['fields'] = array(
      '#type' => 'select',
      '#title' => t('Searched fields'),
      '#description' => t('Select the fields that will be searched. If no fields are selected, all available fulltext fields will be searched.'),
      '#options' => $fields,
      '#size' => min(4, count($fields)),
      '#multiple' => TRUE,
    );
  }
  else {
    $form['fields'] = array(
      '#type' => 'value',
      '#value' => array(),
    );
  }

  $form['per_page'] = array(
    '#type' => 'select',
    '#title' => t('Results per page'),
    '#description' => t('Select how many items will be displayed on one page of the search result.'),
    '#options' => drupal_map_assoc(array(5, 10, 20, 30, 40, 50, 60, 80, 100)),
    '#default_value' => 10,
  );

  $form['get_per_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow GET override'),
    '#description' => t('Allow the „Results per page“ setting to be overridden from the URL, using the "per_page" GET parameter.<br />' .
        'Example: http://example.com/search_results?per_page=7'),
    '#default_value' => FALSE,
  );

  $form['result_page_search_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show search form on result page'),
    '#description' => t('Enable or disable the search form on the result page'),
    '#default_value' => TRUE,
  );

  $view_modes = array(
    'search_api_page_result' => t('Themed as search results'),
  );
  // For entities, we also add all entity view modes.
  if ($index->getEntityType() && ($entity_info = entity_get_info($index->getEntityType()))) {
    foreach ($entity_info['view modes'] as $mode => $mode_info) {
      $view_modes[$mode] = $mode_info['label'];
    }
  }
  if (count($view_modes) > 1) {
    $form['view_mode'] = array(
      '#type' => 'select',
      '#title' => t('View mode'),
      '#options' => $view_modes,
      '#description' => t('Select how search results will be displayed.'),
      '#size' => 1,
      '#default_value' => 'search_api_page_result',
    );
  }
  else {
    $form['view_mode'] = array(
      '#type' => 'value',
      '#value' => key($view_modes),
    );
  }

  $languages = array(
    'current' => t("Current user's language"),
    'default' => t('Default site language'),
  );
  $languages += entity_metadata_language_list();
  if (count($languages) > 4) {
    $form['language_filter'] = array(
      '#type' => 'select',
      '#title' => t('Language filter'),
      '#description' => t('Filter the results by language. Select none to show results independent of language.'),
      '#options' => $languages,
      '#multiple' => TRUE,
      '#size' => min(4, count($languages)),
      '#default_value' => array(),
    );
  }

  if (module_exists('search_api_spellcheck') && ($server = $index->server()) && $server->supportsFeature('search_api_spellcheck')) {
    $form['search_api_spellcheck'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable spell check'),
      '#description' => t('Display "Did you mean … ?" above search results.'),
      '#default_value' => TRUE,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create page'),
  );

  return $form;
}

/**
 * Validation callback for search_api_page_admin_add().
 */
function search_api_page_admin_add_validate(array $form, array &$form_state) {
  if (empty($form_state['step_one'])) {
    $form_state['values']['path'] = drupal_strtolower(trim($form_state['values']['path']));
    if (search_api_page_load_multiple(FALSE, array('path' => $form_state['values']['path']))) {
      form_set_error('path', t('The entered path is already in use. Please enter a unique path.'));
    }
  }
}

/**
 * Submit callback for search_api_page_admin_add().
 */
function search_api_page_admin_add_submit(array $form, array &$form_state) {
  form_state_values_clean($form_state);
  if (empty($form_state['step_one'])) {
    $form_state['step_one'] = $form_state['values'];
    $form_state['rebuild'] = TRUE;
    return;
  }
  $values = $form_state['step_one'];
  $values['options'] = $form_state['values'];
  search_api_page_insert($values);
  drupal_set_message(t('The search page was successfully created.'));
  $form_state['redirect'] = 'admin/config/search/search_api/page';
}

/**
 * Displays a form for editing or deleting a search page.
 */
function search_api_page_admin_edit(array $form, array &$form_state, Entity $page) {
  $index = search_api_index_load($page->index_id);
  $form_state['page'] = $page;

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Search name'),
    '#maxlength' => 50,
    '#required' => TRUE,
    '#default_value' => $page->name,
  );
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#description' => t('This will only take effect if the selected index is also enabled.'),
    '#default_value' => $page->enabled,
    '#disabled' => !$index->enabled,
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Search description'),
    '#default_value' => $page->description,
  );
  $form['index'] = array(
    '#type' => 'item',
    '#title' => t('Index'),
    '#description' => l($index->name, 'admin/config/search/search_api/index/' . $index->machine_name),
  );
  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#description' => t('Set the path under which the search page will be accessible, when enabled.'),
    '#maxlength' => 50,
    '#default_value' => $page->path,
  );

  if ($index->enabled) {
    $modes = array();
    foreach ($index->query()->parseModes() as $mode => $info) {
      $modes[$mode] = $info['name'];
    }
  }
  else {
    $modes = array();
    $modes['direct'] = array(
      'name' => t('Direct query'),
      'description' => t("Don't parse the query, just hand it to the search server unaltered. " .
          "Might fail if the query contains syntax errors in regard to the specific server's query syntax."),
    );
    $modes['single'] = array(
      'name' => t('Single term'),
      'description' => t('The query is interpreted as a single keyword, maybe containing spaces or special characters.'),
    );
    $modes['terms'] = array(
      'name' => t('Multiple terms'),
      'description' => t('The query is interpreted as multiple keywords seperated by spaces. ' .
          'Keywords containing spaces may be "quoted". Quoted keywords must still be seperated by spaces.'),
    );
  }
  $form['options']['#tree'] = TRUE;
  $form['options']['mode'] = array(
    '#type' => 'select',
    '#title' => t('Query type'),
    '#description' => t('Select how the query will be parsed.'),
    '#options' => $modes,
    '#default_value' => $page->options['mode'],
  );

  $fields = array();
  $index_fields = $index->getFields();
  foreach ($index->getFulltextFields() as $name) {
    $fields[$name] = $index_fields[$name]['name'];
  }
  if (count($fields) > 1) {
    $form['options']['fields'] = array(
      '#type' => 'select',
      '#title' => t('Searched fields'),
      '#description' => t('Select the fields that will be searched. If no fields are selected, all available fulltext fields will be searched.'),
      '#options' => $fields,
      '#size' => min(4, count($fields)),
      '#multiple' => TRUE,
      '#default_value' => $page->options['fields'],
    );
  }
  else {
    $form['options']['fields'] = array(
      '#type' => 'value',
      '#value' => array(),
    );
  }

  $form['options']['per_page'] = array(
    '#type' => 'select',
    '#title' => t('Results per page'),
    '#description' => t('Select how many items will be displayed on one page of the search result.'),
    '#options' => drupal_map_assoc(array(5, 10, 20, 30, 40, 50, 60, 80, 100)),
    '#default_value' => $page->options['per_page'],
  );

  $form['options']['result_page_search_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show search form on result page'),
    '#description' => t('Enable or disable the search form on the result page'),
    '#default_value' => isset($page->options['result_page_search_form']) ? $page->options['result_page_search_form'] : TRUE,
  );

  $form['options']['get_per_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow GET override'),
    '#description' => t('Allow the „Results per page“ setting to be overridden from the URL, using the "per_page" GET parameter.<br />' .
        'Example: <code>http://example.com/search_results?per_page=7</code>'),
    '#default_value' => !empty($page->options['get_per_page']),
  );

  $view_modes = array(
    'search_api_page_result' => t('Themed as search results'),
  );
  // For entities, we also add all entity view modes.
  if ($index->getEntityType() && ($entity_info = entity_get_info($index->getEntityType()))) {
    foreach ($entity_info['view modes'] as $mode => $mode_info) {
      $view_modes[$mode] = $mode_info['label'];
    }
  }
  if (count($view_modes) > 1) {
    $form['options']['view_mode'] = array(
      '#type' => 'select',
      '#title' => t('View mode'),
      '#options' => $view_modes,
      '#description' => t('Select how search results will be displayed.'),
      '#size' => 1,
      '#default_value' => isset($page->options['view_mode']) ? $page->options['view_mode'] : 'search_api_page_result',
    );
  }
  else {
    $form['options']['view_mode'] = array(
      '#type' => 'value',
      '#value' => key($view_modes),
    );
  }

  $languages = array(
    'current' => t("Current user's language"),
    'default' => t('Default site language'),
  );
  $languages += entity_metadata_language_list();
  if (count($languages) > 4) {
    $form['options']['language_filter'] = array(
      '#type' => 'select',
      '#title' => t('Language filter'),
      '#description' => t('Filter the results by language. Select none to show results independent of language.'),
      '#options' => $languages,
      '#multiple' => TRUE,
      '#size' => min(4, count($languages)),
      '#default_value' => isset($page->options['language_filter']) ? $page->options['language_filter'] : array(),
    );
  }

  if (module_exists('search_api_spellcheck') && ($server = $index->server()) && $server->supportsFeature('search_api_spellcheck')) {
    $form['options']['search_api_spellcheck'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable spell check'),
      '#description' => t('Display "Did you mean … ?" above search results.'),
      '#default_value' => !empty($page->options['search_api_spellcheck']),
    );
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );

  if ($page->hasStatus(ENTITY_OVERRIDDEN)) {
    $form['actions']['revert'] = array(
      '#type' => 'fieldset',
      '#title' => t('Revert search page'),
      '#description' => t('This will revert all settings on this search page back to the defaults. This action cannot be undone.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'revert' => array(
        '#type' => 'submit',
        '#value' => t('Revert search page'),
      ),
    );
  }
  elseif ($page->hasStatus(ENTITY_CUSTOM)) {
    $form['actions']['delete'] = array(
      '#type' => 'fieldset',
      '#title' => t('Delete search page'),
      '#description' => t('This will delete the search page along with all of its settings.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'delete' => array(
        '#type' => 'submit',
        '#value' => t('Delete search page'),
      ),
    );
  }

  return $form;
}

/**
 * Validation callback for search_api_page_admin_edit().
 */
function search_api_page_admin_edit_validate(array $form, array &$form_state) {
  if (!empty($form_state['values']['op']) && $form_state['values']['op'] == t('Save changes')) {
    $form_state['values']['path'] = drupal_strtolower(trim($form_state['values']['path']));
    $pages = search_api_page_load_multiple(FALSE, array('path' => $form_state['values']['path']));
    if (count($pages) > 1 || (($page = array_shift($pages)) && $page->machine_name != $form_state['page']->machine_name)) {
      form_set_error('path', t('The entered path is already in use. Please enter a unique path.'));
    }
  }
}

/**
 * Submit callback for search_api_page_admin_edit().
 */
function search_api_page_admin_edit_submit(array $form, array &$form_state) {
  $op = $form_state['values']['op'];
  form_state_values_clean($form_state);
  $form_state['redirect'] = 'admin/config/search/search_api/page';

  if ($op == t('Delete search page') || $op == t('Revert search page')) {
    $form_state['page']->delete();

    if ($op == t('Revert search page')) {
      drupal_set_message(t('The search page was successfully reverted.'));
    }
    else {
      drupal_set_message(t('The search page was successfully deleted.'));
    }

    return;
  }
  search_api_page_edit($form_state['page']->machine_name, $form_state['values']);
  drupal_set_message(t('The changes were successfully saved.'));
}
