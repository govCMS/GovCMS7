<?php

/**
 * @file
 * Contains template preprocess files for the add content modal themes.
 */

/**
 * Preprocess the primary entry level theme.
 */
function template_preprocess_panels_add_content_modal(&$vars) {
  // Process the list of categories.
  foreach ($vars['categories'] as $key => $category_info) {
    // 'root' category is actually displayed under the categories, so
    // skip it.
    if ($key == 'root') {
      continue;
    }

    $class = 'panels-modal-add-category';
    if ($key == $vars['category']) {
      $class .= ' active';
    }

    $url = $vars['renderer']->get_url('select-content', $vars['region'], $key);
    $vars['categories_array'][] = ctools_ajax_text_button($category_info['title'], $url, '', $class);
  }

  // Now render the top level buttons (aka the root category) if any.
  $vars['root_content'] = '';
  if (!empty($vars['categories']['root'])) {
    foreach ($vars['categories']['root']['content'] as $content_type) {
      $vars['root_content'] .= theme('panels_add_content_link', array('renderer' => $vars['renderer'], 'region' => $vars['region'], 'content_type' => $content_type));
    }
  }
}

/**
 * Process the panels add content modal.
 *
 * This is run here so that preprocess can make changes before links are
 * actually rendered.
 */
function template_process_panels_add_content_modal(&$vars) {
  $content = !empty($vars['categories'][$vars['category']]['content']) ? $vars['categories'][$vars['category']]['content'] : array();

  // If no category is selected or the category is empty or our special empty
  // category render a 'header' that will appear instead of the columns.
  if (empty($vars['category']) || empty($content) || $vars['category'] == 'root') {
    $vars['header'] = t('Content options are divided by category. Please select a category from the left to proceed.');
  }
  else {
    $titles = array_keys($content);
    natcasesort($titles);

    // This will default to 2 columns in the theme definition but could be
    // changed by a preprocess. Ensure there is at least one column.
    $columns = max(1, $vars['column_count']);
    $vars['columns'] = array_fill(1, $columns, '');

    $col_size = count($titles) / $columns;
    $count = 0;
    foreach ($titles as $title) {
      $which = floor($count++ / $col_size) + 1;
      $vars['columns'][$which] .= theme('panels_add_content_link', array('renderer' => $vars['renderer'], 'region' => $vars['region'], 'content_type' => $content[$title]));
    }
  }

  $vars['messages'] = theme('status_messages');
}

/**
 * Preprocess the add content link used in the modal.
 */
function template_preprocess_panels_add_content_link(&$vars) {
  $vars['title'] = filter_xss_admin($vars['content_type']['title']);
  $vars['description'] = isset($vars['content_type']['description']) ? $vars['content_type']['description'] : $vars['title'];
  $vars['icon'] = ctools_content_admin_icon($vars['content_type']);
  $vars['url'] = $vars['renderer']->get_url('add-pane', $vars['region'], $vars['content_type']['type_name'], $vars['content_type']['subtype_name']);

  $vars['image_button'] = ctools_ajax_image_button($vars['icon'], $vars['url'], $vars['description'], 'panels-modal-add-config');
  $vars['text_button'] = ctools_ajax_text_button($vars['title'], $vars['url'], $vars['description'], 'panels-modal-add-config');
}
