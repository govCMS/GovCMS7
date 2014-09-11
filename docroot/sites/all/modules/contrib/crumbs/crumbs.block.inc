<?php

/**
 * Implements hook_block_info()
 */
function crumbs_block_info() {

  return array(
    'breadcrumb' => array(
      'info' => t('Breadcrumb (Crumbs)'),
      'cache' => DRUPAL_NO_CACHE,
    ),
  );
}

/**
 * Implements hook_block_view()
 *
 * @param string $delta
 *
 * @return array
 */
function crumbs_block_view($delta = '') {

  $block = array();

  switch ($delta) {
    case 'breadcrumb':
      $html = crumbs()->page->breadcrumbHtml;
      if (!empty($html)) {
        $block['content'] = $html;
      }
      break;
  }

  return $block;
}
