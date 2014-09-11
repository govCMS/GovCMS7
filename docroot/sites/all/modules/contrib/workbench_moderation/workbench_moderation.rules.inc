<?php

/**
 * Implements hook_rules_file_info().
 */
function workbench_moderation_rules_file_info() {
  $items = array();
  $items[] = 'workbench_moderation.rules';

  return $items;
}

/**
 * Implements hook_rules_condition_info().
 */
function workbench_moderation_rules_condition_info() {
  $items = array();

  $items['content_is_using_workbench_moderation'] = array(
    'group' => t("Node"),
    'label' => t("Content is using workbench moderation"),
    'base' => 'workbench_access_rules_condition_content_is_using_workbench_moderation',
    'parameter' => array(
      'node' => array('type' => 'node', 'label' => t("Content")),
    ),
    'access callback' => 'rules_node_integration_access',
  );

  $items['content_is_live_revision'] = array(
    'group' => t("Node"),
    'label' => t("Content is live revision"),
    'base' => 'workbench_moderation_rules_condition_content_is_live_revision',
    'parameter' => array(
      'node' => array('type' => 'node', 'label' => t("Content")),
    ),
    'access callback' => 'rules_node_integration_access',
  );

  $items['contents_current_state'] = array(
    'group' => t("Node"),
    'label' => t("Content's current moderation state"),
    'base' => 'workbench_moderation_rules_condition_contents_current_state',
    'parameter' => array(
      'node' => array('type' => 'node', 'label' => t("Content")),
      'moderation_state' => array(
        'type' => 'text',
        'label' => t("Workbench moderation state"),
        'options list' => 'workbench_moderation_state_labels',
        'restriction' => 'input',
        'save' => TRUE,
      ),
    ),
    'access callback' => 'rules_node_integration_access',
  );

  $items['contents_previous_state'] = array(
    'group' => t("Node"),
    'label' => t("Content's previous moderation state"),
    'base' => 'workbench_moderation_rules_condition_contents_previous_state',
    'parameter' => array(
      'node' => array('type' => 'node', 'label' => t("Content")),
      'moderation_state' => array(
        'type' => 'text',
        'label' => t("Workbench moderation state"),
        'options list' => 'workbench_moderation_state_labels',
        'restriction' => 'input',
        'save' => TRUE,
      ),
    ),
    'access callback' => 'rules_node_integration_access',
  );

  return $items;
}

/**
 * Implements hook_rules_event_info().
 */
function workbench_moderation_rules_event_info() {
  $items = array();

  $items['workbench_moderation_after_unpublishing_live_content'] = array(
    'label' => t("After unpublishing live content"),
    'group' => t("Node"),
    'variables' => rules_events_node_variables(t("Unpublished content"), FALSE),
    'access callback' => 'rules_node_integration_access',
  );

  $items['workbench_moderation_after_unpublishing_live_content']['variables']['live_content'] = array(
    'type' => 'node',
    'label' => t("Live workbench content"),
  );

  $items['workbench_moderation_after_moderation_transition'] = array(
    'label' => t("After moderation transition"),
    'group' => t("Node"),
    'variables' => rules_events_node_variables(t("Content"), FALSE) + array(
      'previous_state' => array(
        'type' => 'text',
        'label' => t('Previous state'),
      ),
      'new_state' => array(
        'type' => 'text',
        'label' => t('New state'),
      ),
    ),
    'access callback' => 'rules_node_integration_access',
  );

  return $items;
}

/**
 * Implements hook_rules_action_info() on behalf of the workbench_moderation module.
 */
