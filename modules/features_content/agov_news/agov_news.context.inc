<?php
/**
 * @file
 * agov_news.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function agov_news_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'agov_news';
  $context->description = 'News';
  $context->tag = 'aGov';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'news_article' => 'news_article',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'news-archive',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('News');
  t('aGov');
  $export['agov_news'] = $context;

  return $export;
}
