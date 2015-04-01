<?php
/**
 * @file
 * govcms_front.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function govcms_front_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'front_page';
  $page->task = 'page';
  $page->admin_title = 'Front Page';
  $page->admin_description = 'Provides a front page for govCMS.';
  $page->path = 'front';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_front_page_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'front_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'front';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'header' => NULL,
      'main' => NULL,
      'left' => NULL,
      'right' => NULL,
      'sidebar' => NULL,
      'footer' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Welcome to govCMS';
  $display->uuid = '018af563-e806-4469-95a0-52e841018e36';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-20703086-0ad1-4929-a48f-447b1028a827';
    $pane->panel = 'header';
    $pane->type = 'block';
    $pane->subtype = 'views-feature_article-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '20703086-0ad1-4929-a48f-447b1028a827';
    $display->content['new-20703086-0ad1-4929-a48f-447b1028a827'] = $pane;
    $display->panels['header'][0] = 'new-20703086-0ad1-4929-a48f-447b1028a827';
    $pane = new stdClass();
    $pane->pid = 'new-0597f166-20f3-4190-a3c4-8a27fa0fff5e';
    $pane->panel = 'left';
    $pane->type = 'views';
    $pane->subtype = 'latest_news';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0597f166-20f3-4190-a3c4-8a27fa0fff5e';
    $display->content['new-0597f166-20f3-4190-a3c4-8a27fa0fff5e'] = $pane;
    $display->panels['left'][0] = 'new-0597f166-20f3-4190-a3c4-8a27fa0fff5e';
    $pane = new stdClass();
    $pane->pid = 'new-5cbb73df-cce4-4826-9a8e-c9fd0fb2f08d';
    $pane->panel = 'main';
    $pane->type = 'bean_panels';
    $pane->subtype = 'bean_panels';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'default',
      'bean_delta' => 'about-us',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '5cbb73df-cce4-4826-9a8e-c9fd0fb2f08d';
    $display->content['new-5cbb73df-cce4-4826-9a8e-c9fd0fb2f08d'] = $pane;
    $display->panels['main'][0] = 'new-5cbb73df-cce4-4826-9a8e-c9fd0fb2f08d';
    $pane = new stdClass();
    $pane->pid = 'new-a4d4f6b5-625e-4ec5-bd87-c84d5546a9ac';
    $pane->panel = 'right';
    $pane->type = 'views';
    $pane->subtype = 'home_page_blog_articles';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'a4d4f6b5-625e-4ec5-bd87-c84d5546a9ac';
    $display->content['new-a4d4f6b5-625e-4ec5-bd87-c84d5546a9ac'] = $pane;
    $display->panels['right'][0] = 'new-a4d4f6b5-625e-4ec5-bd87-c84d5546a9ac';
    $pane = new stdClass();
    $pane->pid = 'new-a7dcde2c-c19e-4d26-a6e1-479024917c04';
    $pane->panel = 'sidebar';
    $pane->type = 'block';
    $pane->subtype = 'menu_block-2';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'a7dcde2c-c19e-4d26-a6e1-479024917c04';
    $display->content['new-a7dcde2c-c19e-4d26-a6e1-479024917c04'] = $pane;
    $display->panels['sidebar'][0] = 'new-a7dcde2c-c19e-4d26-a6e1-479024917c04';
    $pane = new stdClass();
    $pane->pid = 'new-b4fc4d0c-e043-4153-8196-83f6353044d7';
    $pane->panel = 'sidebar';
    $pane->type = 'block';
    $pane->subtype = 'menu-menu-quick-links';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'b4fc4d0c-e043-4153-8196-83f6353044d7';
    $display->content['new-b4fc4d0c-e043-4153-8196-83f6353044d7'] = $pane;
    $display->panels['sidebar'][1] = 'new-b4fc4d0c-e043-4153-8196-83f6353044d7';
    $pane = new stdClass();
    $pane->pid = 'new-7f8ceab4-2269-4e58-8af5-1b6eb307851f';
    $pane->panel = 'sidebar';
    $pane->type = 'block';
    $pane->subtype = 'govcms_social-stay_connected';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '7f8ceab4-2269-4e58-8af5-1b6eb307851f';
    $display->content['new-7f8ceab4-2269-4e58-8af5-1b6eb307851f'] = $pane;
    $display->panels['sidebar'][2] = 'new-7f8ceab4-2269-4e58-8af5-1b6eb307851f';
    $pane = new stdClass();
    $pane->pid = 'new-eb2f88a6-803e-4ec1-bbd4-ffb7a350ccb3';
    $pane->panel = 'sidebar';
    $pane->type = 'block';
    $pane->subtype = 'govcms_twitter-feed';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'eb2f88a6-803e-4ec1-bbd4-ffb7a350ccb3';
    $display->content['new-eb2f88a6-803e-4ec1-bbd4-ffb7a350ccb3'] = $pane;
    $display->panels['sidebar'][3] = 'new-eb2f88a6-803e-4ec1-bbd4-ffb7a350ccb3';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['front_page'] = $page;

  return $pages;

}
