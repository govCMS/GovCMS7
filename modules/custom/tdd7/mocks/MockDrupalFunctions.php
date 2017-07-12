<?php
/**
 * @file
 * Mocked up Drupal core functions
 * @author Edward Murrell <edward@catalyst-au.net>
 * @todo: Make this part of DrupalApiService
 */

namespace tdd7\testframework\mocks {
  class MockDrupalFunctions {
    private static $variables = array();
    private static $form_errors = array();
    private static $last_drupal_goto = null;
    private static $last_drupal_json_output = null;
    private static $theme_settings = array();
    private static $htmlHeadLinks = array();
    private static $managedFiles = array();
    private static $fileUsageDeleted = array();

    /**
     * Mock version of variable_set()
     * Original documentation: https://api.drupal.org/api/drupal/includes!bootstrap.inc/function/variable_set/7
     * @param string $name: The name of the variable to set.
     * @param string $value: The value to set. This can be any PHP data type; these
     *  functions take care of serialization as necessary.
     */
    public static function variable_set($name, $value) {
      self::$variables[$name] = $value;
    }

    /**
     * Mock version of variable_get().
     * Returns the mock variables, if set. If a fake variable is not set, then
     *  the function will attempt to return a version from Drupal. If this does
     *  not exist, then the $default will be returned.
     * Original documentation: https://api.drupal.org/api/drupal/includes!bootstrap.inc/function/variable_get/7
     * @param string $name: The name of the variable to return.
     * @param string $default: The default value to use if this variable has
     *  never been set.
     * @return fake variable, real variable, or default
     */
    public static function variable_get($name, $default = NULL) {
      if (array_key_exists($name, self::$variables)) {
        return self::$variables[$name];
      } else {
        return \variable_get($name, $default);
      }
    }

    /**
     * Mock form_set_error
     * @param type $name field name of error
     * @param type $message Error message
     * @param type $limit_validation_errors
     */
    public static function form_set_error($name = NULL, $message = '', $limit_validation_errors = NULL) {
      if ($name != NULL) {
        self::$form_errors[$name] = $message;
      }
    }

    /**
     * Returns all the currently stored errors
     * @return array Array of all errors so far
     */
    public static function form_get_errors() {
      return self::$form_errors;
    }

    /**
     * Clears the internal mock form error list.
     */
    public static function form_clear_error() {
      self::$form_errors = array();
    }

    /**
     * Mock drupal_goto function.
     * Unlike the real drupal_goto, this will return.
     * @param string $url Relative or absolute URL to pass.
     */
    public static function drupal_goto($url = '') {
      self::$last_drupal_goto = $url;
    }

    /**
     * Returns the last URL passed to Mock drupal_goto function. The URL string
     * is not processed in any way.
     * @return string|null last url passed to drupal_goto.
     */
    public static function GetLastDrupalGoto() {
      return self::$last_drupal_goto;
    }

    /**
     * Converts the input to JSON and saves it.
     *  Normally, this function would echo the result of the JSON conversion to
     *  stdout. For testing purposes, this will be saved in a internal variable,
     *  which can be retrieved with GetLastDrupalJsonOutput
     * @param type $var
     * @return type
     */
    public static function drupal_json_output($var = null) {
      self::$last_drupal_json_output = drupal_json_encode($var);
    }

    /**
     * Returns the JSON output sent via drupal_json_output()
     * @return string JSON output.
     */
    public static function GetLastDrupalJsonOutput() {
      return self::$last_drupal_json_output;
    }

    /**
     * Mock version of theme_set_setting()
     * Original documentation: https://api.drupal.org/api/drupal/includes!bootstrap.inc/function/variable_set/7
     * @param string $name: The name of the variable to set.
     * @param string $value: The value to set. This can be any PHP data type; these
     *  functions take care of serialization as necessary.
     */
    public static function theme_set_setting($name, $value, $theme = NULL) {
      if (is_null($theme)) {
        $theme = '';
      }

      self::$theme_settings[$theme][$name] = $value;
    }