function workbench_moderation_rules_action_info() {
  $items = array();

  $items['workbench_moderation_set_state_during_save'] = array(
    'label' => t("Set moderation state during save"),
    'group' => t("Node"),
    'base' => 'workbench_moderation_set_state_during_save_rules_action',

    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t("Content"),
      ),
      'moderation_state' => array(
        'type' => 'text',
        'label' => t("Workbench moderation state"),
        'options list' => 'workbench_moderation_state_labels',
        'restriction' => 'input',
      ),
    ),
  );

  $items['workbench_moderation_set_state'] = array(
    'label' => t("Set moderation state"),
    'group' => t("Node"),
    'base' => 'workbench_moderation_set_state_rules_action',

    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t("Content"),
      ),
      'moderation_state' => array(
        'type' => 'text',
        'label' => t("Workbench moderation state"),
        'options list' => 'workbench_moderation_state_labels',
        'restriction' => 'input',
      ),
      'force_transition' => array(
        'type' => 'boolean',
        'label' => t("Force transition"),
        'restriction' => 'input',
      ),
    ),
  );

  $items['workbench_moderation_load_current_state'] = array(
    'label' => t("Load current moderation state"),
    'group' => t("Node"),
    'base' => 'workbench_moderation_load_current_state_rules_action',

    'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t("Content"),
      ),
    ),
    'provides' => array(
      'workbench_moderation_state' => array(
        'type' => 'unknown',
        'label' => t("Workbench moderation state"),
      ),
    ),
  );

  return $items;
}

/**
 * Condition: Check if the content is using workbench moderation.
 *
 * @param $node
 *   A node object
 *
 * @return
 *   TRUE/FALSE depending on if the content is using workbench moderation.
 */
function workbench_access_rules_condition_content_is_using_workbench_moderation($node) {
  if (!is_object($node)) {
    return FALSE;
  }

  return workbench_moderation_node_type_moderated($node->type);
}

/**
 * Condition: Check if the content is live revision
 *
 * @param $node
 *   A node object
 *
 * @return
 *   TRUE/FALSE depending on if the content is live revision.
 */
function workbench_moderation_rules_condition_content_is_live_revision($node) {
  if (!is_object($node)) {
    return FALSE;
  }

  return workbench_moderation_node_is_current($node);
}

/**
 * Condition: Check if workbench moderation state matched selected state.
 *
 * @param $node
 *   A node object
 *
 * @param $moderation_state
 *   The desired moderation state to compare with
 *
 * @return
 *  TRUE/FALSE depending on if the nodes current state matches selected state.
 */
function workbench_moderation_rules_condition_contents_current_state($node, $moderation_state) {
  if (!is_object($node)) {
    return FALSE;
  }

  if ($node->workbench_moderation['current']->state != $moderation_state) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Condition: Check if workbench moderation previous state matched selected state.
 *
 * @param $node
 *   A node object
 *
 * @param $moderation_state
 *   The desired moderation state to compare with
 *
 * @return
 *  TRUE/FALSE depending on if the nodes previous state matches selected state.
 */
function workbench_moderation_rules_condition_contents_previous_state($node, $moderation_state) {
  if (!is_object($node)) {
    return FALSE;
  }

  if ($node->workbench_moderation['current']->from_state != $moderation_state) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Action: Change the moderation state of a given node.
 *
 * $param $node
 *   A node object
 *
 * $param $moderation_state
 *   The desired moderation state to assign.

 * $param $force_transition
 *   If set to TRUE, then the transition change will be allowed regardless of permissions and allowed transition flow.
 *   If set to FALSE, then the transition only changes if all transition change requirements are met.
 *
 * @return
 *   An array containing the node object stored in the key called 'node'.
 */
function workbench_moderation_set_state_rules_action($node, $moderation_state, $force_transition) {
  if (is_object($node) && !empty($moderation_state)){
    actions_do('workbench_moderation_set_state_action', $node, array('state' => $moderation_state, 'force_transition' => $force_transition));
  }

  return array('node' => $node);
}

/**
 * Action: Set the moderation state on a node object.
 *
 * This should only be used in a process where this node object will later be saved.
 *
 * $param $node
 *   A node object
 *
 * $param $moderation_state
 *   The desired moderation state to assign.
 *
 * @return
 *   An array containing the node object stored in the key called 'node'.
 */
function workbench_moderation_set_state_during_save_rules_action($node, $moderation_state) {

  $node->workbench_moderation_state_new = $moderation_state;

  return array('node' => $node);
}

/**
 * Action: Loads the workbench access states into a variable.
 *
 * $param $node
 *   A node object
 *
 * @return
 *   An array containing the node object stored in the key called 'node' and an array containing the access control states for the given node.
 */
function workbench_moderation_load_current_state_rules_action($node) {
  $state = '';

  if (is_object($node) && property_exists($node, 'workbench_moderation') && isset($node->workbench_moderation['current'])){
    $state = $node->workbench_moderation['current'];
  }

  return array('node' => $node, 'workbench_moderation_state' => $state);
}
