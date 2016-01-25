<?php
/**
 * @file
 * govcms_consultation.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function govcms_consultation_views_default_views() {
  $export = array();

  $nids = entity_get_id_by_uuid('node', array('1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'), FALSE);
  if (!isset($nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'])) {
    return $export;
  }

  $view = new view();
  $view->name = 'consultations_admin';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'webform_submissions';
  $view->human_name = 'Consultations (admin)';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Consultations admin';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    6 => '6',
    7 => '7',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'value' => 'value',
    'submitted' => 'submitted',
    'value_1' => 'value_1',
    'value_2' => 'value_2',
    'value_3' => 'value_3',
    'edit_submission' => 'edit_submission',
  );
  $handler->display->display_options['style_options']['default'] = 'submitted';
  $handler->display->display_options['style_options']['info'] = array(
    'value' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'submitted' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'value_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'value_2' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'value_3' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_submission' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Webform submissions: Node */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Relationship: Submission Data (Name) */
  $handler->display->display_options['relationships']['data']['id'] = 'data';
  $handler->display->display_options['relationships']['data']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['data']['field'] = 'data';
  $handler->display->display_options['relationships']['data']['ui_name'] = 'Submission Data (Name)';
  $handler->display->display_options['relationships']['data']['label'] = 'Submission Data (Name)';
  $handler->display->display_options['relationships']['data']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['relationships']['data']['webform_cid'] = '1';
  /* Relationship: Submission Data (Approved) */
  $handler->display->display_options['relationships']['data_2']['id'] = 'data_2';
  $handler->display->display_options['relationships']['data_2']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['data_2']['field'] = 'data';
  $handler->display->display_options['relationships']['data_2']['ui_name'] = 'Submission Data (Approved)';
  $handler->display->display_options['relationships']['data_2']['label'] = 'Submission Data (Approved)';
  $handler->display->display_options['relationships']['data_2']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['relationships']['data_2']['webform_cid'] = '14';
  /* Relationship: Submission Data (Private) */
  $handler->display->display_options['relationships']['data_3']['id'] = 'data_3';
  $handler->display->display_options['relationships']['data_3']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['data_3']['field'] = 'data';
  $handler->display->display_options['relationships']['data_3']['ui_name'] = 'Submission Data (Private)';
  $handler->display->display_options['relationships']['data_3']['label'] = 'Submission Data (Private)';
  $handler->display->display_options['relationships']['data_3']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['relationships']['data_3']['webform_cid'] = '25';
  /* Relationship: Submission Data (Consultation id) */
  $handler->display->display_options['relationships']['data_1']['id'] = 'data_1';
  $handler->display->display_options['relationships']['data_1']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['data_1']['field'] = 'data';
  $handler->display->display_options['relationships']['data_1']['ui_name'] = 'Submission Data (Consultation id)';
  $handler->display->display_options['relationships']['data_1']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['relationships']['data_1']['webform_cid'] = '16';
  /* Field: Webform submissions: Sid */
  $handler->display->display_options['fields']['sid']['id'] = 'sid';
  $handler->display->display_options['fields']['sid']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['sid']['field'] = 'sid';
  $handler->display->display_options['fields']['sid']['label'] = 'Submission ID';
  $handler->display->display_options['fields']['sid']['separator'] = '';
  /* Field: Webform submission data: Value */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['label'] = '';
  $handler->display->display_options['fields']['value']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value']['webform_cid'] = '1';
  /* Field: Webform submission data: Value */
  $handler->display->display_options['fields']['value_4']['id'] = 'value_4';
  $handler->display->display_options['fields']['value_4']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_4']['field'] = 'value';
  $handler->display->display_options['fields']['value_4']['label'] = '';
  $handler->display->display_options['fields']['value_4']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_4']['webform_cid'] = '2';
  /* Field: Webform submissions: Submitted */
  $handler->display->display_options['fields']['submitted']['id'] = 'submitted';
  $handler->display->display_options['fields']['submitted']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['submitted']['field'] = 'submitted';
  $handler->display->display_options['fields']['submitted']['date_format'] = 'short';
  $handler->display->display_options['fields']['submitted']['second_date_format'] = 'long';
  /* Field: Webform submission data: Value */
  $handler->display->display_options['fields']['value_1']['id'] = 'value_1';
  $handler->display->display_options['fields']['value_1']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_1']['field'] = 'value';
  $handler->display->display_options['fields']['value_1']['label'] = '';
  $handler->display->display_options['fields']['value_1']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_1']['webform_cid'] = '14';
  /* Field: Webform submission data: Value */
  $handler->display->display_options['fields']['value_5']['id'] = 'value_5';
  $handler->display->display_options['fields']['value_5']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_5']['field'] = 'value';
  $handler->display->display_options['fields']['value_5']['label'] = '';
  $handler->display->display_options['fields']['value_5']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_5']['webform_cid'] = '24';
  /* Field: Webform submission data: Value */
  $handler->display->display_options['fields']['value_2']['id'] = 'value_2';
  $handler->display->display_options['fields']['value_2']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_2']['field'] = 'value';
  $handler->display->display_options['fields']['value_2']['label'] = 'Private';
  $handler->display->display_options['fields']['value_2']['alter']['text'] = 'Yes';
  $handler->display->display_options['fields']['value_2']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['value_2']['custom_label'] = 'custom';
  $handler->display->display_options['fields']['value_2']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_2']['webform_cid'] = '25';
  /* Field: Webform submission data: Value */
  $handler->display->display_options['fields']['value_3']['id'] = 'value_3';
  $handler->display->display_options['fields']['value_3']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_3']['field'] = 'value';
  $handler->display->display_options['fields']['value_3']['label'] = 'Consultation';
  $handler->display->display_options['fields']['value_3']['custom_label'] = 'custom';
  $handler->display->display_options['fields']['value_3']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_3']['webform_cid'] = '16';
  /* Field: Webform submissions: Edit link */
  $handler->display->display_options['fields']['edit_submission']['id'] = 'edit_submission';
  $handler->display->display_options['fields']['edit_submission']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['edit_submission']['field'] = 'edit_submission';
  $handler->display->display_options['fields']['edit_submission']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_submission']['access_check'] = 1;
  /* Filter criterion: Webform: Node */
  $handler->display->display_options['filters']['nid']['id'] = 'nid';
  $handler->display->display_options['filters']['nid']['table'] = 'webform';
  $handler->display->display_options['filters']['nid']['field'] = 'nid';
  $handler->display->display_options['filters']['nid']['relationship'] = 'nid';
  $handler->display->display_options['filters']['nid']['value']['value'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['filters']['nid']['group'] = 1;
  /* Filter criterion: Webform submission data: Data field */
  $handler->display->display_options['filters']['data']['id'] = 'data';
  $handler->display->display_options['filters']['data']['table'] = 'webform_submitted_data';
  $handler->display->display_options['filters']['data']['field'] = 'data';
  $handler->display->display_options['filters']['data']['relationship'] = 'data';
  $handler->display->display_options['filters']['data']['operator'] = 'contains';
  $handler->display->display_options['filters']['data']['group'] = 1;
  $handler->display->display_options['filters']['data']['exposed'] = TRUE;
  $handler->display->display_options['filters']['data']['expose']['operator_id'] = 'data_op';
  $handler->display->display_options['filters']['data']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['data']['expose']['operator'] = 'data_op';
  $handler->display->display_options['filters']['data']['expose']['identifier'] = 'data';
  $handler->display->display_options['filters']['data']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
  );
  /* Filter criterion: Webform submission data: Data field */
  $handler->display->display_options['filters']['data_1']['id'] = 'data_1';
  $handler->display->display_options['filters']['data_1']['table'] = 'webform_submitted_data';
  $handler->display->display_options['filters']['data_1']['field'] = 'data';
  $handler->display->display_options['filters']['data_1']['relationship'] = 'data_1';
  $handler->display->display_options['filters']['data_1']['group'] = 1;
  $handler->display->display_options['filters']['data_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['data_1']['expose']['operator_id'] = 'data_1_op';
  $handler->display->display_options['filters']['data_1']['expose']['label'] = 'Consultation id';
  $handler->display->display_options['filters']['data_1']['expose']['operator'] = 'data_1_op';
  $handler->display->display_options['filters']['data_1']['expose']['identifier'] = 'data_1';
  $handler->display->display_options['filters']['data_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    8 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
    9 => 0,
    25 => 0,
    26 => 0,
    27 => 0,
  );
  $handler->display->display_options['filters']['data_1']['group_info']['label'] = 'Data field';
  $handler->display->display_options['filters']['data_1']['group_info']['identifier'] = 'data_1';
  $handler->display->display_options['filters']['data_1']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['data_1']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Webform submission data: Data field */
  $handler->display->display_options['filters']['data_2']['id'] = 'data_2';
  $handler->display->display_options['filters']['data_2']['table'] = 'webform_submitted_data';
  $handler->display->display_options['filters']['data_2']['field'] = 'data';
  $handler->display->display_options['filters']['data_2']['relationship'] = 'data_2';
  $handler->display->display_options['filters']['data_2']['group'] = 1;
  $handler->display->display_options['filters']['data_2']['exposed'] = TRUE;
  $handler->display->display_options['filters']['data_2']['expose']['operator_id'] = 'data_2_op';
  $handler->display->display_options['filters']['data_2']['expose']['label'] = 'Data field';
  $handler->display->display_options['filters']['data_2']['expose']['operator'] = 'data_2_op';
  $handler->display->display_options['filters']['data_2']['expose']['identifier'] = 'data_2';
  $handler->display->display_options['filters']['data_2']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['data_2']['group_info']['label'] = 'Approved for display';
  $handler->display->display_options['filters']['data_2']['group_info']['identifier'] = 'data_2';
  $handler->display->display_options['filters']['data_2']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Approved',
      'operator' => '=',
      'value' => 'approved_for_display',
    ),
    2 => array(
      'title' => 'Not approved',
      'operator' => '!=',
      'value' => 'approved_for_display',
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
  );

  /* Display: Consultations admin */
  $handler = $view->new_display('page', 'Consultations admin', 'consultations_admin');
  $handler->display->display_options['path'] = 'admin/content/consultation';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Consultation submissions';
  $handler->display->display_options['menu']['description'] = 'Consultation submissions';
  $handler->display->display_options['menu']['weight'] = '20';
  $handler->display->display_options['menu']['context'] = 1;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'Consultation';
  $handler->display->display_options['tab_options']['description'] = 'Consultation submissions';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $export['consultations_admin'] = $view;

  $view = new view();
  $view->name = 'formal_submissions';
  $view->description = 'Consultation submissions made public';
  $view->tag = 'default';
  $view->base_table = 'webform_submissions';
  $view->human_name = 'Formal submissions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['css_class'] = 'document-list';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h4>The following formal submissions have been made public.</h4>';
  $handler->display->display_options['header']['area']['format'] = 'rich_text';
  /* Relationship: Submission Data (Parent Consultation) */
  $handler->display->display_options['relationships']['data']['id'] = 'data';
  $handler->display->display_options['relationships']['data']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['data']['field'] = 'data';
  $handler->display->display_options['relationships']['data']['ui_name'] = 'Submission Data (Parent Consultation)';
  $handler->display->display_options['relationships']['data']['label'] = 'Submission Data (Parent Consultation)';
  $handler->display->display_options['relationships']['data']['required'] = TRUE;
  $handler->display->display_options['relationships']['data']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['relationships']['data']['webform_cid'] = '16';
  /* Relationship: Submission Data (Approved for display) */
  $handler->display->display_options['relationships']['data_1']['id'] = 'data_1';
  $handler->display->display_options['relationships']['data_1']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['data_1']['field'] = 'data';
  $handler->display->display_options['relationships']['data_1']['ui_name'] = 'Submission Data (Approved for display)';
  $handler->display->display_options['relationships']['data_1']['label'] = 'Submission Data (Approved for display)';
  $handler->display->display_options['relationships']['data_1']['required'] = TRUE;
  $handler->display->display_options['relationships']['data_1']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['relationships']['data_1']['webform_cid'] = '14';
  /* Relationship: Submission Data (Private) */
  $handler->display->display_options['relationships']['data_2']['id'] = 'data_2';
  $handler->display->display_options['relationships']['data_2']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['data_2']['field'] = 'data';
  $handler->display->display_options['relationships']['data_2']['ui_name'] = 'Submission Data (Private)';
  $handler->display->display_options['relationships']['data_2']['label'] = 'Submission Data (Private)';
  $handler->display->display_options['relationships']['data_2']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['relationships']['data_2']['webform_cid'] = '25';
  /* Relationship: Submission Data (Submission Title) */
  $handler->display->display_options['relationships']['data_3']['id'] = 'data_3';
  $handler->display->display_options['relationships']['data_3']['table'] = 'webform_submissions';
  $handler->display->display_options['relationships']['data_3']['field'] = 'data';
  $handler->display->display_options['relationships']['data_3']['ui_name'] = 'Submission Data (Submission Title)';
  $handler->display->display_options['relationships']['data_3']['label'] = 'Submission Data (Submission Name)';
  $handler->display->display_options['relationships']['data_3']['required'] = TRUE;
  $handler->display->display_options['relationships']['data_3']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['relationships']['data_3']['webform_cid'] = '1';
  /* Field: Webform submission data: Name */
  $handler->display->display_options['fields']['value_2']['id'] = 'value_2';
  $handler->display->display_options['fields']['value_2']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_2']['field'] = 'value';
  $handler->display->display_options['fields']['value_2']['ui_name'] = 'Webform submission data: Name';
  $handler->display->display_options['fields']['value_2']['label'] = '';
  $handler->display->display_options['fields']['value_2']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['value_2']['element_type'] = 'h4';
  $handler->display->display_options['fields']['value_2']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['value_2']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['value_2']['custom_label'] = 'none';
  $handler->display->display_options['fields']['value_2']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_2']['webform_cid'] = '1';
  /* Field: Webform submission data: Short comment */
  $handler->display->display_options['fields']['value_5']['id'] = 'value_5';
  $handler->display->display_options['fields']['value_5']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_5']['field'] = 'value';
  $handler->display->display_options['fields']['value_5']['ui_name'] = 'Webform submission data: Short comment';
  $handler->display->display_options['fields']['value_5']['label'] = '';
  $handler->display->display_options['fields']['value_5']['element_type'] = 'p';
  $handler->display->display_options['fields']['value_5']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['value_5']['custom_label'] = 'none';
  $handler->display->display_options['fields']['value_5']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_5']['webform_cid'] = '34';
  /* Field: Webform submission data: File (excluded) */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['ui_name'] = 'Webform submission data: File (excluded)';
  $handler->display->display_options['fields']['value']['label'] = '';
  $handler->display->display_options['fields']['value']['exclude'] = TRUE;
  $handler->display->display_options['fields']['value']['alter']['text'] = 'Download file';
  $handler->display->display_options['fields']['value']['element_type'] = 'div';
  $handler->display->display_options['fields']['value']['element_class'] = 'file';
  $handler->display->display_options['fields']['value']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['value']['custom_label'] = 'none';
  $handler->display->display_options['fields']['value']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value']['webform_cid'] = '11';
  /* Field: Webform submission data: Additional file 1 (excluded) */
  $handler->display->display_options['fields']['value_4']['id'] = 'value_4';
  $handler->display->display_options['fields']['value_4']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_4']['field'] = 'value';
  $handler->display->display_options['fields']['value_4']['ui_name'] = 'Webform submission data: Additional file 1 (excluded)';
  $handler->display->display_options['fields']['value_4']['label'] = '';
  $handler->display->display_options['fields']['value_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['value_4']['element_type'] = 'div';
  $handler->display->display_options['fields']['value_4']['element_class'] = 'file';
  $handler->display->display_options['fields']['value_4']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['value_4']['custom_label'] = 'none';
  $handler->display->display_options['fields']['value_4']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_4']['webform_cid'] = '18';
  /* Field: Webform submission data: Additional file 2 (excluded) */
  $handler->display->display_options['fields']['value_1']['id'] = 'value_1';
  $handler->display->display_options['fields']['value_1']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_1']['field'] = 'value';
  $handler->display->display_options['fields']['value_1']['ui_name'] = 'Webform submission data: Additional file 2 (excluded)';
  $handler->display->display_options['fields']['value_1']['label'] = '';
  $handler->display->display_options['fields']['value_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['value_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['value_1']['element_class'] = 'file';
  $handler->display->display_options['fields']['value_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['value_1']['custom_label'] = 'none';
  $handler->display->display_options['fields']['value_1']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_1']['webform_cid'] = '30';
  /* Field: Webform submission data: Additional file 3 (excluded) */
  $handler->display->display_options['fields']['value_3']['id'] = 'value_3';
  $handler->display->display_options['fields']['value_3']['table'] = 'webform_submissions';
  $handler->display->display_options['fields']['value_3']['field'] = 'value';
  $handler->display->display_options['fields']['value_3']['ui_name'] = 'Webform submission data: Additional file 3 (excluded)';
  $handler->display->display_options['fields']['value_3']['label'] = '';
  $handler->display->display_options['fields']['value_3']['exclude'] = TRUE;
  $handler->display->display_options['fields']['value_3']['element_type'] = 'div';
  $handler->display->display_options['fields']['value_3']['element_class'] = 'file';
  $handler->display->display_options['fields']['value_3']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['value_3']['custom_label'] = 'none';
  $handler->display->display_options['fields']['value_3']['webform_nid'] = $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'];
  $handler->display->display_options['fields']['value_3']['webform_cid'] = '31';
  /* Field: Global: File set */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Global: File set';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="js-file-extension">
<div class="file">[value]</div>
<div class="file">[value_4]</div>
<div class="file">[value_1]</div>
<div class="file">[value_3]</div>
</div>

<hr />';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Webform submission data: Data field */
  $handler->display->display_options['sorts']['data']['id'] = 'data';
  $handler->display->display_options['sorts']['data']['table'] = 'webform_submitted_data';
  $handler->display->display_options['sorts']['data']['field'] = 'data';
  $handler->display->display_options['sorts']['data']['relationship'] = 'data_3';
  $handler->display->display_options['sorts']['data']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['data']['expose']['label'] = 'Submission title';
  /* Sort criterion: Webform submissions: Submitted */
  $handler->display->display_options['sorts']['submitted']['id'] = 'submitted';
  $handler->display->display_options['sorts']['submitted']['table'] = 'webform_submissions';
  $handler->display->display_options['sorts']['submitted']['field'] = 'submitted';
  $handler->display->display_options['sorts']['submitted']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['submitted']['expose']['label'] = 'Submitted date';
  /* Contextual filter: Webform submission data: Data field */
  $handler->display->display_options['arguments']['data']['id'] = 'data';
  $handler->display->display_options['arguments']['data']['table'] = 'webform_submitted_data';
  $handler->display->display_options['arguments']['data']['field'] = 'data';
  $handler->display->display_options['arguments']['data']['relationship'] = 'data';
  $handler->display->display_options['arguments']['data']['default_action'] = 'default';
  $handler->display->display_options['arguments']['data']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['data']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['data']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['data']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['data']['limit'] = '0';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  /* Filter criterion: Webform submission data: Data field */
  $handler->display->display_options['filters']['data']['id'] = 'data';
  $handler->display->display_options['filters']['data']['table'] = 'webform_submitted_data';
  $handler->display->display_options['filters']['data']['field'] = 'data';
  $handler->display->display_options['filters']['data']['relationship'] = 'data_1';
  $handler->display->display_options['filters']['data']['value'] = 'approved_for_display';
  $handler->display->display_options['filters']['data']['group'] = 1;
  $handler->display->display_options['filters']['data']['expose']['operator_id'] = 'data_op';
  $handler->display->display_options['filters']['data']['expose']['label'] = 'Data field';
  $handler->display->display_options['filters']['data']['expose']['operator'] = 'data_op';
  $handler->display->display_options['filters']['data']['expose']['identifier'] = 'data';
  $handler->display->display_options['filters']['data']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    8 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
  );
  /* Filter criterion: Webform submission data: Data field */
  $handler->display->display_options['filters']['data_1']['id'] = 'data_1';
  $handler->display->display_options['filters']['data_1']['table'] = 'webform_submitted_data';
  $handler->display->display_options['filters']['data_1']['field'] = 'data';
  $handler->display->display_options['filters']['data_1']['relationship'] = 'data_2';
  $handler->display->display_options['filters']['data_1']['group'] = 2;
  /* Filter criterion: Webform submission data: Data field */
  $handler->display->display_options['filters']['data_2']['id'] = 'data_2';
  $handler->display->display_options['filters']['data_2']['table'] = 'webform_submitted_data';
  $handler->display->display_options['filters']['data_2']['field'] = 'data';
  $handler->display->display_options['filters']['data_2']['relationship'] = 'data_2';
  $handler->display->display_options['filters']['data_2']['operator'] = 'empty';
  $handler->display->display_options['filters']['data_2']['group'] = 2;
  /* Filter criterion: Webform submission data: Data field */
  $handler->display->display_options['filters']['data_3']['id'] = 'data_3';
  $handler->display->display_options['filters']['data_3']['table'] = 'webform_submitted_data';
  $handler->display->display_options['filters']['data_3']['field'] = 'data';
  $handler->display->display_options['filters']['data_3']['relationship'] = 'data_3';
  $handler->display->display_options['filters']['data_3']['operator'] = 'contains';
  $handler->display->display_options['filters']['data_3']['exposed'] = TRUE;
  $handler->display->display_options['filters']['data_3']['expose']['operator_id'] = 'data_3_op';
  $handler->display->display_options['filters']['data_3']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['data_3']['expose']['operator'] = 'data_3_op';
  $handler->display->display_options['filters']['data_3']['expose']['identifier'] = 'submission_contains';
  $handler->display->display_options['filters']['data_3']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
    3 => 0,
  );

  /* Display: Approved for display (On this consultation) */
  $handler = $view->new_display('block', 'Approved for display (On this consultation)', 'block_1');
  $export['formal_submissions'] = $view;

  return $export;
}
