<?php

/**
 * Determines if the banner should be excluded for the current page.
 *
 * @param $node
 *   The current node for the page, if any.
 *
 * @return bool
 */
function _dfata_banner_excluded($node = NULL) {
  if (drupal_is_front_page()) {
    return TRUE;
  }
  if ($node && $node->type == "news_article" && empty($node->field_image)) {
    return TRUE;
  }
  return FALSE;
}

function _dfata_faculty_banner_info(&$vars) {
  $vars['academy_banner'] = '';
  $vars['academy_banner_has_image'] = '';
  $vars['academy_title_colour'] = '';
  $node = menu_get_object();
  if (!_dfata_banner_excluded($node)) {
    $is_news = FALSE;
    if ($node) {
      // Set the colour and image based on the faculty.
      // If it's a Course, get the first Faculty.
      switch ($node->type) {
        case "faculty":
          $faculty = $node;

          // Add the badge under the title.
          if (!empty($node->field_badge)) {
            $vars['title_suffix'] = array(
              '#markup' => '<div class="faculty-badge">' . $node->field_badge['und'][0]['safe_value'] . '</div>'
            );
          }

          break;
        case "course":
          // Pick the first Faculty found.
          $faculty = $node->field_faculty['und'][0]['entity'];
          break;
        case "news_article":
          $is_news = TRUE;
          if (!empty($node->field_image)) {
            $image_file = (object) $node->field_image['und'][0];
            $vars['academy_banner_has_image'] = ' has-image';
          }
          break;
        case "page":
          if (!empty($node->field_image)) {
            $image_file = (object) $node->field_image['und'][0];
          }
          break;
      }
      if (isset($faculty)) {
        if (!empty($faculty->field_image)) {
          $image_file = (object) $faculty->field_image['und'][0];
        }
        if (!empty($faculty->field_colour)) {
          $vars['academy_title_colour'] = ' pantone-' . $faculty->field_colour['und'][0]['value'];
        }
      }
    }

    // Default image fid.
    if (!isset($image_file)) {
      $fid = variable_get('dfata_standard_banner_fid', 4);
      $image_file = file_load($fid);
    }

    if (isset($image_file)) {
      if ($is_news) {
        $image_style = "banner_image_large";
      }
      else {
        $image_style = "banner_image";
      }
      $image = array(
        'path' => image_style_url($image_style, $image_file->uri),
        'alt' => $image_file->alt,
        'title' => drupal_get_title(),
        'attributes' => array()
      );
      $vars['academy_banner'] = array(
        'title' => drupal_get_title(),
        'image' => theme_image($image),
      );
    }
  }
}

function _dfata_contact_form_alter(&$form, &$form_state) {
  $form['name']['#title'] = "Your first name";
  $form['surname'] = array(
    '#type' => 'textfield',
    '#title' => 'Your surname',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => 1
  );
  $form['phone'] = array(
    '#type' => 'textfield',
    '#title' => 'Your phone number',
    '#maxlength' => 15,
    '#required' => TRUE,
    '#weight' => 3
  );
  $form['copy']['#access'] = TRUE;

  // Set the right order for fields on the form.
  $field_order = array(
    'name',
    'surname',
    'mail',
    'phone',
    'subject',
    'cid',
    'message',
    'copy',
  );
  foreach ($field_order as $key => $field) {
    // Set/Reset the field's
    // weight to the array key value
    // from our order array.
    $form[$field]['#weight'] = $key;
  }
}

function _dfata_course_enquiry_form_alter(&$form, &$form_state) {
  // Set the value of the Course title from the query parameter.
  $query_params = drupal_get_query_parameters();
  if (!empty($query_params['course_nid'])) {
    $nid = $query_params['course_nid'];
    $course = node_load($nid);
    if ($course->type == "course") {
      $form['submitted']['program_event_title']['#default_value'] = $course->title;
    }
  }
  $form['#validate'][] = "_dfata_course_enquiry_form_validate";
}

function _dfata_course_enquiry_form_validate($form, &$form_state) {
  // Throw an error when email addresses do not match.
  if ($form_state['values']['submitted']['email'] != $form_state['values']['submitted']['email_confirmation']) {
    form_set_error('submitted][email', t('Your emails do not match. Please fix them.'));
    form_set_error('submitted][email_confirmation');
  }
}
