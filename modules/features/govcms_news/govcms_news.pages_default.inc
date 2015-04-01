<?php
/**
 * @file
 * govcms_news.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function govcms_news_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'news_media';
  $page->task = 'page';
  $page->admin_title = 'News & Media';
  $page->admin_description = 'Provides News & Media page.';
  $page->path = 'news-media';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'normal',
    'title' => 'News & Media',
    'name' => 'main-menu',
    'weight' => '-46',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_news_media_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'news_media';
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
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'News & Media';
  $display->uuid = '4baeaa24-4eeb-4753-a9ac-786200ce92b9';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-98cc6888-a918-421b-b9b4-0d2874cd7701';
    $pane->panel = 'middle';
    $pane->type = 'bean_panels';
    $pane->subtype = 'bean_panels';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'highlight',
      'bean_delta' => 'news-and-media-intro',
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
    $pane->uuid = '98cc6888-a918-421b-b9b4-0d2874cd7701';
    $display->content['new-98cc6888-a918-421b-b9b4-0d2874cd7701'] = $pane;
    $display->panels['middle'][0] = 'new-98cc6888-a918-421b-b9b4-0d2874cd7701';
    $pane = new stdClass();
    $pane->pid = 'new-5b9c039e-64e6-4157-82de-dbfbda35d676';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'bean-news';
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
    $pane->uuid = '5b9c039e-64e6-4157-82de-dbfbda35d676';
    $display->content['new-5b9c039e-64e6-4157-82de-dbfbda35d676'] = $pane;
    $display->panels['middle'][1] = 'new-5b9c039e-64e6-4157-82de-dbfbda35d676';
    $pane = new stdClass();
    $pane->pid = 'new-288c494d-6ee7-449b-9beb-a19fc3c3024c';
    $pane->panel = 'middle';
    $pane->type = 'bean_panels';
    $pane->subtype = 'bean_panels';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'default',
      'bean_delta' => 'events',
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
    $pane->uuid = '288c494d-6ee7-449b-9beb-a19fc3c3024c';
    $display->content['new-288c494d-6ee7-449b-9beb-a19fc3c3024c'] = $pane;
    $display->panels['middle'][2] = 'new-288c494d-6ee7-449b-9beb-a19fc3c3024c';
    $pane = new stdClass();
    $pane->pid = 'new-a8040550-f37e-437c-9446-61f0a9350f61';
    $pane->panel = 'middle';
    $pane->type = 'bean_panels';
    $pane->subtype = 'bean_panels';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'default',
      'bean_delta' => 'media-releases',
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
    $pane->uuid = 'a8040550-f37e-437c-9446-61f0a9350f61';
    $display->content['new-a8040550-f37e-437c-9446-61f0a9350f61'] = $pane;
    $display->panels['middle'][3] = 'new-a8040550-f37e-437c-9446-61f0a9350f61';
    $pane = new stdClass();
    $pane->pid = 'new-8fd25fe8-ffb7-4d6a-b694-740c53d9a668';
    $pane->panel = 'middle';
    $pane->type = 'bean_panels';
    $pane->subtype = 'bean_panels';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'default',
      'bean_delta' => 'blog',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = '8fd25fe8-ffb7-4d6a-b694-740c53d9a668';
    $display->content['new-8fd25fe8-ffb7-4d6a-b694-740c53d9a668'] = $pane;
    $display->panels['middle'][4] = 'new-8fd25fe8-ffb7-4d6a-b694-740c53d9a668';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['news_media'] = $page;

  return $pages;

}
