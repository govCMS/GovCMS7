<?php
/**
 * @file
 * govcms_consultation.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function govcms_consultation_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|consultation|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'consultation';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'formal_submission_form' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'progress_bar' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"date_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:5:{s:11:"format_type";s:4:"long";s:15:"multiple_number";s:0:"";s:13:"multiple_from";s:0:"";s:11:"multiple_to";s:0:"";s:6:"fromto";s:4:"both";}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:28:"node:field_consultation_date";}',
        'load_terms' => 0,
      ),
    ),
    'public_submissions' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|consultation|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function govcms_consultation_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|consultation|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'consultation';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_consultation_summary',
        1 => 'group_consultation_htabs',
        2 => 'group_formal_submissions',
        3 => 'public_submissions',
        4 => 'progress_bar',
        5 => 'field_twitter_discussion',
        6 => 'field_formal_submission_cta_1',
        7 => 'field_discussion_forum_heading',
        8 => 'formal_submission_form',
        9 => 'field_discussion_forum_intro',
        10 => 'field_updates',
        11 => 'field_formal_submission_cta_2',
        12 => 'comments',
        13 => 'field_consultation_date',
        14 => 'field_consultation_issue_text',
        15 => 'group_issue',
        16 => 'field_issue_documentation',
        17 => 'group_updates',
        18 => 'group_outcomes',
        19 => 'field_outcomes_text',
      ),
    ),
    'fields' => array(
      'field_consultation_summary' => 'ds_content',
      'group_consultation_htabs' => 'ds_content',
      'group_formal_submissions' => 'ds_content',
      'public_submissions' => 'ds_content',
      'progress_bar' => 'ds_content',
      'field_twitter_discussion' => 'ds_content',
      'field_formal_submission_cta_1' => 'ds_content',
      'field_discussion_forum_heading' => 'ds_content',
      'formal_submission_form' => 'ds_content',
      'field_discussion_forum_intro' => 'ds_content',
      'field_updates' => 'ds_content',
      'field_formal_submission_cta_2' => 'ds_content',
      'comments' => 'ds_content',
      'field_consultation_date' => 'ds_content',
      'field_consultation_issue_text' => 'ds_content',
      'group_issue' => 'ds_content',
      'field_issue_documentation' => 'ds_content',
      'group_updates' => 'ds_content',
      'group_outcomes' => 'ds_content',
      'field_outcomes_text' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|consultation|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|update_type|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'update_type';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_pbundle_image',
      ),
    ),
    'fields' => array(
      'field_pbundle_image' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => TRUE,
    'layout_link_attribute' => FALSE,
    'layout_link_custom' => '',
  );
  $export['taxonomy_term|update_type|default'] = $ds_layout;

  return $export;
}
