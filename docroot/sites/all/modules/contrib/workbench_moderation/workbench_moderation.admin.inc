<?php

/**
 * @file
 *  Administrative functions for Workbench Moderation.
 */

/**
 * Administration form for states.
 *
 * Administrators can use this form to add, delete, reorder, and
 * update the description for states.
 */
function workbench_moderation_admin_states_form($form, &$form_state) {
  $form['states'] = array(
    '#tree' => TRUE,
  );

  // List existing states.
  $states = workbench_moderation_states();
  foreach ($states as $state) {
    $form['states'][$state->name]['state'] = array(
      '#type' => 'value',
      '#value' => $state,
    );
    $form['states'][$state->name]['name'] = array(
      '#type' => 'value',
      '#value' => $state->name,
    );
    $form['states'][$state->name]['label'] = array(
      '#type' => 'textfield',
      '#default_value' => $state->label,
      '#maxlength' => 255,
      '#size' => 30,
    );
    $form['states'][$state->name]['machine_name'] = array(
      '#markup' => check_plain($state->name),
    );
    $form['states'][$state->name]['description'] = array(
      '#type' => 'textfield',
      '#default_value' => $state->description,
    );
    $form['states'][$state->name]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => $state->weight,
    );
    $form['states'][$state->name]['delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete'),
      '#title_display' => 'invisible',
      '#default_value' => FALSE,
    );
    if ($state->name == workbench_moderation_state_published() || $state == workbench_moderation_state_none()) {
      $form['states'][$state->name]['delete']['#disabled'] = TRUE;
    }
  }

  // Provide fields to create a new state.
  $new_state['label'] = array(
    '#title' => t('New state'),
    '#type' => 'textfield',
    '#description' => t('Enter a name for the new state.'),
    '#maxlength' => 255,
    '#size' => 30,
  );
  $new_state['name'] = array(
    '#type' => 'machine_name',
    '#maxlength' => 255,
    '#size' => 30,
    '#required' => FALSE,
    '#machine_name' => array(
      'exists' => 'workbench_moderation_state_load',
      'source' => array('states', '0', 'label'),
    ),
  );
  $new_state['description'] = array(
    '#type' => 'textfield',
    '#maxlength' => 255,
    '#title' => '&nbsp;',
    '#description' => t('Enter a description of the new state.')
  );
  $new_state['weight'] = array(
    '#type' => 'weight',
  );
  $form['states'][] = $new_state;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Transforms the states administration form into a reorderable table.
 */
function theme_workbench_moderation_admin_states_form($variables) {
  $form = $variables['form'];

  drupal_add_tabledrag('workbench-moderation-states', 'order', 'sibling', 'workbench-moderation-state-weight');

  $header = array(
    t('Name'),
    t('Machine name'),
    t('Description'),
    array('data' => t('Delete'), 'class' => array('checkbox')),
    t('Weight'),
  );

  $rows = array();
  foreach (element_children($form['states']) as $key) {
    $element = &$form['states'][$key];

    $row = array(
      'data' => array(),
      'class' => array('draggable'),
    );
    $row['data']['label'] = drupal_render($element['label']);
    $row['data']['name'] = drupal_render($element['name']) . drupal_render($element['machine_name']);
    $row['data']['description'] = drupal_render($element['description']);
    $row['data']['delete'] = drupal_render($element['delete']);

    $element['weight']['#attributes']['class'] = array('workbench-moderation-state-weight');
    $row['data']['weight'] = drupal_render($element['weight']);

    $rows[] = $row;
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'workbench-moderation-states')));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Form submit handler for moderation state administration.
 */
function workbench_moderation_admin_states_form_submit($form, &$form_state) {
  foreach ($form_state['values']['states'] as $key => $info) {
    if (!empty($info['delete'])) {
      workbench_moderation_state_delete($info['state']);
      drupal_set_message(t('Moderation state %label (%name) has been deleted.', array('%label' => $info['label'], '%name' => $info['name'])));
    }
    elseif (!empty($info['name'])) {
      $state = (object) array(
        'name' => $info['name'],
        'label' => $info['label'],
        'description' => $info['description'],
        'weight' => $info['weight'],
      );
      workbench_moderation_state_save($state);
    }
  }

  drupal_set_message(t('Your settings have been saved.'));

  // Warn users that changes here may need require reconfiguring Views that use Workbench.
  $views_message = t('Depending on the changes you have made it may be necessary to <a href="@views">reconfigure Views</a> that leverage Workbench Moderation such as <a href="@workbench_moderation">workbench_moderation</a>', array('@views' => url('admin/structure/views'), '@workbench_moderation' => url('admin/structure/views/edit/workbench_moderation')));
  drupal_set_message($views_message, $type = 'warning', $repeat = FALSE);
}

/**
 * Administration form to create and delete moderation transitions.
 *
 * Transition ordering is based on state ordering.
 */
