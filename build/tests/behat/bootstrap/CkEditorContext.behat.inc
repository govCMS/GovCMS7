<?php

namespace Acquia\govCMSExtension\Context;

use Behat\Mink\Exception\ExpectationException;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\MinkContext;

/**
 * Contains step definitions for working with CKEditor instances.
 */
class CkEditorContext extends DrupalSubContextBase {

  /**
   * The Mink context.
   *
   * @var MinkContext
   */
  protected $minkContext;

  /**
   * Gathers required contexts.
   *
   * @BeforeScenario
   */
  public function gatherContexts() {
    $this->minkContext = $this->getContext(MinkContext::class);
  }

  /**
   * Asserts that a CKEditor instance exists and is fully loaded.
   *
   * @param string $field
   *   (optional) The specific field with the editor enabled.
   *   If not provided will default to the first available
   *   instance.
   *
   * @return string
   *   A snippet of JavaScript for calling instance methods.
   *
   * @Given CKEditor for the :field field exists
   * @Given WYSIWYG for the :field field exists
   * @Then CKEditor for the :field field should exist
   * @Then WYSIWYG for the :field field should exist
   */
  public function assertEditor($field = NULL) {
    // If the field was specified.
    if (!empty($field)) {
      $node = $this->minkContext->assertSession()->fieldExists($field);
      $id = $node->getAttribute('id');
      $js = "CKEDITOR.instances['" . $id . "']";
    }
    else {
      $js = "CKEDITOR.instances['" . $this->getDefault() . "']";
    }

    $this->getSession()->wait(10000, "$js.status === 'ready'");

    return $js;
  }

  /**
   * Puts text or HTML into a CKEditor instance.
   *
   * @param string $text
   *   The text (or HTML) to insert into the editor.
   * @param string $field
   *   (optional) The field that has WYSIWYG.
   *
   * @When I put :text into CKEditor
   * @When I put :text into CKEditor :field (field)
   * @When I put :text into WYSIWYG
   * @When I put :text into WYSIWYG of :field (field)
   */
  public function insert($text, $field = NULL) {
    $js = $this->assertEditor($field);
    $this->getSession()->executeScript("$js.insertHtml('$text');");
  }

  /**
   * Asserts that a CKEditor's content contains a snippet of text.
   *
   * @param string $text
   *   The text (or HTML) snippet to look for.
   * @param string $id
   *   (optional) The editor instance ID.
   *
   * @throws ExpectationException
   *   If the editor does not contain the specified text.
   *
   * @Then CKEditor should contain :text
   * @Then CKEditor :id should contain :text
   */
  public function assertEditorContains($text, $id = NULL) {
    $position = strpos($this->getContent($id), $text);

    if ($position == FALSE) {
      throw new ExpectationException(
        'Expected CKEditor ' . $id . ' to contain "' . $text . '".',
        $this->getSession()->getDriver()
      );
    }
  }

  /**
   * Assert that a CKEditor's content matches a regular expression.
   *
   * @param string $expr
   *   The regular expression to match.
   * @param string $id
   *   (optional) The editor instance ID.
   *
   * @throws ExpectationException
   *   If the expression does not match.
   *
   * @Then CKEditor should match :expression
   * @Then CKEditor :id should match :expression
   */
  public function assertEditorMatch($expr, $id = NULL) {
    $match = preg_match($expr, $this->getContent($id));

    if ($match == 0) {
      throw new ExpectationException(
        'Expected CKEditor ' . $id . ' to match "' . $expr . '".',
        $this->getSession()->getDriver()
      );
    }
  }

  /**
   * Gets the content of a CKEditor instance.
   *
   * @param string $id
   *   (optional) The editor instance ID.
   *
   * @return string
   *   The HTML content of the editor.
   */
  protected function getContent($id = NULL) {
    $js = $this->assertEditor($id);
    return $this->getSession()->evaluateScript("$js.getData()");
  }

  /**
   * Executes a CKEditor command.
   *
   * @param string $command
   *   The command ID, as known to CKEditor's API.
   * @param string $id
   *   (optional) The editor instance ID.
   * @param mixed $data
   *   Additional data to pass to the executed command.
   *
   * @throws ExpectationException
   *   If the command cannot be executed (i.e., returns a falsy value).
   *
   * @When I execute the :command command in CKEditor
   * @When I execute the :command command in CKEditor :id
   */
  public function execute($command, $id = NULL, $data = NULL) {
    $js = $this->assertEditor($id);

    $session = $this->getSession();

    $return = drupal_json_decode($session->evaluateScript("$js.execCommand('$command', " . drupal_json_encode($data) . ')'));

    if (empty($return)) {
      throw new ExpectationException(
        'CKEditor command ' . $command . ' returned ' . var_export($return, TRUE) . ', expected truthy.',
        $session->getDriver()
      );
    }
  }

  /**
   * Returns the first available CKEditor instance ID.
   *
   * @return string|false
   *   The first CKEditor instance ID, or FALSE if there are no instances.
   */
  protected function getDefault() {
    $keys = $this->getKeys();
    return reset($keys);
  }

  /**
   * Returns all CKEditor instance IDs.
   *
   * @return string[]
   *   The CKEditor instance IDs.
   */
  protected function getKeys() {
    $keys = $this
      ->getSession()
      ->evaluateScript('Object.keys(CKEDITOR.instances).join(",")');

    return explode(',', $keys);
  }

}
