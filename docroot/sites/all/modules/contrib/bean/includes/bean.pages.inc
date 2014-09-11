<?php

/**
 * @file
 * Bean Functions
 */

/**
 * Bean view page
 */
function bean_view_page(Bean $bean) {
  $title = $bean->label() ? $bean->label() : $bean->adminTitle();
  drupal_set_title($title);
  return bean_view($bean);
}

/**
 * Edit bean page callback
 */
function bean_edit(Bean $bean) {
  $type = bean_fetch_plugin_info($bean->type);
  drupal_set_title(t('Edit @type: @title', array('@type' => $type['label'], '@title' => $bean->label)));
  return drupal_get_form('bean_form', $bean);
}

/**
 * Add bean page callback
 */
function bean_add($type) {
  $bean = bean_create(array('type' => $type));
  $bean_type = bean_type_load($type);
  drupal_set_title(t('Create @type block', array('@type' => $bean_type->getLabel())));

  return drupal_get_form('bean_form', $bean, $type);
}

/**
 * Menu Callback to list available bean types to add
 */
function bean_add_page() {
  $bean_types = bean_get_types();

  $types = array();
  foreach ($bean_types as $key => $bean_type) {
    if (bean_access('create', $bean_type->type)) {
      $types[$key] = $bean_type;
    }
  }

  // If there are block types, but the user doesn't have access, return 403.
  if (count($types) == 0 && count($bean_types) > 0) {
    return drupal_access_denied();
  }

  // Bypass the block/add listing if only one block type is available.
  if (count($types) == 1) {
    $bean_type = array_shift($types);
    drupal_goto('block/add/' . $bean_type->buildURL());
  }

  return theme('bean_add_list', array('content' => $types));
}

function bean_list() {
  $rows = array();

  // Build the sortable table header.
  $header = array(
    'title' => array(
      'data' => 'Title',
      'type' => 'property',
      'specifier' => 'title',
      'sort' => 'asc'
    ),
    'type' => array(
      'data' => 'Type',
      'type' => 'entity',
      'specifier' => 'bundle',
    ),
    'operations' => array('data' => t('Operations')),
  );

  $filters = bean_get_filter();


  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'bean')
    ->tableSort($header)
    ->pager($filters['per_page']);

  if (!empty($filters['types'])) {
    $query->entityCondition('bundle', $filters['types'], 'IN');
  }

  $result = $query->execute();
  if (!empty($result)) {
    $beans = bean_load_multiple(array_keys($result['bean']));
  }
  else {
    $beans = array();
  }

  foreach ($beans as $bean) {
    $rows[$bean->bid] = array(
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $bean->label,
          '#href' => 'block/' . $bean->delta,
        ),
      ),
      'type' => check_plain($bean->type),
    );

    $destination = drupal_get_destination();

    // Build a list of all the accessible operations for the current bean.
    $operations = array();
    if (bean_access('edit', $bean)) {
      $operations['edit'] = array(
        'title' => t('edit'),
        'href' => 'block/' . $bean->delta . '/edit',
        'query' => $destination,
      );
    }
    if (bean_access('delete', $bean)) {
      $operations['delete'] = array(
        'title' => t('delete'),
        'href' => 'block/' . $bean->delta . '/delete',
        'query' => $destination,
      );
    }
    // Render an unordered list of operations links.
    $rows[$bean->bid]['operations'] = array(
      'data' => array(
        '#theme' => 'links__bean_operations',
        '#links' => $operations,
        '#attributes' => array('class' => array('links', 'inline')),
      ),
    );
  }

  $output = array(
    'bean_filter_form' => drupal_get_form('bean_filter_form'),
    'bean_content' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('There are no Block Available'),
    ),
    'pager' => array(
      '#theme' => 'pager',
    ),
  );

  return $output;
}

/**
 * Returns HTML for a list of available bean types for bean creation.
 *
 * @param $variables
 *   An associative array containing:
 *   - content: An array of bean types.
 *
 * @ingroup themeable
 */
function theme_bean_add_list($variables) {
  $content = $variables['content'];
  $blocks = array();
  $i = 0;

  if ($content) {
    foreach ($content as $item) {
      $title = l(t('<span class="icon"></span>@label', array('@label' => $item->getLabel())), 'block/add/' . $item->buildURL(), array('html' => TRUE));
      $description = (!is_array($item->getDescription())) ? '<div class="description">' . $item->getDescription() . '</div>' : '';
      //creative way to setup sorting by label; add number to prevent duplicate keys
      $blocks[str_replace(' ', '', $item->getLabel()) . '_' . $i] = '<li>' . $title . $description . '</li>';
      $i++;
    }
    ksort($blocks);
    $output = '<ul class="bean-type-list admin-list">' . implode('', $blocks) . '</ul>';
  }
  else {
    $output = '<p>' . t('You have not created any block types yet.') . '</p>';
  }
  return $output;
}

