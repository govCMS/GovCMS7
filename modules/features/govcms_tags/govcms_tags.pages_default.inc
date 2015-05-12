<?php
/**
 * @file
 * govcms_tags.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function govcms_tags_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'term_view__default';
  $handler->task = 'term_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Default taxonomy term display',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'default',
    'access' => array(
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'zen_no_wrapper';
  $display->layout_settings = array(
    'main_classes' => '',
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'a20e6821-6c5e-4e2e-a1dd-8b76b310ac33';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-31caef55-5a5e-46d2-a7fa-66144802b0c9';
    $pane->panel = 'main';
    $pane->type = 'views';
    $pane->subtype = 'govcms_taxonomy_term_page';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 1,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_default_taxonomy_term',
      'context' => array(
        0 => '',
        1 => '',
      ),
      'override_title' => 1,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '31caef55-5a5e-46d2-a7fa-66144802b0c9';
    $display->content['new-31caef55-5a5e-46d2-a7fa-66144802b0c9'] = $pane;
    $display->panels['main'][0] = 'new-31caef55-5a5e-46d2-a7fa-66144802b0c9';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-31caef55-5a5e-46d2-a7fa-66144802b0c9';
  $handler->conf['display'] = $display;
  $export['term_view__default'] = $handler;

  return $export;
}
