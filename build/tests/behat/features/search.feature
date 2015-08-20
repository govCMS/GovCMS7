Feature: Search

  So that all users can search
  As an anonymous user I can use search

  @api @javascript
  Scenario: Search API block is present
    Given I am on the homepage
    Then I should see an "div#block-search-api-page-default-search" element
