<?php
/**
 * @file
 * Context reaction for Metatag.
 */

class metatag_context_reaction extends context_reaction {
  function options_form($context) {
    $form = array();

    // Don't care about the instance name, the data is being managed by
    // Context and not Metatag.
    $instance = "";
    // Load the previously saved settings.
    $data = $this->fetch_from_context($context);
    if (!isset($data['metatags'])) {
      $data['metatags'] = array();
    }
    // No options currently available.
    $options = array();

    $form['help'] = array(
      '#prefix' => '<p><em>',
      '#markup' => t('Values assigned here inherit from the <a href="@url" title="Edit the global default meta tags.">global defaults</a> and will override any other meta tags assigned elsewhere.', array('@url' => url('admin/config/search/metatags/config/global'))),
      '#suffix' => '</em></p>',
    );

    $form['basic_header'] = array(
      '#prefix' => '<hr /><h3>',
      '#markup' => t('Basic tags'),
      '#suffix' => '</h3>',
    );

    // Load the basic Metatag form.
    metatag_metatags_form($form, $instance, $data['metatags'], $options);

    // Stop the meta tag fields appearing within a fieldset.
    $form['metatags']['#type'] = 'container';
    unset($form['metatags']['#collapsed']);
    unset($form['metatags']['#collapsible']);
    unset($form['#submit']);

    // Flatten the fieldsets because otherwise the Context module will not save
    // them properly.
    // TODO: Perhaps it can be done in a better way with #tree and #parents?
    foreach (array('advanced', 'dublin-core', 'open-graph') as $fieldset) {
      if (isset($form['metatags'][$fieldset])) {
        $form['metatags'][$fieldset . '_heading'] = array(
          '#prefix' => '<hr /><h3>',
          '#markup' => $form['metatags'][$fieldset]['#title'],
          '#suffix' => '</h3>',
        );
        if (isset($form['metatags'][$fieldset]['#description'])) {
          $form['metatags'][$fieldset . '_description'] = array(
            '#prefix' => '<p>',
            '#markup' => $form['metatags'][$fieldset]['#description'],
            '#suffix' => '</p>',
          );
        }
        foreach ($form['metatags'][$fieldset] as $key => $value) {
          if (substr($key, 0, 1) == '#') {
            unset ($form['metatags'][$fieldset][$key]);
            continue;
          }
          $form['metatags'][$key] = $value;
          unset($form['metatags'][$key]['#parents']);
          unset($form['metatags'][$fieldset][$key]);
        }
        unset($form['metatags'][$fieldset]);
      }
    }

    // Show all takens.
    $form['metatags']['tokens']['#token_types'] = 'all';

    $form['metatag_admin'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show on metatag admin page.'),
      '#weight' => -98,
      '#default_value' => isset($data['metatag_admin']) ? $data['metatag_admin'] : '',
    );

    return $form;
  }

  /**
   * Output a list of active contexts.
   */
  function execute() {
    $output = &drupal_static('metatag_context');

    if (!isset($output)) {
      $metatags = array();
      $output = array();
      $contexts = context_active_contexts();
      $options = array();
      $instance_names = array();

      foreach ($contexts as $context) {
        if (!empty($context->reactions['metatag_context_reaction']['metatags'])) {
          $metadata_array = $context->reactions['metatag_context_reaction']['metatags'];
          foreach ($metadata_array as $key => $data) {
            if (!empty($data['value'])) {
              $metatags[$key] = $data;//t(check_plain($data['value']));
            }
          }

          // Add this context to the list of instances.
          $instance_names[] = $context->name;
        }
      }

      // Only proceed if metatags were assigned.
      if (!empty($metatags)) {
        // Load the global defaults.
        $metatags += metatag_config_load_with_defaults('');

        // Compile the identifier for this combination based on the context
        // names.
        asort($instance_names);
        $instance = 'context:' . implode(',', $instance_names);
        $options['instance'] = $instance;

        foreach ($metatags as $metatag => $data) {
          if ($metatag_instance = metatag_get_instance($metatag, $data)) {
            $output[$metatag] = $metatag_instance->getElement($options);
          }
        }

        // Allow the output meta tags to be modified using
        // hook_metatag_metatags_view_alter().
        drupal_alter('metatag_metatags_view', $output, $instance);
      }
    }
  }
}
