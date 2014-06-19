Feature: Home Page

  Ensure the home page is available

  Scenario: View the example homepage content
    Given I am on the homepage
    Then the response status code should be 200
