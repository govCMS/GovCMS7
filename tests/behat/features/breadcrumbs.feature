Feature: Breadcrumbs

  So users can navigate the site
  As an user
  I can see breadcrumbs for the parent pages of the current page

  @api
  Scenario: Breadcrumbs are set for news items
    Given I am logged in as a user with the "Content editor" role
    When I go to "/node/add/news-article"
    Then the response status code should be 200
    And I enter "test" for "Title"
    And I enter "When tweetle beetles fight, its called a tweetle beetle battle." for "Body"
    And press "Save"
    Then I should see "News article test has been created"
    And the response should contain "<a href=\"/\">Home</a>"
    And the response should contain "<a href=\"/news-media\">News &amp; Media</a>"
    And the response should contain "<a href=\"/news-media/news\">News</a>"
