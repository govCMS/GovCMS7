<?php
/**
 * @file
 * Integrates Features for Custom Contextual Links.
 */

/**
 * Implements hook_features_export_options().
 */
function ccl_features_export_options() {
  $presets = array();
  foreach (ccl_get_presets() as $preset) {
    $presets[$preset->title] = $preset->title;
  }
  return $presets;
}

/**
 * Implements hook_features_export().
 */
function ccl_features_export($data, &$export, $module_name = '') {
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['ccl'] = 'ccl';

  foreach (ccl_get_presets() as $preset) {
    if (in_array($preset->title, $data)) {

      // Make the submodule required.
      // A 's' needs to be added to the type for the plural module names.
      if ($preset->type != 'node') {
        $export['dependencies']['ccl_' . $preset->type . 's'] = 'ccl_' . $preset->type . 's';
      }

      $export['features']['ccl'][$preset->title] = $preset->title;
    }
  }

  return $export;
}

/**
 * Implements hook_features_export_render().
 */
function ccl_features_export_render($module, $data) {
  $code = array();
  $presets = ccl_get_presets();

  foreach ($data as $title) {
    foreach ($presets as $preset) {
      if ($preset->title == $title) {
        // We don't want to break the entity cache, so we need to clone the
        // presetting before unsetting the id.
        $preset = clone $preset;
        unset($preset->clid);
        $code[$title] = $preset;
      }
    }
  }
  $code = "  return " . features_var_export($code, '  ') . ";";
  return array('ccl_features_preset' => $code);
}

/**
 * Implements hook_features_revert().
 */
function ccl_features_revert($module) {
  ccl_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 *
 * Rebuilds Custom Contextual Links from code defaults.
 */
function ccl_features_rebuild($module) {
  $presets = module_invoke($module, 'ccl_features_preset');
  foreach ($presets as $key => $preset) {
    $preset = (object) $preset;

    $current_record = current(ccl_get_presets($preset->title));
    if (!empty($current_record)) {
      $preset->clid = $current_record->clid;
      drupal_write_record('ccl', $preset, 'clid');
    }
    else {
      drupal_write_record('ccl', $preset);
    }
  }
}
