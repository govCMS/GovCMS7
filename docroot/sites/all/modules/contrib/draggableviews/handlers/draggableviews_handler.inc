<?php

/**
 * @file
 * Base plugin implementation.
 */

/**
 * Parent class for all handlers.
 */
class draggableviews_handler {

  /**
   * Get the weight value.
   *
   * @param object $field
   *   Draggableviews field handler. View is $field->view,
   *   to get a row $field->view->result[$index].
   * @param int $index
   *   Index of the row.
   *
   * @return int
   *   Weight value.
   */
  public function get($field, $index) {}

  /**
   * Save weight value.
   *
   * @param $form_state
   *   Attay of form state of the form.
   *   View object $form_state['values']['view'].
   */
  public function set($form_state) {}

  /**
   * Form with settings of the handler.
   *
   * @param object $field
   *  Draggableviews field handler.
   *
   * @return array
   *  Form array.
   */
  public function options_form($field) {}

  /**
   * Settings form default values.
   *
   * @return array
   *   Array with default values.
   */
  public function option_definition() {}
}