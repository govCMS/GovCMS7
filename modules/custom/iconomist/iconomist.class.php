<?php

namespace Drupal\Iconomist;

/**
 * @file
 * Iconomist Class.
 *
 * Implements the Iconomist functionality in a way that allows for unit testing.
 */

// For _system_theme_settings_validate_path, which isn't otherwise defined.
require_once DRUPAL_ROOT . '/modules/system/system.admin.inc';

/**
 * Iconomist class.
 *
 * The substance of code for the Iconomist module, moved into a class so as to
 * be nice and testable.
 */
class Iconomist {

  /**
   * Body of the theme_settings_alter hook.
   *
   * @param array &$form
   *   The render array for the form.
   * @param array &$form_state
   *   The current form state.
   */
  public static function themeSettingsAlter(array &$form, array &$form_state) {
    $theme = empty($form_state['build_info']['args']) ? NULL : $form_state['build_info']['args'][0];
    if (!isset($form_state['triggering_element'])) {
      // Load existing settings.
      $form_state['values']['iconomist_icons'] = theme_get_setting('iconomist_icons', $theme) ?: array();
      // Set the number of icons.
      $form_state['storage']['iconomist_num_icons'] = count($form_state['values']['iconomist_icons']);
      // Store path/usage_id in storage.
      foreach ($form_state['values']['iconomist_icons'] as $delta => $icon) {
        $form_state['storage']['iconomist_icons'][$delta] = array(
          'path' => $icon['path'],
          'usage_id' => $icon['usage_id'],
        );
      }
    }

    // Default number of icons.
    if (!isset($form_state['storage']['iconomist_num_icons'])) {
      $form_state['storage']['iconomist_num_icons'] = 0;
    }

    // Always show at least one icon on the form.
    $form_state['storage']['iconomist_num_icons'] = max($form_state['storage']['iconomist_num_icons'], 0);

    // Display toggles.
    $default_value = theme_get_setting('toggle_iconomist', $theme);
    $form['theme_settings']['toggle_iconomist'] = array(
      '#type' => 'checkbox',
      '#title' => t('Iconomist Icons'),
      '#default_value' =>  is_null($default_value) ? TRUE : $default_value,
    );

    // Iconomist fieldset.
    $form['iconomist'] = array(
      '#type' => 'fieldset',
      '#title' => t('Iconomist settings'),
      '#description' => t('Additional icons to link to in HTML head.'),
    );

    // The link rel types.
    $relationships = array(
      'apple-touch-icon' => t('Apple Touch'),
      'apple-touch-icon-precomposed' => t('Apple Touch (Precomposed)'),
      'icon' => t('Icon'),
    );

    // Container for ajax commands.
    $form['iconomist']['iconomist_icons'] = array(
      '#type' => 'container',
      '#tree' => TRUE,
      '#prefix' => '<div id="iconomist-icons">',
      '#suffix' => '</div>',
    );

    for ($delta = 0; $delta < $form_state['storage']['iconomist_num_icons']; $delta++) {
      $form['iconomist']['iconomist_icons'][$delta] = array(
        '#type' => 'fieldset',
        '#title' => t('Icon'),
        '#element_validate' => ['_iconomist_icons_validate'],
      );

      if (isset($form_state['values']['iconomist_icons'][$delta])) {
        $icon = $form_state['values']['iconomist_icons'][$delta];
      }
      else {
        $icon = array();
      }

      if (isset($form_state['storage']['iconomist_icons'][$delta])) {
        $storage = $form_state['storage']['iconomist_icons'][$delta];
        $icon['usage_id'] = $storage['usage_id'];
      }

      $form['iconomist']['iconomist_icons'][$delta]['usage_id'] = array(
        '#type' => 'value',
        '#value' => isset($icon['usage_id']) ? $icon['usage_id'] : '',
      );

      $form['iconomist']['iconomist_icons'][$delta]['upload'] = array(
        '#type' => 'managed_file',
        '#title' => t('Upload icon image'),
        '#description' => t("If you don't have direct file access to the server, use this field to upload your touch icon."),
        '#upload_validators' => ['file_validate_is_image'],
        '#upload_location' => 'public://iconomist',
      );

      $form['iconomist']['iconomist_icons'][$delta]['path'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($icon['path']) ? check_plain($icon['path']) : '',
        '#title' => t('Path to custom icon'),
        '#description' => t('The path to the file you would like to use as your icon.'),
      );

      $form['iconomist']['iconomist_icons'][$delta]['width'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($icon['width']) ? check_plain($icon['width']) : '',
        '#title' => t('Icon width'),
        '#description' => t('Width of icon in pixels.'),
        '#element_validate' => ['element_validate_integer_positive'],
        '#size' => 10,
      );

      $form['iconomist']['iconomist_icons'][$delta]['height'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($icon['height']) ? check_plain($icon['height']) : '',
        '#title' => t('Icon height'),
        '#description' => t('Height of icon in pixels.'),
        '#element_validate' => ['element_validate_integer_positive'],
        '#size' => 10,
      );

      $form['iconomist']['iconomist_icons'][$delta]['rel'] = array(
        '#type' => 'radios',
        '#options' => $relationships,
        '#default_value' => isset($icon['rel']) ? $icon['rel'] : 'icon',
        '#title' => t('Icon relationship'),
        '#description' => t('Relationship type of icon.'),
      );

      $form['iconomist']['iconomist_icons'][$delta]['remove_icon'] = array(
        '#type' => 'submit',
        '#name' => 'remove_icon_' . $delta,
        '#submit' => ['_iconomist_remove_icon'],
        '#value' => t('Remove icon'),
        '#ajax' => array(
          'callback' => '_iconomist_ajax_callback',
          'wrapper' => 'iconomist-icons',
        ),
        '#limit_validation_errors' => array(),
      );
    }

    $form['iconomist']['add_icon'] = array(
      '#type' => 'submit',
      '#name' => 'add_icon',
      '#submit' => ['_iconomist_add_icon'],
      '#value' => t('Add icon'),
      '#ajax' => array(
        'callback' => '_iconomist_ajax_callback',
        'wrapper' => 'iconomist-icons',
      ),
      '#limit_validation_errors' => array(),
    );

    // Add custom submit handler to run first.
    array_unshift($form['#submit'], '_iconomist_settings_submit');
  }

