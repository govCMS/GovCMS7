<?php
/**
 * @file
 * agov_events.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function agov_events_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'agov_events';
  $context->description = 'Events';
  $context->tag = 'aGov';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'event' => 'event',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'events',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Events');
  t('aGov');
  $export['agov_events'] = $context;

  return $export;
}
