<?php
/**
 * @file
 * Provides administrative functions for ccl.
 */

/**
 * CCL adminitsration form.
 */
function ccl_admin() {
  $result = db_query("SELECT * FROM {ccl}");
  if ($result->rowCount()) {

    // Get content type names.
    $cts = node_type_get_names();

    // Prepare table header.
    $header = array(
      t('Title'),
      t('URL'),
      t('Type'),
      t('Options'),
      t('Operation'),
    );

    $rows = array();
    foreach ($result as $record) {
      $options = array('desc' => '', 'op' => '');
      // Prepeare the options display.
      if ($record->type == 'node') {
        $link_options = unserialize($record->options);
        switch ($link_options['node_options']) {
          case 'global':
            $options['desc'] = t('Attached to all nodes.');
            break;

          case 'ct':
            $options['desc'] = t('Attached to all nodes of the content type %ct.', array('%ct' => $cts[$link_options['node_type']]));
            break;

          case 'node':
            $node_title = db_query('SELECT title FROM {node} WHERE nid = :nid', array(':nid' => $link_options['node_id']))->fetchField();
            $options['desc'] = t('Attached to %node_title [NID: !nid].', array('%node_title' => $node_title, '!nid' => $link_options['node_id']));
            break;
        }
        $options['op'] = l(t('Edit'), 'admin/config/user-interface/ccl/' . $record->clid . '/edit') . ' | ' . l(t('Delete'), 'admin/config/user-interface/ccl/' . $record->clid . '/delete');

      }
      else {
        foreach (module_implements('ccl_link_info') as $module) {
          $options = module_invoke($module, 'ccl_link_info', $record);
          if (!empty($options)) {
            break;
          }
        }
      }

      // Prepare table row.
      $rows[] = array(
        $record->title,
        $record->link,
        $record->type,
        $options['desc'],
        $options['op'],
      );
    }
    return theme('table', array('header' => $header, 'rows' => $rows));
  }

  // No results text.
  else {
    return array(
      'empty_text' => array(
        '#type' => 'markup',
        '#markup' => '<p>' . t('No custom contextual links have been added yet. <a href="@add-page">Add a link here</a>.', array('@add-page' => url('admin/config/user-interface/ccl/add'))) . '</p>',
      ),
    );
  }
}

/**
 * Link add and edit form.
 */
function ccl_add_form($form, &$form_state, $clid = 0) {
  // Check if we are in edit mode and load the link values.
  if ($clid) {
    $link = db_query('SELECT * FROM {ccl} WHERE clid = :clid', array(':clid' => $clid))->fetchObject();
    $form_state['clid'] = $clid;
    $form_state['link'] = $link;

    // Unserialize options.
    $link->options = unserialize($link->options);
    $node_options = $link->options['node_options'];
    if ($node_options == 'node') {
      $title = db_query('SELECT title FROM {node} WHERE nid = :nid', array(':nid' => $link->options['node_id']))->fetchField();
      $nid_text = $title . ' [nid:' . $link->options['node_id'] . ']';
    }
  }

  $form = array();
  // Pull in library, js and css for the form.
  $form['#attached']['library'][] = array('system', 'ui.button');
  $form['#attached']['js'][] = drupal_get_path('module', 'ccl') . '/ccl.js';
  $form['#attached']['css'][] = drupal_get_path('module', 'ccl') . '/ccl.css';


  $form['link_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Link'),
    '#collapsible' => TRUE,
  );

  $form['link_group']['ccl_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The title of this link as it will be displayed in the contextual widget.'),
    '#size' => 40,
    '#default_value' => $clid ? $link->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['link_group']['ccl_link'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => $clid ? $link->link : '',
    '#description' => t('The URL of this link.'),
    '#size' => 40,
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['link_group']['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['link_group']['advanced']['advanced_css'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS Class'),
    '#default_value' => ($clid && isset($link->options['advanced_css'])) ? $link->options['advanced_css'] : '',
    '#description' => t('Add class name(s) to the link. Multiple classes should be seperated by a space. Example: "%example".', array('%example' => "colorbox-load extra-class")),
    '#size' => 40,
    '#maxlength' => 255,
  );
  $form['link_group']['advanced']['advanced_query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query String'),
    '#default_value' => ($clid && isset($link->options['advanced_query'])) ? $link->options['advanced_query'] : '',
    '#description' => t('Append a query string to the end of the link. Do not use the "?" at the beginning of the query. Tokens can be used for this field as well.<br />Example: "%example".', array('%example' => "width=500&height=500&iframe=true&user=[current-user:uid]")),
    '#size' => 40,
    '#maxlength' => 255,
  );

  $form['link_group']['advanced']['advanced_target'] = array(
    '#type' => 'select',
    '#title' => t('Link Target'),
    '#options' => array(
      'default' => t('Default (no target attribute)'),
      '_top' => t('Open link in window root'),
      '_blank' => t('Open link in new window'),
    ),
    '#default_value' => ($clid && isset($link->options['advanced_target'])) ? $link->options['advanced_target'] : '',
    '#description' => t('Set a target attribute for the link.'),
  );

  $form['link_group']['token_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tokens'),
    '#description' => t("Token replacements will be performed for the link title and for the URL. Note that 'Node' tokens will not be replaced for links that are added to blocks."),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  if (module_exists('token')) {
    $form['link_group']['token_group']['tokens'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node'),
      '#global_types' => TRUE,
      '#click_insert' => TRUE,
    );
  }
  else {
    $form['link_group']['token_group']['token_tree'] = array(
      '#markup' => '<p>' . t('Enable the <a href="@drupal-token">Token module</a> to view the available token browser.', array('@drupal-token' => 'http://drupal.org/project/token')) . '</p>',
    );
  }

  $form['options_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
    '#collapsible' => TRUE,
  );

  $form['options_group']['ccl_type'] = array(
    '#type' => 'radios',
    '#title' => t('Link Type'),
    '#description' => t('Select if this link should be displayed for a node or for a block.'),
    '#options' => array(
      'node' => t('Node'),
    ),
    '#default_value' => $clid ? $link->type : 'node',
  );

  $form['options_group']['node_options'] = array(
    '#type' => 'radios',
    '#title' => t('Show link for'),
    '#description' => t('Select if this link should be displayed for all nodes, all nodes of a content type or a specific node.'),
    '#options' => array(
      'node' => t('Single node'),
      'ct' => t('Content type'),
      'global' => t('All nodes'),
    ),
    '#default_value' => isset($node_options) ? $node_options : 'node',
    '#states' => array(
      'visible' => array(
        ':input[name="ccl_type"]' => array('value' => 'node'),
      ),
    ),

  );

  // Load the content type names.
  $types = node_type_get_names();
  $form['options_group']['node_type'] = array(
    '#type' => 'select',
    '#title' => t('Content Type'),
    '#description' => t('The content type this link will be displayed for.'),
    '#options' => $types,
    '#default_value' => $clid ? $link->options['node_type'] : -1,
    '#states' => array(
      'visible' => array(
        ':input[name="node_options"]' => array('value' => 'ct'),
        ':input[name="ccl_type"]' => array('value' => 'node'),
      ),
    ),
  );

  $form['options_group']['node_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Node ID'),
    '#description' => t('Enter the title of the node or the id of the node this link should be added to.'),
    '#size' => 40,
    '#maxlength' => 128,
    '#default_value' => isset($nid_text) ? $nid_text : '',
    '#autocomplete_path' => 'admin/config/user-interface/ccl/autocomplete',
    '#states' => array(
      'visible' => array(
        ':input[name="node_options"]' => array('value' => 'node'),
        ':input[name="ccl_type"]' => array('value' => 'node'),
      ),
    ),
  );

  $form['ccl_save_link'] = array(
    '#type' => 'submit',
    '#value' => t('Save Link'),
  );

  return $form;
}

