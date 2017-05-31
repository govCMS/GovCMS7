<?php

/**
 * @file
 * PHP unit tests for Iconomist.
 */

namespace Drupal\Iconomist;

require_once DRUPAL_ROOT . '../build/vendor/drupal/tdd7/mocks/MockDrupalFunctions.php';

use tdd7\testframework\mocks\MockDrupalFunctions as MockDrupalFunctions;

/**
 * Get the theme settings.
 *
 * @param string $settingName
 *   The name of the setting being sought.
 * @param string $theme
 *   The name of the theme for which settings should be retrieved.
 *
 * @return array
 *   The render array for the theme settings.
 */
function theme_get_setting($settingName, $theme = NULL) {
  return MockDrupalFunctions::theme_get_setting($settingName, $theme);
}

/**
 * Mock version of setting a variable.
 *
 * @param string $variable
 *   The name of the variable to set.
 * @param mixed $value
 *   The value to assign to the variables.
 */
function variable_set($variable, $value) {
  MockDrupalFunctions::variable_set($variable, $value);
}

/**
 * Mock version of variable_get.
 *
 * @param string $variable
 *   The name of the variable to get.
 * @param mixed $default
 *   The value to use if the variable isn't set.
 *
 * @return mixed
 *   The value of the variable (or the default value)
 */
function variable_get($variable, $default) {
  return MockDrupalFunctions::variable_get($variable, $default);
}

/**
 * Mockable interface to drupal_add_html_head_link.
 *
 * @param array $attributes
 *   The attributes being added to the page.
 */
function drupal_add_html_head_link(array $attributes) {
  MockDrupalFunctions::drupal_add_html_head_link($attributes);
}

/**
 * Retrieve form errors.
 *
 * @return array
 *   The list of form errors that were set.
 */
function get_form_errors() {
  return MockDrupalFunctions::form_get_errors();
}

/**
 * Clear the errors on a form.
 */
function form_clear_error() {
  MockDrupalFunctions::form_clear_error();
}

/**
 * Mocked version of form_error.
 *
 * @param string $element
 *   The name of the element against which the error is being flagged.
 * @param string $error
 *   The error message to be displayed.
 */
function form_error($element, $error) {
  MockDrupalFunctions::form_set_error($element, $error);
}

/**
 * Class MockDbQueryResult.
 *
 * @package Drupal\Iconomist
 */
class MockDbQueryResult {
  private $result;

  /**
   * MockDbQueryResult constructor.
   *
   * @param mixed $result
   *   The result that fetchField() should return.
   */
  public function __construct($result) {
    $this->result = $result;
  }

  /**
   * Returns the result that's been set.
   *
   * @return mixed
   *   The result.
   */
  public function fetchField() {
    return $this->result;
  }

}

/**
 * Mock version of db_query.
 *
 * TTD7 doesn't yet include a db_query mock. Since I'm guessing that would take
 * a fair while to implement, I'll do a very simple implementation for the
 * moment that just hardcodes the fid the query would produce.
 *
 * @param string $query
 *   The fie ID being sought.
 * @param array $params
 *   An array of parameters to the query.
 *
 * @returns \Drupal\Iconomist\MockDbQueryResult
 *   Mock db_query result instance.
 */
function db_query($query, array $params) {
  $uri = $params[':uri'];
  $result = array_key_exists($uri, IconomistPHPUnitTests::$fileUriMappings) ?
    IconomistPHPUnitTests::$fileUriMappings[$uri] : FALSE;
  return new MockDbQueryResult($result);
}

/**
 * Mock version of file_load.
 *
 * @param int $fid
 *   The fie ID being sought.
 *
 * @return object
 *   The file object matching the ID or FALSE.
 */
function file_load($fid) {
  return MockDrupalFunctions::file_load($fid);
}

/**
 * Mock version of file_save.
 *
 * @param \stdClass $file
 *   A file object returned by file_load().
 *
 * @return object
 *   The file object matching the ID or FALSE.
 */
