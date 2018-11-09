Feature: Slide

  Ensure the Slide content type is available and works as expected.

  @api @javascript
  Scenario: Check that the Body WYSIWYG editor is available.
    Given I am logged in as a user with the "Content editor" role
    When I visit "/node/add/slide"
    Then CKEditor for the "Body" field should exist

  @api @javascript @skipped
  Scenario: Create Slide content and check how it's displayed.
    # @TODO change the role to "Content editor" once https://github.com/govCMS/govCMS/pull/483 is merged.
    Given I am logged in as a user with the "administrator" role
    When I go to "/node/add/slide"
    Then I should see "Create Slide"
    And I fill in the following:
      | title                          | New slide         |
      | field_read_more[und][0][title] | Find out more     |
      | URL                            | www.govcms.gov.au |
    And I put "Digital transformation is real. GovCMS is the best!" into WYSIWYG of "Body" field
    When I open the "media[field_slide_image_und_0]" media browser
    Then I attach the file "autotest.jpg" to "files[upload]"
    And I press "Next"
    Then I select the radio button "Public local files served by the webserver."
    And I press "Next"
    Then I fill in "Auto Test" for "Name"
    And I fill in "govCMS test image" for "Alt Text"
    And I fill in "govCMS Automated" for "Title Text"
    And I submit the media browser
    Given I click "Publishing options"
    Then I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see the success message containing "Slide New slide has been created."
    And I logout
    Given I am an anonymous user
    When I am on the homepage
    Then the response should contain "/styles/feature_article/public/images/slide/autotest.jpg"
    And I should see the "img" element with the "width" attribute set to "640" in the "highlighted" region
    And I should see the "img" element with the "height" attribute set to "280" in the "highlighted" region
    And I should see the "img" element with the "alt" attribute set to "govCMS test image" in the "highlighted" region
    And I should see the "img" element with the "title" attribute set to "govCMS Automated" in the "highlighted" region
    And the response should contain "<a href=\"http://www.govcms.gov.au\">New slide</a>"

  @api @javascript
  Scenario: Check that moderation works.
    Given "slide" content:
      | title        | author     | status | state |
      | Agency slide | Jim Editor | 0      | draft |
    And I am logged in as a user with the "Content approver" role
    When I am on "/agency-slide"
    Then I select "Needs Review" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am logged in as a user with the "Content approver" role
    When I am on "/agency-slide"
    Then I select "Published" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am an anonymous user
    When I visit "/agency-slide"
    Then I should see the heading "Agency slide"

  @api @javascript
  Scenario: Check that custom menu links are disabled by default.
    Given "slide" content:
      | title        | author     | status | state         |
      | Agency slide | Jim Editor | 0      | needs_review     |
    And I am logged in as a user with the "administrator" role
    When I am on "/agency-slide"
    Then I click "Edit draft"
    And I should not see "Menu settings"