function workbench_moderation_admin_transitions_form($form, &$form_state) {
  $form['transitions'] = array(
    '#tree' => TRUE,
  );

  // List existing states.
  $transitions = workbench_moderation_transitions();

  foreach ($transitions as $transition) {
    $element = array();

    $element['transition'] = array(
      '#type' => 'value',
      '#value' => $transition,
    );
    $element['from_name'] = array(
      '#markup' => check_plain(workbench_moderation_state_label($transition->from_name)),
    );
    $element['to_name'] = array(
      '#markup' => check_plain(workbench_moderation_state_label($transition->to_name)),
    );
    $element['delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete'),
      '#title_display' => 'invisible',
      '#default_value' => FALSE,
    );

    $form['transitions'][] = $element;
  }

  // Provide fields to create a new transition.
  $options = workbench_moderation_state_labels();

  array_unshift($options, t('- Choose state -'));
  $element = array();
  $element['from_name'] = array(
    '#type' => 'select',
    '#title' => t('New transition'),
    '#options' => $options,
  );
  $element['to_name'] = array(
    '#type' => 'select',
    '#title' => '&nbsp;',
    '#options' => $options,
  );
  $form['transitions']['new'] = $element;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Transforms the transitions administration form into a table.
 */
function theme_workbench_moderation_admin_transitions_form($variables) {
  $form = $variables['form'];

  $header = array(
    t('From'),
    '',
    t('To'),
    array('data' => t('Delete'), 'class' => array('checkbox')),
  );

  $rows = array();
  foreach (element_children($form['transitions']) as $key) {
    $element = &$form['transitions'][$key];
    $row = array('data' => array());
    $row['data']['from'] = drupal_render($element['from_name']);
    $row['data'][] = '--&gt;';
    $row['data']['to'] = drupal_render($element['to_name']);
    $row['data']['delete'] = drupal_render($element['delete']);
    $rows[] = $row;
  }
  // @TODO: change this css call.
  drupal_add_css(drupal_get_path('module', 'workbench_moderation') . '/css/workbench_moderation.css');
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('width-auto'))));
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Form validation handler for the transitions form.
 */
function workbench_moderation_admin_transitions_form_validate($form, &$form_state) {
  $new = $form_state['values']['transitions']['new'];
  if (!empty($new['from_name']) && !empty($new['to_name'])) {
    if ($new['from_name'] == $new['to_name']) {
      form_set_error('transitions][new', t('To and from states of a new transition must be different.'));
    }
    else {
      foreach (workbench_moderation_transitions() as $t) {
        if ($new['from_name'] == $t->from_name && $new['to_name'] == $t->to_name) {
          form_set_error('transitions][new', t('This transition already exists.'));
          break;
        }
      }
    }
  }
}

/**
 * Form submit handler for moderation transitions.
 */
function workbench_moderation_admin_transitions_form_submit($form, &$form_state) {
  foreach ($form_state['values']['transitions'] as $transition) {
    if (!empty($transition['delete'])) {
      workbench_moderation_transition_delete($transition['transition']);
      drupal_set_message(t('%from --&gt; %to has been deleted.', array('%from' => workbench_moderation_state_label($transition['transition']->from_name), '%to' => workbench_moderation_state_label($transition['transition']->to_name))));
    }
    elseif (!empty($transition['from_name']) && !empty($transition['to_name'])) {
      $new_transition = (object) array(
        'from_name' => $transition['from_name'],
        'to_name' => $transition['to_name'],
      );
      workbench_moderation_transition_save($new_transition);
      drupal_set_message(t('%from --&gt; %to has been created.',array('%from' => workbench_moderation_state_label($new_transition->from_name), '%to' => workbench_moderation_state_label($new_transition->to_name))));
    }
  }
}

/**
 * Check proper permissions for moderation roles.
 *
 * This helper administration form checks whether roles have the appropriate
 * permissions to use moderation as intended.
 */
function workbench_moderation_admin_check_role_form($form, &$form_state) {
  $form = array();

  $roles = user_roles();
  $form['role'] = array(
    '#type' => 'select',
    '#title' => t('Drupal role'),
    '#description' => t('Select a role to check.'),
    '#options' => $roles,
  );

  $form['moderation_task'] = array(
    '#type' => 'select',
    '#title' => t('Moderation task'),
    '#description' => t('Select a moderation task that the role should be able to perform.'),
    '#options' => array(
      'author' => t('Author moderated content'),
      'editor' => t('Edit moderated content'),
      'moderator' => t('Moderate content'),
      'publisher' => t('Publish moderated content'),
    ),
  );

  $types = drupal_map_assoc(workbench_moderation_moderate_node_types());
  $all_types = node_type_get_types();
  foreach ($types as $type) {
    $types[$type] = $all_types[$type]->name;
  }
  $form['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#description' => t('Select any content types on which the user should have the ability to perform the moderation task.'),
    '#options' => $types,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Check permissions'),
  );

  if (empty($types)) {
    drupal_set_message(t('Moderation is not enabled for any content types. Visit the <a href="@content_type_administration_page">content type administration page</a> to enable moderation for one or more types.', array('@content_type_administration_page' => url('admin/structure/types'))), 'warning');
    $form['#disabled'] = TRUE;
  }

  return $form;
}