function file_save(\stdClass $file) {
  return MockDrupalFunctions::file_save($file);
}

/**
 * Mock version of file_usage_delete.
 *
 * @param \stdClass $file
 *   A file object.
 * @param string $module
 *   The name of the module using the file.
 * @param string $type
 *   (optional) The type of the object that contains the referenced file. May
 *   be omitted if all module references to a file are being deleted.
 * @param int $id
 *   (optional) The unique, numeric ID of the object containing the referenced
 *   file. May be omitted if all module references to a file are being deleted.
 * @param int $count
 *   (optional) The number of references to delete from the object. Defaults to
 *   1. 0 may be specified to delete all references to the file within a
 *   specific object.
 */
function file_usage_delete(\stdClass $file, $module, $type = NULL, $id = NULL, $count = 1) {
  return MockDrupalFunctions::file_usage_delete($file, $module, $type, $id, $count);
}

/**
 * Create a file URL from a URI.
 *
 * @param string $uri
 *   The URI to a file for which we need an external URL, or the path to a
 *   shipped file.
 *
 * @return string
 *   A string containing a URL that may be used to access the file.
 *   If the provided string already contains a preceding 'http', 'https', or
 *   '/', nothing is done and the same string is returned. If a stream wrapper
 *   could not be found to generate an external URL, then FALSE is returned.
 */
function file_create_url($uri) {
  return MockDrupalFunctions::file_create_url($uri);
}

/**
 * Mock version of _system_theme_settings_validate_path.
 *
 * @param string $path
 *   The file path being checked.
 *
 * @return mixed
 *   The matching path, or FALSE.
 */
function _system_theme_settings_validate_path($path) {
  return $path == 'invalid' ? FALSE : $path;
}

/**
 * Test cases for Iconomist module.
 */
class IconomistPHPUnitTests extends \PHPUnit_Framework_TestCase {

  static public $settings = array(
    '' => array(
      'toggle_iconomist' => FALSE,
      'iconomist_icons' => array(),
    ),
    'foo' => array(
      'toggle_iconomist' => TRUE,
      'iconomist_icons' => array(
        0 => array(
          'usage_id' => 2,
          'path' => 'public://iconomist/test1.jpg',
          'width' => '',
          'height' => '',
          'rel' => 'icon',
          'fid' => '21',
          'uri' => '/path/to/test1.jpg',
        ),
        2 => array(
          'usage_id' => 3,
          'path' => 'public://iconomist/test2.jpg',
          'width' => '64',
          'height' => '64',
          'rel' => 'icon',
          'fid' => '22',
          'uri' => '/path/to/test2.jpg',
        ),
      ),
    ),
  );

  static public $fileUriMappings = array(
    'public://iconomist/test1.jpg' => 21,
    'public://iconomist/test2.jpg' => 22,
  );

  static public $savedFiles = array(
    0 => array(
      'usage_id' => 2,
      'path' => 'public://iconomist/test1.jpg',
      'width' => '',
      'height' => '',
      'rel' => 'icon',
      'fid' => '21',
      'uri' => '/path/to/test1.jpg',
    ),
    1 => array(
      'usage_id' => 3,
      'path' => 'public://iconomist/test2.jpg',
      'width' => '64',
      'height' => '64',
      'rel' => 'icon',
      'fid' => '22',
      'uri' => '/path/to/test2.jpg',
    ),
    2 => array(
      'usage_id' => 4,
      'path' => 'public://iconomist/test3.jpg',
      'width' => '64',
      'height' => '64',
      'rel' => 'icon',
      'fid' => '23',
      'uri' => '/path/to/test3.jpg',
    ),
  );

  /**
   * Setup function for tests.
   */
  public function setUp() {

    // Set mock theme settings from the array above.
    foreach (self::$settings as $theme => $settings) {
      foreach ($settings as $name => $value) {
        MockDrupalFunctions::theme_set_setting($name, $value, $theme);
      }
    }

    foreach (self::$savedFiles as $file) {
      MockDrupalFunctions::file_save((object) $file);
    }

    form_clear_error();
  }

