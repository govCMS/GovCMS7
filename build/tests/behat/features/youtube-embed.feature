Feature: Embed YouTube videos in content

  Users can embed a YouTube video

  @api
  Scenario: Embed YouTube video
    Given I am logged in as a user named "sam" with the "Content editor" role that doesn't force password change
    And I go to "node/add/page"
    And I enter "Test" for "Title"
    And I enter "[video:https://www.youtube.com/watch?v=_zzjd1xadyA]" for "Body"
    And I press "Save"
    Then I should see an "iframe.video-filter" element
