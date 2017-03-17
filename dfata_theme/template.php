<?php

/**
 * @file
 * template.php
 */

// Include helper functions.
$theme_dir = drupal_get_path('theme', 'dfata_theme');
require_once $theme_dir . '/helpers.inc';

/**
 * Implements hook_html_head_alter().
 */
function dfata_theme_html_head_alter(&$head_elements) {
  // Mobile Viewport.
  $head_elements['viewport'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array('name' => 'viewport', 'content' => 'width=device-width, initial-scale=1'),
  );
  // IE Latest Browser.
  $head_elements['ie_view'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array('http-equiv' => 'x-ua-compatible', 'content' => 'ie=edge'),
  );
}

/**
 * Implements hook_js_alter().
 */
function dfata_theme_js_alter(&$javascript) {
  // We need jQuery 1.7.2 so that we can have OwlCarousel working, as well as Panesl IPE.
  $javascript['misc/jquery.js']['data'] = drupal_get_path('theme', 'dfata_theme') . '/vendor/jquery/jquery-1.7.2.min.js';
}

/**
 * Implements hook_css_alter().
 */
function dfata_theme_css_alter(&$css) {
  // Remove the jQuery UI styling.
  unset($css['misc/ui/jquery.ui.core.css']);
  unset($css['misc/ui/jquery.ui.theme.css']);
  unset($css['misc/ui/jquery.ui.accordion.css']);
}

/**
 * Implements hook_preprocess_page().
 */
function dfata_theme_preprocess_page(&$variables) {
  // Sets the Government crest path.
  $variables['gov_logo'] = '';
  $gov_logo_path = path_to_theme() . '/gov-logo.png';
  if (file_exists($gov_logo_path)) {
    $variables['gov_logo'] = '/' . $gov_logo_path;
  }

  _dfata_faculty_banner_info($variables);
}

/**
 * Implements hook_preprocess_html().
 */
function dfata_theme_preprocess_html(&$variables) {
  drupal_add_js("(function(h) {h.className = h.className.replace('no-js', '') })(document.documentElement);", array('type' => 'inline', 'scope' => 'header'));
  drupal_add_js('jQuery.extend(Drupal.settings, { "pathToTheme": "' . path_to_theme() . '" });', 'inline');
}

/**
 * Implements hook_preprocess_field().
 */
function dfata_theme_preprocess_field(&$variables) {
  // Bean 'Image and Text' field 'Link To' to show 'Read [title]' text.
  if ($variables['element']['#field_name'] === 'field_link_to' && $variables['element']['#bundle'] === 'image_and_text') {
    if (!empty($variables['items'][0]) && !empty($variables['element']['#object']->title)) {
      // This only applies if field has a non-configurable title.
      if ($variables['items'][0]['#field']['settings']['title'] === 'none') {
        $variables['items'][0]['#element']['title'] = t('Read !title', array('!title' => $variables['element']['#object']->title));
      }
    }
  }
  if (theme_get_setting('dfata_theme_override_image_styles') == 1) {
    // Define custom image style for image banners on home page.
    if ($variables['element']['#field_name'] === 'field_slide_image') {
      if ($variables['items'][0]['#image_style'] === 'feature_article') {
        $variables['items'][0]['#image_style'] = 'dfata_theme_banner';
      }
    }
    // Define custom image style for thumbnails on news / blogs / etc.
    elseif ($variables['element']['#field_name'] === 'field_thumbnail') {
      $image_style = $variables['items'][0]['#image_style'];
      if ($image_style === 'medium' || $image_style === 'thumbnail') {
        $variables['items'][0]['#image_style'] = 'dfata_theme_thumbnail';
      }
    }
    // Define custom image style for views.
    elseif ($variables['element']['#field_name'] === 'field_image') {
      if ($variables['items'][0]['#image_style'] === 'medium') {
        $variables['items'][0]['#image_style'] = 'dfata_theme_thumbnail';
      }
    }
  }
  if ($variables['element']['#field_name'] === 'field_page_content') {
    // Load jQuery UI Accordion for the field.
    $variables['items'][0]['#attached'] = array(
      'library' => array(
        array('system', 'ui.accordion'),
      ),
    );
  }
  if ($variables['element']['#field_name'] === 'field_title' && $variables['element']['#bundle'] == "paragraph_with_title") {
    // Surround the title with an <h3> tag.
    $variables['items'][0]['#markup'] = '<h3>' . $variables['items'][0]['#markup'] . '</h3>';
  }
}

