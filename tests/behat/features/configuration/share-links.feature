Feature: Share Links

  Ensure the configuration for Service Links is as expected.

  @api @javascript
  Scenario: Check that the default configuration is intact.
    Given I am logged in as a user with the "administer site configuration" permission
    When I visit "admin/config/services/service-links"
    Then I should see the heading "Service Links"
    And the "Append the following text to your URL" field should be empty
    And the "Choose a style" select field should be set to "Only Image"
    And the "Blog Article" checkbox should not be checked
    And the "Event" checkbox should be checked
    And the "Media Release" checkbox should be checked
    And the "News Article" checkbox should be checked
    And the "Promotion" checkbox should be checked
    And the "Publication" checkbox should be checked
    And the "Slide" checkbox should not be checked
    And the "Standard page" checkbox should be checked
    And the "Webform" checkbox should be checked
    And the "Tags" checkbox should not be checked
    And the "Full content" checkbox should not be checked
    And the "Teaser" checkbox should not be checked
    And the "RSS" checkbox should not be checked
    And the "Search index" checkbox should not be checked
    And the "Search result highlighting input" checkbox should not be checked
    And the "Compact" checkbox should not be checked
    And the "Tokens" checkbox should not be checked
    And the "Revision" checkbox should not be checked
    And the "All pages except those listed" radio option should be selected
    And the "Don't show links if the content is unpublished" checkbox should be checked
    And the "Don't show links if the actual user is the author of the node" checkbox should not be checked
    And the "How to fill the title tag" select field should be set to "Use the original node title"
    And the "service_links_override_title_text" field should contain "<title>"
    And the "Standard folder" field should contain "profiles/govcms/modules/features/govcms_share_links/images"
    And the "Use the default icons if missing" checkbox should not be checked
    And the "Use short links" select field should be set to "Never"
    And the "Assign a weight" select field should be set to "10"
    And the "Print the label" field should contain "Share to"
    When I visit "admin/config/services/service-links/services"
    Then the checkbox named "edit-service-links-show-facebook" in table row with text "Show Facebook link" should be checked
    And the checkbox named "edit-service-links-show-twitter" in table row with text "Show Twitter link" should be checked
    And the checkbox named "edit-service-links-show-linkedin" in table row with text "Show LinkedIn link" should be checked
    And the checkbox named "edit-service-links-show-email" in table row with text "Show email link" should be checked

  @api @javascript
  Scenario: Ensure that the share links appear on the page as expected.
    Given I am logged in as a user with the "administer site configuration" permission
    When I visit "admin/config/services/service-links"
    And I check the box "Full content"
    And I press "Save configuration"
    Then I should see the success message containing "The configuration options have been saved."
    And I logout
    Given "media_release" content:
      | title         | author     | status | state     |
      | Agency update | Joe Editor | 1      | published |
    And I am an anonymous user
    When I am on "/news-media/media-releases/agency-update"
    Then I should see the link "Facebook logo"
    And I should see the link "Twitter logo"
    And I should see the link "LinkedIn logo"
    And I should see the link "email logo"
    And the ".service-links-facebook" element should contain "/profiles/govcms/modules/features/govcms_share_links/images/facebook.png"
    And the ".service-links-twitter" element should contain "/profiles/govcms/modules/features/govcms_share_links/images/twitter.png"
    And the ".service-links-linkedin" element should contain "/profiles/govcms/modules/features/govcms_share_links/images/linkedin.png"
    And the ".service-links-email" element should contain "/profiles/govcms/modules/features/govcms_share_links/images/email.png"
    Given I am logged in as a user with the "administer site configuration" permission
    When I visit "admin/config/services/service-links"
    And I uncheck the box "Full content"
    And I press "Save configuration"
    Then I should see the success message containing "The configuration options have been saved."
