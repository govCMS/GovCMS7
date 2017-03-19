<?php
/**
 * @file
 *  Contains logic for the theme.
 */

/**
 * Implements hook_form_alter().
 */
function dfata_admin_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    // Add character count for Summary in News edit form.
    case "news_article_node_form":
      $form['body']['und'][0]['summary']['#attributes']['class'][] = 'add-character-count';
      $form['body']['und'][0]['summary']['#attached']['js'][] = array(
        'data' => '/' . drupal_get_path('theme', 'dfata_admin') . '/js/character-count.js',
        'type' => 'file',
      );
      break;
  }
}
