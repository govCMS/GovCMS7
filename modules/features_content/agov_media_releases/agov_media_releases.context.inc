<?php
/**
 * @file
 * agov_media_releases.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function agov_media_releases_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'agov_media_releases';
  $context->description = 'Media Releases';
  $context->tag = 'aGov';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'media_release' => 'media_release',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => 'media-releases',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Media Releases');
  t('aGov');
  $export['agov_media_releases'] = $context;

  return $export;
}
