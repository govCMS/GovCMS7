<?php

/**
 * @file
 * Custom handler for wcag_scheduler that sets a link to external reports.
 */

class wcag_scheduler_handler_field_url extends views_handler_field_url {

  /**
   * Render results.
   */
  function render($values) {
    $server_base = variable_get('wcag_validate_server_base', wcag_validate_get_config('wcag_validate_server_base'));

    $value = $this->get_value($values);
    if (!empty($this->options['display_as_link'])) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = $server_base . '/view?id=' . $value;
      $text = !empty($this->options['text']) ? $this->sanitize_value($this->options['text']) : $this->sanitize_value($value, 'url');
      return $text;
    }
    else {
      return $this->sanitize_value($value, 'url');
    }
  }
}
