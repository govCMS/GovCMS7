<?php

/**
 * @file
 * Provides a link to Moderation History for Views.
 */

class workbench_moderation_handler_field_history_link extends views_handler_field_node_link {

  function render_link($data, $values) {
    // ensure user has access to view moderation history for this node.
    $node = node_load($this->get_value($values, 'nid'));
    if (!_workbench_moderation_access('view history', $node)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "node/$node->nid/moderation";
    $text = !empty($this->options['text']) ? $this->options['text'] : t('View moderation history');
    return $text;
  }
}
