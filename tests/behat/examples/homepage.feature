Feature: Sample test for Home Page with Default content.

  Ensure the home page is rendering correctly

  @api
  Scenario: Anonymous user visits the homepage
    Given I am an anonymous user
    Given I am on the homepage
    And save screenshot
    # Test the menu items in the Top Navigation region.
    Then I should see the link "Site map and Feeds" in the "header" region
    Then I should see the link "Home" in the "navigation" region
    And I should see the link "Publications" in the "navigation" region
    And I should see the link "News & Media" in the "navigation" region
    And I should see the link "Contact" in the "navigation" region
    # Test for links in the Content region.
    And I should see the link "View more news" in the "content" region
    And I should see the link "View more blog articles" in the "content" region
    # Test for blocks in the Sidebar.
    And I should see the heading "Twitter Feed" in the "sidebar_second" region
    And I should see the heading "Quick Links" in the "sidebar_second" region
    And I should see the heading "Connect with us" in the "sidebar_second" region
    # Test for links in the Footer.
    And I should see the link "Publications" in the "footer" region
    And I should see the link "News & Media" in the "footer" region
    And I should see the link "Contact" in the "footer" region
    And I should see the link "Feedback" in the "footer" region
    And I should see the link "Sitemap and Feeds" in the "footer" region
    # Verify if the logo image exists.
    And the response should contain "/profiles/govcms/themes/govcms/govcms_barton/logo.png"

  @api
  Scenario: Administrator visits the homepage
    # Test on authenticated users will run slower than anonymous users.
    Given I am logged in as a user with the "administrator" role
    Given I am on the homepage
    And save screenshot
    # Test the menu items in the Top Navigation region.
    Then I should see the link "My account" in the "header" region
    Then I should see the link "Log out" in the "header" region
