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
  if ($node && $node->type == "news") {
    return TRUE;
  }
  return FALSE;
}

function _dfata_faculty_banner_info(&$vars) {
  $node = menu_get_object();
  if (!_dfata_banner_excluded($node)) {
    if ($node && $node->type == "faculty") {
      if (!empty($node->field_image)) {
        $image_file = (object) $node->field_image['und'][0];
      }
      if (!empty($node->field_colour)) {
        $bg_class = 'bg-pantone-' . $node->field_colour['und'][0]['value'];
      }
    }
    else {
      // Standard banner image fid.
      $fid = 4;
      $image_file = file_load($fid);
      $bg_class = 'standard';
    }

    if (isset($image_file) && isset($bg_class)) {
      $image = array(
        'path' => image_style_url('banner_image', $image_file->uri),
        'alt' => $image_file->alt,
        'title' => drupal_get_title(),
        'attributes' => array()
      );
      $vars['academy_banner'] = array(
        'title' => drupal_get_title(),
        'image' => theme_image($image),
        'attributes' => array('class' => array($bg_class))
      );
    }
  }
}
