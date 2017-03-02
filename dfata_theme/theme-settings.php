<?php

/**
 * @file
 * Theme settings for govCMS UI Kit theme.
 */

/**
 * Implements hook_system_theme_settings_alter().
 */
function dfata_theme_form_system_theme_settings_alter(&$form, $form_state) {
  $form['dfata_theme_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('govCMS UI Kit settings'),
    '#weight' => 5,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['dfata_theme_options']['dfata_theme_header_title'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Header title'),
    '#default_value' => theme_get_setting('dfata_theme_header_title'),
    '#description'   => t("Text to display beside the site logo in the top header."),
  );

  $form['dfata_theme_options']['dfata_theme_header_logo_alt'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Header logo alternative text'),
    '#default_value' => theme_get_setting('dfata_theme_header_logo_alt'),
    '#description'   => t("Alternative text to assign to the logo in the top header."),
  );

  $form['dfata_theme_options']['dfata_theme_footer_copyright'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Footer copyright'),
    '#default_value' => theme_get_setting('dfata_theme_footer_copyright'),
    '#description'   => t("Text to display beside the sub menu links. Defaults to <em>&copy; [current year]. [Site Name]. All rights reserved.</em>"),
  );

  $form['dfata_theme_options']['dfata_theme_override_image_styles'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Override image styles'),
    '#default_value' => theme_get_setting('dfata_theme_override_image_styles'),
    '#description'   => t("Enable this to override any user-defined image styles with govCMS UI Kit default styles. Disabling this is recommend if modifying site."),
  );
}
