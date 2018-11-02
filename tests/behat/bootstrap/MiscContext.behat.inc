<?php

namespace GovCMS\govCMSExtension\Context;

use Behat\Mink\Element\Element;
use Behat\Mink\Exception\Exception;
use Drupal\DrupalExtension\Context\DrupalSubContextBase;

/**
 * Contains various step definitions to extend default possibilities.
 */
class MiscContext extends DrupalSubContextBase {

  /**
   * Check that a particular option on a select list is selected.
   *
   * @Then the :arg1 select list should be set to :arg2
   */
  public function theSelectListShouldBeSetTo($arg1, $arg2) {
    try {
      $select = $this->getSession()->getPage()->find('css', '#' . $arg1);
    }
    catch (Exception $e) {
      throw new \Exception(sprintf("No select list with id '%s' found on the page '%s'.", $arg1, $this->getSession()->getCurrentUrl()));
    }
    if ($select->getValue() != $arg2) {
      throw new \Exception(sprintf("Select list with id '%s' was found but not set to value '%s'.", $arg1, $arg2));
    }
  }

  /**
   * Checks that a checkbox in a row containing specific text is ticked.
   *
   * Lets you provide a piece of text to use in locating a table row and another
   * piece of text to find a checkbox within that row, then test whether the
   * checkbox is ticked. The use of text avoids reliance on a table having
   * particular content order and makes the test much more readable:
   *
   * "And the checkbox named "enabled" in table row with text "Australian
   * Government ISM Policy (Strong)" should be checked".
   *
   * @param string $rowMatch
   *   The text to match in searching for a table row.
   * @param string $textMatch
   *   The pattern to use in searching for the checkbox (eg. enabled)
   *
   * @Then the checkbox named :rowMatch in table row with text :textMatch should be checked
   */
  public function theCheckboxNamedInTableRowWithTextShouldBeChecked($rowMatch, $textMatch) {
    // Find the table rows containing $rowMatch.
    $rows = $this->getTableRowWithElement($this->getSession()->getPage(), $textMatch);
    // Loop through all found rows and try to find our element.
    foreach ($rows as $row) {
      $checkbox = $row->find('css', sprintf('[id*="%s"]', $rowMatch));
      if (empty($checkbox)) {
        throw new \Exception(sprintf('No checkbox named "%s" found in the table row with text "%s"', $rowMatch, $textMatch, $this->getSession()->getCurrentUrl()));
      }
      if (!$checkbox->isChecked()) {
        throw new \Exception(sprintf("Checkbox with id '%s' in a row containing '%s' was found but was not checked.", $textMatch, $rowMatch));
      }
    }
  }

  /**
   * Checks that a checkbox in a row containing some text is NOT ticked.
   *
   * @param string $rowMatch
   *   The text to match in searching for a table row.
   * @param string $textMatch
   *   The pattern to use in searching for the checkbox (eg. enabled)
   *
   * @Then the checkbox named :rowMatch in table row with text :textMatch should not be checked
   */
  public function theCheckboxNamedInTableRowWithTextShouldBeNotChecked($rowMatch, $textMatch) {
    // Find the table rows containing $rowMatch.
    $rows = $this->getTableRowWithElement($this->getSession()->getPage(), $textMatch);
    // Loop through all found rows and try to find our element.
    foreach ($rows as $row) {
      $checkbox = $row->find('css', sprintf('[id*="%s"]', $rowMatch));
      if (empty($checkbox)) {
        throw new \Exception(sprintf('No checkbox named "%s" found in the table row with text "%s"', $rowMatch, $textMatch, $this->getSession()->getCurrentUrl()));
      }
      if ($checkbox->isChecked()) {
        throw new \Exception(sprintf("Checkbox with id '%s' in a row containing '%s' was found but was checked.", $textMatch, $rowMatch));
      }
    }
  }

  /**
   * Find an element in the table rows containing given element.
   *
   * @Then I should see (the text ):findElement in a table row containing (the text ):rowElement
   */
  public function assertTextInTableRowWithElement($findText, $rowElement) {
    $rows = $this->getTableRowWithElement($this->getSession()->getPage(), $rowElement);
    // Loop through all found rows and try to find our element.
    foreach ($rows as $row) {
      if (strpos($row->getText(), $findText) !== FALSE) {
        return TRUE;
      }
    }
    throw new \Exception(sprintf('Failed to find a row with the element "%s" that also contains "%s" on the page %s', $rowElement, $findText, $this->getSession()->getCurrentUrl()));
  }

  /**
   * Retrieve a table row(s) containing specified element id|name|label|value.
   *
   * @param \Behat\Mink\Element\Element $element
   *   The page object to search within.
   * @param string $rowElement
   *   The text to search for to identify the table row(s).
   *
   * @return \Behat\Mink\Element\NodeElement
   *   The table rows, if found.
   *
   * @throws \Exception
   *   When no such match is found.
   */
  public function getTableRowWithElement(Element $element, $rowElement) {
    $rows = $element->findAll('css', sprintf('table tr:contains("%s")', $rowElement));
    if (empty($rows)) {
      throw new \Exception(sprintf('No rows containing the element with id|name|label|value "%s" found on the page %s', $rowElement, $this->getSession()->getCurrentUrl()));
    }

    return $rows;
  }

  /**
   * Triggers click on field labels.
   *
   * This is helpful when an input is wrapped within a label or
   * in case of checkboxes and radio buttons which can be
   * selected if their label is clicked.
   *
   * @Then /^I click the label of the "([^"]*)" field$/
   *
   * @throws \Exception
   *   When no element is found.
   */
  public function iClickLabelofField($field) {
    $session = $this->getSession();
    $driver = $session->getDriver();
    $page = $session->getPage();

    $element = $page->findField($field);
    if (empty($element)) {
      throw new \Exception(sprintf('Element @element was not found.', $element));
    }

    $elementID = $element->getAttribute('id');
    $label = $page->find('css', 'label[for="' . $elementID . '"]');

    // Click the label if it exists, otherwise, click the element itself.
    if (!empty($label)) {
      $driver->click($label->getXPath());
    }
    else {
      $driver->click($element->getXPath());
    }
  }

}
