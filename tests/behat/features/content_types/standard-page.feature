Feature: Standard Page

  Ensure the standard page content type is available and works as expected.

  @api @javascript
  Scenario: Check that the Body WYSIWYG editor is available.
    Given I am logged in as a user with the "Content editor" role
    When I visit "/node/add/page"
    Then CKEditor for the "Body" field exists

  @api @javascript @skipped
  Scenario: Create Standard page content and check how it's displayed.
    # @TODO change the role to "Content editor" once https://github.com/govCMS/govCMS/pull/483 is merged.
    Given I am logged in as a user with the "administrator" role
    When I go to "/node/add/page"
    Then I should see "Create Standard page"
    And I fill in the following:
      | Title   | New page               |
      | Summary | We migrated to govCMS! |
    And I put "Digital transformation is real. GovCMS is the best!" into WYSIWYG of "Body" field
    When I open the "Attach media" media browser
    Then I attach the file "autotest.jpg" to "files[upload]"
    And I press "Next"
    Then I fill in "Auto Test" for "Name"
    And I fill in "govCMS test image" for "Alt Text"
    And I fill in "govCMS Automated" for "Title Text"
    And I submit the media browser
    Given I click "Publishing options"
    Then I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see the success message containing "Standard page New page has been created."
    And I logout
    Given I am an anonymous user
    When I visit "/new-page"
    Then I should see the heading "New page"
    And I should see "Digital transformation is real. GovCMS is the best!"
    And the response should contain "/styles/article_page_620x349/public/images/page/autotest.jpg"
    And I should see the "img" element with the "width" attribute set to "620" in the "content" region
    And I should see the "img" element with the "height" attribute set to "349" in the "content" region
    And I should see the "img" element with the "alt" attribute set to "govCMS test image" in the "content" region
    And I should see the "img" element with the "title" attribute set to "govCMS Automated" in the "content" region

  @api @javascript
  Scenario: View the about us page
    Given I am logged in as a user with the "Content editor" role
    When I go to "/node/add/page"
    Then I should see "Create Standard page"
    And I enter "About Us" for "Title"
    And I put "govCMS is the best!" into WYSIWYG of "Body" field
    And press "Save"
    Then I should see "Standard Page About Us has been created"
    Then I logout
    Given I am logged in as a user named "teresa" with the "Content approver" role
    Given I am on "about-us"
    Then I select "Needs Review" from "state"
    And press "Apply"
    Then I should see "Revision state: Needs Review"
    Then I logout
    Given I am logged in as a user named "helen" with the "Content approver" role
    And I am on "about-us"
    Then I select "published" from "state"
    And press "Apply"
    Then I logout
    Given I am on "about-us"
    Then I should see "About Us"
    And I should see an "nav.breadcrumb:contains(About Us)" element
