<?php
/**
 * @file
 * Custom code for the Consultation feature.
 */

define("LATE_SUBMISSION_SALT", variable_get('govcms_consultation_late_hash'));

/**
 * Implements hook_menu().
 */
function govcms_consultation_menu() {
  $items = array();
  $items['admin/config/govcms/consultation'] = array(
    'title' => 'govCMS Consultation',
    'description' => 'Configure Consultation module',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('govcms_consultation_admin_form'),
    'access arguments' => array('administer site configuration'),
    'position' => 'left',
    'weight' => -15,
    'file' => 'govcms_consultation.admin.inc',
  );
  return $items;
}

/**
 * Implements hook_cron().
 */
function govcms_consultation_cron() {
  // Workaround for issue in uuid_features where files do not import first time.
  if (!variable_get('govcms_consultation_uuid_revert', 0)) {
    features_revert(array('govcms_consultation' => array('uuid_term')));
    variable_set('govcms_consultation_uuid_revert', 1);
  }
}

/**
 * Implements hook_uuid_entity_features_rebuild_complete().
 */
function govcms_consultation_uuid_entity_features_rebuild_complete($entity_type, $entities, $module) {
  // Trigger a one time revert of uuid_features on initial complete.
  if ($entity_type == 'node' && $module == 'govcms_consultation') {
    if (!variable_get('govcms_consultation_node_uuid_revert', 0)) {
      if (module_exists('webform_clear')) {
        $nids = entity_get_id_by_uuid('node', array('1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'), FALSE);

        if (isset($nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'])) {
          db_insert('webform_clear')
          ->fields(array(
            'nid' => $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'],
            'clear_time' => '-1',
          ))
          ->execute();
          variable_set('govcms_consultation_node_uuid_revert', 1);
        }
      }
    }
  }
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function govcms_consultation_ds_custom_fields_info() {
  $export = array();

  $nids = entity_get_id_by_uuid('node', array('1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'), FALSE);

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'formal_submission_form';
  $ds_field->label = 'Formal submission form';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'consultation|*';
  $ds_field->properties = array(
    'block' => 'webform|client-block-' . $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'],
    'block_render' => '3',
  );
  $export['formal_submission_form'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'progress_bar';
  $ds_field->label = 'Progress bar';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'consultation|*';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['progress_bar'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'public_submissions';
  $ds_field->label = 'Public submissions';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'consultation|*';
  $ds_field->properties = array(
    'block' => 'views|formal_submissions-block_1',
    'block_render' => '3',
  );
  $export['public_submissions'] = $ds_field;

  return $export;
}

function govcms_consultation_theme_registry_alter(&$theme_registry) {
  // Defined path to the current module.
  $module_path = drupal_get_path('module', 'govcms_consultation');
  // Find all .tpl.php files in this module's folder recursively.
  $template_file_objects = drupal_find_theme_templates($theme_registry, '.tpl.php', $module_path);
  // Iterate through all found template file objects.
  foreach ($template_file_objects as $key => $template_file_object) {
    // If the template has not already been overridden by a theme.
    if (!isset($theme_registry[$key]['theme path']) || !preg_match('#/themes/#', $theme_registry[$key]['theme path'])) {
      // Alter the theme path and template elements.
      $theme_registry[$key]['theme path'] = $module_path;
      $theme_registry[$key] = array_merge($theme_registry[$key], $template_file_object);
      $theme_registry[$key]['type'] = 'module';
    }
  }

}

/**
 * Implements hook_form_alter().
 */
function govcms_consultation_form_alter(&$form, &$form_state, $form_id) {
  // Hide option for private submissions if not enabled.
  if (!variable_get('consultation_enable_private', 0)) {
    $nids = entity_get_id_by_uuid('node', array('1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0'), FALSE);
    if ($form_id == 'webform_client_form_' . $nids['1bc43c5f-fc01-4ac4-bcc8-2b50660f3ae0']) {
      hide($form['submitted']['step_1_your_submission']['private_submission']);
    }
  }
}

/**
 * Implements hook_form_node_form_alter().
 */
function govcms_consultation_form_node_form_alter(&$form, $form_state, $form_id) {
  $type = $form['#node']->type;

  if ($type == 'consultation') {
    if (!variable_get('consultation_enable_private', 0)) {
    }

    if (!variable_get('consultation_enable_twitter', 0)) {
      field_group_hide_field_groups($form, array('group_twitter'));
    }

    if (!variable_get('consultation_enable_disqus', 0)) {
      field_group_hide_field_groups($form, array('group_discussion_settings'));
      $form['comment_settings']['comment']['#value'] = 0;
      $form['comment_settings']['comment']['#default_value'] = 0;
      hide($form['comment_settings']);
    }
    else {
      $form['comment_settings']['#group'] = 'group_discussion_settings';
      $form['#group_children']['comment_settings'] = 'group_discussion_settings';
    }

    // Display late submission URL on edit form.
    // Work out if this node can validly accept late submissions.
    $accept_late_submissions = _govcms_consultation_admin_accept_late_submission($form['#node']);

    // If able to accept late submissions.
    if ($accept_late_submissions) {
      // Get the late submission URL.
      $url = _govcms_consultation_admin_return_late_submission_url($form['#node']);
      // Create a message to let the admin know the URL.
      $args = array(
        '!url' => $url,
      );
      $message = t('Use the following URL for late submissions: !url', $args);
      // Finally output the message.
      drupal_set_message($message);
    } 
  } 
}

/**
 * Implements hook_preprocess_field().
 */
function govcms_consultation_preprocess_field(&$variables, $hook) {
  if ($variables['element']['#field_name'] == 'progress_bar') {
    $element =& $variables['element'];
    _consultation_vars($variables, $element['#object']);
  }
}

/**
 * Implements hook_preprocess_node().
 */
function govcms_consultation_preprocess_node(&$variables, $hook) {
  $node = $variables['node'];

  // Conditionally remove Formal Submission fields where relevant.
  if ($variables['type'] == 'consultation' && $variables['view_mode'] == 'full') {

    // Include Consultation specific script & styles.
    drupal_add_js(drupal_get_path('module', 'govcms_consultation') . '/js/govcms_consultation.js', array('file'));
    drupal_add_css(drupal_get_path('module', 'govcms_consultation') . '/css/govcms_consultation.css', array('file'));

    _consultation_vars($variables, $variables['node']);
    $consultation = $variables['consultation'];

    // Return if formal submissions are not accepted.
    if (!empty($consultation['hide_form'])) {
      //field_group_hide_field_groups($variables['elements'], array('group_formal_submissions'));
      hide($variables['content']['formal_submission_form']);
      hide($variables['content']['field_formal_submission_cta_1']);
      hide($variables['content']['field_formal_submission_cta_2']);
    }

    // Add formal submission field to JS Drupal.settings if a value is present.
    if (!empty($consultation['notify_email'])) {
      drupal_add_js(array(
        'govcms_consultation' => array(
          'formalSubmissionNotify' => check_plain($consultation['notify_email']),
        ),
      ), 'setting');

    }
    hide($variables['content']['field_formal_submission_notify']);

    // Set default values.
    $short_comments_enabled = $file_uploads_enabled = FALSE;
    // Create the entity metadata wrapper.
    $wrapper = $consultation['wrapped_entity'];

    // If the 'Short comments enabled' field exists and is TRUE.
    if (isset($node->field_short_comments_enabled) && $wrapper->field_short_comments_enabled->value()) {
      $short_comments_enabled = TRUE;
    }

    // If the 'File upload enabled' field exists and is TRUE.
    if (isset($node->field_file_uploads_enabled) && $wrapper->field_file_uploads_enabled->value()) {
      $file_uploads_enabled = TRUE;
    }

    // Add the above results to javascript.
    drupal_add_js(array(
      'govcms_consultation' => array(
        'shortCommentsEnabled' => $short_comments_enabled,
        'fileUploadsEnabled' => $file_uploads_enabled,
      ),
    ), 'setting');

    // Get the end consultation date.
    $end_consultation_date = _govcms_consultation_admin_return_end_consultation_date($node, $wrapper);
    // Get the current timestamp.
    $time = time();

    // Check if a fso has been provided.
    if (isset($_GET['fso'])) {
      // Check if the node is able to accept late submissions.
      $accept_late_submissions = _govcms_consultation_admin_accept_late_submission($node);
      // If the node can accept late submissions.
      if ($accept_late_submissions) {
        // Get the salted hash for this nid.
        $salted_hash = _govcms_consultation_admin_return_salted_hash($node->nid);
        // If the salted hash and the fso are equal.
        if ($_GET['fso'] == $salted_hash) {
          // Show the relevant HYS sections.
          show($variables['content']['formal_submission_form']);

          // Build up the message to let the user know of the special case.
          $message = t("Please note that acceptance of submissions for this round of the consultation has closed. It is at the discretion of the Consultation owner if late submissions are accepted. Thank you.");
          $variables['status_message'] = $message;
        }
      }
    }

    // Hide 'Discussion Forum' related fields initially.
    hide($variables['content']['field_discussion_forum_heading']);
    hide($variables['content']['field_discussion_forum_intro']);

    if (!$wrapper->field_short_comments_enabled->value()) {
      $variables['classes_array'][] = 'consultation__hide_short_comments';
    }
    if (!$wrapper->field_file_uploads_enabled->value()) {
      $variables['classes_array'][] = 'consultation__hide_files';
    }

    // If comments are open.
    if ($variables['comment'] == COMMENT_NODE_OPEN) {
      // If the heading 'Discussion Forum' heading field exists and is not blank.
      if (isset($node->field_discussion_forum_heading) && $wrapper->field_discussion_forum_heading->value() != '') {
        // Show the 'Discussion Forum' heading field.
        show($variables['content']['field_discussion_forum_heading']);
      }
      // If the 'Discussion Forum' introduction field eixsts and is not blank.
      if (isset($node->field_discussion_forum_intro) && $wrapper->field_discussion_forum_intro->value() != '') {
        // Show the 'Discussion Forum' introduction field.
        show($variables['content']['field_discussion_forum_intro']);
      }
    }
  }
}

/**
 * Helper function to add consultation variables to template files.
 */
function _consultation_vars(&$variables, $element_object) {
  $consultation['now'] = time();
  $consultation['wrapped_entity'] = entity_metadata_wrapper('node', $element_object);
  $date = $consultation['wrapped_entity']->field_consultation_date->value();
  $consultation['start'] = $date['value'];
  $consultation['end'] = $date['value2'];
  $consultation['notify_email'] = $consultation['wrapped_entity']->field_formal_submission_notify->value();
  $consultation['duration'] = ($consultation['end'] - $consultation['start']);
  $consultation['percentage'] = _consultation_percentage($consultation);
  $consultation['days_total'] = round($consultation['duration'] / strtotime('1 day', 0));
  $consultation['days_remain'] = _consultation_days_remain($consultation);
  $consultation['submission_enabled'] = $consultation['wrapped_entity']->field_formal_submission_enabled->value();
  $consultation['status_class'] = ($consultation['percentage'] === 100 ? 'consultation__progress-bar--complete' : '');
  $consultation['hide_form'] = !$consultation['submission_enabled'] || ($consultation['start'] > $consultation['now']) || ($consultation['end'] < $consultation['now']);
  $variables['consultation'] = $consultation;

  return $variables;
}

/**
 * Helper function: Return end consultation date.
 */
function _govcms_consultation_admin_return_end_consultation_date($node, $wrapper) {
  // Set default consultation date end value.
  $consultation_date_end = '';

  // If the 'Consultation date' field exists and is not blank.
  $consultation_date_value = $wrapper->field_consultation_date->value();
  if (isset($node->field_consultation_date) && !empty($consultation_date_value)) {
    // Get the 'Consultation date' field.
    $consultation_date = $consultation_date_value;
    // Get the end date.
    $consultation_date_end = $consultation_date['value2'];
  }

  return $consultation_date_end;
}

/**
 * Helper function to determine percentage complete.
 */
function _consultation_percentage($consultation) {
  $time_until_it_starts = ($consultation['now'] - $consultation['start']);
  $percentage = $time_until_it_starts / $consultation['duration'] * 100;
  $percentage = max(0, min(100, $percentage));
  return $percentage;
}

/**
 * Helper function - days_remain for progress bar.
 */
function _consultation_days_remain($consultation) {

  $days_total = round($consultation['duration'] / strtotime('1 day', 0));

  if ($consultation['percentage'] === 0) {
    $days_remain = $days_total;
  }
  elseif ($consultation['percentage'] === 100) {
    $days_remain = "0";
  }
  elseif (($consultation['end'] > $consultation['now']) && ($consultation['end'] - $consultation['now'] < strtotime('1 day', 0))) {
    $days_remain = "< 1";
  }
  else {
    $days_remain = round(($consultation['end'] - time()) / strtotime('1 day', 0));
  }
  return $days_remain;
}

/**
 * Helper function: Return whether a node can validly accept late submissions.
 *
 * Check that the 'Enable late submissions' value is set.
 * Check that the date has passed.
 */
function _govcms_consultation_admin_accept_late_submission($node) {
  // Set a default answer.
  $answer = FALSE;
  // Create an entity metadata wrapper.
  $wrapper = entity_metadata_wrapper('node', $node);

  // Check if the 'Enable late submissions' field exists and is TRUE.
  if (isset($node->field_enable_late_submissions) && $wrapper->field_enable_late_submissions->value() === TRUE) {
    // Get the consultation date end.
    $consultation_date_end = _govcms_consultation_admin_return_end_consultation_date($node, $wrapper);
    // Get the current time.
    $time = time();
    // Check if the current date is greater than the end date (i.e. it's in the past).
    if ($time > $consultation_date_end) {
      // Update the answer.
      $answer = TRUE;
    }
  }

  // Return the answer.
  return $answer;
}

/**
 * Helper function: Return salted hash for a given node ID.
 */
function _govcms_consultation_admin_return_salted_hash($nid) {
  return crc32(LATE_SUBMISSION_SALT + $nid);
}

/**
 * Helper function: Return formatted late submission URL.
 */
function _govcms_consultation_admin_return_late_submission_url($node) {
  global $base_url;

  // Get the salted hash for this nid.
  $salted_hash = _govcms_consultation_admin_return_salted_hash($node->nid);

  // Get the node path.
  $uri = entity_uri('node', $node);
  // Update the options with the query.
  $uri['options']['query']['fso'] = $salted_hash;
  // Output the URL.
  $url = $base_url . url($uri['path'], $uri['options']);

  // Return the URL.
  return $url;
}
