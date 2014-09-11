<?php

/**
 * @file
 * Provides moderation links for Views.
 */

class workbench_moderation_handler_field_links extends views_handler_field {
  function render($values) {
    if ($values->{$this->aliases['current']}) {
      $node = node_load($values->{$this->aliases['nid']}, $values->{$this->aliases['vid']});
      return theme('links', array('links' => workbench_moderation_get_moderation_links($node, array('html' => TRUE, 'query' => array('destination' => $_GET['q'])))));
    }
    return '';
  }
}