  /**
   * Iconomist_form_system_theme_settings_alter implements sitewide settings.
   *
   * @test
   */
  public function implementsSitewideSettings() {
    $form = array();
    $form_state = array();

    Iconomist::themeSettingsAlter($form, $form_state);
    unset($form_state['add_icon']);
    unset($form_state['iconomist_icons']);

    // If sitewide settings are properly implemented, they should be reflected
    // in changes to the form_state array...
    $expected = array(
      'values' => array(
        'iconomist_icons' => array(),
      ),
      'storage' => array(
        'iconomist_num_icons' => 0,
      ),
    );
    $this->assertEquals($expected, $form_state);

    // ... and in the form's render array.
    $toggle = $form['theme_settings']['toggle_iconomist'];
    $this->assertEquals(FALSE, $toggle['#default_value']);
  }

  /**
   * Iconomist_form_system_theme_settings_alter implements settings per theme.
   *
   * @test
   */
  public function implementsSettingsPerTheme() {
    $form = array();
    $form_state = array(
      'values' => array(
        'iconomist_icons' => array(
          0 => array(
            'usage_id' => 2,
            'path' => 'public://iconomist/test1.jpg',
            'width' => '',
            'height' => '',
            'rel' => 'icon',
            'fid' => '21',
            'uri' => '/path/to/test1.jpg',
          ),
          1 => array(
            'usage_id' => 3,
            'path' => 'public://iconomist/test2.jpg',
            'width' => '64',
            'height' => '64',
            'rel' => 'icon',
            'fid' => '22',
            'uri' => '/path/to/test2.jpg',
          ),
        ),
      ),
    );

    // Set the name of the 'theme' we're using.
    $form_state['build_info']['args'] = array('foo');

    Iconomist::themeSettingsAlter($form, $form_state);

    $expected = array(
      0 => array(
        'path' => 'public://iconomist/test1.jpg',
        'usage_id' => '2',
      ),
      2 => array(
        'path' => 'public://iconomist/test2.jpg',
        'usage_id' => '3',
      ),
    );
    $this->assertEquals($expected, $form_state['storage']['iconomist_icons']);

    $toggle = $form['theme_settings']['toggle_iconomist'];
    $this->assertEquals(TRUE, $toggle['#default_value']);
  }

  /**
   * Iconomist_form_system_theme_settings_alter loads the form state correctly.
   *
   * @test
   */
  public function loadsStateWhenNoTriggeringElement() {
    $form = array();
    $form_state = array(
      'build_info' => array(
        'args' => array(
          'foo',
        ),
      ),
    );

    Iconomist::themeSettingsAlter($form, $form_state);

    $expected = array(
      'values' => array(
        'iconomist_icons' => array(
          0 => array(
            'usage_id' => 2,
            'path' => 'public://iconomist/test1.jpg',
            'width' => '',
            'height' => '',
            'rel' => 'icon',
            'fid' => '21',
            'uri' => '/path/to/test1.jpg',
          ),
          2 => array(
            'usage_id' => 3,
            'path' => 'public://iconomist/test2.jpg',
            'width' => '64',
            'height' => '64',
            'rel' => 'icon',
            'fid' => '22',
            'uri' => '/path/to/test2.jpg',
          ),
        ),
      ),
      'build_info' => array(
        'args' => array(
          'foo',
        ),
      ),
      'storage' => array(
        'iconomist_num_icons' => 2,
        'iconomist_icons' => array(
          0 => array(
            'usage_id' => 2,
            'path' => 'public://iconomist/test1.jpg',
          ),
          2 => array(
            'usage_id' => 3,
            'path' => 'public://iconomist/test2.jpg',
          ),
        ),
      ),
    );
    $this->assertEquals($expected, $form_state);
  }