/**
 * Bean form
 */
function bean_form($form, &$form_state, Bean $bean, $type = NULL) {

  // During initial form build, add the bean entity to the form state for use
  // during form building and processing. During a rebuild, use what is in the
  // form state.
  if (!isset($form_state['bean'])) {
    if (!isset($bean->label)) {
      $bean->label = NULL;
    }
    if (isset($type)) {
      $bean->type = $type;
    }
    $form_state['bean'] = $bean;
  }
  else {
    $bean = $form_state['bean'];
  }

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#required' => TRUE,
    '#default_value' => $bean->label,
    '#description' => t('Name that displays in the admin interface'),
    '#weight' => -10,
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The Title of the block. The &lt;em&gt;, &lt;strong&gt;, &lt;i&gt; and &lt;b&gt; HTML tags are allowed, all others will be filtered out.'),
    '#default_value' => $bean->title,
    '#weight' => -9,
  );

  $form['revision'] = array(
    '#weight' => 10,
  );

  if (isset($bean->is_new)) {
    $form['revision']['#access'] = FALSE;
  }

  ctools_include('dependent');
  ctools_add_js('dependent');

  $form['revision']['is_new_revision'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create new revision'),
    '#default_value' => 1,
    '#id' => 'edit-revision',
  );

  if (isset($bean->is_new)) {
    $form['default_revision'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }
  else {
    $form['revision']['default_revision'] = array(
      '#type' => 'checkbox',
      '#title' => t('Set Revision as default'),
      '#default_value' => $bean->isDefaultRevision(),
      '#states' => array(
        // Hide if the option above is disabled, to avoid potential dataloss.
        'invisible' => array(
          ':input[name="is_new_revision"]' => array('checked' => FALSE),
        ),
      ),
    );
  }

  $form['revision']['log'] = array(
    '#type' => 'textarea',
    '#title' => t('Log message'),
    '#description' => t('Provide an explanation of the changes you are making. This will help other authors understand your motivations.'),
    '#dependency' => array('edit-revision' => array(1)),
    '#default_value' => '',
  );

  // The view mode.
  if (user_access('edit bean view mode')) {
    $bean_info = $bean->entityInfo();
    foreach ($bean_info['view modes'] as $view_mode_name => $data) {
      $view_modes[$view_mode_name] = $data['label'];
    }

    $form['view_mode'] = array(
      '#title' => t('View Mode'),
      '#description' => t('Edit the view mode of the Bean'),
      '#default_value' => $bean->view_mode,
      '#type' => 'select',
      '#required' => TRUE,
      '#options' => $view_modes,
      '#weight' => -8,
    );
  }
  else {
    $form['view_mode'] = array(
      '#type' => 'value',
      '#value' => $bean->view_mode,
    );
  }

  $form['bean'] = array(
    '#type' => 'value',
    '#value' => $bean,
  );

  // Get the Bean type form.
  $form += $bean->getForm($form, $form_state);

  // Add the buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 200,
    '#submit' => array('bean_form_submit'),
  );
  if (!empty($bean->bid) && bean_access('delete', $bean)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 201,
      '#submit' => array('bean_form_delete_submit'),
    );
  }

  $form['#validate'][] = 'bean_form_validate';
  if (!isset($form['#submit']) && function_exists($bean->type . '_bean_form_submit')) {
    $form['#submit'][] = $bean->type . '_bean_form_submit';
  }
  $form += array('#submit' => array());

  if(function_exists('entity_language')){
    $langcode = entity_language('bean', $bean);
  }
  else {
    $langcode = NULL;
  }

  field_attach_form('bean', $bean, $form, $form_state, $langcode);
  return $form;
}

/**
 * Validation for bean form
 */
function bean_form_validate($form, &$form_state) {
  $bean = $form_state['values']['bean'];
  $bean->label = $form_state['values']['label'];
  $bean->title = $form_state['values']['title'];
  $bean->view_mode = $form_state['values']['view_mode'];
  $bean->is_new_revision = $form_state['values']['is_new_revision'];
  // Avoid dataloss.
  if (empty($form_state['values']['is_new_revision'])) {
    $bean->default_revision = TRUE;
  }
  else {
    $bean->default_revision = $form_state['values']['default_revision'];
  }

  if ($bean->is_new_revision) {
    $bean->log = $form_state['values']['log'];
  }

  if(function_exists('entity_language')){
    $langcode = entity_language('bean', $bean);
  }
  else {
    $langcode = NULL;
  }

  field_attach_form_validate('bean', $bean, $form, $form_state);
  $form_state['values']['bean'] = $bean;

  $bean->validate($form_state['values'], $form_state);
}

