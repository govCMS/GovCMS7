<?php

/**
 * @file
 * wcag_scheduler.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function wcag_scheduler_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'wcag_scheduler_report';
  $view->description = 'Provides a report for WCAG Scheduler.';
  $view->tag = 'WCAG';
  $view->base_table = 'wcag_scheduler_reports';
  $view->human_name = 'WCAG Scheduler Report';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'WCAG Scheduler Report';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'View WCAG Scheduler';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '3';
  $handler->display->display_options['pager']['options']['tags']['first'] = '';
  $handler->display->display_options['pager']['options']['tags']['last'] = '';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are currently no results.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: WCAG Service Reports: Report ID */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'wcag_scheduler_reports';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['label'] = 'ID';
  /* Field: WCAG Service Reports: URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'wcag_scheduler_reports';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  /* Field: WCAG Service Reports: Last Updated */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'wcag_scheduler_reports';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'medium';
  /* Field: WCAG Service Reports: Major Issues */
  $handler->display->display_options['fields']['major']['id'] = 'major';
  $handler->display->display_options['fields']['major']['table'] = 'wcag_scheduler_reports';
  $handler->display->display_options['fields']['major']['field'] = 'major';
  $handler->display->display_options['fields']['major']['label'] = 'Major';
  /* Field: WCAG Service Reports: Minor Issues */
  $handler->display->display_options['fields']['minor']['id'] = 'minor';
  $handler->display->display_options['fields']['minor']['table'] = 'wcag_scheduler_reports';
  $handler->display->display_options['fields']['minor']['field'] = 'minor';
  $handler->display->display_options['fields']['minor']['label'] = 'Minor';
  /* Field: WCAG Service Reports: Suggestions */
  $handler->display->display_options['fields']['suggestions']['id'] = 'suggestions';
  $handler->display->display_options['fields']['suggestions']['table'] = 'wcag_scheduler_reports';
  $handler->display->display_options['fields']['suggestions']['field'] = 'suggestions';
  /* Sort criterion: WCAG Service Reports: Last Updated */
  $handler->display->display_options['sorts']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['table'] = 'wcag_scheduler_reports';
  $handler->display->display_options['sorts']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['order'] = 'DESC';
  /* Filter criterion: WCAG Service Reports: Filter latest reports */
  $handler->display->display_options['filters']['latest']['id'] = 'latest';
  $handler->display->display_options['filters']['latest']['table'] = 'wcag_scheduler_reports';
  $handler->display->display_options['filters']['latest']['field'] = 'latest';
  $handler->display->display_options['filters']['latest']['value'] = '1';

  /* Display: Results */
  $handler = $view->new_display('page', 'Results', 'wcag_scheduler_results');
  $handler->display->display_options['display_description'] = 'Main results page for wcag_scheduler module.';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/reports/wcag-scheduler';

  $export['wcag_scheduler_report'] = $view;

  return $export;
}
