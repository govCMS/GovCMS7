Feature: News Article

  Ensure the News Article content type is available and works as expected.

  @api @javascript
  Scenario: Check that the WYSIWYG editor is available.
    Given I am logged in as a user with the "Content editor" role
    When I visit "/node/add/news-article"
    Then CKEditor for the "Body" field should exist

  @api @javascript
  Scenario: Create News Article content and check how it's displayed.
    # @TODO change the role to "Content editor" once https://github.com/govCMS/govCMS/pull/483 is merged.
    Given I am logged in as a user with the "administrator" role
    Given "tags" terms:
      | name       |
      | govcmstest |
    When I go to "/node/add/news-article"
    Then I should see "Create News Article"
    And I fill in the following:
      | Title   | Good news              |
    And I select "2015" from "Year"
    And I select "Nov" from "Month"
    And I select "19" from "Day"
    And I select "16" from "Hour"
    And I select "45" from "Minute"
    Then I set the chosen element "Tags" to "govcmstest"
    And I put "We migrated to govCMS!" into WYSIWYG of "Summary" field
    And I put "Digital transformation is real. GovCMS is the best!" into WYSIWYG of "Body" field
    Given I click "Publishing options"
    Then I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see the success message containing "News Article Good news has been created."
    And I logout
    Given I am an anonymous user
    When I visit "/news-media/news/news"
    Then I should see the heading "News"
    And I should see the link "Good news"
    And I should see "19 November 2015"
    And I should see "We migrated to govCMS!"
    And I should see the link "Read more"
    When I click "Good news"
    Then the response should contain "<li><a href=\"/news-media/news\">News</a> › </li>"
    And the "h1" element should contain "Good news"
    And I should see an "nav.breadcrumb:contains(Good news)" element
    And I should see "19 November 2015"
    And I should see "Digital transformation is real. GovCMS is the best!"
    And the ".field-name-field-tags" element should contain "<a href=\"/tags/govcmstest\""
    And I should see the link "govcmstest"

  @api @javascript
  Scenario: Check that moderation works.
    Given "news_article" content:
      | title       | author     | status | state |
      | Good things | Joe Editor | 0      | draft |
    And I am logged in as a user with the "Content approver" role
    When I am on "/news-media/news/good-things"
    Then I select "Needs Review" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am logged in as a user with the "Content approver" role
    When I am on "/news-media/news/good-things"
    Then I select "Published" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am an anonymous user
    When I visit "/news-media/news/good-news"
    Then I should see the heading "Good things"

  @api @javascript
  Scenario: Check that custom menu link can be created.
    Given "news_article" content:
      | title       | author     | status | state         |
      | Good things | Joe Editor | 0      | needs_review  |
    And I am logged in as a user with the "Site builder" role
    When I am on "/news-media/news/good-things"
    Then I click "Edit draft"
    And I should not see "Menu settings"

  @api @javascript
  Scenario: Scheduling a node for publishing.
    Given I am logged in as a user with the "administrator" role
    And "news_article" content:
      | title       | author     | status | state         |
      | Good things | Joe Editor | 0      | needs_review  |
    When I visit "/news-media/news/good-things"
    And I click "Edit draft"
    And I select "2015" from "Year"
    And I select "Nov" from "Month"
    And I select "19" from "Day"
    And I select "16" from "Hour"
    And I select "45" from "Minute"
    Then I click "Publishing options"
    And I select "Needs Review" from "Moderation state"
    And I schedule the node to be published at "2020-12-31 08:57:00"
    And I press "Save"
    Then I should see the message containing "This post is unpublished and will be published 2020-12-31 08:57:00."
    When I go to "/admin/config/content/scheduler/list"
    Then I should see the link "Good things"
    When I go to "/admin/config/content/scheduler/cron"
    And I press "Run Scheduler's lightweight cron now"
    Then I should see the success message "Lightweight cron run completed."
    Given I am an anonymous user
    When I visit "/news-media/news/good-things"
    Then I should see the error message containing "Access denied."
