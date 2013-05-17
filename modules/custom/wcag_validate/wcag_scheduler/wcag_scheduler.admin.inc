<?php

/**
 * @file
 * Provides admin callbacks for wcag_scheduler.
 */

/**
 * Configuration admin page callback.
 */
function wcag_scheduler_config_form() {
  $form = array();

  // Frequency to check site.
  $form['wcag_scheduler_frequency'] = array(
    '#type' => 'select',
    '#title' => 'Frequency',
    '#options' => array(
      86400   => t('Nightly'),
      604800  => t('Weekly'),
      1209600 => t('Fortnightly'),
    ),
    '#default_value' => variable_get('wcag_scheduler_frequency', WCAG_SCHEDULER_FREQUENCY),
  );

  // Timeframe for execution.
  $form['wcag_scheduler_timeframe'] = array(
    '#type' => 'fieldset',
    '#title' => t('Timeframe'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $timeframe_start = variable_get('wcag_scheduler_zulu_start', WCAG_SCHEDULER_ZULU_START);
  $form['wcag_scheduler_timeframe']['wcag_scheduler_zulu_start'] = array(
    '#type' => 'textfield',
    '#title' => t('Start'),
    '#maxlength' => '4',
    '#size' => '4',
    '#element_validate' => array(
      'element_validate_integer_positive',
      'wcag_scheduler_validate_zulu',
    ),
    '#default_value' => str_pad($timeframe_start, 4, "0", STR_PAD_LEFT),
  );

  $timeframe_finish = variable_get('wcag_scheduler_zulu_finish', WCAG_SCHEDULER_ZULU_FINISH);
  $form['wcag_scheduler_timeframe']['wcag_scheduler_zulu_finish'] = array(
    '#type' => 'textfield',
    '#title' => t('Finish'),
    '#maxlength' => '4',
    '#size' => '4',
    '#element_validate' => array(
      'element_validate_integer_positive',
      'wcag_scheduler_validate_zulu',
    ),
    '#default_value' => str_pad($timeframe_finish, 4, "0", STR_PAD_LEFT),
  );

  // Add a handler to make sure the start isn't greater than the finish.
  $form['#validate'][] = 'wcag_validate_zulu_difference';

  // Reset the last run variable to ensure the query gets run on time.
  $form['#submit'][] = 'wcag_scheduler_reset_last_run';

  // Add a resend button to the form.
  $form['actions']['resend'] = array(
    '#type' => 'submit',
    '#value' => 'Resend Request',
    '#submit' => array('wcag_scheduler_resend'),
  );

  return system_settings_form($form);
}

/**
 * Ensures that we have a zulu clock integer less than 2400.
 */
function wcag_scheduler_validate_zulu($element, &$form_state) {
  $value = $element['#value'];
  if ($value > 2400) {
    form_error($element, t('%name must be in 24 hour format (between 0001 and 2400).', array('%name' => $element['#title'])));
  }
}

/**
 * Enforces start time isn't greater than the finish.
 */
function wcag_validate_zulu_difference(&$form, &$form_state) {
  $values = $form_state['values'];
  if ($values['wcag_scheduler_zulu_start'] > $values['wcag_scheduler_zulu_finish']) {
    form_error($form['wcag_scheduler_timeframe'], t('Finish time must be greater than the start.', array('%name' => $form['wcag_scheduler_timeframe']['#title'])));
  }
}

/**
 * Resets the last run variable to ensure the query gets run on time.
 */
function wcag_scheduler_reset_last_run() {
  variable_set('wcag_scheduler_last_run', 0);
}

/**
 * Resends the request to the backend service.
 */
function wcag_scheduler_resend() {
  _wcag_scheduler_send_request();

  // Let them know the request was sent.
  drupal_set_message(t('A new request has been sent to the backend service.'));
}
