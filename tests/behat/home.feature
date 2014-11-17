Feature: Home Page

  Ensure the home page is available

  Scenario: Complete a task feature on home page
    Given I am on the homepage
    Then the response status code should be 200