  /**
   * Form_system_theme_settings_alter doesn't reload state if Ajax call.
   *
   * @test
   */
  public function noStateLoadWhenTriggeringElementSet() {
    $form = array();
    $form_state = array(
      'build_info' => array(
        'args' => array(
          'foo',
        ),
      ),
      'triggering_element' => 'bar',
    );

    $expected = array_merge($form_state,
      array(
        'storage' => array(
          'iconomist_num_icons' => 0,
        ),
      )
    );

    Iconomist::themeSettingsAlter($form, $form_state);

    $this->assertEquals($expected, $form_state);
  }

  /**
   * Form_system_theme_settings_alter adds the toggle_iconomist checkbox.
   *
   * @test
   */
  public function addsToggleDisplay() {
    $form = array();
    $form_state = array();

    // The theme argument should be used too.
    $form_state['build_info']['args'] = array('foo');

    Iconomist::themeSettingsAlter($form, $form_state);

    $expected = array(
      '#type' => 'checkbox',
      '#title' => t('Iconomist Icons'),
      '#default_value' => TRUE,
    );
    $this->assertEquals($expected, $form['theme_settings']['toggle_iconomist']);
  }

  /**
   * Form_system_theme_settings_alter adds Iconomist Settings fieldset.
   *
   * @test
   */
  public function addsIconomistSettingsFieldset() {
    $form = [];
    $form_state = [];

    // The theme argument should be used too.
    $form_state['build_info']['args'] = ['foo'];

    Iconomist::themeSettingsAlter($form, $form_state);

    $expected = array(
      '#type' => 'fieldset',
      '#title' => t('Iconomist settings'),
      '#description' => t('Additional icons to link to in HTML head.'),
    );

    // Remove the extra parts we also expect and will test for below.
    unset($form['iconomist']['iconomist_icons']);
    unset($form['iconomist']['add_icon']);
    $this->assertEquals($expected, $form['iconomist']);
  }

  /**
   * Form_system_theme_settings_alter adds container for Ajax commands.
   *
   * @test
   */
  public function addsAjaxContainer() {
    $form = [];
    $form_state = [];

    Iconomist::themeSettingsAlter($form, $form_state);

    $this->assertArrayHasKey('iconomist_icons', $form['iconomist']);
    $form['iconomist']['iconomist_icons'] = array(
      '#type' => 'container',
      '#tree' => TRUE,
      '#prefix' => '<div id="iconomist-icons">',
      '#suffix' => '</div>',
    );
  }

  /**
   * Form_system_theme_settings_alter adds a fieldset for each icon.
   *
   * @test
   */
  public function addsFieldsetForEachIcon() {
    $form = [];
    $form_state = [];

    // The link rel types.
    $relationships = array(
      'apple-touch-icon' => t('Apple Touch'),
      'apple-touch-icon-precomposed' => t('Apple Touch (Precomposed)'),
      'icon' => t('Icon'),
    );

    // The theme argument should be used too.
    $form_state['build_info']['args'] = ['foo'];

    Iconomist::themeSettingsAlter($form, $form_state);

    $expected = count(self::$settings['foo']['iconomist_icons']);

    for ($i = 0; $i < $expected; $i++) {
      $this->assertArrayHasKey($i, $form['iconomist']['iconomist_icons']);
      $actual = $form['iconomist']['iconomist_icons'][$i];

      $expectedIcon = self::$settings['foo']['iconomist_icons'][$i];
      $expectedFieldset = array(
        '#type' => 'fieldset',
        '#title' => t('Icon'),
        '#element_validate' => ['_iconomist_icons_validate'],
        'usage_id' => array(
          '#type' => 'value',
          '#value' => $expectedIcon['usage_id'] ?: "",
        ),
        'upload' => array(
          '#type' => 'managed_file',
          '#title' => t('Upload icon image'),
          '#description' => t("If you don't have direct file access to the server, use this field to upload your touch icon."),
          '#upload_validators' => ['file_validate_is_image'],
          '#upload_location' => 'public://iconomist',
        ),
        'path' => array(
          '#type' => 'textfield',
          '#default_value' => $expectedIcon['path'] ?: "",
          '#title' => t('Path to custom icon'),
          '#description' => t('The path to the file you would like to use as your icon.'),
        ),
        'width' => array(
          '#type' => 'textfield',
          '#default_value' => $expectedIcon['width'] ?: "",
          '#title' => t('Icon width'),
          '#description' => t('Width of icon in pixels.'),
          '#element_validate' => ['element_validate_integer_positive'],
          '#size' => 10,
        ),
        'height' => array(
          '#type' => 'textfield',
          '#default_value' => $expectedIcon['height'] ?: "",
          '#title' => t('Icon height'),
          '#description' => t('Height of icon in pixels.'),
          '#element_validate' => ['element_validate_integer_positive'],
          '#size' => 10,
        ),
        'rel' => array(
          '#type' => 'radios',
          '#options' => $relationships,
          '#default_value' => $expectedIcon['rel'] ?: "icon",
          '#title' => t('Icon relationship'),
          '#description' => t('Relationship type of icon.'),
        ),
        'remove_icon' => array(
          '#type' => 'submit',
          '#name' => 'remove_icon_' . $i,
          '#submit' => ['_iconomist_remove_icon'],
          '#value' => t('Remove icon'),
          '#ajax' => array(
            'callback' => '_iconomist_ajax_callback',
            'wrapper' => 'iconomist-icons',
          ),
          '#limit_validation_errors' => array(),
        ),
      );
      $this->assertEquals($expectedFieldset, $actual);
    }
  }