/**
 * Form submit handler for moderation role tests.
 */
function workbench_moderation_admin_check_role_form_submit($form, &$form_state) {
  $rid = $form_state['values']['role'];
  $role = user_role_load($rid);

  $types = array_filter($form_state['values']['types']);

  $moderation_task = $form_state['values']['moderation_task'];
  $recommended_permissions = workbench_moderation_recommended_permissions($types);
  $recommended_permissions = $recommended_permissions[$moderation_task];

  // Get a full list of this role's permissions.
  $actual_permissions = user_role_permissions(array_filter(array(
    $rid => TRUE,
    DRUPAL_AUTHENTICATED_RID => ($rid != DRUPAL_ANONYMOUS_RID),
  )));

  // The results of user_role_permissions() are in a nested array:
  // array(rid => array("permission name" => TRUE))
  // Check each for our recommended permissions.
  foreach ($actual_permissions as $permissions) {
    $recommended_permissions = array_diff($recommended_permissions, array_keys(array_filter($permissions)));
  }

  if (empty($recommended_permissions)) {
    // All of the recommended permissions were accounted for.
    drupal_set_message(t('The @role role should be a qualified @moderation_task.', array(
      '@role' => $role->name,
      '@moderation_task' => $moderation_task,
    )), 'status');
  }
  else {
    // The specified role didn't have some of the recommended permissions. Print a list for the user.
    $all_permissions = module_invoke_all('permission');
    foreach ($recommended_permissions as $permission) {
      drupal_set_message(t('The @role role may need the "!permission_label" permission in order to be a qualified @moderation_task of @types content.', array(
        '@role' => $role->name,
        '@moderation_task' => $moderation_task,
        '@types' => implode(t(' and '), array(implode(', ', array_slice($types, 0, -1)), end($types))), // @TODO: Context senstive translation bug
        '!permission_label' => $all_permissions[$permission]['title'],
      )), 'error');
    }
    // Provide links to node and moderation permissions.
    drupal_set_message(t('View <a href="@node_permissions">node permissions</a> or <a href="@moderation_permissions">moderation permissions</a> for the @role role.', array(
      '@node_permissions' => url('admin/people/permissions/' . $rid, array('fragment' => 'module-node')),
      '@moderation_permissions' => url('admin/people/permissions/' . $rid, array('fragment' => 'module-workbench_moderation')),
      '@role' => $role->name,
    )), 'error');

    // Note that we don't cover all configurations.
    drupal_set_message(t('The @role role may be a qualified @moderation_task regardless of these notices if it has liberal overall node and moderation permissions, like "Administer content" and "Bypass moderation restrictions".', array(
      '@role' => $role->name,
      '@moderation_task' => $moderation_task,
    )), 'warning');
  }

  // Note that we don't cover all configurations.
  drupal_set_message(t('You must check manually that this role has the appropriate transition permissions for your workflow. <a href="@moderation_permissions_link">View moderation permissions for this role.</a>', array('@moderation_permissions_link' => url('admin/people/permissions/' . $rid, array('fragment' => 'module-workbench_moderation')))), 'warning');

  // Repopulate the form with the submitted values.
  $form_state['rebuild'] = TRUE;
}

/**
 * Recommended permissions for typical moderation roles.
 */
function workbench_moderation_recommended_permissions($types = array()) {
  $states = workbench_moderation_states();
  $draft = workbench_moderation_state_none();
  $published = workbench_moderation_state_published();

  $permissions = array(
    'author' => array(
      // node
      "access content",
      "view own unpublished content",
      "view revisions",

      // workbench_moderation
      "view moderation messages",
      "use workbench_moderation my drafts tab",
    ),
    'editor' => array(
      // node
      "access content",
      "view revisions",
      "revert revisions",

      // workbench
      "view all unpublished content",

      // workbench_moderation
      "view moderation messages",
      "view moderation history",
      "use workbench_moderation my drafts tab",
      "use workbench_moderation needs review tab",
    ),
    'moderator' => array(
      // node
      "access content",
      "view revisions",

      // workbench
      "view all unpublished content",

      // workbench_moderation
      "view moderation messages",
      "view moderation history",
      "use workbench_moderation needs review tab",
    ),
    'publisher' => array(
      // node
      "access content",
      "view revisions",
      "revert revisions",

      // workbench
      "view all unpublished content",

      // workbench_moderation
      "view moderation messages",
      "view moderation history",
      "use workbench_moderation needs review tab",
    ),
  );

  foreach ($types as $type) {
    $permissions['author'][] = "create $type content";
    $permissions['author'][] = "edit own $type content";
    $permissions['editor'][] = "edit any $type content";
    $permissions['moderator'][] = "edit any $type content";
    $permissions['publisher'][] = "edit any $type content";
  }

  return $permissions;
}
