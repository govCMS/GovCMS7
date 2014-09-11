<?php
/**
 * @file
 * Custom tokens for Metatag.
 */

/**
 * Implements hook_tokens_alter().
 *
 * Fix [node:summary] until http://drupal.org/node/1295524 is committed, this
 * code is retrofitted from the patches in that issue.
 */
function metatag_tokens_alter(array &$replacements, array $context) {
  // Only proceed if this is working on a node.
  if ($context['type'] == 'node' && !empty($context['data']['node'])) {
    // Loop through each of the tokens.
    foreach ($context['tokens'] as $name => $original) {
      // Only deal with the 'node:summary' token, that's the one being fixed.
      if ($name == 'summary') {
        // A shortcut to the node being processed.
        $node = $context['data']['node'];

        // Work out the langcode being used.
        if (isset($context['options']['language'])) {
          $langcode = $context['options']['language']->language;
        }
        else {
          $langcode = NULL;
        }

        // Decide whether the string needs to be sanitized.
        $sanitize = !empty($context['options']['sanitize']);

        if ($items = field_get_items('node', $node, 'body', $langcode)) {
          $instance = field_info_instance('node', 'body', $node->type);
          $field_langcode = field_language('node', $node, 'body', $langcode);

          // If the summary is not empty, use it.
          if (!empty($items[0]['summary'])) {
            $output = $sanitize ? _text_sanitize($instance, $field_langcode, $items[0], 'summary') : $items[0]['summary'];
          }

          // Attempt to provide a suitable version of the 'body' field.
          else {
            $output = $sanitize ? _text_sanitize($instance, $field_langcode, $items[0], 'value') : $items[0]['value'];
            // A summary was requested.
            if ($name == 'summary') {
              if (isset($instance['display']['teaser']['settings']['trim_length'])) {
                $trim_length = $instance['display']['teaser']['settings']['trim_length'];
              }
              else {
                // Use default value.
                $trim_length = NULL;
              }
              // Generate an optionally trimmed summary of the body field.
              $output = text_summary($output, $instance['settings']['text_processing'] ? $items[0]['format'] : NULL, $trim_length);
            }
          }

          // Override the original value.
          $replacements[$original] = $output;
        }
      }
    }
  }
}
