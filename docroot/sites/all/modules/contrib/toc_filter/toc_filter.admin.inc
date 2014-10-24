<?php
/**
 * @file
 * Administration pages for the 'TOC filter' module.
 */

/**
 * Form builder; Settings page for the 'TOC filter' module.
 *
 * @ingroup forms
 */
function toc_filter_admin_settings() {
  $form['toc_filter_header_tag'] = array(
    '#type' => 'select',
    '#title' => t('Header tag'),
    '#description' => t('The selected header tag is used to generate the table of contents when the TOC filter is assigned to an input format.'),
    '#options' => array(
      'h1' => 'h1',
      'h2' => 'h2',
      'h3' => 'h3',
      'h4' => 'h4',
      'h5' => 'h5',
      'h6' => 'h6',
    ),
    '#required' => 1,
    '#default_value' => variable_get('toc_filter_header_tag', 'h3')
  );

  $form['toc_filter_ul_default_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Un-order list default title'),
    '#default_value' => variable_get('toc_filter_ul_default_title', '')
  );

  $form['toc_filter_ol_default_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Order list default title'),
    '#default_value' => variable_get('toc_filter_ol_default_title', '')
  );

  $form['toc_filter_faq_default_title'] = array(
    '#type' => 'textfield',
    '#title' => t('FAQ default title'),
    '#default_value' => variable_get('toc_filter_faq_default_title', '')
  );

  $form['toc_filter_smooth_scroll'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable smooth scrolling'),
    '#description' => t('Smooth scrolling will be applied to all anchor links'),
    '#default_value' => variable_get('toc_filter_smooth_scroll', '1')
  );

  $form['toc_filter_smooth_scroll_duration'] = array(
    '#type' => 'select',
    '#title' => t('Smooth scrolling duration'),
    '#default_value' => variable_get('toc_filter_smooth_scroll_duration', ''),
    '#options' => array(
      'slow' => 'slow',
      '' => 'medium',
      'fast' => 'fast',
    ),
  );

  return system_settings_form($form);
}
