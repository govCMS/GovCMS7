<?php

/**
 * @file
 * Menu implementations for the contact feature.
 */

/**
 * Menu callback for the printable config page.
 */
function agov_contact_printable() {
  $form = array();

  // Upload a file for printing.
  $form['agov_contact_printable_upload'] = array(
    '#type' => 'managed_file',
    '#title' => t('Provide a printable version of the contact form.'),
    '#description' => t('This file provides a printable version of the contact form.
                       It is then displayed on the site contact form.'),
    '#upload_location' => 'public://contact/',
    '#default_value' => _agov_contact_get_fid(),
    '#upload_validators' => array(
      'file_validate_extensions' => array('pdf doc docx txt rtf'),
    ),
  );

  // Setup our custom submit.
  $form['#submit'][] = 'agov_contact_printable_submit';
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for agov_contact_printable.
 */
function agov_contact_printable_submit($form, &$form_state) {
  $field = 'agov_contact_printable_upload';

  if (empty($form_state['values'][$field])) {
    variable_del($field);
    return;
  };

  // Load the file, set it to perminant and save.
  $file = file_load($form_state['values'][$field]);
  $file->status = FILE_STATUS_PERMANENT;
  file_save($file);

  // Save the file fid for form use later.
  variable_set($field, $file->fid);
}
