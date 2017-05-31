<?php
/**
 * @file
 * @author Edward Murrell <edward@catalyst-au.net>
 */

namespace tdd7\testframework;
require_once __DIR__ . '/../basefixtures/BasicTestCase.php';

abstract class DrupalFormsFrameworkTestCase extends BasicTestCase {
  private $validfields = array();

  /**
   * Creates internal array of fields for testing.
   */
  public function setUp() {
    $this->validfields['fieldset']  = array('#access' => TRUE, '#after_build' => TRUE, '#attributes' => TRUE, '#collapsed' => TRUE, '#description' => TRUE, '#element_validate' => TRUE, '#parents' => TRUE, '#post_render' => TRUE, '#prefix' => TRUE, '#pre_render' => TRUE, '#process' => TRUE, '#theme' => TRUE, '#theme_wrappers' => TRUE, '#title' => TRUE, '#title_display' => TRUE, '#tree' => TRUE, '#type' => TRUE, '#weight' => TRUE, '#prefix' => TRUE, '#suffix' => TRUE);
    $this->validfields['textfield'] = array('#access' => TRUE, '#after_build' => TRUE, '#ajax' => TRUE, '#attributes' => TRUE, '#autocomplete_path' => TRUE, '#default_value' => TRUE, '#description' => TRUE, '#disabled' => TRUE, '#element_validate' => TRUE, '#field_prefix' => TRUE, '#field_suffix' => TRUE, '#maxlength' => TRUE, '#parents' => TRUE, '#post_render' => TRUE, '#prefix' => TRUE, '#pre_render' => TRUE, '#process' => TRUE, '#required' => TRUE, '#size' => TRUE, '#states' => TRUE, '#suffix' => TRUE, '#text_format' => TRUE, '#theme' => TRUE, '#theme_wrappers' => TRUE, '#title' => TRUE, '#title_display' => TRUE, '#tree' => TRUE, '#type' => TRUE, '#weight' => TRUE);
    $this->validfields['submit']    = array('#access' => TRUE, '#after_build' => TRUE, '#ajax' => TRUE, '#attributes' => TRUE, '#button_type' => TRUE, '#disabled' => TRUE, '#element_validate' => TRUE, '#executes_submit_callback' => TRUE, '#limit_validation_errors' => TRUE, '#name' => TRUE, '#parents' => TRUE, '#post_render' => TRUE, '#prefix' => TRUE, '#pre_render' => TRUE, '#process' => TRUE, '#submit' => TRUE, '#states' => TRUE, '#suffix' => TRUE, '#theme' => TRUE, '#theme_wrappers' => TRUE, '#tree' => TRUE, '#type' => TRUE, '#validate' => TRUE, '#value' => TRUE, '#weight' => TRUE);
    parent::setUp();
  }
  
  /**
   * Virtual function that must be implemented to enforce a form.
   * @return array() Array containing an array contain form arrays.
   */
  public abstract function GetForms();

  /**
   * Checks that form elements are of acceptable elements, and passes them to
   *  check methods called checkElement{$type}Fields
   * @dataProvider GetForms
   * @param array $form Drupal form array
   */
  public function testForm(array $forms) {
    $this->checkElement('form', $forms, TRUE);
  }

  /**
   * Test a drupal field element.
   *
   * Checks if fields are allowed for the element, test their validity and
   * recursively calls itself for sub elements.
   *
   * @param string $key
   *   The key that identifies this element in parent array.
   * @param array $data
   *   Element data.
   * @param boolean $root
   *   Is this a root node (ie; form), default to FALSE.
   */
  public function checkElement($id, array $data = array(), $root = FALSE) {
    // Set the type in a form so we can autodetect types elsewhere.
    if ($root === TRUE) {
      $data['#type'] = 'form';
    }

    // Check that this field is allowed to have it's data fields
    $this->checkElementFieldsList($id, $data);

    foreach ($data as $key => $element) {
      // This is another element, so recurisively call this function.
      if (substr($key,0,1) != '#') {
        $this->checkElement($key, $element);
        continue;
      }

      // Check element type
      $type = ltrim($key, '#');
      $check_method = "checkElementFieldData_{$type}";
      if (method_exists($this, $check_method)) {
        $this->$check_method($id, $element);
      }
    }
  }

  /**
   * Tests fields have only allowable fields.
   *
   * @param string $key
   *   The key that identifies this element in parent array.
   * @param array $element
   *   Element being tested.
   */
  public function checkElementFieldsList($key = 'unknown', array $element = array()){
    $this->assertArrayHasKey('#type', $element, "Error in '{$key}' - Missing #type data.");
    if (!array_key_exists($element['#type'], $this->validfields)) {
      return;
    }
    $type = $element['#type'];
    $fields = $this->validfields[$type];

    // Iterate through all the fields in the element
    foreach ($element as $fieldname => $fieldata) {
      $this->assertArrayHasKey($field, $fields, "Error in '{$key}' - {$type} elements are not allowed to have a {$fieldname} setting.");
    }
  }

  /**
   * Check #autocomplete_path is valid.
   *
   * @param string $key
   *   Name of the containing element.
   * @param $field
   *   The value for the array where the key is #autocomplete_path
   */
  public function checkElementFieldData_autocomplete_path($key = '', $field) {
    $menu = menu_get_item($field);
    $this->assertNotEmpty($menu, "Path for '{$field}' not found in menu structure.");
  }

  /**
   * Check the contents of a #validate field
   *
   * @param string $key
   *   Name of the containing element.
   * @param $field
   *   The value for the array where the key is #validate
   */
  public function checkElementFieldData_validate($key = '', $field) {
    $this->assertTrue(is_array($field), "Validate element for {$key} should be a list.");
    foreach ($field as $callback) {
      $this->assertTrue(function_exists($callback), "Validate callback {$callback} for {$key} does not exist.");
    }
  }

  /**
   * Check textfield element field #ajax is valid
   *
   * @param string $key
   *   Name of the containing element.
   * @param $field
   *   The value for the array where the key is #$ajax
   */
  public function checkElementFieldData_ajax($key = '', $field) {
    $this->assertTrue(is_array($field), "Ajax element for {$key} should be an array.");

    $this->assertFalse(array_key_exists('callback', $field) && array_key_exists('path', $field),
        "Ajax configuration for {$key} contains muturally exclusive callback and path settings.");

    if (array_key_exists('callback', $field)) {
      $this->assertTrue(function_exists($field['callback']), "Callback {$field['callback']} for {$key} does not exist.");
    }
    if (array_key_exists('path', $field)) {
      $menu = menu_get_item($field['path']);
      $this->assertNotEmpty($menu, "Path '{$field['path']}' not found in menu structure.");
    }
  }

}