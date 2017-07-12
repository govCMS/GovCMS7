Feature: Social Media Links

  As a user able to administer blocks
  I want to have a configurable block provided
  So that minimal configuration for social media links is required out of the box

  @api @javascript
  Scenario: The social media links block should be available OOTB
    Given I am logged in as a user with the "administer blocks" permission
    When I go to "/admin/structure/block/manage/govcms_social_links/services/configure"
    Then the "edit-regions-govcms-barton" select list should be set to "sidebar_second"
    And I fill in the following:
    | facebook  | http://example.com/facebook  |
    | twitter   | http://example.com/twitter   |
    | youtube   | http://example.com/youtube   |
    | vimeo     | http://example.com/vimeo     |
    | flickr    | http://example.com/flickr    |
    | instagram | http://example.com/instagram |
    | linkedin  | http://example.com/linkedin  |
    | rss       | http://example.com/rss       |
    | email     | http://example.com/email     |
    And I press "Save block"
    Then I should see "The block configuration has been saved."
    When I am on the homepage
    Then I should see the heading "Connect with us" in the "sidebar_second" region
    And the response should contain "<a href=\"http://example.com/facebook\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/facebook.png\" alt=\"Facebook\" title=\"Facebook\"></a>"
    And the response should contain "<a href=\"http://example.com/twitter\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/twitter.png\" alt=\"Twitter\" title=\"Twitter\"></a>"
    And the response should contain "<a href=\"http://example.com/youtube\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/youtube.png\" alt=\"Youtube\" title=\"Youtube\"></a>"
    And the response should contain "<a href=\"http://example.com/vimeo\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/vimeo.png\" alt=\"Vimeo\" title=\"Vimeo\"></a>"
    And the response should contain "<a href=\"http://example.com/flickr\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/flickr.png\" alt=\"Flickr\" title=\"Flickr\"></a>"
    And the response should contain "<a href=\"http://example.com/instagram\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/instagram.png\" alt=\"Instagram\" title=\"Instagram\"></a>"
    And the response should contain "<a href=\"http://example.com/linkedin\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/linkedin.png\" alt=\"Linkedin\" title=\"Linkedin\"></a>"
    And the response should contain "<a href=\"http://example.com/rss\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/rss.png\" alt=\"RSS Feed\" title=\"RSS Feed\"></a>"
    And the response should contain "<a href=\"http://example.com/email\"><img typeof=\"foaf:Image\" src=\""
    And the response should contain "/profiles/govcms/modules/custom/govcms_social_links/images/email.png\" alt=\"Email\" title=\"Email\"></a>"
    And I go to "/admin/structure/block/manage/govcms_social_links/services/configure"
    When for "Linkedin URL" I enter "https://www.linkedin.com/"
    And I press "Save block"
    Then I should see "The block configuration has been saved."
