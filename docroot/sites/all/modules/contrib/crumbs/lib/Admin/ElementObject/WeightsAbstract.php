<?php

class crumbs_Admin_ElementObject_WeightsAbstract extends crumbs_Admin_ElementObject_Abstract {

  /**
   * Callback for $element['#element_validate']
   *
   * @param array $element
   * @param array $form_state
   *
   * @return bool|void
   */
  function validate(&$element, &$form_state) {
    // We need to unset the NULL values from child elements we created.
    $weights = $element['#value'];
    form_set_value($element, $weights, $form_state);
  }
}
