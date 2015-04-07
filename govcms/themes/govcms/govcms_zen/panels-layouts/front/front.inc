<?php
/**
 * @file
 * Defines the front panel layout
 * @copyright Copyright(c) 2012 Previous Next Pty Ltd
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Nick Schuch nick at previousnext dot com dot au
 */

/**
 * Implementation of hook_panels_layouts().
 */
$plugin = array(
  'title' => t('Front Layout'),
  'category' => t('govCMS'),
  'icon' => 'front.png',
  'theme' => 'govcms_layouts_front',
  'css' => 'front.css',
  'admin css' => 'front.admin.css',
  'regions' => array(
    'header' => t('Header region'),
    'main' => t('Main region'),
    'left' => t('Left region'),
    'right' => t('Right region'),
    'sidebar' => t('Sidebar region'),
    'footer' => t('Footer region'),
  ),
);