    /**
     * Mock version of theme_get_setting().
     *
     * Returns the mock theme setting, if set. If a fake value is not set, then
     *  the function will attempt to return a version from Drupal.
     * Original documentation: https://api.drupal.org/api/drupal/includes%21theme.inc/function/theme_get_setting/7.x

     * @param string $name
     *   The name of the setting to return.
     * @param string $theme
     *   The name of the theme or NULL for the sitewide default.
     *
     * @return mixed
     *   The fake value or real value.
     */
    public static function theme_get_setting($name, $theme = NULL) {
      if (!is_null($theme) && array_key_exists($theme, self::$theme_settings)) {
        $focus = self::$theme_settings[$theme];
      }
      else {
        $focus = self::$theme_settings[''];
      }
      if (array_key_exists($name, $focus)) {
        return $focus[$name];
      }
      else {
        return \theme_get_setting($name, $theme);
      }
    }

    /**
     * Mock version of drupal_add_html_head_link()
     * Original documentation: https://api.drupal.org/api/drupal/includes%21common.inc/function/drupal_add_html_head_link/7.x
     *
     * @param array $attributes
     *   The attributes of the link to be added.
     * @param bool $header
     *   Whether a 'Link:' HTTP header should also be added.
     */
    public static function drupal_add_html_head_link($attributes, $header = FALSE) {
      if ($header) {
        self::$htmlHeadLinks['headers'][] = $attributes;
      }

      self::$htmlHeadLinks['head'][] = $attributes;
    }

    /**
     * Return any data used to invoke drupal_add_html_head_link, above.
     *
     * @return array
     *   The values passed to drupal_add_html_head_link.
     */
    public static function get_html_head_links() {
      return self::$htmlHeadLinks;
    }

    /**
     * Mock version of file_load()
     * Original documentation: https://api.drupal.org/api/drupal/includes%21file.inc/function/file_load/7.x
     *
     * @param integer $fid
     *   The file ID to load.
     *
     * @return mixed
     *   An object representing the file, or FALSE if the file was not found.
     */
    public static function file_load($fid) {
      return key_exists($fid, self::$managedFiles) ? self::$managedFiles[$fid] : FALSE;
    }

    /**
     * Mock version of file_save()
     * Original documentation: https://api.drupal.org/api/drupal/includes%21file.inc/function/file_save/7.x
     *
     * @param stdClass $file
     *   The file object to be saved.
     */
    public static function file_save(\stdClass $file) {
      self::$managedFiles[$file->fid] = $file;
    }

    /**
     * Mock version of file_usage_delete()
     * Original documentation: https://api.drupal.org/api/drupal/includes%21file.inc/function/file_usage_delete/7.x
     *
     * @param $file
     *   A file object.
     * @param $module
     *   The name of the module using the file.
     * @param $type
     *   (optional) The type of the object that contains the referenced file. May
     *   be omitted if all module references to a file are being deleted.
     * @param $id
     *   (optional) The unique, numeric ID of the object containing the referenced
     *   file. May be omitted if all module references to a file are being deleted.
     * @param $count
     *   (optional) The number of references to delete from the object. Defaults to
     *   1. 0 may be specified to delete all references to the file within a
     *   specific object.
     */
    public static function file_usage_delete(\stdClass $file) {
      self::$fileUsageDeleted[] = $file->fid;
    }

    /**
     * Get the list of files that had usage deleted.
     *
     * @return array
     *   List of file IDs for which file_usage_delete was invoked.
     */
    public static function fileUsageDeleted() {
      return self::$fileUsageDeleted;
    }

    /**
     * Create a URL for a file.
     *
     * @param $uri
     *   The URI to a file for which we need an external URL, or the path to a
     *   shipped file.
     *
     * @return
     *   A string containing a URL that may be used to access the file.
     *   If the provided string already contains a preceding 'http', 'https', or
     *   '/', nothing is done and the same string is returned. If a stream wrapper
     *   could not be found to generate an external URL, then FALSE is returned.
     */
    public static function file_create_url($uri) {
      // Just return the original string to make the result nice and
      // predictable, even if it won't always be correct.
      return $uri;
    }

  }
}
