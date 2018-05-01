Feature: Events

  Ensure the Event content type is available and works as expected.

  @api @javascript
  Scenario: Check that the Body WYSIWYG editor is available.
    Given I am logged in as a user with the "Content editor" role
    When I visit "/node/add/event"
    Then CKEditor for the "Body" field exists

  @api @javascript
  Scenario: Create past Event content and verify it's not getting listed.
    Given I am logged in as a user with the "administrator" role
    When I go to "/node/add/event"
    Then I should see "Create Event"
    And I fill in "Past event" for "Title"
    And I select "2016" from "Year"
    Given I click "Publishing options"
    Then I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see the success message containing "Event Past event has been created."
    And I logout
    Given I am an anonymous user
    When I visit "/news-media/events"
    Then I should see the heading "Events"
    And I should not see "Past event"


  @api @javascript
  Scenario: Create Event content and check how it's displayed.
    # @TODO change the role to "Content editor" once https://github.com/govCMS/govCMS/pull/483 is merged.
    Given I am logged in as a user with the "administrator" role
    Given "tags" terms:
      | name       |
      | govcmstest |
    When I go to "/node/add/event"
    Then I should see "Create Event"
    And I fill in the following:
      | Title            | New event                           |
      | Summary          | We celebrate govCMS!                |
      | Location         | Canberra, ACT                       |
      | Cost             | Free entry                          |
    And fill in "Contact" with:
    """
    Department of Finance
    FORREST ACT 2603
    """
    And I select "2020" from "Year"
    And I select "Nov" from "Month"
    And I select "19" from "Day"
    And I select "16" from "Hour"
    And I select "45" from "Minute"
    Then I set the chosen element "Tags" to "govcmstest"
    And I put "Digital transformation is real. GovCMS is the best!" into WYSIWYG of "Body" field
    When I open the "Feature Image" media browser
    Then I attach the file "autotest.jpg" to "files[upload]"
    And I press "Next"
    Then I select the radio button "Public local files served by the webserver."
    And I press "Next"
    Then I fill in "Auto Test" for "Name"
    And I fill in "govCMS test image" for "Alt Text"
    And I fill in "govCMS Automated" for "Title Text"
    And I submit the media browser
    Then the "#edit-field-feature-image" element should contain "Edit"
    And the "#edit-field-feature-image" element should contain "Remove"
    Given I click "Publishing options"
    Then I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see the success message containing "Event New event has been created."
    And I logout
    Given I am an anonymous user
    When I visit "/news-media/events"
    Then I should see the heading "Events"
    And the response should contain "<a href=\"/news-media/events/new-event\">New event</a>"
    And I should see "19/11/2020 - 4:45pm"
    And I should see the "img" element with the "width" attribute set to "220" in the "content" region
    And I should see the "img" element with the "alt" attribute set to "govCMS test image" in the "content" region
    And I should see the "img" element with the "title" attribute set to "govCMS Automated" in the "content" region
    And the response should contain "/files/styles/medium/public/images/events/autotest.jpg"
    And I should see the text "We celebrate govCMS!"
    And I should see the link "Read more"
    Given I click "New event"
    Then the "h1" element should contain "New event"
    And I should see an "nav.breadcrumb:contains(New event)" element
    And I should see "Thursday, November 19, 2020 - 16:45"
    And I should see the "img" element with the "width" attribute set to "620" in the "content" region
    And I should see the "img" element with the "height" attribute set to "349" in the "content" region
    And I should see the "img" element with the "alt" attribute set to "govCMS test image" in the "content" region
    And I should see the "img" element with the "title" attribute set to "govCMS Automated" in the "content" region
    And the response should contain "/files/styles/article_page_620x349/public/images/events/autotest.jpg"
    And I should see "Digital transformation is real. GovCMS is the best!"
    And I should see "Canberra, ACT" in the ".field-name-field-location" element
    And I should see "Free entry" in the ".field-name-field-cost" element
    And I should see "Department of Finance FORREST ACT 2603" in the ".field-name-field-contact" element
    And the ".field-name-field-tags" element should contain "<a href=\"/tags/govcmstest\""
    And I should see the link "govcmstest"

  @api @javascript
  Scenario: Check that Events moderation works.
    Given "event" content:
      | title        | author     | status | state |
      | Agency event | Jim Editor | 0      | draft |
    And I am logged in as a user with the "Content approver" role
    When I am on "/news-media/events/agency-event"
    Then I select "Needs Review" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am logged in as a user with the "Content approver" role
    When I am on "/news-media/events/agency-event"
    Then I select "Published" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am an anonymous user
    When I visit "/news-media/events/agency-event"
    Then I should see the heading "Agency event"

  @api @javascript
  Scenario: Check that custom menu links are disabled by default.
    Given "event" content:
      | title        | author     | status | state         |
      | Agency event | Jim Editor | 0      | needs_review     |
    And I am logged in as a user with the "Site builder" role
    When I am on "/news-media/events/agency-event"
    Then I click "Edit draft"
    And I should not see "Menu settings"