  /**
   * Form_system_theme_settings_alter always displays the 'Add icon' button.
   *
   * @test
   */
  public function alwaysDisplaysAddIconButton() {
    $form = [];
    $form_state = [];

    $expected = array(
      '#type' => 'submit',
      '#name' => 'add_icon',
      '#submit' => ['_iconomist_add_icon'],
      '#value' => t('Add icon'),
      '#ajax' => array(
        'callback' => '_iconomist_ajax_callback',
        'wrapper' => 'iconomist-icons',
      ),
      '#limit_validation_errors' => array(),
    );

    Iconomist::themeSettingsAlter($form, $form_state);

    // Sitewide (empty) form should have it.
    $this->assertEquals($expected, $form['iconomist']['add_icon']);

    // A form with a couple of icons already existing should also still have the
    // icon.
    $form_state = array();
    $form_state['build_info']['args'] = ['foo'];
    Iconomist::themeSettingsAlter($form, $form_state);
    $this->assertEquals($expected, $form['iconomist']['add_icon']);
  }

  /**
   * Form_system_theme_settings_alter adds submit handler to head of list.
   *
   * @test
   */
  public function addsSubmitHandlerAtHeadOfList() {
    $form = array(
      '#submit' => array(
        'iwasfirst',
        'iwaslast',
      ),
    );
    $form_state = [];

    $expected = array(
      '_iconomist_settings_submit',
      'iwasfirst',
      'iwaslast',
    );

    Iconomist::themeSettingsAlter($form, $form_state);
    $this->assertEquals($expected, $form['#submit']);
  }

  /**
   * Add_icon ajax callback increases no. of icons and triggers form rebuild.
   *
   * @test
   */
  public function ajaxCallbackIncreasesNumberOfIconsAndTriggersFormRebuild() {
    $form = array();
    $form_state = array();

    $expected = array(
      'rebuild' => TRUE,
      'storage' => array(
        'iconomist_num_icons' => 1,
      ),
    );

    // From empty to one.
    Iconomist::addIcon($form, $form_state);
    $this->assertEquals($expected, $form_state);

    // From 2 to 3.
    $form_state['build_info']['args'] = ['foo'];
    Iconomist::themeSettingsAlter($form, $form_state);
    Iconomist::addIcon($form, $form_state);

    $actual = $form_state['storage']['iconomist_num_icons'];
    $this->assertEquals(3, $actual);
  }

