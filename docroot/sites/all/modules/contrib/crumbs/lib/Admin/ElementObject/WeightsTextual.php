<?php

class crumbs_Admin_ElementObject_WeightsTextual extends crumbs_Admin_ElementObject_WeightsAbstract {

  /**
   * Callback for $element['#value_callback']
   *
   * @param array $element
   * @param bool $input
   * @param array $form_state
   *
   * @return array|bool
   */
  function value_callback(&$element, $input = FALSE, $form_state = array()) {

    if (FALSE === $input) {
      return isset($element['#default_value']) ? $element['#default_value'] : array();
    }

    /** @var crumbs_PluginSystem_PluginInfo $info */
    $info = $element['#crumbs_plugin_info'];
    $available_keys_meta = $info->availableKeysMeta;

    $weights = array();
    $weight = 0;
    foreach (explode("\n", $input['text']) as $line) {
      $line = trim($line);
      list($key, $title) = explode(' ', $line, 2) + array(NULL, NULL);
      if (isset($available_keys_meta[$key])) {
        $weights[$key] = $weight;
        ++$weight;
      }
      elseif (preg_match('/^-/', $line)) {
        if ($weight !== FALSE) {
          $weight = FALSE;
        }
        else {
          break;
        }
      }
    }

    return $weights;
  }

  /**
   * Callback for $element['#process']
   * Create a big textarea.
   *
   * @param array $element
   * @param array $form_state
   *
   * @return array
   */
  function process($element, $form_state) {

    $text = $this->getDefaultText($element);
    $element['text'] = array(
      '#tree' => TRUE,
      '#type' => 'textarea',
      '#rows' => 24,
      '#default_value' => $text,
      '#attributes' => array(
        'style' => 'font-family: monospace;',
      ),
    );
    return $element;
  }

  /**
   * Get the text for the textarea
   *
   * @param array $element
   *
   * @return string
   */
  protected function getDefaultText($element) {

    $available_keys = $element['#crumbs_plugin_info']->availableKeysMeta;
    $weights = $element['#value'];
    $default_weights = $element['#crumbs_plugin_info']->defaultWeights;

    $key_lengths = array();
    foreach ($available_keys as $key => $title) {
      $key_lengths[] = strlen($key);
    }
    $ideal_length = $this->findIdealLength($key_lengths);

    $key_lines = array();
    foreach ($available_keys as $key => $meta) {
      $string = $key;
      $desc = $meta->descriptions;
      if (!empty($desc[0])) {
        $title = $desc[0];
        if (strlen($string) < $ideal_length) {
          $string .= str_repeat(' ', $ideal_length - strlen($string));
        }
        $string .= ' - '. $title;
      }
      $key_lines[$key] = $string;
    }

    $lines = array(
      'inherit' => $key_lines,
      'disabled_by_default' => array(),
      'enabled' => array(),
      'disabled' => array(),
    );

    foreach ($weights as $key => $weight) {
      $section = ($weight === FALSE) ? 'disabled' : 'enabled';
      $string = $key;
      if (isset($key_lines[$key])) {
        $string = $key_lines[$key];
      }
      else if ($key !== '*') {
        // an orphan setting.
        if (strlen($string) < $ideal_length) {
          $string .= str_repeat(' ', $ideal_length - strlen($string));
        }
        $string .= '   (orphan rule)';
      }
      $lines[$section][$key] = $string;
      unset($lines['inherit'][$key]);
    }

    foreach ($default_weights as $key => $default_weight) {
      if (isset($lines['inherit'][$key]) && FALSE === $default_weight) {
        $lines['disabled_by_default'][$key] = $lines['inherit'][$key];
        unset($lines['inherit'][$key]);
      }
    }

    ksort($lines['inherit']);
    $module = FALSE;
    foreach ($lines['inherit'] as $key => $line) {
      if (isset($prev) && $prev === '' && $line === '') {
        unset($lines['inherit'][$key]);
      }
      $pieces = explode('.', $key);
      if ($module !== $pieces[0]) {
        if (FALSE !== $module) {
          // Add in a blank line.
          $lines['inherit'][$key] = "\n" . $line;
        }
        $module = $pieces[0];
      }
      $prev = $line;
    }

    return "\n\n"
      . implode("\n", $lines['enabled'])
      . "\n\n\n---- disabled ----\n\n". implode("\n", $lines['disabled'])
      . "\n\n\n---- disabled by default ----\n\n". implode("\n", $lines['disabled_by_default'])
      . "\n\n\n---- inherit ----\n\n". implode("\n", $lines['inherit'])
      . "\n\n"
    ;
  }

  /**
   * This algorithm is copied 1:1 from blockadminlight
   *
   * @param array $key_lengths
   * @param int $factor
   *
   * @return int
   */
  protected function findIdealLength(array $key_lengths, $factor = 30) {
    sort($key_lengths, SORT_NUMERIC);
    $n = count($key_lengths);
    $length = 0;
    $best_length = 0;
    $cost = $n * $factor;
    $best_cost = $cost;
    for ($i=0; $i<$n; ++$i) {
      $increment = $key_lengths[$i] - $length;
      $length = $key_lengths[$i];
      $cost += $i * $increment;
      $cost -= $factor;
      if ($cost < $best_cost) {
        $best_cost = $cost;
        $best_length = $length;
      }
    }
    return $best_length;
  }
}
