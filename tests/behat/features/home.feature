Feature: Home Page

  Ensure the home page content is available

  Scenario: View the homepage content
    Given I am on the homepage
    Then the response status code should be 200
    And I should see "Publications"
    And I should see "News & Media"
    And I should see "Contact"
    And I should see "View more news"
    And I should see "View more blog articles"
    And I should see "Twitter Feed"
    And I should see "Quick Links"
    And I should see "Connect with us"
