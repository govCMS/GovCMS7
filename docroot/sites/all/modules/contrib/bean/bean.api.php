<?php

/**
 * Implements hook_bean_types_api_info().
 *
 * Tell the bean module that you are implemented a plugin and
 * which version of the API are you using.
 *
 * THIS IS REQUIRED
 */
function hook_bean_types_api_info() {
  return array(
    'api' => 4,
  );
}

/**
 * Implements hook_bean_types().
 *
 * Beans uses ctools plugins to define the block types.
 * All plugin files must be registered in the .info file.
 */
function hook_bean_types() {
  $plugins = array();
  $plugins['plugin_key'] = array(
    'label' => t('Title'),
    'description' => t('Description'),
    // This is optional. Set it to TRUE if you do not want the plugin to be
    // displayed in the UI.
    'abstract' => FALSE,
    'handler' => array(
      'class' => 'ClassName',
      'parent' => 'bean',
      // This should be pointing to the path of your custom bean plugin module.
      'path' => drupal_get_path('module', 'example_bean') . '/plugins',
      // Class files should be named accordingly in order to support ctools
      // autoloading procedures.
      'file' => 'ClassName.class.php',
    ),
  );
  return $plugins;
}

/**
 * Implements hook_bean_access().
 *
 * Access callback for beans
 *
 * @param $bean
 *  Tthe fully loaded bean object
 * @param $bean
 *  The access type of view, edit, delete, create
 * @param $account
 *  The user account
 *
 * @return boolean
 *  True if access is allowed, FALSE if not.
 */
function hook_bean_access($bean, $op, $account) {
  return TRUE;
}

/**
 * Implements hook_bean_submit().
 *
 * React to the bean form submit.
 */
function hook_bean_form_submit($form, $form_state) {

}

/**
 * Implements hook_bean_cache_clear().
 */
function hook_bean_cache_clear() {

}
