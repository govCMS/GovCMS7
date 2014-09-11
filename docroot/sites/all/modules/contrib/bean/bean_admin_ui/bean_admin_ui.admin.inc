<?php

/**
 * @file
 * Bean Admin Page
 */

/**
 * Main page callback on the bean type
 */
function bean_admin_ui_admin_page() {
  $field_ui = module_exists('field_ui');
  $rows = array();
  $i = 0;

  foreach (bean_get_types() as $bean_type) {
    $row = array();
    $row[] = array('data' => check_plain($bean_type->getLabel()));
    if (method_exists($bean_type, 'getExportStatus')) {
      $export_status = $bean_type->getExportStatus();
    }
    else {
      $export_status = t('Normal');
    }
    $row[] = array('data' => $export_status);
    // Edit and delete buttons
    if ($bean_type->isEditable()) {
      $row[] = array('data' => l(t('Edit'), 'admin/structure/block-types/manage/' . $bean_type->buildURL() . '/edit'));
      switch ($export_status) {
        case t('Normal'):
          $row[] = array('data' => l(t('Delete'), 'admin/structure/block-types/manage/' . $bean_type->buildURL() . '/delete'));
          break;
        case t('Overridden'):
          $row[] = array('data' => l(t('Revert'), 'admin/structure/block-types/manage/' . $bean_type->buildURL() . '/revert'));
          break;
        case t('Default'):
          $row[] = array();
          break;
      }
    }
    else {
      // For the operations
      $row[] = array();
      $row[] = array();
    }

    if ($field_ui) {
      // Manage fields.
      $row[] = array('data' => l(t('manage fields'), 'admin/structure/block-types/manage/' . $bean_type->buildURL() . '/fields'));

      // Display fields.
      $row[] = array('data' => l(t('manage display'), 'admin/structure/block-types/manage/' . $bean_type->buildURL() . '/display'));
    }
    //creative way to setup sorting rows; add number to prevent dual keys
    $rows[str_replace(' ', '', $bean_type->getLabel()) . '_' . $i] = $row;
  }
  ksort($rows);

  $header = array(t('Name'), t('Status'), array('data' => t('Operations'), 'colspan' => $field_ui ? '4' : '2'));

  $build['bean_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are no Block Types Available'),
  );
  return $build;
}

/**
 * Generates the bean type editing form.
 */
function bean_admin_ui_type_form($form, &$form_state, $bean_type = NULL) {
  $form['new'] = array(
    '#type' => 'value',
    '#value' => TRUE,
  );
  // If bean_type is null then load an empty one.
  if (is_null($bean_type)) {
    $plugin_info = _bean_admin_default_plugin();
    $plugin_info['name'] = '';

    $bean_type = new BeanCustom($plugin_info);
  }
  elseif (!method_exists($bean_type, 'getExportStatus') || $bean_type->getExportStatus() == 'Normal') {
    $form['new'] = array(
      '#type' => 'value',
      '#value' => FALSE,
    );
  }

  $disabled = !$bean_type->isEditable();

  if ($disabled) {
    drupal_set_message(t('This Block Type can not be edited'));
  }
  $form['bean_type'] = array(
    '#type' => 'value',
    '#value' => $bean_type,
  );

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $bean_type->getLabel(),
    '#description' => t('The human-readable name of this block type.'),
    '#required' => TRUE,
    '#size' => 30,
    '#disabled' => $disabled,
  );

  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textarea',
    '#default_value' => $bean_type->getDescription(),
    '#description' => t('The description of this block type.'),
    '#disabled' => $disabled,
  );

  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($bean_type->type) ? $bean_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'bean_type_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this block type. It must only contain lowercase letters, numbers, and underscores.'),
    '#disabled' => $disabled,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Block type'),
    '#weight' => 40,
    '#disabled' => $disabled,
  );

  // This is a new bean type.
  if (!empty($bean_type->type)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#name' => 'delete',
      '#value' => t('Delete Block type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#disabled' => $disabled,
    );

    if (method_exists($bean_type, 'getExportStatus')) {
      if ($bean_type->getExportStatus() == 'Overridden') {
        $form['actions']['delete']['#name'] = 'revert';
        $form['actions']['delete']['#value'] = t('Revert to defaults');
      }
      else {
        unset($form['actions']['delete']);
      }

    }
  }
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function bean_admin_ui_type_form_submit(&$form, &$form_state) {
  $op = $form_state['clicked_button']['#name'];
  if (in_array($op, array('revert', 'delete'))) {
    $form_state['redirect'] = 'admin/structure/block-types/manage/' . $form['bean_type']['#value']->type . '/' . $op;
  }
  $bean_type = $form_state['values']['bean_type'];
  $bean_type->type = $form_state['values']['name'];
  $bean_type->setLabel($form_state['values']['label']);
  $bean_type->setDescription($form_state['values']['description']);
  $bean_type->save($form_state['values']['new']);
  $form_state['redirect'] = 'admin/structure/block-types';
  ctools_include('export');

  // Clear the site caches so that the new "manage fields" and "display fields"
  // pages for the new bean type work.
  drupal_flush_all_caches();
}

/**
 * Menu callback; Form builder to confirm delete/revert of a bean type.
 */
function bean_admin_ui_type_op_confirm($form, &$form_state, $op, $type) {
  $form['op'] = array('#type' => 'value', '#value' => $op);
  $form['type'] = array('#type' => 'value', '#value' => $type);
  $form['name'] = array('#type' => 'value', '#value' => $type->getLabel());
  $caption = '';
  if ($op == 'delete') {
    $message = t('Are you sure you want to delete the block type %type?', array('%type' => $type->getLabel()));
    $num_beans = db_query("SELECT COUNT(*) FROM {bean} WHERE type = :type", array(':type' => $type->type))->fetchField();
    if ($num_beans) {
      $caption .= '<p>' . format_plural($num_beans, '%type is used by 1 block on your site that is going to be removed along with %type.', '%type is used by @count blocks on your site that are going to be removed along %type.', array('%type' => $type->getLabel())) . '</p>';
    }
    $action = t('Delete');
  }
  else {
    $message = t('Are you sure you want to revert the block type %type?', array('%type' => $type->getLabel()));
    $action = t('Revert');
  }
  $caption .= '<p>' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, $message, 'admin/structure/block-types', $caption, $action);
}

function bean_admin_ui_type_op_confirm_submit($form, &$form_state) {
  $form_state['values']['type']->{$form['op']['#value']}();
  $form_state['redirect'] = 'admin/structure/block-types';
}
