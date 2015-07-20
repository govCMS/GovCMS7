Feature: Home Page

  Ensure the home page content is available

  @javascript
  Scenario: View the homepage content
    Given I am on the homepage
    Then I should see "Publications"
    And I should see "News & Media"
    And I should see "Contact"
    And I should see "View more news"
    And I should see "View more blog articles"
    And I should see "Twitter Feed"
    And I should see "Quick Links"
    And I should see "Connect with us"
