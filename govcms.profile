<?php
/**
 * @file
 * The govCMS install profile file.
 *
 * The original foundation for the govCMS distribution is aGov; the Drupal distribution created by PreviousNext to provide a core set of elements, functionality and features that can be used to develop government websites
 *
 * @copyright Copyright(c) 2015 Commonwealth of Australia as represented by Department of Finance
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Department of Finance
 */

/**
 * Implements hook_install_configure_form_alter().
 *
 * Changes the inserted variables on the installer to some different defaults
 */
function govcms_form_install_configure_form_alter(&$form, &$form_state) {
  $form['site_information']['site_name']['#default_value'] = 'govCMS';
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
    drupal_get_path('module', 'govcms_core') . '/js/govcms_core.js' => array(
      'type' => 'file',
    ),
  );
}


/**
 * Implements hook_block_info_alter().
 */
function govcms_block_info_alter(&$blocks, $theme, $code_blocks) {
  $blocks['system']['help']['region'] = 'content';
  $blocks['system']['user-menu']['title'] = '<none>';
  if (isset($blocks['superfish'][1])) {
    $blocks['superfish'][1]['title'] = '<none>';
  }
}

/**
 * Implements hook_system_info_alter().
 */
function govcms_system_info_alter(&$info, $file, $type) {
  if (isset($info['project']) && $info['project'] == 'govcms' && arg(0) == 'admin' && arg(1) == 'modules') {
    $info['dependencies'] = array();
  }
}
