<?php

/**
 * @file
 * Provides drush commands for the acsf_variables module.
 */

/**
 * Implements hook_drush_command().
 */
function acsf_variables_drush_command() {
  return array(
    'acsf-vget' => array(
      'description' => dt('Retrieves a named ACSF variable.'),
      'arguments' => array(
        'name' => dt('The name of the variable to retrieve.'),
      ),
      'options' => array(
        'format' => array(
          'description' => dt('Format to output the object. Use "print_r" for print_r (default), "export" for var_export, and "json" for JSON.'),
          'example-value' => 'json',
        ),
        'exact' => dt('Only retrieve the exact variable name specified.'),
      ),
    ),
    'acsf-vset' => array(
      'description' => dt('Sets a named ACSF variable with an optional group.'),
      'arguments' => array(
        'name' => dt('The name of the variable to set.'),
        'value' => dt('The value of the variable to set.'),
      ),
      'options' => array(
        'group' => dt('An optional group name for the variable.'),
      ),
    ),
    'acsf-vget-group' => array(
      'description' => dt('Retrieves a group of variables.'),
      'arguments' => array(
        'group' => dt('The group name of the variable to retrieve.'),
      ),
      'options' => array(
        'format' => array(
          'description' => dt('Format to output the object. Use "print_r" for print_r (default), "export" for var_export, and "json" for JSON.'),
          'example-value' => 'json',
        ),
      ),
    ),
    'acsf-vdel' => array(
      'description' => dt('Deletes a named variable.'),
      'arguments' => array(
        'name' => dt('The name of the variable to delete.'),
      ),
    ),
    'acsf-info' => array(
      'description' => dt('Retrieves info about a site.'),
    ),
  );
}

/**
 * Command callback. Retrieves a named ACSF variable.
 */
function drush_acsf_variables_acsf_vget($name) {
  if (!module_exists('acsf_variables')) {
    return drush_set_error(dt('The acsf_variables module must be enabled.'));
  }

  if (empty($name)) {
    return drush_set_error(dt('You must provide the name of the variable to retrieve as the first argument.'));
  }

  $format = drush_get_option('format', 'print_r');
  $exact = drush_get_option('exact');
  $variables = array();

  if ($exact) {
    $variables[] = $name;
  }
  else {
    $select = db_select('acsf_variables', 'v')
      ->fields('v', array('name'))
      ->condition('name', '%' . $name . '%', 'LIKE')
      ->execute();

    while ($value = $select->fetchField()) {
      $variables[] = $value;
    }
  }

  if (!empty($variables)) {
    foreach ($variables as $name) {
      if ($variable = acsf_vget($name)) {
        if ($format == 'json') {
          $value = drush_format($variable, NULL, $format);
        }
        else {
          $value = dt('@name: !value', array(
            '@name' => $name,
            '!value' => drush_format($variable, NULL, $format),
          ));
        }
        drush_print($value);
      }
    }
  }
  else {
    return drush_set_error(dt('@name not found.', array('@name' => $name)));
  }
}

/**
 * Command callback. Sets a named variable with an optional group.
 */
function drush_acsf_variables_acsf_vset($name, $value) {
  if (!module_exists('acsf_variables')) {
    return drush_set_error(dt('The acsf_variables module must be enabled.'));
  }

  if (empty($name)) {
    return drush_set_error(dt('You must provide the name of the variable to set as the first argument.'));
  }
  if (empty($value)) {
    return drush_set_error(dt('You must provide the value of the variable to set as the second argument.'));
  }

  if (acsf_vset($name, $value, drush_get_option('group'))) {
    drush_print(dt('@name was set to !value', array('@name' => $name, '!value' => $value)));
  }
  else {
    return drush_set_error(dt('The @name variable count not be set.'));
  }
}

/**
 * Command callback. Retrieves a group of variables.
 */
function drush_acsf_variables_acsf_vget_group($group) {
  if (!module_exists('acsf_variables')) {
    return drush_set_error(dt('The acsf_variables module must be enabled.'));
  }

  if (empty($group)) {
    return drush_set_error(dt('You must provide the group name of the variables to retrieve as the first argument.'));
  }

  $format = drush_get_option('format', 'print_r');

  if ($data = acsf_vget_group($group)) {
    if ($format == 'json') {
      $value = drush_format($data, NULL, $format);
    }
    else {
      $value = dt('@group: !value', array(
        '@group' => $group,
        '!value' => drush_format($data, NULL, $format),
      ));
    }
    drush_print($value);
  }
  else {
    return drush_set_error(dt('@group group not found.', array('@group' => $group)));
  }
}

/**
 * Command callback. Deletes a named variable.
 */
function drush_acsf_variables_acsf_vdel($name) {
  if (!module_exists('acsf_variables')) {
    return drush_set_error(dt('The acsf_variables module must be enabled.'));
  }

  if (empty($name)) {
    return drush_set_error(dt('You must provide the name of the variable to set as the first argument.'));
  }

  if ($variable = acsf_vget($name)) {
    if (acsf_vdel($name)) {
      drush_print(dt('@name was deleted.', array('@name' => $name)));
    }
    else {
      return drush_set_error(dt('Unable to delete the @name variable.', array('@name' => $name)));
    }
  }
  else {
    return drush_set_error(dt('@name not found.', array('@name' => $name)));
  }
}

/**
 * Command callback. Prints information about the site.
 */
function drush_acsf_variables_acsf_info() {
  drush_print(drush_format(acsf_vget('acsf_site_info'), NULL, 'print_r'));
}
