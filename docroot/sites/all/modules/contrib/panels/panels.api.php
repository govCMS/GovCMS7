<?php

/**
 * @file
 * Hooks provided by Panels.
 */

/**
 * Allow modules to provide their own caching mechanism for the display editor.
 *
 * @param string $argument
 *   The second half of the cache key. Full key module:TASK_NAME:HANDLER_NAME
 *   passed part: TASK_NAME:HANDLER_NAME
 * @param stdClass $cache
 *   The display to cache.
 */
function hook_panels_cache_set($argument, $cache) {
  list($handler, $item) = _panels_mini_panels_cache_get($argument);
  $item->mini_panels_display_cache = $cache;
  $handler->edit_cache_set_key($item, $argument);
}

/**
 * Allow modules to provide their own caching mechanism for the display editor.
 *
 * @param string $argument
 *   The second half of the cache key. Full key module:TASK_NAME:HANDLER_NAME
 *   passed part: TASK_NAME:HANDLER_NAME
 *
 * @return stdClass|NULL
 *   The cached display or NULL if the cache wasn't hit.
 */
function hook_panels_cache_get($argument) {
  ctools_include('common', 'panels');
  list($handler, $item) = _panels_mini_panels_cache_get($argument);
  if (isset($item->mini_panels_display_cache)) {
    return $item->mini_panels_display_cache;
  }

  $cache = new stdClass();
  $cache->display = $item->display;
  $cache->display->context = ctools_context_load_contexts($item);
  $cache->display->cache_key = 'panels_mini:' . $argument;
  $cache->content_types = panels_common_get_allowed_types('panels_mini', $cache->display->context);
  $cache->display_title = TRUE;

  // @TODO support locking.
  $cache->locked = FALSE;

  return $cache;
}

/**
 * Allow modules to provide their own caching mechanism for the display editor.
 *
 * @param string $argument
 *   The second half of the cache key. Full key module:TASK_NAME:HANDLER_NAME
 *   passed part: TASK_NAME:HANDLER_NAME
 * @param stdClass $cache
 *   The display to cache.
 *
 * @return stdClass
 *   The cached display.
 */
function hook_panels_cache_save($argument, $cache) {
  list($handler, $item) = _panels_mini_panels_cache_get($argument);
  $item->display = $cache->display;
  panels_mini_save($item);

  $handler->edit_cache_clear($item);

  return $item;
}

/**
 * Allow modules to provide their own caching mechanism for the display editor.
 *
 * @param string $argument
 *   The second half of the cache key. Full key module:TASK_NAME:HANDLER_NAME
 *   passed part: TASK_NAME:HANDLER_NAME
 * @param stdClass $cache
 *   The cached display.
 */
function hook_panels_cache_clear($argument, $cache) {
  list($handler, $item) = _panels_mini_panels_cache_get($argument);
  $handler->edit_cache_clear($item);
}

/**
 * Allow modules to adjust the rendering array of the panels dashboard.
 *
 * @param array $vars
 *   The output variables.
 */
function hook_panels_dashboard_blocks(&$vars) {
  $vars['links']['panels_node'] = array(
    'title' => l(t('Panel node'), 'node/add/panel'),
    'description' => t('Panel nodes are node content and appear in your searches, but are more limited than panel pages.'),
    'weight' => -1,
  );
}

/**
 * Allow to alter the pane content to render.
 *
 * This happens after the keyword substitution.
 *
 * @param stdClass $content
 *   The content block to render.
 * @param stdClass $pane
 *   The pane object.
 * @param array $args
 *   The display arguments.
 * @param array $contexts
 *   Array with the used contexts.
 */
function hook_panels_pane_content_alter($content, $pane, $args, $contexts) {
  // Don't display titles.
  unset($content->title);
}

/**
 * Allow modules to provide a mechanism to break locks.
 *
 * @param string $argument
 *   The second half of the cache key. Full key module:TASK_NAME:HANDLER_NAME
 *   passed part: TASK_NAME:HANDLER_NAME
 * @param stdClass $cache
 *   The cached display.
 */
