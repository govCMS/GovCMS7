<?php

class crumbs_Admin_ElementObject_WeightsTabledrag extends crumbs_Admin_ElementObject_WeightsAbstract {

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
      $i = 0;
      $section_key = NULL;
      foreach ($input as $row_key => $row_values) {
        if (substr($row_key, 0, 9) === 'sections.') {
          $section_key = substr($row_key, 9);
          if ($section_key === 'auto') {
            break;
          }
        }
        elseif (substr($row_key, 0, 6) === 'rules.') {
          $key = substr($row_key, 6);
          if ($section_key === 'enabled') {
            $weights[$key] = ++$i;
          }
          elseif ($section_key === 'disabled') {
            $weights[$key] = FALSE;
          }
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
   *
   * @return array
   */
  function process($element, $form_state) {

    /** @var crumbs_PluginSystem_PluginInfo $info */
    $info = $element['#crumbs_plugin_info'];
    $default_weights = $info->defaultWeights;
    $available_keys_meta = $info->availableKeysMeta;

    $sections = array(
      'enabled' => t('Enabled'),
      'disabled' => t('Disabled'),
    );

    foreach ($default_weights as $value) {
      if (FALSE === $value) {
        $sections['default:disabled'] =  t('Disabled by default');
      }
      else {
        $sections["default:$value"] =  t('!key:&nbsp;!value', array(
          '!key' => t('Default weight'),
          '!value' => t('Disabled'),
        ));
      }
    }

    $sections['inherit'] = t('Inherit');

    // Set up sections
    foreach ($sections as $section_key => $section_title) {
      $element["sections.$section_key"] = array(
        '#tree' => TRUE,
        '#title' => $section_title,
        'weight' => array(
          '#type' => 'hidden',
          '#default_value' => 'section',
        ),
        '#section_key' => $section_key,
      );
    }

    // Set up tabledrag rows
    foreach ($available_keys_meta as $key => $meta) {
      $child = array(
        '#title' => $key,
        'weight' => array(
          '#type' => 'textfield',
          '#size' => 10,
          '#default_value' => -1,
          '#class' => array('crumbs-weight-element'),
        ),
        '#section_key' => 'inherit',
        '#crumbs_rule_info' => $meta,
      );
      $element["rules.$key"] = $child;
    }

    foreach ($default_weights as $key => $value) {
      if (FALSE === $value) {
        $element["rules.$key"]['#section_key'] = 'default:disabled';
      }
      else {
        $element["rules.$key"]['#section_key'] = "default:$value";
      }
    }

    if (is_array($element['#value'])) {
      foreach ($element['#value'] as $key => $value) {
        if (isset($element["rules.$key"])) {
          $child = &$element["rules.$key"];
          if (FALSE === $value) {
            $child['#section_key'] = 'disabled';
          }
          elseif (is_numeric($value)) {
            $child['weight']['#default_value'] = $value;
            $child['#section_key'] = 'enabled';
          }
        }
      }
    }

    return $element;
  }
}