/**
 * Implements hook_views_pre_render().
 */
function dfata_theme_views_pre_render(&$variables) {
  if (theme_get_setting('dfata_theme_override_image_styles') == 1) {
    if ($variables->name === 'footer_teaser') {
      $len = count($variables->result);
      for ($i = 0; $i < $len; $i++) {
        if (!empty($variables->result[$i]->field_field_image)) {
          // Define custom image style for thumbnails on footer_teaser.
          if ($variables->result[$i]->field_field_image[0]['rendered']['#image_style'] == 'blog_teaser_thumbnail') {
            $variables->result[$i]->field_field_image[0]['rendered']['#image_style'] = 'dfata_theme_thumbnail';
          }
        }
      }
    }
  }
}

/**
 * Implements hook_image_styles_alter().
 */
function dfata_theme_image_styles_alter(&$styles) {
  if (theme_get_setting('dfata_theme_override_image_styles') == 1) {
    $styles['dfata_theme_banner'] = array(
      'label' => 'govCMS UI-KIT - Banner',
      'name' => 'dfata_theme_banner',
      'storage' => IMAGE_STORAGE_NORMAL,
      'effects' => array(
        array(
          'label' => 'Scale and crop',
          'name' => 'image_scale_and_crop',
          'data' => array(
            'width' => 1650,
            'height' => 440,
            'upscale' => 1,
          ),
          'effect callback' => 'image_scale_and_crop_effect',
          'dimensions callback' => 'image_resize_dimensions',
          'form callback' => 'image_resize_form',
          'summary theme' => 'image_resize_summary',
          'module' => 'image',
          'weight' => 0,
        ),
      ),
    );
    $styles['dfata_theme_thumbnail'] = array(
      'label' => 'govCMS UI-KIT - Thumbnail',
      'name' => 'dfata_theme_thumbnail',
      'storage' => IMAGE_STORAGE_NORMAL,
      'effects' => array(
        array(
          'label' => 'Scale and crop',
          'name' => 'image_scale_and_crop',
          'data' => array(
            'width' => 370,
            'height' => 275,
            'upscale' => 1,
          ),
          'effect callback' => 'image_scale_and_crop_effect',
          'dimensions callback' => 'image_resize_dimensions',
          'form callback' => 'image_resize_form',
          'summary theme' => 'image_resize_summary',
          'module' => 'image',
          'weight' => 0,
        ),
      ),
    );
  }
  return $styles;
}

/**
 * Implements hook_preprocess_node().
 */
function dfata_theme_preprocess_node(&$variables) {
  if ($variables['view_mode'] === 'teaser' || $variables['view_mode'] === 'compact') {
    // Apply thumbnail class to node teaser view if image exists.
    $has_thumb = !empty($variables['content']['field_thumbnail']);
    $has_image = !empty($variables['content']['field_image']);
    $has_featured_image = !empty($variables['content']['field_feature_image']);
    if ($has_thumb || $has_image || $has_featured_image) {
      $variables['classes_array'][] = 'has-thumbnail';
    }
  }

  if ($variables['type'] === 'webform') {
    // Hide submitted date on webforms.
    $variables['display_submitted'] = FALSE;
  }
}

/**
 * Implements theme_breadcrumb().
 */
function dfata_theme_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $output = '';

  if (!empty($breadcrumb)) {
    // Build the breadcrumb trail.
    $output = '<nav class="breadcrumbs--inverted" role="navigation" aria-label="breadcrumb">';
    $output .= '<ul><li>' . implode('</li><li>', $breadcrumb) . '</li></ul>';
    $output .= '</nav>';
  }

  return $output;
}

/**
 * Implements hook_form_alter().
 */
function dfata_theme_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case "search_api_page_search_form_default_search":
      // Global header form.
      $form['keys_1']['#attributes']['placeholder'] = t('Type search term here');
      $form['keys_1']['#title'] = t('Search field');
      break;
    case "search_api_page_search_form":
      // Search page (above results) form.
      $form['form']['keys_1']['#title'] = t('Type search term here');
      break;
    case "search_form":
      // Search form on page not found (404 page).
      $form['basic']['keys']['#title'] = t('Type search term here');
      break;
    case "contact_site_form":
      _dfata_contact_form_alter($form, $form_state);
      break;
  }

  if (!empty($form['#node']) && $form['#node']->machine_name == "course_enquiry") {
    _dfata_course_enquiry_form_alter($form, $form_state);
  }
}

