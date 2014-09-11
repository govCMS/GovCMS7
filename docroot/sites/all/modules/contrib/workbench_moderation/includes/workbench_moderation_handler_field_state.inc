<?php

/**
 * Field handler to translate a moderation state into its readable form.
 */
class workbench_moderation_handler_field_state extends views_handler_field_node {
  function option_definition() {
    $options = parent::option_definition();
    $options['machine_name'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Provide machine_name option for to node type display.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['machine_name'] = array(
      '#title' => t('Output machine name'),
      '#description' => t('Display field as the moderation state machine name.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['machine_name']),
      '#fieldset' => 'more',
    );
  }

  /**
    * Render node type as human readable name, unless using machine_name option.
    */
  function render_name($data, $values) {
    if ($this->options['machine_name'] != 1 && $data !== NULL && $data !== '') {
      return t($this->sanitize_value(workbench_moderation_state_label($data)));
    }
    return $this->sanitize_value($data);
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->render_name($value, $values), $values);
  }
}
