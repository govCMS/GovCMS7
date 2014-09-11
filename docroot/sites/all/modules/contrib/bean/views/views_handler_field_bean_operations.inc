<?php

/**
 * @file
 * Definition of views_handler_field_bean_operations.
 */

/**
 * Field handler to present the contextual links of the bean block.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_bean_operations extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    $options['add_destination'] = TRUE;
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['add_destination'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add a destination parameter to contextual / operation links so users return to this View on form submission.'),
      '#default_value' => $this->options['add_destination'],
    );
  }

  function render($values) {
    if ($entity = $this->get_value($values)) {
      return $this->render_link($entity);
    }
  }

  function render_link($bean) {
    if (bean_access('edit', $bean)) {
      // Get the operations links.
      $links = menu_contextual_links('bean', 'block', array($bean->delta));

      if (!empty($links)) {
        // Add the destination to the links if specified.
        if ($this->options['add_destination']) {
          foreach ($links as $id => &$link) {
            $link['query'] = drupal_get_destination();
          }
        }

        return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
      }
    }
  }
}
