Feature: Breadcrumbs

  So users can navigate the site
  As an user
  I can see breadcrumbs for the parent pages of the current page

  @api @javascript
  Scenario: Breadcrumbs are set for news items
    Given I am logged in as a user named "peta" with the "Content editor" role
    When I go to "/node/add/news-article"
    Then I should see "Create News Article"
    And I enter "test" for "Title"
    And I put "Body text" into WYSIWYG of "Body" field
    And press "Save"
    Then I should see "News Article test has been created"
    Then the response should contain "<a href="/front">Home</a>"
    And the response should contain "<a href="/news-media">News &amp; Media</a>"
    And the response should contain "<a href="/news-media/news">News</a>"