/**
 * Submit function for bean form
 */
function bean_form_submit($form, &$form_state) {
  $bean = bean_form_submit_build_bean($form, $form_state);
  $bean->setValues($form_state['values']);

  // Avoid dataloss.
  if (empty($form_state['values']['is_new_revision'])) {
    $bean->default_revision = TRUE;
  }

  $insert = $bean->internalIdentifier();
  field_attach_submit('bean', $bean, $form, $form_state);
  $bean->save();
  $form_state['values']['bean'] = $bean;

  $watchdog_args = array('@type' => $bean->typeName(), '%title' => $bean->label());
  $t_args = array('@type' => $bean->typeName(), '%title' => $bean->label());

  if (!$insert) {
    watchdog('bean', '@type: added %title.', $watchdog_args, WATCHDOG_NOTICE, $bean->viewURL());
    drupal_set_message(t('@type %title has been created.', $t_args));
  }
  else {
    watchdog('bean', '@type: updated %title.', $watchdog_args, WATCHDOG_NOTICE, $bean->viewURL());
    drupal_set_message(t('@type %title has been updated.', $t_args));
  }

  if ($bean->identifier()) {
    $form_state['redirect'] = $bean->viewURL();
  }
  else {
    // In the unlikely case something went wrong on save, the bean will be
    // rebuilt and bean form redisplayed the same way as in preview.
    drupal_set_message(t('The block could not be saved.'), 'error');
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Updates the form state's bean entity by processing this submission's values.
 *
 * This is the default builder function for the bean form. It is called
 * during the "Save" and "Preview" submit handlers to retrieve the entity to
 * save or preview. This function can also be called by a "Next" button of a
 * wizard to update the form state's entity with the current step's values
 * before proceeding to the next step.
 *
 * @return Bean
 *
 * @see bean_form()
 * @see node_form_submit_build_node()
 */
function bean_form_submit_build_bean($form, &$form_state) {

  // @todo Legacy support for modules that extend the bean form with form-level
  //   submit handlers that adjust $form_state['values'] prior to those values
  //   being used to update the entity. Module authors are encouraged to instead
  //   adjust the bean directly within a hook_bean_submit() implementation. For
  //   Drupal 8, evaluate whether the pattern of triggering form-level submit
  //   handlers during button-level submit processing is worth supporting
  //   properly, and if so, add a Form API function for doing so.
  unset($form_state['submit_handlers']);
  form_execute_handlers('submit', $form, $form_state);

  $bean = $form_state['bean'];
  entity_form_submit_build_entity('bean', $bean, $form, $form_state);

  foreach (module_implements('bean_submit') as $module) {
    $function = $module . '_bean_submit';
    $function($bean, $form, $form_state);
  }
  return $bean;
}

/**
 * Button submit function: handle the 'Delete' button on the bean form.
 */
function bean_form_delete_submit($form, &$form_state) {
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  $bean = $form_state['values']['bean'];
  $form_state['redirect'] = array($bean->deleteURL(), array('query' => $destination));
}

/**
 * Menu callback -- ask for confirmation of bean deletion
 */
function bean_delete_confirm($form, &$form_state, $bean) {
  $form['#bean'] = $bean;

  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $bean->label())),
    $bean->viewUrl(),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Execute bean deletion
 */
function bean_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $bean = $form['#bean'];
    $bean->delete();
    watchdog('bean', '@type: deleted %title.', array('@type' => $bean->typeName(), '%title' => $bean->label()));
    drupal_set_message(t('@type %title has been deleted.', array('@type' => $bean->typeName(), '%title' => $bean->label())));
  }

  $form_state['redirect'] = '<front>';
}

/**
 * Menu callback -- ask for confirmation of bean deletion
 */
function bean_delete_revision_confirm($form, &$form_state, $bean) {
  $form['#bean'] = $bean;

  return confirm_form($form,
    t('Are you sure you want to delete revision %vid of %title?', array('%vid' => $bean->vid, '%title' => $bean->label())),
    $bean->viewUrl(),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete a bean revisiosn
 */
function bean_delete_revision_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $bean = $form['#bean'];
    bean_delete_revision($bean->vid);
    watchdog('bean', '@type: deleted %title revision %vid.', array('%vid' => $bean->vid, '@type' => $bean->typeName(), '%title' => $bean->label()));
    drupal_set_message(t('@type %title revision %vid has been deleted.', array('%vid' => $bean->vid, '@type' => $bean->typeName(), '%title' => $bean->label())));
  }
}

/**
 * Form for setting a revision active
 */
