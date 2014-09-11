<?php

/**
 * @file
 * Hooks provided by the Draggableviews module.
 */

/**
 * If Native handler used, you can alter arguments set before saved to database.
 *
 * This can be used when you would like to exclude or add some of arguments
 * to be recorded to database. Also you can add new records to be saved to
 * database (for example for translated nodes, etc.)
 *
 * @see http://drupal.org/node/1463596#comment-5687620
 *
 * @param array $arguments
 *   Array of arguments before saving.
 * @param array $form_values
 *   Array of submitted entity ids and weights.
 * @param object $view
 *   Views object.
 */
function hook_draggableviews_handler_native_arguments_alter(&$arguments, $view, &$form_values) {}
