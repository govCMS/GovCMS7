<?php

namespace GovCMS\govCMSExtension\Context;

use Drupal\DrupalExtension\Context\DrupalSubContextInterface;
use Drupal\DrupalDriverManager;
use Behat\Mink\Exception\ExpectationException;
use Drupal\DrupalExtension\Context\MinkContext;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;

/**
 * Contains step definitions for working with Chosen JS library.
 */
class ChosenContext implements DrupalSubContextInterface {

  private $drupal;
  protected $lastId;

  /**
   * Store Mink context.
   *
   * @var \Drupal\DrupalExtension\Context\MinkContext
   */
  private $minkContext;

  /**
   * Initializes context.
   */
  public function __construct(DrupalDriverManager $drupal) {
    $this->drupal = $drupal;
  }

  /**
   * Include Mink context.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();
    $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
  }

  /**
   * Helper function to retrieve Mink context.
   *
   * @return \Drupal\DrupalExtension\Context\MinkContext
   *   Mink class.
   */
  public function getMinkContext() {
    return $this->minkContext;
  }

  /**
   * Sets the specified Chosen element to a certain value.
   *
   * @When /^I set the chosen element "([^"]*)" to "([^"]*)"$/
   */
  public function iSetChosenElement($locator, $value) {
    $session = $this->getMinkContext()->getSession();
    $el = $session->getPage()->findField($locator);

    if (empty($el)) {
      throw new ExpectationException(t('No such select element @locator', array(
        '@value' => $value,
        '@locator' => $locator,
      )), $session);
    }

    $element_id = str_replace('-', '_', $el->getAttribute('id')) . '_chosen';

    $el = $session->getPage()->find('xpath', "//div[@id='{$element_id}']");

    if ($el->hasClass('chosen-container-single')) {
      // This is a single select element.
      $el = $session->getPage()->find('xpath', "//div[@id='{$element_id}']/a[@class='chosen-single']");
      $el->click();
    }
    elseif ($el->hasClass('chosen-container-multi')) {
      // This is a multi select element.
      $el = $session->getPage()->find('xpath', "//div[@id='{$element_id}']/ul[@class='chosen-choices']/li[@class='search-field']/input");
      $el->click();
    }

    $selector = "//div[@id='{$element_id}']/div[@class='chosen-drop']/ul[@class='chosen-results']/li[text() = '{$value}']";
    $el = $session->getPage()->find('xpath', $selector);

    if (empty($el)) {
      throw new ExpectationException(t('No such option @value in @locator', array(
        '@value' => $value,
        '@locator' => $locator,
      )), $session);
    }

    $el->click();
  }

}
