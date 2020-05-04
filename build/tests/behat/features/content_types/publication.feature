Feature: Publication

  Ensure the Publication content type is available and works as expected.

  @api @javascript
  Scenario: Check that the Body WYSIWYG editor is available.
    Given I am logged in as a user with the "Content editor" role
    When I visit "/node/add/publication"
    Then CKEditor for the "Body" field exists

  @api @javascript
  Scenario: Create Publication content and check how it's displayed.
    # @TODO change the role to "Content editor" once https://github.com/govCMS/govCMS/pull/483 is merged.
    Given I am logged in as a user with the "administrator" role
    Given "tags" terms:
      | name       |
      | govcmstest |
    When I go to "/node/add/publication"
    Then I should see "Create Publication"
    And I fill in the following:
      | Title                       | New publication           |
      | Subtitle                    | GovCMS Performance report |
    And I select "2018" from "Year"
    And I select "Nov" from "Month"
    And I select "19" from "Day"
    Then I set the chosen element "Tags" to "govcmstest"
    And I put "Digital transformation is real. GovCMS is the best!" into WYSIWYG of "Body" field
    And I click "Edit summary"
    And I put "Our recent and independent performance audit" into WYSIWYG of "Summary" field
    Then I open the media browser for "Attach media" in "Image" field set
    And I attach the file "autotest.jpg" to "files[upload]"
    And I press "Next"
    Then I fill in "Auto Test" for "Name"
    And I fill in "govCMS test image" for "Alt Text"
    And I fill in "govCMS Automated" for "Title Text"
    And I submit the media browser
    Then I click "Publishing options"
    And I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see the success message containing "Publication New publication has been created."
    And I logout
    Given I am an anonymous user
    When I visit "/publications"
    Then I should see the heading "Publications"
    And I should see the link "New publication"
    And I should see "GovCMS Performance report"
    And I should not see "Our recent and independent performance audit"
    And the response should contain "/styles/medium/public/images/publication/autotest.jpg"
    And I should see the "img" element with the "width" attribute set to "220" in the "content" region
    And I should see the "img" element with the "alt" attribute set to "govCMS test image" in the "content" region
    And I should see the "img" element with the "title" attribute set to "govCMS Automated" in the "content" region
    And I should see the link "Read more"
    Given I click "New publication"
    Then the "h1" element should contain "New publication"
    And I should see an "nav.breadcrumb:contains(New publication)" element
    And I should see "GovCMS Performance report"
    And I should see "Date of Publication: 19 November 2018"
    And I should see "Digital transformation is real. GovCMS is the best!"
    And the response should contain "/images/publication/autotest.jpg"
    And the ".field-name-field-tags" element should contain "<a href=\"/tags/govcmstest\""
    And I should see the link "govcmstest"

  @api @javascript
  Scenario: Check that Publication moderation works.
    Given "publication" content:
      | title              | author     | status | state |
      | Agency publication | Jim Editor | 0      | draft |
    And I am logged in as a user with the "Content approver" role
    When I am on "/publications/agency-publication"
    Then I select "Needs Review" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am logged in as a user with the "Content approver" role
    When I am on "/publications/agency-publication"
    Then I select "Published" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am an anonymous user
    When I am on "/publications/agency-publication"
    Then I should see the heading "Agency publication"

  @api @javascript
  Scenario: Check that custom menu link can be created.
    Given "publication" content:
      | title              | author     | status | state         |
      | Agency publication | Joe Editor | 0      | needs_review  |
    And I am logged in as a user with the "administrator" role
    When I am on "/publications/agency-publication"
    Then I click "Edit draft"
    And I click "Menu settings"
    And I check the box "Provide a menu link"
    Given I click "Publishing options"
    Then I select "Published" from "Moderation state"
    And I press "Save"
    When I am on homepage
    And the cache has been cleared
    Then I should see the link "Agency publication" in the "navigation" region
