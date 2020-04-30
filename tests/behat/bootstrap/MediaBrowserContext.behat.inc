<?php

namespace GovCMS\govCMSExtension\Context;

use Drupal\DrupalExtension\Context\DrupalSubContextBase;
use Drupal\DrupalExtension\Context\MinkContext;

/**
 * Contains step definitions for working with media browsers.
 */
class MediaBrowserContext extends DrupalSubContextBase {

  /**
   * The Mink context.
   *
   * @var \Drupal\DrupalExtension\Context\MinkContext
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
   * Submits the media browser.
   *
   * @When I submit the media browser
   */
  public function submit() {
    $session = $this->getSession();

    // The entity browser frame will be destroyed, so we need to switch into
    // the main window and reach into the frame to submit the form. Ugh.
    // @TODO: Make this smarter, because we can't be sure that Save
    $this->minkContext->pressButton('Save');
    $session->switchToWindow();
    $this->minkContext->iWaitForAjaxToFinish();
  }

  /**
   * Opens an media browser for a particular field.
   *
   * @param string $field
   *   The field label.
   *
   * @throws \Exception
   *   If the field element does not exist on the page.
   *
   * @When I open the :field (field )media browser
   */
  public function openMediaBrowser($field) {
    $session = $this->getSession();
    $element = $session->getPage()->findField($field);
    if (empty($element)) {
      throw new \Exception(sprintf('Failed to find the field element "%s" on the page %s', $field, $session->getCurrentUrl()));
    }
    $link = $element->getParent()->findLink('Browse');
    if (empty($link)) {
      throw new \Exception(sprintf('Failed to find Media Browser for the field "%s" on the page %s', $field, $session->getCurrentUrl()));
    }
    $link->click();
    $this->minkContext->iWaitForAjaxToFinish();
    $session->switchToIFrame('mediaBrowser');
  }

  /**
   * Opens an media browser for a field in a particular field set.
   *
   * @param string $field
   *   The field label.
   * @param string $fieldset
   *   The name of a fieldset.
   *
   * @throws \Exception
   *   If the field or field set element does not exist on the page.
   *
   * @When I open the media browser for :field in :fieldset field set
   */
  public function openFieldsetMediaBrowser($field, $fieldset) {
    $session = $this->getSession();
    $element = $session->getPage()->find('xpath', '//span[@class="fieldset-legend"][text()="' . $fieldset . '"]')->getParent()->getParent();
    if (empty($fieldset)) {
      throw new \Exception(sprintf('Failed to find the field set "%s" on the page %s', $fieldset, $session->getCurrentUrl()));
    }
    $link = $element->findLink('Browse');
    if (empty($link)) {
      throw new \Exception(sprintf('Failed to find Media Browser in the fieldset "%s" on the page %s', $fieldset, $session->getCurrentUrl()));
    }
    $link->click();
    $this->minkContext->iWaitForAjaxToFinish();
    $session->switchToIFrame('mediaBrowser');
  }

  /**
   * Selects an item in an media browser view.
   *
   * @param int $n
   *   The one-based index of the item to select.
   * @param string $browser_id
   *   (optional) The media browser ID.
   *
   * @When I select item :n
   * @When I select item :n from the media browser
   * @When I select item :n from the :browser_id media browser
   */
  public function selectItem($n, $browser_id = NULL) {
    if ($browser_id) {
      $selector = 'form#media-browser-' . drupal_clean_css_identifier($browser_id) . '-form';
    }
    else {
      $selector = 'form[data-media-browser-uuid]';
    }

    /** @var \Behat\Mink\Element\NodeElement[] $items */
    $items = $this
      ->assertSession()
      ->elementExists('css', $selector)
      ->findAll('css', '[data-selectable]');

    $items[$n - 1]->click();
  }

}
