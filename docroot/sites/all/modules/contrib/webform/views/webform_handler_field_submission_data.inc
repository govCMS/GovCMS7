<?php

/**
 * @file
 * Views handler to display data value of a webform submission component.
 */

/**
 * Field handler to show if submission is draft or not.
 *
 * @ingroup views_field_handlers
 */
class webform_handler_field_submission_data extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();
    $options['format'] = array('default' => 'html');
    $options['custom_label'] = array('default' => 'default');
    $options['webform_nid'] = array('default' => NULL);
    $options['webform_cid'] = array('default' => NULL);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    form_load_include($form_state, 'inc', 'webform', 'views/webform.views');

    $form['custom_label']['#type'] = 'radios';
    $form['custom_label']['#options'] = array(
      'default' => t('Use component label'),
      'custom' => t('Custom label'),
      'none' => t('No label'),
    );
    $form['custom_label']['#default_value'] = $this->options['custom_label'];
    $form['label']['#dependency'] = array('radio:options[custom_label]' => array('custom'));

    $nid = (int) $this->options['webform_nid'];
    $cid = (int) $this->options['webform_cid'];

    // Helper function provides webform_nid and webform_cid options.
    _webform_views_options_form($form, $form_state, $nid, $cid);

    // Provide the selection for the display format.
    $form['format'] = array(
      '#type' => 'select',
      '#title' => t('Display format'),
      '#options' => array(
        'html' => t('HTML'),
        'plain' => t('Plain text'),
      ),
      '#default_value' => $this->options['format'],
    );
  }

  function options_validate(&$form, &$form_state) {
    parent::options_validate($form, $form_state);
    _webform_views_options_validate($form, $form_state);
  }

  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
    _webform_views_options_submit($form, $form_state);
  }

  /**
   * Load the node and submissions needed for this components values.
   */
  function pre_render(&$values) {
    $nid = $this->options['webform_nid'];
    $this->webform_node = node_load($nid);
    // Load all the submissions needed for this page. This is stored at the
    // view level to ensure it's available between fields so we don't load
    // them twice.
    if (!isset($this->view->_webform_submissions[$nid])) {
      module_load_include('inc', 'webform', 'includes/webform.submissions');
      $this->view->_webform_submissions[$nid] = array();
      $sids = array();
      foreach ($values as $value) {
        $sids[] = $value->{$this->field_alias};
      }
      if ($sids) {
        $this->view->_webform_submissions[$nid] = webform_get_submissions(array('sid' => $sids));
      }
    }
  }

  /**
   * Get this field's label based on the selected component.
   */
  function label() {
    if ($this->options['custom_label'] === 'default' && isset($this->options['webform_cid'])) {
      if (isset($this->webform_node)) {
        $node = $this->webform_node;
      }
      else {
        $node = node_load($this->options['webform_nid']);
      }
      if ($node && isset($node->webform['components'][$this->options['webform_cid']])) {
        $component = $node->webform['components'][$this->options['webform_cid']];
        return $component['name'];
      }
    }
    elseif ($this->options['custom_label'] === 'custom' && isset($this->options['label'])) {
      return $this->options['label'];
    }
    return '';
  }

  /**
   * Render the field using the loaded submissions from pre_render().
   */
  function render($row) {
    $sid = $this->get_value($row);
    $nid = $this->options['webform_nid'];
    $cid = $this->options['webform_cid'];
    $webform = $this->webform_node;
    if (isset($sid) && isset($webform->webform['components'][$cid])) {

      $component = $webform->webform['components'][$cid];
      $submission = $this->view->_webform_submissions[$nid][$sid];
      if ($submission->nid != $nid) {
        // The actual submission is from a different webform than the one used to define the view.
        // Rather than using the component with the same cid, try to match the form_key.
        if (!isset($this->view->_webform_components[$nid][$submission->nid][$cid])) {
          if (!isset($this->view->_webform_components[$nid][$submission->nid]['webform'])) {
            $this->view->_webform_components[$nid][$submission->nid]['webform'] = $webform;
          }
          $this->view->_webform_components[$nid][$submission->nid][$cid] = $component;
          $submission_node = node_load($submission->nid);
          foreach ($submission_node->webform['components'] as $sub_cid => $sub_component) {
            if ($sub_component['form_key'] == $component['form_key'] && $sub_component['type'] == $component['type']) {
              $this->view->_webform_components[$nid][$submission->nid]['webform'] = $submission_node;
              $this->view->_webform_components[$nid][$submission->nid][$cid] = $sub_component;
              break;
            }
          }
        }
        $webform = $this->view->_webform_components[$nid][$submission->nid]['webform'];
        $component = $this->view->_webform_components[$nid][$submission->nid][$cid];
        // Note: $nid and $cid refer to the definition webform, not the submission webform
        // whereas $component refers to the submission component.
      }

      $render = array();
      $format = $this->options['format'];

      _webform_client_form_add_component($webform, $component, NULL, $render, $render, $submission->data, $format);
      $render = $render[$component['form_key']];

      // Remove display label.
      $render['#theme_wrappers'] = array();

      return render($render);
    }
  }
}
