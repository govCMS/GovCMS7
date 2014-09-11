<?php

/**
 * @file
 * Provides node functions for Workbench Moderation.
 */

/**
 * Redirects the user to the current revision of the node.
 *
 * This page will deliver either the 'draft' page or the regular node view page.
 *
 * @param $node
 *   The node being acted upon.
 */
function workbench_moderation_node_current_view($node) {
  if (_workbench_moderation_access_current_draft($node)) {
    drupal_goto('node/' . $node->nid . '/draft');
  }
  drupal_goto('node/' . $node->nid);
}

/**
 * Get the menu router item for nodes.
 *
 * @param $node
 *   The node being acted upon.
 * @return
 *   A fully themed node page.
 */
function workbench_moderation_router_item_page_callback($node) {
  $router_item = menu_get_item('node/' . $node->nid);
  if ($router_item['include_file']) {
    require_once DRUPAL_ROOT . '/' . $router_item['include_file'];
  }

  // Call whatever function is assigned to the main node path but pass the
  // current node as an argument. This approach allows for the reuse of of Panel
  // definition acting on node/%node.
  return $router_item['page_callback']($node);

}
/**
 * Displays the current draft the node, if it is not published.
 *
 * @param $node
 *   The node being acted upon.
 *
 * @return
 *   A fully themed node page.
 */
function workbench_moderation_node_view_draft($node) {
  $current_node = workbench_moderation_node_current_load($node);
  return workbench_moderation_router_item_page_callback($current_node);
}

/**
 * Displays a specific revisison of the node.
 *
 * @param $node
 *   The node being acted upon.
 *
 * @return
 *   A fully themed node page.
 */
function workbench_moderation_node_view_revision($node) {
  return workbench_moderation_router_item_page_callback($node);
}

/**
 * Display a node's moderation history.
 *
 * @param $node
 *   The node being acted upon.
 *
 * @return
 *   A themed table of data and links for node moderation actions.
 */
function workbench_moderation_node_history_view($node) {
  global $user;

  // Page title.
  drupal_set_title(t('History of %title', array('%title' => $node->title)), PASS_THROUGH);

  // Alert if there is no live node
  if (!isset($node->workbench_moderation['published'])) {
    drupal_set_message(t('Currently there is no published revision of this node.'), 'warning');
  }

  // Get all of the node revisions, each with its most recent moderation.
  $query = db_select('node', 'n');
  $query->leftJoin('node_revision', 'r', 'n.nid = r.nid');
  $query->leftJoin('users', 'u', 'r.uid = u.uid');
  $query->addField('n', 'vid', 'live_revision');
  $query->condition('n.nid', $node->nid)
    ->orderBy('r.vid', 'DESC')
    ->fields('r', array('nid', 'vid', 'title', 'log', 'uid', 'timestamp'))
    ->fields('u', array('name'));

  $revisions = $query->execute()
    ->fetchAllAssoc('vid');

  // Build the table rows.
  $rows = array();
  foreach ($revisions as $revision) {
    $row = array(
      'data' => array(
        'vid' => '',
        'info' => '',
        'date' => '',
        'revision' => '',
        'moderation' => '',
      ),
      'class' => array('revision'),
    );

    // Add row classes.
    if ($revision->vid == $node->workbench_moderation['current']->vid) {
      $row['class'][] = 'current-revision';
    }
    if (isset($node->workbench_moderation['published']) && $revision->vid == $node->workbench_moderation['published']->vid) {
      $row['class'][] = 'published-revision';
    }
    else {
      $row['class'][] = 'unpublished-revision';
    }

    // Add row data.
    $row['data']['vid'] = $revision->vid;
    $row['data']['info'] .= '<div class="revision-title">' . check_plain($revision->title) . '</div>';
    $row['data']['info'] .= '<div class="revision-log description">' . filter_xss($revision->log) . '</div>';
    $row['data']['info'] .= '<div class="revision-user description">' . t('Revised by !user', array('!user' => theme('username', array('account' => $revision)))) . '</div>';
    $row['data']['date'] = format_date($revision->timestamp, 'short');

    // Revision operations.
    $revision_operations = array();
    if (isset($node->workbench_moderation['published']) && $revision->vid == $node->workbench_moderation['published']->vid) {
      $revision_operations['view'] = workbench_moderation_access_link(t('view'), "node/{$revision->nid}");
    }
    elseif ($revision->vid == $node->workbench_moderation['current']->vid) {
      $revision_operations['view'] = workbench_moderation_access_link(t('view'), "node/{$revision->nid}/current-revision");
    }
    else {
      $revision_operations['view'] = workbench_moderation_access_link(t('view'), "node/{$revision->nid}/revisions/{$revision->vid}/view");
    }

    $revision_operations['revert'] = workbench_moderation_access_link(t('revert'), "node/{$revision->nid}/revisions/{$revision->vid}/revert");
    $revision_operations['delete'] = workbench_moderation_access_link(t('delete'), "node/{$revision->nid}/revisions/{$revision->vid}/delete");

    $row['data']['revision'] = implode(' | ', array_filter($revision_operations));

    // Get the moderation history of this revision.
    $query = db_select('workbench_moderation_node_history', 'm');
    $query->leftJoin('users', 'u', 'm.uid = u.uid');
    $query->condition('m.vid', $revision->vid)
      ->orderBy('m.stamp', 'DESC')
      ->orderBy('m.hid', 'DESC')
      ->fields('m')
      ->fields('u', array('name'));

    $moderations = $query->execute()
      ->fetchAllAssoc('hid');

    // Make sure it's an array.
    if (empty($moderations)) {
      $moderations = array();
      if ($revision->vid == $node->workbench_moderation['current']->vid) {
        $moderations = array($node->workbench_moderation['current']);
      }
    }

    // If this is the current revision, provide moderation links.
    if (!empty($node->workbench_moderation['published']) && $revision->vid == $node->workbench_moderation['published']->vid) {
      $row['data']['moderation'] = '<div class="moderation-state"><strong>' . t('This is the published revision.') . '</strong></div>';
      // Provide an unpublish link.
      $next_states = workbench_moderation_states_next(workbench_moderation_state_published(), $user, $node);
      if (!empty($next_states)) {
        $row['data']['moderation'] .= '<div class="moderation-actions">' . l(t('Unpublish'), "node/{$revision->nid}/moderation/{$revision->live_revision}/unpublish") . '</div>';
      }
    }
    elseif ($revision->vid == $node->workbench_moderation['current']->vid) {
      $node_current = workbench_moderation_node_current_load($node);
      $row['data']['moderation'] = '<div class="moderation-state"><strong>' . t('This is the current revision. The current state is %state.', array('%state' => workbench_moderation_state_label($node->workbench_moderation['current']->state))) . '</strong></div>';
      $moderate_form = drupal_get_form('workbench_moderation_moderate_form', $node_current);
      $row['data']['moderation'] .= '<div class="moderation-actions">' . t('Set moderation state: !moderation-actions-form', array('!moderation-actions-form' => drupal_render($moderate_form))) . '</div>';
    }

    // Build a table of the moderation history.
    $moderation_rows = array();
    $items = array();
    foreach ($moderations as $moderation) {
      if ($moderation->from_state) {
        $items[] = t('From %from_state --> %to_state on %date by !user',
          array(
            '%from_state' => workbench_moderation_state_label($moderation->from_state),
            '%to_state' => workbench_moderation_state_label($moderation->state),
            '%date' => format_date($moderation->stamp, 'short'),
            '!user' => theme('username', array('account' => $moderation)),
          )
        );
      }
      else {
        $items[] = t('Created as %to_state on %date by !user',
          array(
            '%to_state' => workbench_moderation_state_label($moderation->state),
            '%date' => format_date($moderation->stamp, 'short'),
            '!user' => theme('username', array('account' => $moderation)),
          )
        );
      }
    }
    $row['data']['moderation'] .= theme('item_list', array('items' => $items));

    $rows[] = $row;
  }

  // Set the table header.
  $header = array(t('Revision'), t('Title'), t('Date'), t('Revision actions'), t('Moderation actions'));

  // Return properly styled output.
  return array(
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'workbench_moderation') . '/css/workbench_moderation.css',
      ),
    ),
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
}

