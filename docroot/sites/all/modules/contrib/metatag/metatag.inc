<?php

interface DrupalMetaTagInterface {

  /**
   * Constructor
   *
   * @param array $info
   *   The information about the meta tag from metatag_get_info().
   */
  function __construct(array $info, array $data = array());

  function getForm();

  //function validateForm();

  //function processForm();

  function getValue();

  function getWeight();

  function getElement();

  function tidyValue($value);
}

class DrupalDefaultMetaTag implements DrupalMetaTagInterface {

  protected $info;
  protected $data = array('value' => '');
  protected $weight = 0;

  function __construct(array $info, array $data = NULL) {
    $this->info = $info;
    if (isset($data)) {
      $this->data = $data;
    }
  }

  /**
   * Calculate the weight or this meta tag.
   *
   * @return integer
   */
  public function getWeight() {
    static $counter = 0;

    // If no weight value is found, stack this meta tag at the end.
    $weight = 100;
    if (!empty($this->info['weight'])) {
      $weight = $this->info['weight'];
    }

    return $weight + ($counter++ * 0.1);
  }

  public function getForm(array $options = array()) {
    return array();
  }

  public function getValue(array $options = array()) {
    return $this->tidyValue($this->data['value']);
  }

  public function getElement(array $options = array()) {
    $value = $this->getValue($options);
    if (strlen($value) === 0) {
      return array();
    }

    // The stack of elements that will be output.
    $elements = array();

    // Dynamically add each option to this setting.
    $base_element = isset($this->info['element']) ? $this->info['element'] : array();

    // Single item.
    if (empty($this->info['multiple'])) {
      $values = array($value);
    }

    // Multiple items.
    else {
      $values = array_filter(explode(',', $value));
    }

    // Loop over each item.
    if (!empty($values)) {
      foreach ($values as $ctr => $value) {
        $value = trim($value);

        // Some meta tags must be output as secure URLs.
        if (!empty($this->info['secure'])) {
          $value = str_replace('http://', 'https://', $value);
        }

        // Combine the base configuration for this meta tag with the value.
        $element = $base_element + array(
          '#theme' => 'metatag',
          '#tag' => 'meta',
          '#id' => 'metatag_' . $this->info['name'] . '_' . $ctr,
          '#name' => $this->info['name'],
          '#value' => $value,
          '#weight' => $this->getWeight(),
        );

        // Add header information if desired.
        if (!empty($this->info['header'])) {
          $element['#attached']['drupal_add_http_header'][] = array($this->info['header'], $value);
        }

        $elements[] = array($element, $element['#id']);
      }
    }

    if (!empty($elements)) {
      return array(
        '#attached' => array('drupal_add_html_head' => $elements),
      );
    }
  }

  /**
   * Remove unwanted formatting from a meta tag.
   *
   * @param $value string
   *   The meta tag value to be tidied up.
   *
   * @return string
   *   The meta tag value after it has been tidied up.
   */
  public function tidyValue($value) {
    // Specifically replace encoded spaces, because some WYSIWYG editors are
    // silly. Do this before decoding the other HTML entities so that the output
    // doesn't end up with a bunch of a-circumflex characters.
    $value = str_replace('&nbsp;', ' ', $value);

    // Convert any HTML entities into regular characters.
    $value = decode_entities($value);

    // Remove any HTML code that might have been included.
    $value = strip_tags($value);

    // Strip errant whitespace.
    $value = str_replace(array("\r\n", "\n", "\r", "\t"), ' ', $value);
    $value = str_replace('  ', ' ', $value);
    $value = str_replace('  ', ' ', $value);
    $value = trim($value);

    return $value;
  }
}

/**
 * Text-based meta tag controller.
 */
class DrupalTextMetaTag extends DrupalDefaultMetaTag {

