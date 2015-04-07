<?php
/**
 * @file
 * govcms_editing.linkit_profiles.inc
 */

/**
 * Implements hook_default_linkit_profiles().
 */
function govcms_editing_default_linkit_profiles() {
  $export = array();

  $linkit_profile = new LinkitProfile();
  $linkit_profile->disabled = FALSE; /* Edit this to true to make a default linkit_profile disabled initially */
  $linkit_profile->api_version = 1;
  $linkit_profile->name = 'wysiwyg';
  $linkit_profile->admin_title = 'WYSIWYG';
  $linkit_profile->admin_description = 'Default WYSIWYG Profile';
  $linkit_profile->profile_type = '1';
  $linkit_profile->data = array(
    'text_formats' => array(
      'rich_text' => 'rich_text',
      'plain_text' => 0,
    ),
    'search_plugins' => array(
      'entity:bean' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:comment' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:user' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:node' => array(
        'enabled' => 1,
        'weight' => '-10',
      ),
      'entity:taxonomy_term' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:file' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'entity:menu_link' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
    ),
    'entity:bean' => array(
      'result_description' => '',
      'bundles' => array(
        'basic_content' => 0,
        'image_and_text' => 0,
      ),
      'group_by_bundle' => 0,
    ),
    'entity:comment' => array(
      'result_description' => '',
      'bundles' => array(
        'comment_node_blog_article' => 0,
        'comment_node_event' => 0,
        'comment_node_media_release' => 0,
        'comment_node_news_article' => 0,
        'comment_node_footer_teaser' => 0,
        'comment_node_publication' => 0,
        'comment_node_slide' => 0,
        'comment_node_page' => 0,
        'comment_node_webform' => 0,
      ),
      'group_by_bundle' => 0,
    ),
    'entity:node' => array(
      'result_description' => '',
      'bundles' => array(
        'blog_article' => 'blog_article',
        'event' => 'event',
        'media_release' => 'media_release',
        'news_article' => 'news_article',
        'publication' => 'publication',
        'page' => 'page',
        'webform' => 'webform',
        'footer_teaser' => 0,
        'slide' => 0,
      ),
      'group_by_bundle' => 0,
      'include_unpublished' => 1,
    ),
    'entity:file' => array(
      'result_description' => '',
      'bundles' => array(
        'image' => 0,
        'video' => 0,
        'audio' => 0,
        'document' => 0,
      ),
      'group_by_bundle' => 0,
      'show_scheme' => 0,
      'group_by_scheme' => 0,
      'image_extra_info' => array(
        'thumbnail' => 'thumbnail',
        'dimensions' => 'dimensions',
      ),
    ),
    'entity:taxonomy_term' => array(
      'result_description' => '',
    ),
    'entity:user' => array(
      'result_description' => '',
    ),
    'entity:menu_link' => array(
      'result_description' => '',
      'bundles' => array(
        'main-menu' => 'main-menu',
        'features' => 0,
        'menu-footer-sub-menu' => 0,
        'management' => 0,
        'navigation' => 0,
        'menu-quick-links' => 0,
        'user-menu' => 0,
      ),
      'group_by_bundle' => 0,
    ),
    'insert_plugin' => array(
      'url_method' => '2',
    ),
    'attribute_plugins' => array(
      'accesskey' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'target' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'class' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'rel' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'id' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
      'title' => array(
        'enabled' => 0,
        'weight' => '-10',
      ),
    ),
    'autocomplete' => array(
      'charLimit' => '3',
      'wait' => '350',
      'remoteTimeout' => '10000',
    ),
  );
  $export['wysiwyg'] = $linkit_profile;

  return $export;
}
