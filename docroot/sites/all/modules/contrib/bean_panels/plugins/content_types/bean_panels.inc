<?php

/**
 * @file
 * Content type plugin to expose rendered beans, view mode configuration
 * still available.
 */

$plugin = array(
  'title' => t('Rendered bean'),
  'defaults' => array('view_mode' => 'full', 'bean_delta' => ''),
  'category' => t('Beans')
);

/**
 * Returns an edit form for a entity.
 *
 * Rendered entity use entity types machine name as subtype name.
 *
 * @see bean_panels_bean_panels_view_get_content_types()
 */
function bean_panels_bean_panels_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $entity_info = entity_get_info('bean');

  $options = array();
  if (!empty($entity_info['view modes'])) {
    foreach ($entity_info['view modes'] as $mode => $settings) {
      $options[$mode] = $settings['label'];
    }
  }

  if (count($options) > 1) {
    $form['view_mode'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#title' => t('View mode'),
      '#default_value' => $conf['view_mode'],
    );
  }
  else {
    $form['view_mode_info'] = array(
      '#type' => 'item',
      '#title' => t('View mode'),
      '#description' => t('Only one view mode is available for this entity type.'),
      '#markup' => $options ? current($options) : t('Default'),
    );

    $form['view_mode'] = array(
      '#type' => 'value',
      '#value' => $options ? key($options) : 'default',
    );
  }

  $beans = bean_get_all_beans();
  $bean_options = array();
  foreach ($beans as $bean) {
    $bean_options[$bean->delta] = $bean->label;
  }
  $form['bean_delta'] = array(
    '#type' => 'select',
    '#options' => $bean_options,
    '#title' => t('Bean'),
    '#description' => t('Select the bean you want to display.'),
    '#default_value' => $conf['bean_delta']
  );

  return $form;
}

/**
 * Save selected view mode.
 */
function bean_panels_bean_panels_content_type_edit_form_submit(&$form, &$form_state) {
  if (isset($form_state['values']['view_mode'])) {
    $form_state['conf']['view_mode'] = $form_state['values']['view_mode'];
  }
  if (isset($form_state['values']['bean_delta'])) {
    $form_state['conf']['bean_delta'] = $form_state['values']['bean_delta'];
  }
}

/**
 * Implements hook_PLUGIN_content_type_render().
 *
 * Ctools requires us to return a block.
 *
 * @see ctools_content_render()
 */
function bean_panels_bean_panels_content_type_render($entity_type, $conf, $panel_args, $contexts) {
  $block = new stdClass();
  $block->module = 'bean_panels';
  $delta = $conf['bean_delta'];
  $view_mode = $conf['view_mode'];
  $block->delta = 'bean_panels' . '-' . str_replace('-', '_', $view_mode) . '-' . str_replace('-', '_', $delta);
  // Default to empty.
  $block->content = FALSE;
  if (($bean = bean_load_delta($delta))) {
    // Bean delta exists.
    if (bean_access('view', $bean)) {
      if (!empty($bean->title)) {
        $block->title = check_plain($bean->title);
      }
      $block->content = $bean->view($view_mode);
      $block->content['#contextual_links']['bean'] = array('block', array($delta));
    }
  }
  elseif (bean_add_page_access()) {
    $block->content = array(
      '#markup' => t('Bean with delta %delta does not exist, please <a href="!url">create it first</a>.',
                    array(
                      '!url' => url('block/add'),
                      '%delta' => $delta
                    ))
    );
  }
  return $block;
}

/**
 * Implements hook_PLUGIN_content_type_admin_title().
 *
 * Returns the administrative title for a type.
 */
function bean_panels_bean_panels_content_type_admin_title($entity_type, $conf, $contexts) {
  $entity_info = entity_get_info('bean');
  $view_mode = $conf['view_mode'];
  if (isset($entity_info['view modes'][$view_mode])) {
    $view_mode = $entity_info['view modes'][$view_mode]['label'];
  }
  return t('Rendered bean of delta %delta using view mode "@view_mode"', array('%delta' => $conf['bean_delta'], '@view_mode' => $view_mode));
}
