<?php
/**
 * @file
 * Implements base testing of basic module functions.
 * @author Edward Murrell <edward@catalyst-au.net>
 */

namespace tdd7\testframework {
  require_once ('FrameworkTemplateTestCase.inc');

  abstract class DrupalFrameworkTestCase extends TemplateTestBase {
    /**
     * Checks validity of Drupal menu arrays
     *  Asserts the following:
     *  - Menu is not empty
     *  - Passes each item to checkMenuItemValidity
     * @TODO : add check for valid menu keys (ie; url path)
     * @param $menu A filled menu array.
     */
    public function checkMenuValidity($menu) {
      $this->assertTrue(is_array($menu), 'Menu variable is not an array.');
      $this->assertNotEmpty($menu);
      foreach($menu as $path => $item) {
        $this->checkMenuItemValidity($item, $path);
      }
    }

    /**
     * Checks validity of Drupal menu items
     *  Asserts the following:
     *  - 'page callback' exists and points to a real function
     * @param $item A drupal menu item
     * @param $key Identifiying key (path) of the menu item
     */
    public function checkMenuItemValidity($item, $key = '') {
      $this->assertArrayHasKey('page callback', $item, "Menu item {$key} missing 'page callback'.");
      $function = $item['page callback'];
      $this->assertTrue(is_string($function),       "Menu item {$key} 'page callback' is not a string.");
      $this->assertNotEmpty($function,              "Menu item {$key} 'page callback' is empty.");
      $this->assertTrue(function_exists($function), "Menu item {$key} 'page callback' function does not exist.");

      if (array_key_exists('page arguments', $item)) {
        $this->assertTrue(is_array($item['page arguments']),  "Menu item {$key} 'page arguments' is not an array.");
      }
    }

    /**
     * Checks if a supplied form function is valid. Resulting form array is
     *  passed to checkFormArrayValidity()
     * @param type $function
     */
    public function checkFormFunctionValidity($function) {
      $this->assertTrue(function_exists($function), "Function '{$function}' does not exist.");
      $form_state = array();
      $form = \drupal_get_form($function);
      $this->assertArrayHasKey('#build_id', $form);
    }

    /**
     * Checks if the block_info and modules for a given module are valid
     *  according to the specifications at:
     *  https://api.drupal.org/api/drupal/modules!block!block.api.php/function/hook_block_info/7
     * @param string $module module name to check.
     */
    public function checkModuleBlockInfo($module = '') {
      if (empty($module)) {
        throw new \Exception('Supplied argument for checkModuleBlocks cannot be null');
      }
      $info_callback = "{$module}_block_info";
      $this->assertTrue(function_exists($info_callback), "Expected function '{$info_callback}' does not exist");
      $info = call_user_func($info_callback);
      $this->assertTrue(is_array($info));
      foreach ($info as $delta => $data) {
        $this->assertTrue(is_string($delta));
        $this->assertTrue(is_array($data));

        // Check that data has an info string that is not empty
        $this->assertArrayHasKey('info', $data);
        $this->assertTrue(is_string($delta));
        $this->assertNotEmpty($data['info']);

        $this->checkModuleBlockView($module, $delta);
      }
    }

    /**
     * Checks the validity of data returned from hook_block_view. This is
     *  automatically called from checkModuleBlockInfo
     * @param type $module module name to check
     * @param type $delta delta string to pass to hook_block_view
     */
    public function checkModuleBlockView($module = '', $delta = '') {
      $view_callback = "{$module}_block_view";
      $this->assertTrue(function_exists($view_callback), "Expected function '{$view_callback}' does not exist");
      $emptyresult = call_user_func($view_callback);
      if (!empty($emptyresult)) {
        $this->assertArrayHasKey('subject', $emptyresult, "Function '{$view_callback}' does not contain expected key 'subject'.");
        $this->assertArrayHasKey('content', $emptyresult, "Function '{$view_callback}' does not contain expected key 'content'.");

        $this->assertEquals('', $emptyresult['subject'], "Function '{$view_callback}' does not return empty string for null delta argument in key 'subject'.");
        $this->assertEquals('', $emptyresult['content'], "Function '{$view_callback}' does not return empty string for null delta argument in key 'content'.");
      }

      $result = call_user_func($view_callback, $delta);
      $this->assertArrayHasKey('subject', $result);
      $this->assertArrayHasKey('content', $result);
      if (is_array($result['content'])) {
        $this->AssertValidHtml5(drupal_render($result['content']));
      } else {
        $this->AssertValidHtml5($result['content']);
      }
    }

    /**
     * A test so that child classes of \PHPUnit_Framework_TestCase don't fail
     *  due to a lack of tests. Also should catch changes to the class name.
     *
     * Test that this class is being inheritted properly.
     */
    public function testSelfClassName() {
      $this->assertEquals('tdd7\testframework\DrupalFrameworkTestCase', __CLASS__);
    }
  }
}

