<?php

class crumbs_Admin_ElementObject_Abstract {

  /**
   * @param array $element
   */
  function __construct($element) {
    // We do NOT store the element, because it might be replaced by other callbacks.
  }

  /**
   * @param array &$element
   *   The form element.
   * @param bool $input
   * @param array $form_state
   *
   * @return array|bool
   */
  function value_callback(&$element, $input = FALSE, $form_state = array()) {

    // TODO: What is the correct "neutral" behavior of a validation callback?
    if ($input === FALSE) {
      return isset($element['#default_value']) ? $element['#default_value'] : array();
    }
    else {
      return $input;
    }
  }

  /**
   * @param array $element
   *   The original form element.
   * @param array $form_state
   *
   * @return array
   *   The modified form element.
   */
  function process($element, $form_state) {
    return $element;
  }

  /**
   * @param array $element
   *   The original form element.
   * @param array $form_state
   *
   * @return array
   *   The modified form element.
   */
  function after_build($element, $form_state) {
    return $element;
  }

  /**
   * @param array &$element
   *   The form element.
   * @param array &$form_state
   *
   * @return bool
   *   TRUE, if validation is successful.
   */
  function validate(&$element, &$form_state) {
    // TODO: What is the correct "neutral" behavior of a validation callback?
    return TRUE;
  }

  /**
   * @param array $element
   *   The original form element.
   *
   * @return array
   *   The modified form element.
   */
  function pre_render($element) {
    return $element;
  }
}
