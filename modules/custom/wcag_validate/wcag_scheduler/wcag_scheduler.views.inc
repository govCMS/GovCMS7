<?php

/**
 * @file
 * Views data functionality to expose reports.
 */

/**
 * Implements hook_views_data().
 */
function wcag_scheduler_views_data() {
  // Define the wcag service reports table.
  $data['wcag_scheduler_reports']['table']['group'] = t('WCAG Service Reports');

  // Advertise this table as a possible base table.
  $data['wcag_scheduler_reports']['table']['base'] = array(
    'field' => 'rid',
    'title' => t('WCAG Service Reports'),
    'weight' => -10,
    'defaults' => array(
      'field' => 'url',
    ),
  );

  // Expose the column rid.
  $data['wcag_scheduler_reports']['rid'] = array(
    'title' => t('Report ID'),
    'help' => t('The ID of the report that was conducted.'),
    'field' => array(
      'handler' => 'wcag_scheduler_handler_field_url',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expose the field url.
  $data['wcag_scheduler_reports']['url'] = array(
    'title' => t('URL'),
    'help' => t('The URL of the page that was reported.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expose the column last_updated.
  $data['wcag_scheduler_reports']['last_updated'] = array(
    'title' => t('Last Updated'),
    'help' => t('The date in which the page was last checked.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );

  // Expose the field major.
  $data['wcag_scheduler_reports']['major'] = array(
    'title' => t('Major Issues'),
    'help' => t('The major issues found on this page.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expose the field minor.
  $data['wcag_scheduler_reports']['minor'] = array(
    'title' => t('Minor Issues'),
    'help' => t('The minor issues found on this page.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expose the field major.
  $data['wcag_scheduler_reports']['suggestions'] = array(
    'title' => t('Suggestions'),
    'help' => t('The suggestions found for this page.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Filter to only show the latest records.
  $data['wcag_scheduler_reports']['latest'] = array(
    'title' => t('Filter latest reports'),
    'help' => t('Filter latest reports in results.'),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
    ),
  );

  return $data;
}
