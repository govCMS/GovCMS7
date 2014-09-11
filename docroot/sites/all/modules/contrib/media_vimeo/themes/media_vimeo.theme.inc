<?php

/**
 * @file media_vimeo/themes/media_vimeo.theme.inc
 *
 * Theme and preprocess functions for Media: Vimeo.
 */

/**
 * Preprocess function for theme('media_vimeo_video').
 */
function media_vimeo_preprocess_media_vimeo_video(&$variables) {
  // Build the URI.
  $wrapper = file_stream_wrapper_get_instance_by_uri($variables['uri']);
  $parts = $wrapper->get_parameters();
  $variables['video_id'] = $parts['v'];

  // Make the file object available.
  $file_object = file_uri_to_object($variables['uri']);

  // Parse options and build the query string. Only add the option to the query
  // array if the option value is not default. Be careful, depending on the
  // wording in media_vimeo.formatters.inc, TRUE may be query=0.
  // @see http://developer.vimeo.com/player/embedding
  $query = array();

  // These queries default to 0. If the option is true, set value to 1.
  foreach (array('api', 'autoplay', 'loop') as $option) {
    if ($variables['options'][$option]) {
      $query[$option] = 1;
    }
  }
  // Add a query player ID and identical html ID if js API is set.
  if ($variables['options']['api']) {
    $query['player_id'] = drupal_html_id('media-vimeo-' . $variables['video_id']);
    $variables['api_id_attribute'] = 'id="' . $query['player_id'] . '" ';
  }
  else {
    $variables['api_id_attribute'] = NULL;
  }

  // These queries default to 1. If the option is false, set value to 0.
  foreach (array('portrait', 'title', 'byline') as $option) {
    if (!$variables['options'][$option]) {
      $query[$option] = 0;
    }
  }

  // Strings.
  if (isset($variables['options']['color'])) {
    $query['color'] = str_replace('#', '', $variables['options']['color']);
  }

  // Non-query options.
  if ($variables['options']['protocol_specify']) {
    $protocol = $variables['options']['protocol'];
  }
  else {
    $protocol = '//';
  }

  // Add some options as their own template variables.
  foreach (array('width', 'height') as $themevar) {
    $variables[$themevar] = $variables['options'][$themevar];
  }

  // Do something useful with the overridden attributes from the file
  // object. We ignore alt and style for now.
  if (isset($variables['options']['attributes']['class'])) {
    if (is_array($variables['options']['attributes']['class'])) {
      $variables['classes_array'] = array_merge($variables['classes_array'], $variables['options']['attributes']['class']);
    }
    else {
      // Provide nominal support for Media 1.x.
      $variables['classes_array'][] = $variables['options']['attributes']['class'];
    }
  }

  // Add template variables for accessibility.
  $variables['title'] = check_plain($file_object->filename);
  // @TODO: Find an easy/ not too expensive way to get the Vimeo description
  // to use for the alternative content.
  $variables['alternative_content'] = t('Video of @title', array('@title' => $variables['title']));

  // Build the iframe URL with options query string.
  $variables['url'] = url($protocol . 'player.vimeo.com/video/' . $variables['video_id'], array('query' => $query, 'external' => TRUE));
}
