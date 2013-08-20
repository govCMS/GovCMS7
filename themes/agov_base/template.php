<?php
/**
 * @file
 * Template preprocessor functions for the agov theme.
 */

/**
 * Implements hook_preprocess_html().
 */
function agov_base_preprocess_html(&$vars) {

  // Make valid HTML5 + RDFa.
  $prefixes = array();
  $namespaces = explode("\n", trim($vars['rdf_namespaces']));
  foreach ($namespaces as $name) {
    list($key, $url) = explode('=', $name, 2);
    list($xml, $space) = explode(':', $key, 2);
    $url = trim($url, '"');
    if (!empty($space) && !empty($url)) {
      $prefixes[] = $space . ': ' . $url;
    }
  }
  $prefix = implode(" ", $prefixes);
  $vars['rdf_namespaces'] = ' xmlns="http://www.w3.org/1999/xhtml" prefix="' . $prefix . '"';

  // Add colour scheme css to page.
  $colour_toggle = theme_get_setting('colour_toggle');
  if ($colour_toggle == '1') {
    $colour_scheme = theme_get_setting('colour_scheme');
    drupal_add_css(drupal_get_path('theme', 'agov_base') . '/css/colour_schemes/' . $colour_scheme . '/theme-colour.css', array(
      'media' => 'screen',
      'group' => CSS_THEME
    ));
  }
  else {
    drupal_add_css(drupal_get_path('theme', variable_get('theme_default')) . '/css/colour_schemes/base/theme-colour.css', array(
      'media' => 'screen',
      'group' => CSS_THEME
    ));
  }

  // Attributes for html element.
  $vars['html_attributes_array'] = array(
    'lang' => $vars['language']->language,
    'dir' => $vars['language']->dir,
  );

}

/**
 * Override or insert variables into the html templates.
 *
 * @param array $vars
 *   An array of variables to pass to the theme template.
 */
function agov_base_process_html(&$vars) {

  // Flatten out html_attributes.
  $vars['html_attributes'] = drupal_attributes($vars['html_attributes_array']);
}

/**
 * Implements hook_preprocess_node().
 */
function agov_base_preprocess_node(&$vars) {

  unset($vars['title_attributes_array']['datatype']);
}

/**
 * Implements hook_preprocess_entity().
 */
function agov_base_preprocess_entity(&$vars) {

  // Fix invalid rdfa attributes.
  if (!empty($vars['classes_array']) && !empty($vars['attributes_array']['class'])) {
    unset($vars['attributes_array']['class']);
  }
  if (empty($vars['attributes_array']['typeof'])) {
    unset($vars['attributes_array']['typeof']);
  }
  if (!empty($vars['attributes_array']['about'])) {
    unset($vars['attributes_array']['about']);
  }
}

/**
 * Implements hook_form_alter().
 *
 * We just need to add a label to the search form.
 */
function agov_base_form_alter(&$form, &$form_state, $form_id) {

  if ($form_id == 'search_block_form') {
    // If this is the search form, set a unique id and provide a label element.
    $form['actions']['submit']['#id'] = 'edit-agov-search';
    $form['actions']['submit']['#prefix'] = '<label class="element-invisible" for="edit-agov-search">Search</label>';
  }
  elseif ($form_id == 'system_theme_settings') {
    unset($form['alpha_settings']['layout']['grid_layouts']['alpha_default']['fluid']);
    unset($form['alpha_settings']['layout']['grid_layouts']['alpha_default']['wide']);
  }
}

/**
 * Implements theme_breadcrumb().
 */
function agov_base_breadcrumb($variables) {

  $breadcrumb = $variables['breadcrumb'];
  // Remove additional breadcrumbs on search page.
  $path = explode("/", current_path());
  if ($path[0] == 'search') {
    unset($breadcrumb[1]);
    unset($breadcrumb[2]);
  }
  if (!empty($breadcrumb)) {
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    $crumbs = '<div class="breadcrumb">';
    $array_size = count($breadcrumb);
    $i = 0;
    while ($i < $array_size) {
      $crumbs .= '<span class="breadcrumb-' . $i;
      if ($i == 0) {
        $crumbs .= ' first';
      }
      $crumbs .= '">' . $breadcrumb[$i] . '</span> &raquo; ';
      $i++;
    }
    $crumbs .= '<span class="active">' . drupal_get_title() . '</span></div>';

    return $crumbs;
  }
}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function agov_base_preprocess_maintenance_page(&$variables) {

  $variables['footer'] = t('!aGov is developed by !PreviousNext', array(
    '!aGov' => l(t('aGov'), 'http://agov.com.au'),
    '!PreviousNext' => l(t('PreviousNext'), 'http://previousnext.com.au'),
  ));
}

/**
 * Overrides theme_views_more().
 */
function agov_base_views_more($variables) {

  global $base_url;
  if ($variables['view']->name == 'latest_news') {
    $link_text = 'View more news';
    $link_url = $base_url . '/news-media/news';
  }
  else {
    $link_text = check_plain($variables['link_text']);
    $link_url = $base_url . $variables['more_url'];
  }

  return '<div class="more-link">' . l($link_text, $link_url, array('attributes' => array('title' => $link_text))) . '</div>';
}

/**
 * Overrides theme_file_icon.
 *
 * @param (array) $vars
 *   Theme hook variables.
 *
 * @return string
 *   Themed output.
 */
function agov_base_file_icon(&$vars) {

  $file = $vars['file'];
  $icon_directory = $vars['icon_directory'];
  $mime = check_plain($file->filemime);
  $icon_url = file_icon_url($file, $icon_directory);
  $mime_type_parse = explode('/', $mime, 2);
  $mime_type = $mime_type_parse[1];

  return '<img class="file-icon" alt="File type ' . $mime_type . ' icon" src="' . $icon_url . '" />';
}
