Feature: Breadcrumbs

  So users can navigate the site
  As an user
  I can see breadcrumbs for the parent pages of the current page

  @api
  Scenario: Breadcrumbs are set for news items
    Given I am logged in as a user named "peta" with the "Content editor" role that doesn't force password change
    When I go to "/node/add/news-article"
    Then the response status code should be 200
    And I enter "test" for "Title"
    And I enter "govCMS is the best!" for "Body"
    And press "Save"
    Then I should see "News Article test has been created"
    Then the response should contain "<a href=\"/\">Home</a>"
    And the response should contain "<a href=\"/news-media\">News &amp; Media</a>"
    And the response should contain "<a href=\"/news-media/news\">News</a>"
