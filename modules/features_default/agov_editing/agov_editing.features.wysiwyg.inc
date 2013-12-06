<?php
/**
 * @file
 * agov_editing.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function agov_editing_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: full_html
  $profiles['full_html'] = array(
    'format' => 'full_html',
    'editor' => 'tinymce',
    'settings' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 1,
      'theme' => 'advanced',
      'language' => 'en',
      'buttons' => array(
        'default' => array(
          'bold' => 1,
          'italic' => 1,
          'underline' => 1,
          'strikethrough' => 1,
          'justifyleft' => 1,
          'justifycenter' => 1,
          'justifyright' => 1,
          'justifyfull' => 1,
          'bullist' => 1,
          'numlist' => 1,
          'outdent' => 1,
          'indent' => 1,
          'link' => 1,
          'unlink' => 1,
          'anchor' => 1,
          'formatselect' => 1,
          'styleselect' => 1,
          'sup' => 1,
          'sub' => 1,
          'code' => 1,
          'hr' => 1,
          'removeformat' => 1,
        ),
        'inlinepopups' => array(
          'inlinepopups' => 1,
        ),
        'paste' => array(
          'pasteword' => 1,
        ),
        'drupal' => array(
          'media' => 1,
        ),
      ),
      'toolbar_loc' => 'top',
      'toolbar_align' => 'left',
      'path_loc' => 'bottom',
      'resizing' => 1,
      'verify_html' => 1,
      'preformatted' => 0,
      'convert_fonts_to_spans' => 1,
      'remove_linebreaks' => 1,
      'apply_source_formatting' => 0,
      'paste_auto_cleanup_on_paste' => 0,
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'css_setting' => 'self',
      'css_path' => '%bprofiles/agov/modules/features_default/agov_editing/agov_editing.tinymce.css',
      'css_classes' => '',
    ),
    'rdf_mapping' => array(),
  );

  // Exported profile: rich_text
  $profiles['rich_text'] = array(
    'format' => 'rich_text',
    'editor' => 'tinymce',
    'settings' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 1,
      'theme' => 'advanced',
      'language' => 'en',
      'buttons' => array(
        'default' => array(
          'bold' => 1,
          'italic' => 1,
          'bullist' => 1,
          'numlist' => 1,
          'outdent' => 1,
          'indent' => 1,
          'link' => 1,
          'unlink' => 1,
          'formatselect' => 1,
          'styleselect' => 1,
          'sup' => 1,
          'sub' => 1,
          'blockquote' => 1,
          'removeformat' => 1,
          'charmap' => 1,
        ),
        'paste' => array(
          'pasteword' => 1,
        ),
        'drupal' => array(
          'media' => 1,
        ),
      ),
      'toolbar_loc' => 'top',
      'toolbar_align' => 'left',
      'path_loc' => 'bottom',
      'resizing' => 1,
      'verify_html' => 1,
      'preformatted' => 0,
      'convert_fonts_to_spans' => 1,
      'remove_linebreaks' => 1,
      'apply_source_formatting' => 1,
      'paste_auto_cleanup_on_paste' => 1,
      'block_formats' => 'p,h2,h3,h4,h5,h6',
      'css_setting' => 'self',
      'css_path' => '%bprofiles/agov/themes/agov/css/wysiwyg.css',
      'css_classes' => 'Image: Inline Right=img-float-right
Image: Inline Left=img-float-left',
    ),
    'rdf_mapping' => array(),
  );

  return $profiles;
}
