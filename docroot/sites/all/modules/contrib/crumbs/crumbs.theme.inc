<?php

/**
 * Replacement theme callback for theme('breadcrumb').
 *
 * @param $variables
 * @return string|null
 *   Rendered breadcrumb HTML
 */
function crumbs_theme_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (empty($breadcrumb)) {
    return NULL;
  }

  // These settings may be missing, if theme('breadcrumb') is called from
  // somewhere outside of Crumbs, or if another module is messing with the theme
  // registry.
  $variables += array(
    'crumbs_trailing_separator' => FALSE,
    'crumbs_separator' => ' &raquo; ',
    'crumbs_separator_span' => FALSE,
  );

  $separator = $variables['crumbs_separator'];
  if ($variables['crumbs_separator_span']) {
    $separator = '<span class="crumbs-separator">' . $separator . '</span>';
  }

  $output = implode($separator, $breadcrumb);
  if ($variables['crumbs_trailing_separator']) {
    $output .= $separator;
  }

  $output = '<div class="breadcrumb">' . $output . '</div>';

  // Provide a navigational heading to give context for breadcrumb links to
  // screen-reader users. Make the heading invisible with .element-invisible.
  return '<h2 class="element-invisible">' . t('You are here') . '</h2>' . $output;
}

/**
 * Default theme implementation for theme('crumbs_breadcrumb_link').
 *
 * @param array $item
 *
 * @return string
 */
function theme_crumbs_breadcrumb_link(array $item) {
  if ('<nolink>' === $item['href']) {
    return check_plain($item['title']);
  }
  else {
    $options = isset($item['localized_options']) ? $item['localized_options'] : array();
    return l($item['title'], $item['href'], $options);
  }
}

/**
 * Default theme implementation for theme('crumbs_breadcrumb_current_page').
 *
 * @param array $variables
 *
 * @return string
 */
function theme_crumbs_breadcrumb_current_page(array $variables) {
  $item = $variables['item'];
  switch ($variables['show_current_page']) {
    case CRUMBS_SHOW_CURRENT_PAGE_SPAN:
      return '<span class="crumbs-current-page">' . check_plain($item['title']) . '</span>';
    case CRUMBS_SHOW_CURRENT_PAGE_LINK:
      $options = isset($item['localized_options']) ? $item['localized_options'] : array();
      return l($item['title'], $item['href'], $options);
    default:
      return check_plain($item['title']);
  }
}
