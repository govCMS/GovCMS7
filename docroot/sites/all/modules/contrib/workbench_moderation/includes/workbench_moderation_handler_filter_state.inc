<?php

/**
 * @file
 * Filter based on moderation state.
 */
class workbench_moderation_handler_filter_state extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Moderation status');
      $this->value_options = array_map('check_plain', workbench_moderation_state_labels());
    }
  }
}
