<?php

/**
 * @file
 * Holds the options for drush command to be picked up automatically.
 */

$options['structure-tables'] = array(
  'acsf_duplicate' => array(
    'accesslog',
    'aggregator_item',
    'apachesolr_index_entities*',
    'apachesolr_search_node',
    'cache',
    'cache_*',
    'captcha_sessions',
    'ctools_css_cache',
    'ctools_object_cache',
    'flood',
    'history',
    'masquerade',
    'mollom',
    'migrate_*',
    'realname',
    'search_api_item',
    'search_dataset',
    'search_index',
    'search_node_links',
    'search_total',
    'sessions',
    'sparql_store_*',
    'themebuilder_session',
    'themebuilder_undo',
    'views_content_cache',
    'watchdog',
    'xmlsitemap',
  ),
);