  public function getForm(array $options = array()) {
    $options += array(
      'token types' => array(),
    );

    $form['value'] = isset($this->info['form']) ? $this->info['form'] : array();

    $form['value'] += array(
      '#type' => 'textfield',
      '#title' => $this->info['label'],
      '#description' => !empty($this->info['description']) ? $this->info['description'] : '',
      '#default_value' => isset($this->data['value']) ? $this->data['value'] : '',
      '#element_validate' => array('token_element_validate'),
      '#token_types' => $options['token types'],
      '#maxlength' => 1024,
    );

    if (!empty($this->info['multiple'])) {
      $form['value']['#description'] .= ' ' . t('Multiple values may be used, separated by a comma. Note: Tokens that return multiple values will be handled automatically.');
    }

    // Support for dependencies, using Form API's #states system.
    // @see metatag.api.php.
    // @see https://api.drupal.org/drupal_process_states
    if (!empty($this->info['dependencies'])) {
      foreach ($this->info['dependencies'] as $specs) {
        $form['value']['#states']['visible'][':input[name*="[' . $specs['dependency'] . '][' . $specs['attribute'] . ']"]'] = array(
          $specs['condition'] => $specs['value'],
        );
      }
    }

    return $form;
  }

  public function getValue(array $options = array()) {
    $options += array(
      'instance' => '',
      'token data' => array(),
      'clear' => TRUE,
      'sanitize' => TRUE,
      'raw' => FALSE,
    );

    $name = "metatag:" . $options["instance"] . ":" . $this->info["name"];

    $value = metatag_translate($name, $this->data['value']);
    if (empty($options['raw'])) {
      // Give other modules the opportunity to use hook_metatag_pattern_alter()
      // to modify defined token patterns and values before replacement.
      drupal_alter('metatag_pattern', $value, $options['token data'], $this->info['name']);
      $value = token_replace($value, $options['token data'], $options);
    }
    return $this->tidyValue($value);
  }
}

/**
 * Extended meta tag controller for tags supporting the full attribute set.
 */
class DrupalExtendedMetaTag extends DrupalTextMetaTag {

  /**
   * Implements DrupalMetaTagInterface::getForm().
   */
  public function getForm(array $options = array()) {
    // Ensure the 'token types' element is available.
    $options += array(
      'token types' => array(),
    );

    $form['item'] = array(
      '#type' => 'fieldset',
      '#title' => $this->info['label'],
      '#description' => !empty($this->info['description']) ? $this->info['description'] : '',
      '#attributes' => array('class' => array('metatag-item', 'extended-metatag-item')),
      // '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['item']['value'] = isset($this->info['form']['value']) ? $this->info['form']['value'] : array();

    // Check for old single value format.
    if (!empty($this->data['value'])) {
      $this->data['item']['value'] = $this->data['value'];
    }

    $form['item']['value'] += array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#description' => t('The actual value to be used on this field.'),
      '#default_value' => isset($this->data['item']['value']) ? $this->data['item']['value'] : '',
      '#attributes' => array('class' => array('extended-metatag-field')),
      '#element_validate' => array('token_element_validate'),
      '#token_types' => $options['token types'],
      '#maxlength' => 1024,
    );

    $form['item']['scheme'] = isset($this->info['form']['scheme']) ? $this->info['form']['scheme'] : array();

    $form['item']['scheme'] += array(
      '#type' => 'textfield',
      '#title' => t('Scheme'),
      '#description' => t('Some metadata standards specify encoding schemes, though it is rarely used.'),
      '#default_value' => isset($this->data['item']['scheme']) ? $this->data['item']['scheme'] : '',
      '#attributes' => array('class' => array('extended-metatag-field', 'metatag-exclude')),
      '#element_validate' => array('token_element_validate'),
      '#token_types' => $options['token types'],
    );

    $form['item']['lang'] = isset($this->info['form']['lang']) ? $this->info['form']['lang'] : array();

    $form['item']['lang'] += array(
      '#type' => 'textfield',
      '#title' => t('Language'),
      '#description' => t("A language code that identifies a natural language spoken, written, or otherwise used for the communication of information."),
      '#default_value' => isset($this->data['item']['lang']) ? $this->data['item']['lang'] : '',
      '#attributes' => array('class' => array('extended-metatag-field', 'metatag-exclude')),
      '#element_validate' => array('token_element_validate'),
      '#token_types' => $options['token types'],
    );

    $form['item']['dir'] = isset($this->info['form']['dir']) ? $this->info['form']['dir'] : array();

    $form['item']['dir'] += array(
      '#type' => 'select',
      '#title' => t('Text direction'),
      '#description' => t("Specifies the base direction of directionally-neutral text."),
      '#default_value' => isset($this->data['item']['dir']) ? $this->data['item']['dir'] : '',
      '#options' => array(
        FALSE => t('- none -'),
        'ltr' => t('Left to right'),
        'rtl' => t('Right to left'),
      ),
      '#attributes' => array('class' => array('extended-metatag-field', 'metatag-exclude')),
    );

    return $form;
  }

