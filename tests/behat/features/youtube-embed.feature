Feature: Embed YouTube videos in content

  Users can embed a YouTube video

  @api
  Scenario: Embed YouTube video
    Given I am logged in as a user with the "Content editor" role
    And I go to "node/add/page"
    And I enter "Test" for "Title"
    And I enter "[video:https://www.youtube.com/watch?v=ktCgVopf7D0]" for "Body"
    And I press "Save"
    Then I should see an "iframe.video-filter" element
