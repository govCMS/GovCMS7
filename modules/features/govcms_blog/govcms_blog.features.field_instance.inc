<?php
/**
 * @file
 * govcms_blog.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function govcms_blog_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-blog_article-body'
  $field_instances['node-blog_article-body'] = array(
    'bundle' => 'blog_article',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The <em>Summary</em> field above is included in any listings of this page as well as the initial paragraph of the page view.
The <em>body</em> field is used for the main article content. 
',
    'display' => array(
      'blog_teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 130,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 3,
      ),
      'compact' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 200,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 1,
      ),
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 3,
      ),
      'snippet' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 130,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 200,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 3,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'display_summary' => 1,
      'required_summary' => array(
        0 => 0,
      ),
      'show_summary' => array(
        0 => 1,
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-blog_article-field_tags'
  $field_instances['node-blog_article-field_tags'] = array(
    'bundle' => 'blog_article',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Provides grouping and single word descriptions for this content.',
    'display' => array(
      'blog_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 12,
      ),
      'compact' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'full' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 4,
      ),
      'snippet' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_tags',
    'label' => 'Tags',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => 1,
        'flatten_options' => 0,
        'flatten_sort' => 1,
      ),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-blog_article-field_thumbnail'
  $field_instances['node-blog_article-field_thumbnail'] = array(
    'bundle' => 'blog_article',
    'deleted' => 0,
    'description' => 'Provides a image to be associated with this <em>Blog Article</em>.',
    'display' => array(
      'blog_teaser' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'blog_teaser_thumbnail',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'compact' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => 'content',
          'image_style' => 'thumbnail',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'article_page_620x349',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
      'full' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'article_page_620x349',
        ),
        'type' => 'image',
        'weight' => 1,
      ),
      'snippet' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'blog_teaser_thumbnail',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => 'content',
          'image_style' => 'medium',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
    ),
    'ds_extras_field_template' => '',
    'entity_type' => 'node',
    'field_name' => 'field_thumbnail',
    'label' => 'Feature Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 1,
      'default_image' => 0,
      'file_directory' => 'images/blog',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
          'vimeo' => 0,
          'youtube' => 0,
        ),
        'allowed_types' => array(
          'audio' => 0,
          'document' => 0,
          'image' => 'image',
          'video' => 0,
        ),
        'browser_plugins' => array(
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 0,
          'upload' => 0,
        ),
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('Feature Image');
  t('Provides a image to be associated with this <em>Blog Article</em>.');
  t('Provides grouping and single word descriptions for this content.');
  t('Tags');
  t('The <em>Summary</em> field above is included in any listings of this page as well as the initial paragraph of the page view.
The <em>body</em> field is used for the main article content. 
');

  return $field_instances;
}
