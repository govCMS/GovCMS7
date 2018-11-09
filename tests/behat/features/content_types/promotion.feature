Feature: Promotion

  Ensure the Promotion content type is available and works as expected.


  @api @javascript
  Scenario: Check that the Body WYSIWYG editor is available.
    Given I am logged in as a user with the "Content editor" role
    When I visit "/node/add/footer-teaser"
    Then CKEditor for the "Promotion Text" field exists

  @api @javascript
  Scenario: Create Publication content and check how it's displayed.
    # @TODO change the role to "Content editor" once https://github.com/govCMS/govCMS/pull/483 is merged.
    Given I am logged in as a user with the "administrator" role
    And "publication" content:
      | title              | author     | status | state     |
      | Agency publication | Joe Editor | 1      | published |
    When I go to "/node/add/footer-teaser"
    Then I should see "Create Promotion"
    And I fill in "Big promotion" for "Title"
    And I set the chosen element "Reference" to "Agency publication"
    When I open the "Attach media" media browser
    Then I attach the file "autotest.jpg" to "files[upload]"
    And I press "Next"
    Then I should see the message containing "The image was resized to fit within the maximum allowed dimensions of 78x64 pixels."
    And I fill in "Auto Test" for "Name"
    And I fill in "govCMS test image" for "Alt Text"
    And I fill in "govCMS Automated" for "Title Text"
    And I submit the media browser
    Then I put "Digital transformation is real. GovCMS is the best!" into WYSIWYG of "Promotion Text" field
    Given I click "Publishing options"
    And I click the label of the "Promoted to front page" field 
    And I select "Published" from "Moderation state"
    And I press "Save"
    Then I should see the success message containing "Promotion Big promotion has been created."
    And I logout
    Given I am an anonymous user
    When I am on the homepage
    Then I should see the link "Big promotion" in the "footer" region
    And I should see "Digital transformation is real. GovCMS is the best!" in the "footer" region
    And I should see the "img" element with the "width" attribute set to "64" in the "footer" region
    And I should see the "img" element with the "height" attribute set to "64" in the "footer" region
    And I should see the "img" element with the "alt" attribute set to "govCMS test image" in the "footer" region
    And I should see the "img" element with the "title" attribute set to "govCMS Automated" in the "footer" region
    And the response should contain "/styles/blog_teaser_thumbnail/public/images/promo/autotest.jpg"
    Given I click "Big promotion"
    Then I should see "Agency publication"

  @api @javascript
  Scenario: Check that Promotion moderation works.
    Given "footer_teaser" content:
      | title            | author     | status | state |
      | Agency promotion | Jim Editor | 0      | draft |
    And I am logged in as a user with the "Content approver" role
    When I am on "/promotions/agency-promotion"
    Then I select "Needs Review" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am logged in as a user with the "Content approver" role
    When I am on "/promotions/agency-promotion"
    Then I select "Published" from "Moderation state"
    And press "Apply"
    And I logout
    Given I am an anonymous user
    When I am on "/promotions/agency-promotion"
    Then I should see the heading "Agency promotion"

  @api @javascript
  Scenario: Check that custom menu links are disabled by default.
    Given "footer_teaser" content:
      | title        | author     | status | state         |
      | Agency promo | Jim Editor | 0      | needs_review     |
    And I am logged in as a user with the "Site builder" role
    When I am on "/promotions/agency-promo"
    Then I click "Edit draft"
    And I should not see "Menu settings"
