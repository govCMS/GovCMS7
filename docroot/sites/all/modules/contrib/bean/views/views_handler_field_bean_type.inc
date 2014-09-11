<?php

/**
 * @file
 * Field handler to present a type of bean.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_bean_type extends views_handler_field {
  function construct() {
    parent::construct();
  }

  function render($values) {
    if (!empty($values->bean_type)) {
      $types = bean_get_types();
      if (!empty($types[$values->bean_type])) {
        return $types[$values->bean_type]->getLabel();
      }
    }
    return '';
  }
}