  /**
   * Remove_icon removes the appropriate icon from the form state.
   *
   * @test
   */
  public function ajaxRemoveIconCallbackRemovesIconFromFormState() {
    // Get the initial form.
    $form = array();
    $form_state['build_info']['args'] = ['foo'];
    Iconomist::themeSettingsAlter($form, $form_state);

    // Adjust the form state to emulate having the remove button pressed.
    $form_state['triggering_element']['#name'] = 'remove_icon_0';
    Iconomist::removeIcon($form, $form_state);

    $expected = array(
      'build_info' => array(
        'args' => array(
          0 => 'foo',
        ),
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(
            'usage_id' => 3,
            'path' => 'public://iconomist/test2.jpg',
            'width' => '64',
            'height' => '64',
            'rel' => 'icon',
            'fid' => '22',
            'uri' => '/path/to/test2.jpg',
          ),
        ),
      ),
      'storage' => array(
        'iconomist_num_icons' => 1,
        'iconomist_icons' => array(
          0 => array(
            'path' => 'public://iconomist/test2.jpg',
            'usage_id' => 3,
          ),
        ),
      ),
      'triggering_element' => array(
        '#name' => 'remove_icon_0',
      ),
      'rebuild' => TRUE,
      'input' => array(
        'iconomist_icons' => NULL,
      ),
    );