function bean_set_default_confirm($form, &$form_state, $bean) {
  $form['#bean'] = $bean;

  return confirm_form($form,
    t('Are you sure you want to set revision %vid of %title active?', array('%vid' => $bean->vid, '%title' => $bean->label())),
    $bean->viewUrl(),
    t('This action cannot be undone.'),
    t('Set Default'),
    t('Cancel')
  );
}

/**
 * Submit function
 */
function bean_set_default_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $bean = $form['#bean'];
    $bean->setDefault()->save();
    watchdog('bean', '@type: %title revision %vid was set active.', array('%vid' => $bean->vid, '@type' => $bean->typeName(), '%title' => $bean->label()));
    drupal_set_message(t('@type %title revision %vid has been set active.', array('%vid' => $bean->vid, '@type' => $bean->typeName(), '%title' => $bean->label())));
  }
}

function bean_filter_form($form, &$form_state) {
  $filters = bean_get_filter();

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  $type_options = array();
  foreach (bean_get_types() as $type) {
    $type_options[$type->type] = $type->getLabel();
  }
  asort($type_options);

  $form['filters']['types'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#multiple' => TRUE,
    '#options' => $type_options,
    '#default_value' => $filters['types'],
  );

  $form['filters']['per_page'] = array(
    '#type' => 'select',
    '#title' => t('Items Per Page'),
    '#multiple' => FALSE,
    '#options' => array(20 => '20', 50 => '50', 100 => '100', 200 => '200', 500 => '500'),
    '#default_value' => $filters['per_page'],
  );

  $form['filters']['filter'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('bean_filter_submit'),
  );
  $form['filters']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('bean_reset_filter_submit'),
  );

  return $form;
}

/**
 * Submit function for filter
 */
function bean_filter_submit($form, &$form_state) {
  $filters = array(
    'types' => $form_state['values']['filters']['types'],
    'per_page' => $form_state['values']['filters']['per_page'],
  );

  bean_set_filter($filters);

  drupal_goto('admin/content/blocks');

}

function bean_reset_filter_submit($form, &$form_state) {
  bean_reset_filter();

  drupal_goto('admin/content/blocks');
}

/**
 * Set the filter in the session
 */
function bean_set_filter($filter) {
  $_SESSION['bean-filter'] = $filter;
}

/**
 * Get the filter
 */
function bean_get_filter() {
  // Pull any saved values from the session.
  $filters = isset($_SESSION['bean-filter']) ? $_SESSION['bean-filter'] : array();
  // ...fill in gaps with default values.
  return $filters + array('types' => array(), 'per_page' => 50);
}

/**
 * Reset the filter
 */
function bean_reset_filter() {
  unset($_SESSION['bean-filter']);
}

/**
 * Revisions page callback
 *
 * @param $bean Bean
 */
function bean_revisions_page(Bean $bean) {
  $bean->loadRevisions();

  // Build the sortable table header.
  $header = array(
    'vid' => array('data' => t('Revision ID')),
    'title' => array('data' => t('Title')),
    'author' => array('data' => t('Author')),
    'changed' => array('data' => t('Date Changed')),
    'operations' => array(
      'data' => t('Operations'),
      'colspan' => 2,
    ),
  );

  $rows = array();

  // Dont' show link for default revision
  $can_delete = bean_access('delete', $bean);
  $can_edit = bean_access('edit', $bean);

  foreach ($bean->revisions as $rev) {
    $active = $rev->vid == $bean->vid ? TRUE : FALSE;
    $user = user_load($rev->uid);
    $rows[$rev->vid]  = array(
      'vid' => $active ? t('@label (Current Revision)', array('@label' => $rev->vid)) : $rev->vid,
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $rev->label,
          '#href' => "block/{$rev->delta}/revisions/{$rev->vid}",
        ),
      ),
      'author' => format_username($user),
      'changed' => format_date($rev->changed),
    );

    $operations = array();

    if ($can_edit) {
      $operations['edit'] = array(
        'title' => t('edit'),
        'href' => "block/{$bean->delta}/revisions/{$rev->vid}/edit",
        'query' => drupal_get_destination(),
      );
    }

    if ($can_delete && !$active) {
      $operations['delete'] = array(
        'title' => t('delete'),
        'href' => "block/{$bean->delta}/revisions/{$rev->vid}/delete",
        'query' => drupal_get_destination(),
      );
    }

    if ($can_edit && !$active) {
      $operations['set-active'] = array(
        'title' => t('set active'),
        'href' => "block/{$bean->delta}/revisions/{$rev->vid}/set-active",
        'query' => drupal_get_destination(),
      );
    }

    $rows[$rev->vid]['operations'] = array(
      'data' => array(
        '#theme' => 'links__bean_operations',
        '#links' => $operations,
        '#attributes' => array('class' => array('links', 'inline')),
      ),
    );
  }

  return array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no revisions'),
  );
}
