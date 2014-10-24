<?php

/**
 * @file
 * API documentation for the Event Log module.
 */

/**
 * Returns event log handlers.
 * @return array
 *   An associative array, keyed by event type, and valued by handler info:
 *   - {string} title
 *     The title that describes the events logged by this handler.
 *   - {array} form_ids
 *     This handler's 'form_submit_callback' callback will be notified when a
 *     form is submitted that has an id as specified in this array. Optional.
 *   - {array} form_ids_regexp
 *     The same as form_ids, but instead of identical matches regular
 *     expressions can be specified.
 *   - {string} form_submit_callback
 *     Callback that's called when a form is submitted with a form id as
 *     specified in form_ids. The callback function profile:
 *
 *     Returns the event to be inserted in the event log, if any.
 * @param {array} $form
 * @param {array} $form_state
 * @param {string} $form_id
 * @return {mixed}
 *       Either a log record or NULL if no event should be added. The event type
 *       is automatically added.
 *
 *     Optional. Notice that events can also be manually created using the
 *     event_log_save function.
 *   - {array} relationships
 *     An array with relationships. Every relationship is defined as follows:
 *     - {string} table
 *       Example: node.
 *     - {string} field
 *       Example: nid.
 *     - {array} operations
 *       NULL for all operations.
 *     - {Boolean} numeric
 *       A numeric key or not?
 */
function hook_event_log_handlers() {
  $handlers = array();
  $handlers['my_contact_form'] = array(
    'form_ids' => array('contact_form'),
    'form_submit_callback' => 'contact_form_log_event',
  );
  return $handlers;
}

/**
 * Allows modules to alter event log handlers.
 * @param array $handlers
 *   An array with event log handlers.
 */
function hook_event_log_handlers_alter(&$handlers) {
  // Overrule the node form submit callback handler.
  $handlers['node']['form_submit_callback'] = 'my_own_handler';
}