/**
 * Implements theme_preprocess_search_api_page_result().
 */
function dfata_theme_preprocess_search_api_page_result(&$variables) {
  // Strip out HTML tags from search results.
  $variables['snippet'] = strip_tags($variables['snippet']);
  // Remove the author / date from the result display.
  $variables['info'] = '';
}

/**
 * Implements theme_preprocess_search_result().
 */
function dfata_theme_preprocess_search_result(&$variables) {
  // Strip out HTML tags from search results (404 page).
  $variables['snippet'] = strip_tags($variables['snippet']);
  // Remove the author / date from the result display (404 page).
  $variables['info'] = '';
}

/**
 * Implements hook_ds_pre_render_alter.
 */
function dfata_theme_ds_pre_render_alter(&$layout_render_array, $context) {
  $is_bean = $context['entity_type'] == "bean";
  $is_image_text = $context['bundle'] == "image_and_text";
  $is_homepage_tile = $context['view_mode'] == "homepage_tile";
  if ($is_bean && $is_image_text && $is_homepage_tile) {
    $title = '<h2>' . $context['entity']->title . '</h2>';
    // Remove link options and replace the link path.
    unset($layout_render_array['ds_content'][0][0]['#path']['options']);
    unset($layout_render_array['ds_content'][0][0]['#path']['path']);
    if (!empty($context['entity']->field_link_to)) {
      $url = $context['entity']->field_link_to['und'][0]['url'];
      $layout_render_array['ds_content'][0][0]['#path']['path'] = $url;
      $title = l($title, $url, array(
        'html' => TRUE,
        'attributes' => array(
          'title' => $context['entity']->title,
        ),
      ));
    }
    $layout_render_array['ds_content'][1] = array(
      '#markup' => $title
    );
  }

  $is_node = $context['entity_type'] == "node";
  $is_full = $context['view_mode'] == "full";
  if ($is_node && $is_full) {
    $node = $context['entity'];
    // If the actual summary field is empty,
    // do not display the trimmed body in the DS Summary field.
    if (empty($node->body['und'][0]['summary'])) {
      foreach ($layout_render_array['ds_content'] as &$field) {
        if (!empty($field['#field_name']) && $field['#field_name'] == "summary") {
          $field[0]['#markup'] = '';
          break;
        }
      }
    }

    if ($node->type == "course") {
      if (!empty($node->field_enquiry) && $node->field_enquiry['und'][0]['value']) {
        $enquiry_url = l('here', 'course-enquiry', array('query' => array('course_nid' => $node->nid)));
        $markup = '<div><h3>Enquire Now</h3>';
        $markup .= '<div>Click ' . $enquiry_url . ' to enquire about this course.</div>';
        $markup .= '</div>';
        foreach ($layout_render_array['ds_content'] as &$field) {
          if (!empty($field['#field_name']) && $field['#field_name'] == "field_enquiry") {
            $field[0]['#markup'] = $markup;
            break;
          }
        }
      }
    }
  }

  $is_tile = $context['view_mode'] == "tile";
  if ($is_node && $is_tile) {
    $node = $context['entity'];
    // Add a link around the Faculty tile to make the whole image clickable.
    if ($node->type == "faculty") {
      $markup = $layout_render_array['ds_content'][0]['field_badge'][0]['#markup'];
      $link = l($markup, 'node/' . $node->nid, array('html' => TRUE));
      $layout_render_array['ds_content'][0]['field_badge'][0]['#markup'] = $link;
    }
  }
}

/**
 * Implements hook_mail_alter.
 *
 * @see _dfata_contact_form_alter()
 */
function dfata_theme_mail_alter(&$message) {
  // Alter the Contact Page emails to include our custom fields.
  if ($message['id'] == 'contact_page_mail' || $message['id'] == 'contact_page_copy') {
    $message['body'][1] = t('First Name') . ': ' . $message['params']['name'];
    $message['body'][] = t('Surname') . ': ' . $message['params']['surname'];
    $message['body'][] = t('Email') . ': ' . $message['params']['mail'];
    $message['body'][] = t('Phone number') . ': ' . $message['params']['phone'];
    $message['body'][] = $message['params']['message'];
  }
}