/**
 * Form to unpublish the live revision.
 *
 * @param $node
 *   The node being acted upon.
 *
 * @return
 *   A Drupal confirmation form to unpublish the live revision.
 */
function workbench_moderation_node_unpublish_form($form, &$form_state, $node) {
  global $user;

  // Ensure that this is the live revision.
  if (isset($node->workbench_moderation['published']->vid) && $node->vid != $node->workbench_moderation['published']->vid) {
    drupal_set_message(t('This is not the live revision of this node.'), 'error');
    drupal_goto("node/{$node->nid}/moderation");
  }

  $form = array();
  $form['node'] = array(
    '#value' => $node,
    '#type' => 'value',
  );
  $form['message'] = array(
    '#markup' =>  '<p>' . t('Are you sure that you want to unpublish the live revision of this content?') . '</p>',
  );

  $current_state = $node->workbench_moderation['my_revision']->state;
  if ($next_states = workbench_moderation_states_next($current_state, $user, $node)) {
    $form['state'] = array(
      '#title' => t('Set moderation state'),
      '#type' => 'select',
      '#options' => $next_states,
      '#default_value' => _workbench_moderation_default_next_state($current_state, $next_states),
    );
  }
  else {
    $form['message']['#markup'] .= '<p>' . t('The current live revision will be set to moderation state %state.', array('%state' => workbench_moderation_state_label(workbench_moderation_state_none()))) . '</p>';
    $form['state'] = array(
      '#type' => 'value',
      '#value' => workbench_moderation_state_none(),
    );
  }

  return confirm_form($form, t('Unpublish %title?', array('%title' => $node->title)), "node/{$node->nid}/moderation", '', t('Unpublish'));
}

/**
 * Submit handler for unpublishing a live revision of a node.
 */
function workbench_moderation_node_unpublish_form_submit($form, &$form_state) {
  global $user;
  $node = $form['node']['#value'];

  // Remove the moderation record's "published" flag.
  $query = db_update('workbench_moderation_node_history')
    ->condition('hid', $node->workbench_moderation['published']->hid)
    ->fields(array('published' => 0))
    ->execute();

  // Moderate the revision.
  workbench_moderation_moderate($node, $form_state['values']['state']);

  // Make sure the 'current' revision is the 'live' revision -- ie, the revision
  // in {node}.
  $live_revision = workbench_moderation_node_current_load($node);
  $live_revision->status = 0;
  $live_revision->revision = 0;
  $live_revision->workbench_moderation['updating_live_revision'] = TRUE;
  // @TODO: do we trust node_save() here?
  node_save($live_revision);

  drupal_set_message(t('The live revision of this content has been unpublished.'));
  $form_state['redirect'] ="node/{$node->nid}/moderation";
}
