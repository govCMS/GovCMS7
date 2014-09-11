<?php

/**
 * @file
 * Rules hooks implementation.
 */

/**
 * Implements hook_rules_event_info().
 */
function draggableviews_rules_event_info() {
  $events = array();

  $events['draggableviews_rules_event_sorted'] = array(
    'label' => t('A view has been sorted'),
    'group' => t('DraggableViews'),
    'variables' => array(
      'view_name' => array(
        'type' => 'text',
        'label' => t('view name'),
      ),
      'display_name' => array(
        'type' => 'text',
        'label' => t('view current display name'),
      ),
    ),
  );

  return $events;
}
