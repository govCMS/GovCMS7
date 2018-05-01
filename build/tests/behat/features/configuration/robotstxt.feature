Feature: Robots.txt is available

  Ensure the robotstxt module returns a valid robots.txt file

  Scenario: Load /robots.txt
    When I visit "robots.txt"
    Then the response status code should be 200
    And the response should contain "sitemap.xml"
