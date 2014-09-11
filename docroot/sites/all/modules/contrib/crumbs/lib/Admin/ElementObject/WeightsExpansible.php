<?php

class crumbs_Admin_ElementObject_WeightsExpansible extends crumbs_Admin_ElementObject_WeightsAbstract {

  /**
   * Callback for $element['#value_callback']
   *
   * @param array $element
   * @param array|bool $input
   * @param array $form_state
   * @return array
   */
  function value_callback(&$element, $input = FALSE, $form_state = array()) {
    if ($input === FALSE) {
      return isset($element['#default_value']) ? $element['#default_value'] : array();
    }
    else {
      $weights = array();
      // Make sure that all weights are distinct and positive.
      asort($input);
      $i = 0;
      foreach ($input as $key => $weight) {
        if (is_numeric($weight)) {
          $weights[$key] = ++$i;
        }
        elseif ('disabled' === $weight) {
          $weights[$key] = FALSE;
        }
      }
      return $weights;
    }
  }

  /**
   * Callback for $element['#process']
   * Create one textfield element per rule.
   *
   * @param array $element
   * @param array $form_state
   * @return array
   */
  function process($element, $form_state) {

    /** @var crumbs_PluginSystem_PluginInfo $info */
    $info = $element['#crumbs_plugin_info'];
    $available_keys_meta = $info->availableKeysMeta;

    // Set up table rows
    /** @var crumbs_Container_MultiWildcardDataOffset $meta */
    foreach ($available_keys_meta as $key => $meta) {
      $element[$key] = array(
        '#type' => 'textfield',
        '#size' => 10,
        '#default_value' => 'inherit',
        '#class' => array('crumbs-weight-element'),
        '#crumbs_rule_info' => $meta,
      );
      if (isset($element['#value'][$key])) {
        $v = $element['#value'][$key];
        if (FALSE === $v) {
          $v = 'disabled';
        }
        elseif (-1 === $v || '-1' === $v) {
          $v = 'auto';
        }
        $element[$key]['#default_value'] = $v;
      }
    }

    // Calculate md5 hashes for keys, because javascript sucks at it.
    $keys_md5 = array();
    foreach ($available_keys_meta as $key => $meta) {
      $keys_md5[$key] = md5($key);
    }

    $settings['crumbs']['default_weights'] = $element['#crumbs_plugin_info']->defaultWeights;
    $settings['crumbs']['keys_md5'] = $keys_md5;
    $element['#attached']['js'][] = array(
      'data' => $settings,
      'type' => 'setting',
    );
    $element['#attached']['js'][] = drupal_get_path('module', 'crumbs') . '/js/crumbs.admin.expansible.js';
    $element['#attached']['css'][] = drupal_get_path('module', 'crumbs') . '/css/crumbs.admin.expansible.css';

    return $element;
  }
}
