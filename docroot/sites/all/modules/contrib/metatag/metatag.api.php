<?php
/**
 * @file
 * API documentation for the Metatag module.
 */

/**
 * To enable Metatag support in custom entities, add 'metatags' => TRUE to the
 * entity definition in hook_entity_info(), e.g.:
 * 
 * /**
 *  * Implements hook_entity_info().
 *  *
 *  * Taken from the Examples module.
 *  * /
 * function entity_example_entity_info() {
 *   $info['entity_example_basic'] = array(
 *     'label' => t('Example Basic Entity'),
 *     'controller class' => 'EntityExampleBasicController',
 *     'base table' => 'entity_example_basic',
 *     'uri callback' => 'entity_example_basic_uri',
 *     'fieldable' => TRUE,
 *     'metatags' => TRUE,
 *     'entity keys' => array(
 *       'id' => 'basic_id' , // The 'id' (basic_id here) is the unique id.
 *       'bundle' => 'bundle_type' // Bundle will be determined by the 'bundle_type' field
 *     ),
 *     'bundle keys' => array(
 *       'bundle' => 'bundle_type',
 *     ),
 *     'static cache' => TRUE,
 *     'bundles' => array(
 *       'first_example_bundle' => array(
 *         'label' => 'First example bundle',
 *         'admin' => array(
 *           'path' => 'admin/structure/entity_example_basic/manage',
 *           'access arguments' => array('administer entity_example_basic entities'),
 *         ),
 *       ),
 *     ),
 *     'view modes' => array(
 *       'tweaky' => array(
 *         'label' => t('Tweaky'),
 *         'custom settings' =>  FALSE,
 *       ),
 *     )
 *   );
 * 
 *   return $info;
 * }
 *
 * The definition of each bundle may be handled separately, thus support may be
 * disabled for the entity as a whole but enabled for individual bundles. This
 * is handled via the 'metatags' value on the bundle definition, e.g.:
 *
 *     'bundles' => array(
 *       'first_example_bundle' => array(
 *         'label' => 'First example bundle',
 *         'metatags' => TRUE,
 *         'admin' => array(
 *           'path' => 'admin/structure/entity_example_basic/manage',
 *           'access arguments' => array('administer entity_example_basic entities'),
 *         ),
 *       ),
 *     ),
 */

/**
 * Provides a default configuration for Metatag intances.
 *
 * This hook allows modules to provide their own Metatag instances which can
 * either be used as-is or as a "starter" for users to build from.
 *
 * This hook should be placed in MODULENAME.metatag.inc and it will be auto-
 * loaded. MODULENAME.metatag.inc *must* be in the same directory as the
 * .module file which *must* also contain an implementation of
 * hook_ctools_plugin_api, preferably with the same code as found in
 * metatag_ctools_plugin_api().
 *
 * The $config->disabled boolean attribute indicates whether the Metatag
 * instance should be enabled (FALSE) or disabled (TRUE) by default.
 *
 * @return
 *   An associative array containing the structures of Metatag instances, as
 *   generated from the Export tab, keyed by the Metatag config name.
 *
 * @see metatag_metatag_config_default()
 * @see metatag_ctools_plugin_api()
 */
function hook_metatag_config_default() {
  $configs = array();

  $config = new stdClass();
  $config->instance = 'config1';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'title' => array('value' => '[current-page:title] | [site:name]'),
    'generator' => array('value' => 'Drupal 7 (http://drupal.org)'),
    'canonical' => array('value' => '[current-page:url:absolute]'),
    'shortlink' => array('value' => '[current-page:url:unaliased]'),
  );
  $configs[$config->instance] = $config;

  $config = new stdClass();
  $config->instance = 'config2';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'title' => array('value' => '[user:name] | [site:name]'),
  );
  $configs[$config->instance] = $config;

  return $configs;
}

/**
 * 
 */
function hook_metatag_config_default_alter(&$config) {
}

/**
 * 
 */
function hook_metatag_config_delete($entity_type, $entity_ids) {
}

/**
 * 
 */
function hook_metatag_config_insert($config) {
}

/**
 * 
 */
function hook_metatag_config_instance_info() {
  return array();
}

/**
 * 
 */
function hook_metatag_config_instance_info_alter(&$info) {
}

/**
 * 
 */
function hook_metatag_config_load() {
}

/**
 * 
 */
function hook_metatag_config_load_presave() {
}

/**
 * 
 */
function hook_metatag_config_presave($config) {
}

/**
 * 
 */
function hook_metatag_config_update($config) {
}

/**
 * 
 */
function hook_metatag_info() {
  return array();
}

/**
 * 
 */
function hook_metatag_info_alter(&$info) {
}

/**
 * 
 */
function hook_metatag_load_entity_from_path_alter(&$path, $result) {
}

/**
 * Alter metatags before being cached.
 *
 * This hook is invoked prior to the meta tags for a given page are cached.
 *
 * @param array $output
 *   All of the meta tags to be output for this page in their raw format. This
 *   is a heavily nested array.
 * @param string $instance
 *   An identifier for the current page's page type, typically a combination
 *   of the entity name and bundle name, e.g. "node:story".
 */
function hook_metatag_metatags_view_alter(&$output, $instance) {
  if (isset($output['description']['#attached']['drupal_add_html_head'][0][0]['#value'])) {
    $output['description']['#attached']['drupal_add_html_head'][0][0]['#value'] = 'O rly?';
  }
}

/**
 * 
 */
function hook_metatag_page_cache_cid_parts_alter(&$cid_parts) {
}

/**
 * 
 */
function hook_metatag_presave(&$metatags, $entity_type, $entity_id) {
}
