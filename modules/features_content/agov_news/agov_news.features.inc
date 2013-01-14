<?php
/**
 * @file
 * agov_news.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function agov_news_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function agov_news_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function agov_news_image_default_styles() {
  $styles = array();

  // Exported image style: feature_article.
  $styles['feature_article'] = array(
    'name' => 'feature_article',
    'effects' => array(
      7 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '640',
          'height' => '280',
        ),
        'weight' => '2',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function agov_news_node_info() {
  $items = array(
    'news_article' => array(
      'name' => t('News Article'),
      'base' => 'node_content',
      'description' => t('Use <em>News articles</em> to keep your audience up-to-date with the latest news. Articles flagged as "Featured" will be shown on the front page slideshow. Articles flagged "Promoted to front page" will appear in the "Latest News" section of the front page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