    $this->assertEquals($expected, $form_state);
  }

  /**
   * Ajax_callback returns the portion of the render array needed.
   *
   * @test
   */
  public function ajaxCallbackReturnsRenderArray() {
    $form = array(
      'iconomist' => array(
        'iconomist_icons' => array(
          'test' => TRUE,
        ),
      ),
    );

    $result = Iconomist::ajaxCallback($form);

    $expected = array('test' => TRUE);
    $this->assertEquals($expected, $result);
  }

  /**
   * Get managed file returns the file object when given a valid URI.
   *
   * @test
   */
  public function getManagedFileReturnsAppropriateFileObject() {
    $expected = (object) self::$settings['foo']['iconomist_icons'][0];

    $result = Iconomist::getManagedFile('public://iconomist/test1.jpg');
    $this->assertEquals($expected, $result);
  }

  /**
   * Get managed file returns FALSE when given an invalid URI.
   *
   * @test
   */
  public function getManagedFileReturnsFalseForInvalidUri() {
    $result = Iconomist::getManagedFile('public://iconomist/test99.jpg');
    $this->assertEquals(FALSE, $result);
  }

  /**
   * Get_usage_id does not return the same usage_id twice.
   *
   * @test
   */
  public function getUsageIdDoesNotReturnSameUsageIdTwice() {
    variable_set('iconomist_counter', 4);
    $first = Iconomist::getUseId();
    $second = Iconomist::getUseId();

    // The value we set will be returned from the first call.
    $this->assertEquals(4, $first);
    $this->assertNotEquals($first, $second);
  }

  /**
   * Get_usage_id returns an integer.
   *
   * @test
   */
  public function getUsageIdReturnsInteger() {
    variable_set('iconomist_counter', 4);

    // Check the updated value, not the one we set.
    $result = Iconomist::getUseId();
    $this->assertEquals(TRUE, is_int($result));
  }

  /**
   * Validate honours the #limit_validation_errors element.
   *
   * @test
   */
  public function validateHonoursTheLimitValidationErrorsElement() {
    $element = array('#parents' => array(1 => 1));
    $form_state = array(
      'triggering_element' => array(
        '#limit_validation_errors' => array(),
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'upload' => 'foo',
            'file' => FALSE,
          ),
        ),
      ),
    );

    Iconomist::validate($element, $form_state);

    // If it performs validation, the call will either set form errors or unset
    // $icon['upload']. Check for either having happened.
    $this->assertEmpty(get_form_errors());

    $parent = $form_state['values']['iconomist_icons'][1];
    $this->assertArrayHasKey('upload', $parent);
  }

  /**
   * Validate sets a form error on the path field when given an invalid file.
   *
   * @test
   */
  public function validateSetsPathIsInvalidErrorForInvalidPaths() {
    $element = array(
      '#parents' => array(1 => 1),
      'path' => 'non_existent_path',
    );
    $form_state = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'path' => 'invalid',
            'upload' => FALSE,
          ),
        ),
      ),
    );

    Iconomist::validate($element, $form_state);

    $expected = array(
      'non_existent_path' => t('Path is invalid'),
    );
    $this->assertEquals($expected, get_form_errors());
  }

  /**
   * Validate sets the file ID when a valid file path is provided.
   *
   * @test
   */
  public function validateSetsFileIdForValidPaths() {
    $element = array(
      '#parents' => array(1 => 1),
      'path' => 'public://iconomist/test2.jpg',
    );
    $form_state = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'path' => 'public://iconomist/test2.jpg',
            'upload' => FALSE,
          ),
        ),
      ),
    );

    Iconomist::validate($element, $form_state);

    $expected = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'path' => 'public://iconomist/test2.jpg',
            'fid' => 22,
          ),
        ),
      ),
    );
    $this->assertEquals($expected, $form_state);
  }

  /**
   * Validate sets a 'Upload failed' form error when given an invalid file path.
   *
   * @test
   */
  public function validateSetsUploadFailedErrorForInvalidFilePath() {
    $element = array(
      '#parents' => array(1 => 1),
      'upload' => 'upload_contents',
    );
    $form_state = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'upload' => 29,
            'path' => '',
          ),
        ),
      ),
    );

    Iconomist::validate($element, $form_state);

    $expected = array(
      'upload_contents' => t('Upload failed'),
    );
    $this->assertEquals($expected, get_form_errors());
  }

  /**
   * Validate sets the file ID when a valid file upload is provided.
   *
   * @test
   */
  public function validateSetsFileIdForValidFileUploadPath() {
    $element = array(
      '#parents' => array(1 => 1),
      'upload' => 'upload_contents',
    );
    $form_state = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'upload' => 21,
            'path' => '',
          ),
        ),
      ),
    );

    Iconomist::validate($element, $form_state);

    $expected = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'fid' => 21,
            'path' => '/path/to/test1.jpg',
          ),
        ),
      ),
    );
    $this->assertEquals($expected, $form_state);
  }

  /**
   * Validate removes a file upload when no file is specified.
   *
   * @test
   */
  public function validateRemovesFileUploadAndGivesNoErrorWhenNoFileChosen() {
    $element = array(
      '#parents' => array(1 => 1),
      'upload' => 'upload_contents',
    );
    $form_state = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'upload' => FALSE,
            'path' => FALSE,
          ),
        ),
      ),
    );

    Iconomist::validate($element, $form_state);

    $expected = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
        ),
      ),
    );
    $this->assertEquals($expected, $form_state);
  }

  /**
   * Validate removes file usage when the file is changed.
   *
   * @test
   */
  public function validateRemovesFileUsageWhenFileChanged() {
    $element = array(
      '#parents' => array(1 => 1),
      'upload' => 'upload_contents',
    );
    $form_state = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'upload' => FALSE,
            'path' => 'public://iconomist/test3.jpg',
          ),
        ),
      ),
      'storage' => array(
        'iconomist_num_icons' => 1,
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'path' => 'public://iconomist/test2.jpg',
            'usage_id' => 3,
          ),
        ),
      ),
    );

    Iconomist::validate($element, $form_state);

    $expected = array(
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'path' => 'public://iconomist/test3.jpg',
          ),
        ),
      ),
      'storage' => array(
        'iconomist_num_icons' => 1,
        'iconomist_icons' => array(
          0 => array(),
          1 => array(
            'path' => 'public://iconomist/test2.jpg',
            'usage_id' => NULL,
          ),
        ),
      ),
    );
    $this->assertEquals($expected, $form_state);
  }

  /**
   * Settings_submit correctly removes file usage for now unused files.
   *
   * @test
   */
  public function submitRemovesFileUsageForFilesNoLongerInUse() {
    $form = array();
    $form_state = array(
      'build_info' => array(
        'args' => array(
          '0' => 'foo',
        ),
      ),
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(
            'path' => 'public://iconomist/test1.jpg',
            'fid' => 21,
            'usage_id' => 2,
          ),
        ),
      ),
      'storage' => array(
        'iconomist_num_icons' => 1,
        'iconomist_icons' => array(
          0 => array(
            'path' => 'public://iconomist/test1.jpg',
            'usage_id' => 2,
          ),
          1 => array(
            'path' => 'public://iconomist/test2.jpg',
            'usage_id' => 3,
          ),
        ),
      ),
    );

    Iconomist::settingsSubmit($form, $form_state);

    $deleted = MockDrupalFunctions::fileUsageDeleted();
    $expected = array('22');

    $this->assertEquals($expected, $deleted);
  }

  /**
   * Settings_submit correctly persists file usage for newly used files.
   *
   * @test
   */
  public function submitPersistsFileUsageForFilesNewlyInUse() {
    $form = array();
    $form_state = array(
      'build_info' => array(
        'args' => array(
          '0' => 'foo',
        ),
      ),
      'triggering_element' => array(
        '#limit_validation_errors' => FALSE,
      ),
      'values' => array(
        'iconomist_icons' => array(
          0 => array(
            'path' => 'public://iconomist/test1.jpg',
            'fid' => 21,
            'usage_id' => 2,
          ),
          1 => array(
            'path' => 'public://iconomist/test2.jpg',
            'fid' => 22,
            'usage_id' => 3,
          ),
          2 => array(
            'path' => 'public://iconomist/test3.jpg',
            'fid' => 23,
            'usage_id' => NULL,
          ),
        ),
      ),
      'storage' => array(
        'iconomist_num_icons' => 1,
        'iconomist_icons' => array(
          0 => array(
            'path' => 'public://iconomist/test1.jpg',
            'usage_id' => 2,
          ),
          1 => array(
            'path' => 'public://iconomist/test2.jpg',
            'usage_id' => 3,
          ),
        ),
      ),
    );

    Iconomist::settingsSubmit($form, $form_state);

    $deleted = MockDrupalFunctions::fileUsageDeleted();
    $expected = array('22');

    $this->assertEquals($expected, $deleted);
  }

  /**
   * Preprocess_html does nothing if toggle is off.
   *
   * @test
   */
  public function preprocessHtmlDoesNothingIfToggleOff() {
    $vars = array();
    MockDrupalFunctions::theme_set_setting('toggle_iconomist', FALSE);
    $icons = self::$settings['foo']['iconomist_icons'];
    MockDrupalFunctions::theme_set_setting('iconomist_icons', $icons);

    Iconomist::preprocessHtml($vars);

    $links = MockDrupalFunctions::get_html_head_links();
    $this->assertEmpty($links);
  }

  /**
   * Preprocess_html adds all chosen icons to the html head with attributes.
   *
   * @test
   */
  public function preprocessHmlAddsIconsToHtmlHeadWithAttributes() {
    $vars = array();
    MockDrupalFunctions::theme_set_setting('toggle_iconomist', TRUE);

    $icons = self::$settings['foo']['iconomist_icons'];
    MockDrupalFunctions::theme_set_setting('iconomist_icons', $icons);

    Iconomist::preprocessHtml($vars);

    $links = MockDrupalFunctions::get_html_head_links();
    $expected = array(
      'head' => array(
        0 => array(
          'rel' => 'icon',
          'href' => 'public://iconomist/test1.jpg',
          'type' => 'image/jpeg',
        ),
        1 => array(
          'rel' => 'icon',
          'href' => 'public://iconomist/test2.jpg',
          'type' => 'image/jpeg',
          'sizes' => '64x64',
        ),
      ),
    );
    $this->assertEquals($expected, $links);
  }

}
