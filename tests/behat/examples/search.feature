Feature: Sample test for Search.

  Ensure the Search page is rendering correctly

  @api
  Scenario: Anonymous user visits the homepage and perform a simple search
    Given I am an anonymous user
    Given I am on the homepage
    And save screenshot
    # The quick search form should exist.
    Then I should see an "form#search-api-page-search-form-default-search" element
    And I fill in "Enter your keywords" with "Keyword"
    And I press "Search"
    # Performing a search will bring to the Search results page.
    Then I should be on "/search/Keyword"
    And save screenshot
    And I should see the heading "Search" in the "content" region
    # The Search page should have a search form.
    And I should see an "form#search-api-page-search-form" element
    And I should see the heading "Search results" in the "content" region
    And I should see an ".search-results" element
    # Each search result should have summary text.
    And I should see an ".search-snippet" element
    And I should see an ".search-info" element
    # The search results page also has pagination.
    And I should see an ".pager" element
