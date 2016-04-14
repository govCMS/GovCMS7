<?php
/**
 * @file
 * govcms_consultation.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function govcms_consultation_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_consultation_htabs|node|consultation|default';
  $field_group->group_name = 'group_consultation_htabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Consultation tabs',
    'weight' => '1',
    'children' => array(
      0 => 'group_issue',
      1 => 'group_outcomes',
      2 => 'group_updates',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Consultation tabs',
      'instance_settings' => array(
        'classes' => 'group-consultation-htabs field-group-htabs',
      ),
    ),
  );
  $export['group_consultation_htabs|node|consultation|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_consultation_vtabs|node|consultation|form';
  $field_group->group_name = 'group_consultation_vtabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Consultation tabs',
    'weight' => '8',
    'children' => array(
      0 => 'group_discussion_settings',
      1 => 'group_formal_submissions',
      2 => 'group_twitter',
      3 => 'group_outcomes',
      4 => 'group_updates',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-consultation-vtabs field-group-tabs',
      ),
    ),
  );
  $export['group_consultation_vtabs|node|consultation|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_discussion_settings|node|consultation|form';
  $field_group->group_name = 'group_discussion_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_consultation_vtabs';
  $field_group->data = array(
    'label' => 'Informal discussion',
    'weight' => '14',
    'children' => array(
      0 => 'field_discussion_forum_heading',
      1 => 'field_discussion_forum_intro',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Informal discussion',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-disqus-settings field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_discussion_settings|node|consultation|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_formal_submissions|node|consultation|default';
  $field_group->group_name = 'group_formal_submissions';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Participate',
    'weight' => '2',
    'children' => array(
      0 => 'field_formal_submission_cta_1',
      1 => 'field_formal_submission_cta_2',
      2 => 'formal_submission_form',
      3 => 'progress_bar',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Participate',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-formal-submissions field-group-div layout-max spacer--medium',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h2',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_formal_submissions|node|consultation|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_formal_submissions|node|consultation|form';
  $field_group->group_name = 'group_formal_submissions';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_consultation_vtabs';
  $field_group->data = array(
    'label' => 'Formal Submissions',
    'weight' => '8',
    'children' => array(
      0 => 'field_enable_late_submissions',
      1 => 'field_file_uploads_enabled',
      2 => 'field_formal_submission_cta_1',
      3 => 'field_formal_submission_cta_2',
      4 => 'field_formal_submission_enabled',
      5 => 'field_formal_submission_notify',
      6 => 'field_short_comments_enabled',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-formal-submissions field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_formal_submissions|node|consultation|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_issue|node|consultation|default';
  $field_group->group_name = 'group_issue';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_consultation_htabs';
  $field_group->data = array(
    'label' => 'The Issue',
    'weight' => '8',
    'children' => array(
      0 => 'field_consultation_date',
      1 => 'field_consultation_issue_text',
      2 => 'field_issue_documentation',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'The Issue',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-issue field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_issue|node|consultation|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_issue|node|consultation|form';
  $field_group->group_name = 'group_issue';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'The issue',
    'weight' => '7',
    'children' => array(
      0 => 'field_consultation_issue_text',
      1 => 'field_issue_documentation',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'The issue',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_issue|node|consultation|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_outcomes|node|consultation|default';
  $field_group->group_name = 'group_outcomes';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_consultation_htabs';
  $field_group->data = array(
    'label' => 'Outcomes',
    'weight' => '11',
    'children' => array(
      0 => 'field_outcomes_text',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Outcomes',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-outcomes field-group-htab tabber__pane--no-space',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_outcomes|node|consultation|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_outcomes|node|consultation|form';
  $field_group->group_name = 'group_outcomes';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_consultation_vtabs';
  $field_group->data = array(
    'label' => 'Outcomes',
    'weight' => '6',
    'children' => array(
      0 => 'field_outcomes_text',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-outcomes field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_outcomes|node|consultation|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_twitter|node|consultation|form';
  $field_group->group_name = 'group_twitter';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_consultation_vtabs';
  $field_group->data = array(
    'label' => 'Twitter discussion',
    'weight' => '10',
    'children' => array(
      0 => 'field_twitter_discussion',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Twitter discussion',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-twitter field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_twitter|node|consultation|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_updates|node|consultation|default';
  $field_group->group_name = 'group_updates';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_consultation_htabs';
  $field_group->data = array(
    'label' => 'Updates and Milestones',
    'weight' => '10',
    'children' => array(
      0 => 'field_updates',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-updates field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_updates|node|consultation|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_updates|node|consultation|form';
  $field_group->group_name = 'group_updates';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'consultation';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_consultation_vtabs';
  $field_group->data = array(
    'label' => 'Updates/Milestones',
    'weight' => '7',
    'children' => array(
      0 => 'field_updates',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-updates field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_updates|node|consultation|form'] = $field_group;

  return $export;
}