  /**
   * Implements DrupalMetaTagInterface::getValue().
   */
  public function getValue(array $options = array()) {
    $name = "metatag:" . $options["instance"] . ":" . $this->info["name"];

    $options += array(
      'token data' => array(),
      'clear' => TRUE,
      'sanitize' => TRUE,
      'raw' => FALSE,
    );

    // Check for old single value format.
    if (!empty($this->data['value'])) {
      $this->data['item']['value'] = $this->data['value'];
    }

    if (!isset($this->data['item']['value'])) {
      return NULL;
    }

    $value = metatag_translate($name, $this->data['item']['value']);
    if (empty($options['raw'])) {
      // Give other modules the opportunity to use hook_metatag_pattern_alter()
      // to modify defined token patterns and values before replacement.
      drupal_alter('metatag_pattern', $value, $options['token data']);
      $value = token_replace($value, $options['token data'], $options);
    }

    $value = $this->tidyValue($value);

    return $value;
  }

  /**
   * Return the item attributes for the extended tag.
   *
   * @param array $options
   *   (optional) An array of options.
   *
   * @return array
   *   An array of values.
   */
  public function getAttributes(array $options = array()) {

    $options += array(
      'token data' => array(),
      'clear' => TRUE,
      'sanitize' => TRUE,
      'raw' => FALSE,
    );

    $values = $this->data['item'];

    unset($values['value']);

    foreach ($values as $name => $value) {
      if (empty($value)) {
        unset($values[$name]);
      }
    }

    if (isset($values['lang'])) {
      $values['xml:lang'] = $values['lang'];
    }

    foreach ($values as $key => $value) {
      if (empty($options['raw'])) {
        $value = token_replace($value, $options['token data'], $options);
      }

      $values[$key] = $this->tidyValue($value);
    }

    return $values;
  }

  /**
   * Implements DrupalMetaTagInterface::getElement().
   */
  public function getElement(array $options = array()) {

    $element = isset($this->info['element']) ? $this->info['element'] : array();

    $value = $this->getValue($options);
    if (strlen($value) === 0) {
      return array();
    }

    $element += array(
      '#theme' => 'metatag',
      '#tag' => 'meta',
      '#id' => 'metatag_' . $this->info['name'],
      '#name' => $this->info['name'],
      '#value' => $value,
      '#attributes' => $this->getAttributes($options),
    );

    // Add header information if desired.
    if (!empty($this->info['header'])) {
      $element['#attached']['drupal_add_http_header'][] = array(
        $this->info['header'],
        $value,
      );
    }

    return array(
      '#attached' => array(
        'drupal_add_html_head' => array(
          array(
            $element,
            $element['#id'],
          ),
        ),
      ),
    );
  }
}


/**
 * Link type meta tag controller.
 */
