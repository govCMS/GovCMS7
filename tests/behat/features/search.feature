Feature: Search

  So that all users can search
  As an anonymous user I can use search

  @api
  Scenario: Search API block is present
    Given I am on the homepage
    Then the response status code should be 200
    And I should see an "div#block-search-api-page-default-search" element
