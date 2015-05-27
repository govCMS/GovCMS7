Feature: Standard Page

  Ensure the standard page content displayed correctly

  @api
  Scenario: View the about us page
    Given I am logged in as a user named "dean" with the "Content editor" role that doesn't force password change
    When I go to "/node/add/page"
    Then the response status code should be 200
    And I enter "About Us" for "Title"
    And I enter "govCMS is the best!" for "Body"
    And press "Save"
    Then I should see "Standard Page About Us has been created"
    Then I logout
    Given I am logged in as a user named "teresa" with the "Content approver" role that doesn't force password change
    Given I am on "about-us"
    Then I select "Needs Review" from "state"
    And press "Apply"
    Then I should see "Revision state: Needs Review"
    Then I logout
    Given I am logged in as a user named "helen" with the "Content approver" role that doesn't force password change
    And I am on "about-us"
    Then I select "published" from "state"
    And press "Apply"
    Then I logout
    Given I am on "about-us"
    Then the response status code should be 200
    And I should see an "nav.breadcrumb:contains(About Us)" element