function hook_panels_edit_cache_break_lock($argument, $cache) {
  $cache->locked = FALSE;
}

/**
 * Fired before a panels display is rendered.
 *
 * Last chance to modify the panels display or add output before the keyword
 * substitution runs and the panels display is rendered.
 *
 * @param panels_display $panels_display
 *   The panels display that will be rendered.
 * @param stdClass $renderer
 *   The renderer object that will be used to render.
 *
 * @return string
 *   Additional output to add before the panels display.
 */
function hook_panels_pre_render($panels_display, $renderer) {
  $translation = i18n_string_object_translate('panels_display_configuration', $panels_display);
  $panels_display->title = $translation->title;
}

/**
 * Fired after a panels display is rendered.
 *
 * Allow to add additional output after the output of the panels display.
 *
 * @param panels_display $panels_display
 *   The rendered panels display.
 * @param stdClass $renderer
 *   The used renderer object.
 *
 * @return string
 *   Additional output to add after the panels display.
 */
function hook_panels_post_render($panels_display, $renderer) {
  return t('Output proudly sponsored by panels.');
}

/**
 * Fired before a new pane is inserted in the storage.
 *
 * @param stdClass $pane
 *   Pane that will be rendered.
 */
function hook_panels_pane_insert($pane) {
  // Check if this pane has a custom title enabled.
  if (!empty($pane->configuration['override_title'])) {
    $translation_object = (object) array(
      'pid' => $pane->pid,
      'title' => $pane->configuration['override_title_text'],
    );
    $status = i18n_string_object_update('panels_pane_configuration', $translation_object);
  }
}

/**
 * Fired before a changed pane is updated in the storage.
 *
 * @param stdClass $pane
 *   Pane that will be rendered.
 */
function hook_panels_pane_update($pane) {
  // Check if this pane has a custom title enabled.
  if (!empty($pane->configuration['override_title'])) {
    $translation_object = (object) array(
      'pid' => $pane->pid,
      'title' => $pane->configuration['override_title_text'],
    );
    $status = i18n_string_object_update('panels_pane_configuration', $translation_object);
  }
}

/**
 * Fired before a panel is rendered.
 *
 * Last chance to modify the pane before the keyword substitution runs and the
 * pane is rendered.
 *
 * @param stdClass $pane
 *   Pane that will be rendered.
 */
function hook_panels_pane_prerender($pane) {
  // Check if this pane has a custom title enabled.
  if (!empty($pane->configuration['override_title'])) {
    $translation_object = (object) array(
      'pid' => $pane->pid,
      'title' => $pane->configuration['override_title_text'],
    );
    $translation_object = i18n_string_object_translate('panels_pane_configuration', $translation_object);
    $pane->configuration['override_title_text'] = $translation_object->title;
  }
}

/**
 * Fired before panes are deleted.
 *
 * @param array $pids
 *   Array with the panel id's to delete.
 */
function hook_panels_pane_delete($pids) {
  foreach ($pids as $pid) {
    // Create dummy pane with pid as property.
    $pane = (object) array('pid' => $pid);
    i18n_string_object_remove('panels_pane_configuration', $pane);
  }
}

/**
 * Fired after a display is saved.
 *
 * @param panels_display $display
 *   The display to save.
 */
function hook_panels_display_save($display) {
  i18n_string_object_update('display_configuration', $display);
}

/**
 * Fired before a display is deleted.
 *
 * @param integer $did
 *   Id of the display to delete.
 */
function hook_panels_delete_display($did) {
  $uuid = db_select('panels_display')
    ->fields('panels_display', array('uuid'))
    ->condition('did', $did)
    ->execute()
    ->fetchColumn();
  $display = (object) array('uuid' => $uuid);
  i18n_string_object_remove('display_configuration', $display);
}
