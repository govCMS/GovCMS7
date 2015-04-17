<?php
/**
 * @file
 * Tests for GovCMS install profile.
 *
 * The original foundation for the govCMS distribution is aGov; the Drupal distribution created by PreviousNext to provide a core set of elements, functionality and features that can be used to develop government websites
 *
 * @copyright Copyright(c) 2015 Commonwealth of Australia as represented by Department of Finance
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Department of Finance
 */

class GovCMSTestBase extends DrupalWebTestCase {

  protected $profile = 'govcms';
  protected $testUser;

  /**
   * Provides test info.
   */
  public static function getInfo() {
    return array(
      'name'  => 'GovCMS tests',
      'description'  => "Tests for GovCMS.",
      'group' => 'GovCMS',
    );
  }

  /**
   * Setup function.
   */
  public function setUp() {
    parent::setUp(array(
      'govcms_content_event',
      'govcms_content_publication',
      'govcms_content_blog',
      'govcms_content_media_release',
      'govcms_content_news_article',
      'govcms_content_promotion',
      'govcms_content_standard_page',
    ));

    // Continue setup of default content.
    _govcms_default_beans();
    _govcms_default_news_beans();

    // Create a user.
    $this->testUser = $this->drupalCreateUser(array(
      'access content',
      'view revisions',
      'view all unpublished content',
      'create blog_article content',
      'create event content',
      'create media_release content',
      'create news_article content',
      'create footer_teaser content',
      'create publication content',
      'create slide content',
      'create page content',
      'create webform content',
      'edit any webform content',
      'search all content',
      'bypass workbench moderation',
      'administer nodes',
      'moderate content from draft to needs_review',
      'moderate content from needs_review to published',
      'administer files',
    ));

    variable_set('site_name', 'GovCMS');
    variable_set('site_slogan', 'GovCMS website');

  }

}
