<?php

/**
 * @file
 * Views hook implementations.
 */

/**
 * Implements hook_views_handlers().
 */
function node_freshness_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'node_freshness') . '/views/includes',
    ),
    'handlers' => array(
      'node_freshness_handler_filter' => array(
        'parent' => 'views_handler_filter',
      ),
    ),
  );
}
