<?php
/**
 * @file
 * Implementation for Fields and Linkit.
 */

/**
 * Implements hook_linkit_allowed_field_types().
 */
function linkit_linkit_allowed_field_types() {
  $allowed_field_types = array(
    'text',
    'text_long',
    'link_field',
  );
  return $allowed_field_types;
}

/**
 * Get all allowed filed types.
 * @return
 *   An array of allowed filed types.
 */
function linkit_get_allowed_field_types() {
  // Get allowed field and widget types.
  $allowed_field_types = module_invoke_all('linkit_allowed_field_types');
  drupal_alter('linkit_allowed_field_types', $allowed_field_types);
  return $allowed_field_types;
}

/**
 * Implements hook_linkit_allowed_elements().
 */
function linkit_linkit_allowed_field_elements() {
  $allowed_elements = array(
    'textfield',
    'textarea',
    'link_field',
  );
  return $allowed_elements;
}

/**
 * Get all allowed filed elements.
 * @return
 *   An array of allowed filed elements.
 */
function linkit_get_allowed_field_elements() {
  // Get allowed field and widget types.
  $allowed_field_elements = module_invoke_all('linkit_allowed_field_elements');
  drupal_alter('linkit_allowed_field_elements', $allowed_field_elements);
  return $allowed_field_elements;
}

/**
 * Implements hook_linkit_allowed_field_widget_types().
 */
function linkit_linkit_allowed_field_widget_types() {
  $allowed_field_widget_types = array(
    'text_textfield',
    'text_textarea',
    'link_field',
  );
  return $allowed_field_widget_types;
}

/**
 * Get all allowed filed widget types.
 * @return
 *   An array of allowed filed widget types.
 */
function linkit_get_allowed_field_widget_types() {
  // Get allowed field and widget types.
  $allowed_field_widget_types = module_invoke_all('linkit_allowed_field_widget_types');
  drupal_alter('linkit_allowed_field_widget_types', $allowed_field_widget_types);
  return $allowed_field_widget_types;
}

/**
 * Implements hook_form_FIELD_UI_FIELD_EDIT_FORM_alter().
 */
function linkit_form_field_ui_field_edit_form_alter(&$form, &$form_state) {
  $instance = $form['#instance'];

  // Get allowed field types.
  $allowed_field_types = linkit_get_allowed_field_types();
  // Get allowed field widget types.
  $allowed_field_widget_types = linkit_get_allowed_field_widget_types();

  $allowed_field = in_array($form['#field']['type'], $allowed_field_types);
  $allowed_widget = in_array($form['instance']['widget']['type']['#value'], $allowed_field_widget_types);

  // Add the linkit settings to the field instance form if it's valid.
  if ($allowed_field  && $allowed_widget) {

    // Fieldset for Linkit settings on this field instance.
    $form['instance']['settings']['linkit'] = array(
      '#type' => 'fieldset',
      '#title' => t('Linkit field settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );

    // Enable Linkit on this field instance.
    $form['instance']['settings']['linkit']['enable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable Linkit for this field.'),
      '#default_value' => isset($instance['settings']['linkit']['enable'])
        ? $instance['settings']['linkit']['enable'] : 0,
      '#description' => t('Do not use this for CKeditor and TinyMCE fields.'),
    );

    $profiles = linkit_profile_field_load_all();
    $options = array();
    foreach ($profiles as $profile) {
      $options[$profile->name] = $profile->admin_title;
    }

    // Sort the options.
    natsort($options);

    $form['instance']['settings']['linkit']['profile'] = array(
      '#type' => 'select',
      '#title' => t('Profile'),
      '#options' => $options,
      '#empty_option' => t('- Select a profile -'),
      '#default_value' => isset($instance['settings']['linkit']['profile'])
        ? $instance['settings']['linkit']['profile'] : '',
      '#states' => array(
        'invisible' => array(
          'input[name="instance[settings][linkit][enable]"]' => array('checked' => FALSE),
        ),
        'required' => array(
          'input[name="instance[settings][linkit][enable]"]' => array('checked' => TRUE),
        ),
      ),
      '#element_validate' => array('linkit_field_profile_validate'),
    );

    // Enable Linkit on this field instance.
    $form['instance']['settings']['linkit']['button_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Button text that activates linkit modal.'),
      '#default_value' => isset($instance['settings']['linkit']['button_text'])
        ? $instance['settings']['linkit']['button_text'] : 'Search',
    );
  }
}

/**
 * Validation callback; Only validate the profile field if linkit is enabled on
 * the instance.
 *
 * @see linkit_form_field_ui_field_edit_form_alter()
 */
function linkit_field_profile_validate($element, &$form_state, $form) {
  if (isset($form_state['values']['instance']['settings']['linkit']['enable'])
    && $form_state['values']['instance']['settings']['linkit']['enable']) {
    if (empty($element['#value'])) {
      form_error($element, t('You must select an profile.'));
    }
  }
}

/**
 * Process callback.
 */
function linkit_process_field_element($element, &$form_state, &$complete_form) {
  // Only proceed if the field is attached to an entity.
  if (!isset($element['#entity_type'])) {
    return $element;
  }

  $field = field_info_field($element['#field_name']);
  $instance = field_info_instance($element['#entity_type'], $element['#field_name'], $element['#bundle']);

  if (isset($instance['settings']['linkit']['enable']) && $instance['settings']['linkit']['enable']) {

    // Load the profile.
    $profile = linkit_profile_load($instance['settings']['linkit']['profile']);
    // Load the insert plugin for the profile.
    $insert_plugin = linkit_insert_plugin_load($profile->data['insert_plugin']['plugin']);

    // Set the field ID.
    $field_id = $element['#id'];

    // Special treatment for link fields.
    if ($element['#type'] == 'link_field') {
      $field_id = $element['#id'] . '-url';
    }

    $field_js = array(
      'data' => array(
        'linkit' => array(
          'fields' => array(
            $field_id => array(
              'profile' => $instance['settings']['linkit']['profile'],
              'insert_plugin' => $profile->data['insert_plugin']['plugin'],
              'url_method' => $profile->data['insert_plugin']['url_method'],
              // @TODO: Add autocomplete settings.
            ),
          ),
        ),
      ),
      'type' => 'setting',
    );


    // Link fields can have a title field.
    if ($element['#type'] == 'link_field') {
      if (isset($instance['settings']['title']) && in_array($instance['settings']['title'], array('optional', 'required'))) {
        $field_js['data']['linkit']['fields'][$field_id]['title_field'] = $element['#id'] . '-title';
      }
    }

    // Attach js files and settings Linkit needs.
    $element['#attached']['library'][] = array('linkit', 'base');
    $element['#attached']['library'][] = array('linkit', 'field');
    $element['#attached']['js'][] = $insert_plugin['javascript'];
    $element['#attached']['js'][] = $field_js;

    $button_text = !empty($instance['settings']['linkit']['button_text']) ? $instance['settings']['linkit']['button_text'] : t('Search');
    // Add Linkit dialog button to the element suffix.
    $element['#field_suffix'] = '<a class="button linkit-field-button linkit-field-' . $field_id . '" href="#">' . $button_text . '</a>';
  }

  return $element;
}