<?php
/**
 * @file
 * Define Linkit class attribute plugin.
 */

$plugin = array(
  'name' => t('Classes'),
  'callback' => 'linkit_attribute_plugin_class',
);

/**
 * Create a FAPI element.
 *
 * @param array $plugin
 *   This is the plugin definition.
 *
 * @param array $settings
 *   An array of settings for this attribute. This is from the profile settings.
 *
 * @return
 *   An FAPI element.
 *
 * @see LinkitProfile::setAttributes()
 */
function linkit_attribute_plugin_class($plugin, $settings = array()) {
  return array(
    '#type' => 'textfield',
    '#title' => $plugin['name'],
    '#maxlength' => 255,
    '#size' => 40,
    '#default_value' => '',
    '#weight' => isset($settings['weight']) ? $settings['weight'] : 0,
  );
}