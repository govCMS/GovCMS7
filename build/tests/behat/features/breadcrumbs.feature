Feature: Breadcrumbs

  So users can navigate the site
  As an user
  I can see breadcrumbs for the parent pages of the current page

  @api @javascript
  Scenario: Breadcrumbs are set for news items
    Given I am logged in as a user named "peta" with the "Content editor" role that doesn't force password change
    When I go to "/node/add/news-article"
    Then I should see "Create News Article"
    And I enter "test" for "Title"
    Given the iframe in element "cke_edit-body-und-0-value" has id "body-wysiwyg"
    And I fill in "Body text" in WYSIWYG editor "body-wysiwyg"
    And press "Save"
    Then I should see "News Article test has been created"
    Then the response should contain "<a href=\"/\">Home</a>"
    And the response should contain "<a href=\"/news-media\">News &amp; Media</a>"
    And the response should contain "<a href=\"/news-media/news\">News</a>"
