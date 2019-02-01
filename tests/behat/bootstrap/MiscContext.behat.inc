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
      throw new \Exception(sprintf('Field "%s" was not found.', $field));
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

  /**
   * @Given I wait :arg1 seconds
   */
  public function iWaitSeconds($arg1) {
    sleep($arg1);
  }

  /**
   * Click any element.
   *
   * @Given I click the :selector element
   *
   * @see https://stackoverflow.com/a/33672497/1023773
   */
  public function iClickTheElement($selector) {
    $page = $this->getSession()->getPage();
    $element = $page->find('css', $selector);

    if (empty($element)) {
      throw new Exception("No html element found for selector '{$selector}'");
    }

    $element->click();
  }


    /**
     * Expands all moodleform's fields, including collapsed fieldsets and advanced fields if they are present.
     * @Given /^I expand all fieldsets$/
     */
    public function i_expand_all_fieldsets() {
        $this->expand_all_fields();
    }

    /**
     * Expands all moodle form fieldsets if they exists.
     *
     * Externalized from i_expand_all_fields to call it from
     * other form-related steps without having to use steps-group calls.
     *
     * @throws ElementNotFoundException Thrown by behat_base::find_all
     * @return void
     */
    protected function expand_all_fields() {
      $page = $this->getSession()->getPage();
        // We already know that we waited for the DOM and the JS to be loaded, even the editor
        // so, we will use the reduced timeout as it is a common task and we should save time.
        try {

            // Expand all fieldsets link - which will only be there if there is more than one collapsible section.
            $expandallxpath = "//div[@class='collapsible-actions']" .
                "//a[contains(concat(' ', @class, ' '), ' collapseexpand ')]" .
                "[not(contains(concat(' ', @class, ' '), ' collapse-all '))]";
            // Else, look for the first expand fieldset link.
            $expandonlysection = "//legend[@class='ftoggler']" .
                    "//a[contains(concat(' ', @class, ' '), ' fheader ') and @aria-expanded = 'false']";

            $collapseexpandlink = $page->find('xpath', $expandallxpath . '|' . $expandonlysection,
                    false, false, self::REDUCED_TIMEOUT);
            $collapseexpandlink->click();

        } catch (ElementNotFoundException $e) {
            // The behat_base::find() method throws an exception if there are no elements,
            // we should not fail a test because of this. We continue if there are not expandable fields.
        }

        // Different try & catch as we can have expanded fieldsets with advanced fields on them.
        try {

            // Expand all fields xpath.
            $showmorexpath = "//a[normalize-space(.)='" . get_string('showmore', 'form') . "']" .
                "[contains(concat(' ', normalize-space(@class), ' '), ' moreless-toggler')]";

            // We don't wait here as we already waited when getting the expand fieldsets links.
            if (!$showmores = $this->getSession()->getPage()->findAll('xpath', $showmorexpath)) {
                return;
            }

            if ($this->getSession()->getDriver() instanceof \DMore\ChromeDriver\ChromeDriver) {
                // Chrome Driver produces unique xpaths for each element.
                foreach ($showmores as $showmore) {
                    $showmore->click();
                }
            } else {
                // Funny thing about this, with findAll() we specify a pattern and each element matching the pattern
                // is added to the array with of xpaths with a [0], [1]... sufix, but when we click on an element it
                // does not matches the specified xpath anymore (now is a "Show less..." link) so [1] becomes [0],
                // that's why we always click on the first XPath match, will be always the next one.
                $iterations = count($showmores);
                for ($i = 0; $i < $iterations; $i++) {
                    $showmores[0]->click();
                }
            }

        } catch (ElementNotFoundException $e) {
            // We continue with the test.
        }

    }

}
