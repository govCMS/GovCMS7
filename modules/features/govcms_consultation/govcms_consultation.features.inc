<?php
/**
 * @file
 * govcms_consultation.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function govcms_consultation_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function govcms_consultation_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function govcms_consultation_node_info() {
  $items = array(
    'consultation' => array(
      'name' => t('Consultation'),
      'base' => 'node_content',
      'description' => t('Consultations are to engage with the general public on a given topic and incorporate the Have Your Say functionality.'),
      'has_title' => '1',
      'title_label' => t('Consultation Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_paragraphs_info().
 */
function govcms_consultation_paragraphs_info() {
  $items = array(
    'issue_documentation' => array(
      'name' => 'File attachment',
      'bundle' => 'issue_documentation',
      'locked' => '1',
    ),
    'twitter_stream' => array(
      'name' => 'Twitter Stream',
      'bundle' => 'twitter_stream',
      'locked' => '1',
    ),
    'update_milestone' => array(
      'name' => 'Update/Milestone',
      'bundle' => 'update_milestone',
      'locked' => '1',
    ),
  );
  return $items;
}