class DrupalLinkMetaTag extends DrupalTextMetaTag {

  public function getElement(array $options = array()) {
    $element = isset($this->info['element']) ? $this->info['element'] : array();

    $value = $this->getValue($options);
    if (strlen($value) === 0) {
      return array();
    }

    $element += array(
      '#theme' => 'metatag_link_rel',
      '#tag' => 'link',
      '#id' => 'metatag_' . $this->info['name'],
      '#name' => $this->info['name'],
      '#value' => $value,
      '#weight' => $this->getWeight(),
    );

    if (!isset($this->info['header']) || !empty($this->info['header'])) {
      // Also send the generator in the HTTP header.
      // @todo This does not support 'rev' or alternate link headers.
      $element['#attached']['drupal_add_http_header'][] = array('Link', '<' . $value . '>;' . drupal_http_header_attributes(array('rel' => $element['#name'])), TRUE);
    }

    return array(
      '#attached' => array('drupal_add_html_head' => array(array($element, $element['#id']))),
    );
  }
}

/**
 * Title meta tag controller.
 *
 * This extends DrupalTextMetaTag as we need to alter variables in
 * template_preprocess_html() rather output a normal meta tag.
 */
class DrupalTitleMetaTag extends DrupalTextMetaTag {

  public function getElement(array $options = array()) {
    $element = array();
    $value = $this->getValue($options);
    $element['#attached']['metatag_set_preprocess_variable'][] = array('html', 'head_title', $value);
    $element['#attached']['metatag_set_preprocess_variable'][] = array('html', 'head_array', array('title' => $value));
    return $element;
  }
}

/**
 * Multiple value meta tag controller.
 */
class DrupalListMetaTag extends DrupalDefaultMetaTag {

  function __construct(array $info, array $data = NULL) {
    // Ensure that the $data['value] argument is an array.
    if (empty($data['value'])) {
      $data['value'] = array();
    }
    $data['value'] = (array) $data['value'];

    parent::__construct($info, $data);
  }

  public function getForm(array $options = array()) {
    $form['value'] = isset($this->info['form']) ? $this->info['form'] : array();

    $form['value'] += array(
      '#type' => 'checkboxes',
      '#title' => $this->info['label'],
      '#description' => !empty($this->info['description']) ? $this->info['description'] : '',
      '#default_value' => isset($this->data['value']) ? $this->data['value'] : array(),
    );

    return $form;
  }

  public function getValue(array $options = array()) {
    $values = array_keys(array_filter($this->data['value']));
    sort($values);
    $value = implode(', ', $values);
    return $this->tidyValue($value);
  }
}

/**
 * Date interval meta tag controller.
 */
class DrupalDateIntervalMetaTag extends DrupalDefaultMetaTag {

  public function getForm(array $options = array()) {
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('@title interval', array('@title' => $this->info['label'])),
      '#default_value' => isset($this->data['value']) ? $this->data['value'] : '',
      '#element_validate' => array('element_validate_integer_positive'),
      '#maxlength' => 4,
      '#description' => isset($this->info['description']) ? $this->info['description'] : '',
    );
    $form['period'] = array(
      '#type' => 'select',
      '#title' => t('@title interval type', array('@title' => $this->info['label'])),
      '#default_value' => isset($this->data['period']) ? $this->data['period'] : '',
      '#options' => array(
        '' => t('- none -'),
        'day' => t('Day(s)'),
        'week' => t('Week(s)'),
        'month' => t('Month(s)'),
        'year' => t('Year(s)'),
      ),
    );

    return $form;
  }

  public function getValue(array $options = array()) {
    $value = '';
    if (!empty($this->data['value'])) {
      $interval = intval($this->data['value']);
      if (!empty($interval) && !empty($this->data['period'])) {
        $period = $this->data['period'];
        $value = format_plural($interval, '@count ' . $period, '@count ' . $period . 's');
      }
    }
    return $value;
  }
}