  /**
   * Add a new (blank) icon form.
   *
   * @param array $form
   *   The $form array.
   * @param array &$form_state
   *   The form state.
   */
  public static function addIcon(array $form, array &$form_state) {
    $form_state['rebuild'] = TRUE;
    $form_state['storage']['iconomist_num_icons']++;
  }

  /**
   * Remove an icon form.
   *
   * @param array $form
   *   The $form array.
   * @param array $form_state
   *   The form state.
   */
  public static function removeIcon(array $form, array &$form_state) {
    $form_state['rebuild'] = TRUE;
    $trigger_element_name = $form_state['triggering_element']['#name'];
    $delta = (int) substr($trigger_element_name, strlen('remove_icon_'));

    // Remove icon from form.
    unset($form_state['input']['iconomist_icons'][$delta]);
    unset($form_state['values']['iconomist_icons'][$delta]);
    unset($form_state['storage']['iconomist_icons'][$delta]);

    // Rebuild array index keys.
    $form_state['input']['iconomist_icons'] = array_values($form_state['input']['iconomist_icons']);
    if (isset($form_state['values']['iconomist_icons'])) {
      $form_state['values']['iconomist_icons'] = array_values($form_state['values']['iconomist_icons']);
    }
    if (isset($form_state['storage']['iconomist_icons'])) {
      $form_state['storage']['iconomist_icons'] = array_values($form_state['storage']['iconomist_icons']);
    }

    // Reduce number of icons in form.
    $form_state['storage']['iconomist_num_icons']--;
  }

  /**
   * Ajax callback.
   *
   * @param array $form
   *   Render array for the whole form.
   *
   * @return array
   *   Render array for the portion of the form to be replaced.
   */
  public static function ajaxCallback(array $form) {
    return $form['iconomist']['iconomist_icons'];
  }

  /**
   * Helper function to get managed file object.
   *
   * @param string $uri
   *   File URI.
   *
   * @return bool|mixed
   *   File object if managed otherwise FALSE.
   */
  public static function getManagedFile($uri) {
    $fid = db_query('SELECT fid FROM {file_managed} WHERE uri = :uri', [':uri' => $uri])->fetchField();
    if (!empty($fid)) {
      $file_object = file_load($fid);
      return $file_object;
    }
    return FALSE;
  }

  /**
   * Helper function to get usage id.
   *
   * @return int
   *   Available usage id.
   */
  public static function getUseId() {
    $usage_id = variable_get('iconomist_counter', 1);
    variable_set('iconomist_counter', $usage_id + 1);
    return $usage_id;
  }