/**
 * Validafion handler for ccl_add_form().
 *
 * @see ccl_add_form()
 */
function ccl_add_form_validate($form, &$form_state) {
  $values = $form_state['values'];

  // Check that that we can get the node id and transform it for saving.
  if ($values['ccl_type'] == 'node' && $values['node_options'] == 'node') {
    if (is_numeric($values['node_id'])) {
      form_set_value(
        $form['options_group']['node_id'],
        $values['node_id'], $form_state
      );
    }
    elseif (preg_match('/\[nid:[0-9]*\]/', $values['node_id'], $match)) {
      form_set_value($form['options_group']['node_id'], substr(rtrim($match[0], ']'), 5), $form_state);
    }
    else {
      form_set_error('nid', t('Enter a node id or use the autocomplete widget to select an existing node.'));
    }
  }
}

/**
 * Submit handler for ccl_add_form().
 *
 * @see ccl_add_form()
 */
function ccl_add_form_submit($form, &$form_state) {
  // Clean up the values array.
  form_state_values_clean($form_state);
  $values = $form_state['values'];

  // Extract the options out of the values.
  $options = array();
  foreach ($values as $key => $data) {
    if (strpos($key, 'ccl_') === FALSE) {
      $options[$key] = $data;
    }
  }

  $record = array(
    'type' => $values['ccl_type'],
    'title' => $values['ccl_title'],
    'link' => $values['ccl_link'],
    'options' => serialize($options),
  );

  if (isset($form_state['clid'])) {
    $record['clid'] = $form_state['clid'];
    $res = drupal_write_record('ccl', $record, 'clid');
  }
  else {
    $res = drupal_write_record('ccl', $record);
  }

  if ($res) {
    drupal_set_message(t('Contextual link saved.'));
    _ccl_update_cache();
  }
  else {
    drupal_set_message(t('There was an error writing this record to the database. Please try again.'), 'error');
  }
  drupal_goto('admin/config/user-interface/ccl');
}

/**
 * Link delete confirmation page.
 */
function ccl_delete_confirm($form, &$form_state, $id) {
  $form['clid'] = array(
    '#type' => 'value',
    '#value' => $id,
  );
  $title = db_query('SELECT title FROM {ccl} WHERE clid = :clid', array(':clid' => $id))->fetchField();
  return confirm_form($form,
    t('Are you sure you want to delete the link %title?', array('%title' => $title)),
    'admin/config/user-interface/ccl',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

/**
 * Submit handler for link deletion page.
 */
function ccl_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    db_delete('ccl')
      ->condition('clid', $form_state['values']['clid'])
      ->execute();
    drupal_set_message(t('Link removed.'));
    _ccl_update_cache();
    drupal_goto('admin/config/user-interface/ccl');
  }
}

/**
 * Node ID autocomplete callback function.
 */
function ccl_node_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $result = db_select('node', 'n')
      ->fields('n', array('title', 'nid'))
      ->condition('title', db_like($string) . '%', 'LIKE')
      ->range(0, 10)
      ->execute();
    foreach ($result as $node) {
      $matches[check_plain($node->title) . ' [nid:' . $node->nid . ']'] = check_plain($node->title);
    }
  }
  drupal_json_output($matches);
}
