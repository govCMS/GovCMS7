<?php
/**
 * @file
 * Tests for Agov install profile.
 * @author Tim Eisenhuth tim dot eisenhuth at previousnext dot com dot au
 */

class AgovTestBase extends DrupalWebTestCase {

  protected $profile = 'agov';
  protected $testUser;

  /**
   * Provides test info.
   */
  public static function getInfo() {
    return array(
      'name'  => 'Agov tests',
      'description'  => "Tests for Agov.",
      'group' => 'Agov',
    );
  }

  /**
   * Setup function.
   */
  public function setUp() {
    parent::setUp(array(
      'agov_content_event',
      'agov_content_publication',
      'agov_content_blog',
      'agov_content_media_release',
      'agov_content_news_article',
      'agov_content_promotion',
      'agov_content_standard_page',
    ));

    // Continue setup of default content.
    _agov_default_beans();
    _agov_default_news_beans();

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

    variable_set('site_name', 'Agov');
    variable_set('site_slogan', 'Agov website');

  }

}