  /**
   * Validate custom plain touch icon settings.
   *
   * @param array $element
   *   The element being validated.
   * @param array $form_state
   *   The form state.
   */
  public static function validate(array $element, array &$form_state) {
    $limit_validation = $form_state['triggering_element']['#limit_validation_errors'];
    if (is_array($limit_validation) && empty($limit_validation)) {
      // Skip validation.
      return;
    }

    $delta = $element['#parents'][1];
    $icon = &$form_state['values']['iconomist_icons'][$delta];
    if (isset($form_state['storage']['iconomist_icons'][$delta])) {
      $storage = &$form_state['storage']['iconomist_icons'][$delta];
    }
    else {
      $storage = NULL;
    }
    $path = FALSE;

    if ($icon['path']) {
      $path = _system_theme_settings_validate_path($icon['path']);
      if (!$path) {
        form_error($element['path'], t('Path is invalid'));
        return;
      }
      $file = static::getManagedFile($path);
      if ($file) {
        $icon['fid'] = $file->fid;
      }
    }

    if ($icon['upload']) {
      $file = file_load($icon['upload']);
      if ($file) {
        $path = $file->uri;
        $icon['fid'] = $file->fid;
      }
      else {
        form_error($element['upload'], t('Upload failed'));
        return;
      }
    }

    // Remove upload field.
    unset($icon['upload']);

    if (!$path) {
      // Remove empty icon.
      unset($form_state['values']['iconomist_icons'][$delta]);
      return;
    }

    // Store path of icon.
    $icon['path'] = $path;

    // If path has changed then need to remove file usage.
    if (isset($storage) && $storage['path'] !== $path) {
      $storage['usage_id'] = NULL;
      unset($icon['usage_id']);
    }
  }

  /**
   * Custom theme settings submit handler.
   *
   * @param array $form
   *   The $form array.
   * @param array $form_state
   *   The form state.
   */
  public static function settingsSubmit(array $form, array &$form_state) {
    $theme = empty($form_state['build_info']['args']) ? NULL : $form_state['build_info']['args'][0];
    $existing_icons = theme_get_setting('iconomist_icons', $theme) ?: array();
    $existing_file_usages = array();
    foreach ($existing_icons as $icon) {
      if (!empty($icon['usage_id'])) {
        $existing_file_usages[$icon['usage_id']] = $icon['fid'];
      }
    }

    $icons = &$form_state['values']['iconomist_icons'];
    $file_usages = array();
    foreach ($icons as $icon) {
      if (!empty($icon['usage_id'])) {
        $file_usages[$icon['usage_id']] = $icon['fid'];
      }
    }

    // Remove all usages no longer being used.
    $removed_usages = array_diff_key($existing_file_usages, $file_usages);
    foreach ($removed_usages as $usage_id => $fid) {
      $file = file_load($fid);
      if ($file) {
        file_usage_delete($file, 'iconomist', 'theme', $usage_id);
      }
    }

    // Add new file usages.
    foreach ($icons as &$icon) {
      if (isset($icon['fid']) && empty($icon['usage_id'])) {
        $file = file_load($icon['fid']);
        if ($file) {
          // Mark file as permanent.
          $file->status = FILE_STATUS_PERMANENT;
          file_save($file);
          // Add file usage.
          $icon['usage_id'] = static::getUseId();
          file_usage_add($file, 'iconomist', 'theme', $icon['usage_id']);
        }
      }
    }
  }

  /**
   * Implements hook_preprocess_html().
   */
  public static function preprocessHtml(&$vars) {
    $toggle = theme_get_setting('toggle_iconomist');
    $icons = theme_get_setting('iconomist_icons') ?: array();
    // If $toggle hasn't been set, it will be NULL. Treat as ticked in that case.
    if ($toggle === FALSE || empty($icons)) {
      // Do nothing if iconomist is toggled off or no icons.
      return;
    }
    foreach ($icons as $icon) {
      $icon_path = file_create_url($icon['path']);
      $attributes = array(
        'rel' => $icon['rel'],
        'href' => $icon_path,
        'type' => file_get_mimetype($icon_path),
      );
      if (!empty($icon['width']) && !empty($icon['height'])) {
        $attributes['sizes'] = $icon['width'] . 'x' . $icon['height'];
      }
      drupal_add_html_head_link($attributes);
    }
  }

}
