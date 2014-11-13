<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Single column stacked'),
  'category' => t('Columns: 1'),
  'icon' => 'onecol_stacked.png',
  'theme' => 'panels_onecol_stacked',
  'css' => 'onecol_stacked.css',
  'regions' => array(
    'top' => t('Top'),
    'middle' => t('Middle'),
    'bottom' => t('Bottom'),
  ),
);
