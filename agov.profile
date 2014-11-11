<?php
/**
 * @file
 * The aGov install profile modules file.
 *
 * @copyright Copyright(c) 2012 PreviousNext
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Chris Skene chris at previousnext.com.au
 */

/**
 * Implements hook_install_configure_form_alter().
 *
 * Changes the inserted variables on the installer to some different defaults
 */
function agov_form_install_configure_form_alter(&$form, &$form_state) {
  $form['site_information']['site_name']['#default_value'] = 'aGov';
  $form['site_information']['site_mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['admin_account']['account']['mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  $form['server_settings']['site_default_country']['#default_value'] = 'AU';
  $timezone_form = $form['server_settings']['date_default_timezone'];
  $sydney_tz = $timezone_form['#options']['Australia/Sydney'];
  $sydney_re = '/Sydney/';
  $canberra_tz = preg_replace($sydney_re, 'Canberra', $sydney_tz, 1);
  $timezone_form['#options']['Australia/Canberra'] = $canberra_tz;
  asort($timezone_form['#options']);
  $form['server_settings']['date_default_timezone'] = $timezone_form;


  // As a workaround to core issue #1017020 (http://drupal.org/node/1017020),
  // we override the timezone javascript behaviour by setting it to null in the
  // javascript file added below.
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'agov_core') . '/js/agov_core.js' => array(
      'type' => 'file',
    ),
  );
}


/**
 * Implements hook_block_info_alter().
 */
function agov_block_info_alter(&$blocks, $theme, $code_blocks) {
  $blocks['system']['help']['region'] = 'content';
  $blocks['superfish'][1]['title'] = '<none>';
  $blocks['system']['user-menu']['title'] = '<none>';
}

/**
 * Implements hook_system_info_alter().
 */
function agov_system_info_alter(&$info, $file, $type) {
  if (isset($info['project']) && $info['project'] == 'agov' && arg(0) == 'admin' && arg(1) == 'modules') {
    $info['dependencies'] = array();
  }
}

/**
 * Convert node reference to entity reference.
 */
function agov_update_7100() {
  module_enable(array('entityreference'));
  $field = field_info_field('field_reference');
  if (!$field) {
    throw new DrupalUpdateException('field_reference not found');
  }

  db_transaction();

  // Modify table structure.
  $spec = array(
    'description' => 'The id of the target entity.',
    'type' => 'int',
    'unsigned' => TRUE,
    'not null' => TRUE,
  );
  db_change_field('field_data_field_reference', 'field_reference_nid', 'field_reference_target_id', $spec);
  db_change_field('field_revision_field_reference', 'field_reference_nid', 'field_reference_target_id', $spec);

  // Update the field config.
  $data = serialize(array(
    'translatable' => '0',
    'entity_types' => array(),
    'settings' => array(
      'target_type' => 'node',
      'handler' => 'base',
      'handler_settings' => array(
        'target_bundles' => $field['settings']['referenceable_types'],
        'sort' => array(
          'type' => 'property',
          'property' => 'title',
          'direction' => 'ASC',
        ),
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
      ),
    ),
    'storage' => array(
      'type' => 'field_sql_storage',
      'settings' => array(),
      'module' => 'field_sql_storage',
      'active' => '1',
      'details' => array(
        'sql' => array(
          'FIELD_LOAD_CURRENT' => array(
            'field_data_field_reference' => array(
              'target_id' => 'field_reference_target_id',
            ),
          ),
          'FIELD_LOAD_REVISION' => array(
            'field_revision_field_reference' => array(
              'target_id' => 'field_reference_target_id',
            ),
          ),
        ),
      ),
    ),
    'foreign keys' => array(
      'node' => array(
        'table' => 'node',
        'columns' => array(
          'target_id' => 'nid',
        ),
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'id' => $field['id'],
  ));
  $fields = array(
    'type' => 'entityreference',
    'module' => 'entityreference',
    'data' => $data,
  );
  db_merge('field_config')
    ->key(array('id' => $field['id']))
    ->fields($fields)
    ->execute();

  // Update field instance config.
  foreach ($field['bundles'] as $entity_type => $bundle) {
    foreach ($bundle as $bundle_name) {
      $field_instance = field_info_instance($entity_type, 'field_reference', $bundle_name);
      if ($field_instance) {
        foreach ($field_instance['display'] as $display_mode => &$display) {
          switch ($display['type']) {
            case 'node_reference_default':
              $display['module'] = 'entityreference';
              $display['type'] = 'entityreference_label';
              $display['settings']['link'] = 1;
              break;
            case 'node_reference_plain':
              $display['module'] = 'entityreference';
              $display['type'] = 'entityreference_label';
              $display['settings']['link'] = FALSE;
              break;
            case 'node_reference_node':
              $display['module'] = 'entityreference';
              $display['type'] = 'entityreference_entity_view';
              $display['settings']['view_mode'] = $display['settings']['node_reference_view_mode'];
              unset($display['settings']['node_reference_view_mode']);
              break;
            case 'node_reference_nid':
              $display['module'] = 'entityreference';
              $display['type'] = 'entityreference_entity_id';
              break;
            case 'node_reference_path':
              $display['module'] = 'entityreference';
              $display['type'] = 'entityreference_path';
              break;
          }
        }
        field_update_instance($field_instance);
      }
    }
  }
}
