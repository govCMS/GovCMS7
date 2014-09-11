<?php
/**
 * @file
 * Contains functions only needed for drush integration.
 */

/**
 * Implementation of hook_drush_command().
 */
function zen_drush_command() {
  $items = array();

  $items['zen'] = array(
    'description' => 'Create a theme using Zen.',
    'arguments' => array(
      'name'         => 'A name for your theme.',
      'machine_name' => '[optional] A machine-readable name for your theme.',
    ),
    'options' => array(
      'name'         => 'A name for your theme.',
      'machine-name' => '[a-z, 0-9] A machine-readable name for your theme.',
      'path'         => 'The path where your theme will be created. Defaults to: sites/all/themes',
      'description'  => 'A description of your theme.',
      'without-rtl'  => 'Remove all RTL stylesheets.',
    ),
    'examples' => array(
      'drush zen "My theme name"' => 'Create a sub-theme, using the default options.',
      'drush zen "My theme name" my_theme' => 'Create a sub-theme with a specific machine name.',
      'drush zen "My theme" --without-rtl --path=sites/default/themes' => 'Create a sub-theme in the specified directory without RTL stylesheets.',
    ),
  );

  return $items;
}

/**
 * Create a Zen sub-theme using the starter kit.
 */
function drush_zen($name = NULL, $machine_name = NULL) {
  // Determine the theme name.
  if (!isset($name)) {
    $name = drush_get_option('name');
  }

  // Determine the machine name.
  if (!isset($machine_name)) {
    $machine_name = drush_get_option('machine-name');
  }
  if (!$machine_name) {
    $machine_name = $name;
  }
  $machine_name = str_replace(' ', '_', strtolower($machine_name));
  $search = array(
    '/[^a-z0-9_]/', // Remove characters not valid in function names.
    '/^[^a-z]+/',   // Functions must begin with an alpha character.
  );
  $machine_name = preg_replace($search, '', $machine_name);

  // Determine the path to the new subtheme.
  $subtheme_path = 'sites/all/themes';
  if ($path = drush_get_option('path')) {
    $subtheme_path = drush_trim_path($path);
  }
  $subtheme_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . $subtheme_path . '/' . $machine_name);

  // Make a fresh copy of the original starter kit.
  $starter_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('theme', 'zen') . '/STARTERKIT');
  if (!is_dir(dirname($subtheme_path))) {
    drush_die(dt('The directory "!directory" was not found.', array('!directory' => dirname($subtheme_path))));
  }
  drush_op('drush_copy_dir', $starter_path, $subtheme_path);

  // Rename the .info file.
  $subtheme_info_file = $subtheme_path . '/' . $machine_name . '.info';
  drush_op('rename', drush_normalize_path($subtheme_path . '/STARTERKIT.info.txt'), drush_normalize_path($subtheme_info_file));

  // Alter the contents of the .info file based on the command options.
  $alterations = array(
    '= Zen Sub-theme Starter Kit' => '= ' . $name,
  );
  if ($description = drush_get_option('description')) {
    $alterations['Read the <a href="https://drupal.org/node/873778">online docs</a> or the included README.txt on how to create a theme with Zen.'] = $description;
  }
  drush_op('zen_file_str_replace', $subtheme_info_file, array_keys($alterations), $alterations);

  // Replace all occurrences of 'STARTERKIT' with the machine name of our sub theme.
  drush_op('zen_file_str_replace', $subtheme_path . '/theme-settings.php', 'STARTERKIT', $machine_name);
  drush_op('zen_file_str_replace', $subtheme_path . '/template.php', 'STARTERKIT', $machine_name);

  // Remove all RTL stylesheets.
  if ($without_rtl = drush_get_option('without-rtl')) {
    foreach (array('layouts/_fixed', 'layouts/_responsive', 'components/_misc', '_normalize', 'styles') as $file) {
      // Move any sub-directory into a separate variable.
      list($sub_dir, $css_file) = explode('/', $file . '/');
      if (!$css_file) {
        $css_file = $sub_dir;
        $sub_dir = '';
      }
      else {
        $sub_dir .= '/';
      }
      // Remove the RTL css file.
      $css_file = $sub_dir . (($css_file[0] == '_') ? substr($css_file, 1) : $css_file);
      drush_op('unlink', drush_normalize_path($subtheme_path . '/css/' . $css_file . '-rtl.css'));
      drush_op('zen_file_str_replace', $subtheme_path . '/css/' . $css_file . '.css', ' /* LTR */', '');
      // Remove the RTL sass file.
      drush_op('unlink', drush_normalize_path($subtheme_path . '/sass/' . $file . '-rtl.scss'));
      drush_op('zen_file_str_replace', $subtheme_path . '/sass/' . $file . '.scss', ' /* LTR */', '');
    }
  }

  // Notify user of the newly created theme.
  drush_print(dt('Starter kit for "!name" created in: !path', array(
    '!name' => $name,
    '!path' => $subtheme_path,
  )));
}

/**
 * Replace strings in a file.
 */
function zen_file_str_replace($file_path, $find, $replace) {
  $file_path = drush_normalize_path($file_path);
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}
