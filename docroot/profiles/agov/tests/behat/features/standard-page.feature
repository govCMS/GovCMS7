Feature: Standard Page

  Ensure the standard page content displayed correctly

  Scenario: View the about us page
    Given I am on "about-us"
    Then the response status code should be 200
    And I should see an "nav.breadcrumb:contains(About Us)" element
