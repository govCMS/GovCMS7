Feature: Home Page

  Ensure the home page is rendering correctly

  @javascript
  Scenario: Anonymous user visits the homepage
    Given I am on the homepage
    And save screenshot
    Then I should see the link "Site map and Feeds" in the "header" region
    Then I should see the link "Home" in the "navigation" region
    And I should see the link "Publications" in the "navigation" region
    And I should see the link "News & Media" in the "navigation" region
    And I should see the link "Contact" in the "navigation" region
    And I should see the link "View more news" in the "content" region
    And I should see the link "View more blog articles" in the "content" region
    And I should see the heading "Twitter Feed" in the "sidebar_second" region
    And I should see the heading "Quick Links" in the "sidebar_second" region
    And I should see the heading "Connect with us" in the "sidebar_second" region
    And I should see the link "Publications" in the "footer" region
    And I should see the link "News & Media" in the "footer" region
    And I should see the link "Contact" in the "footer" region
    And I should see the link "Feedback" in the "footer" region
    And I should see the link "Sitemap and Feeds" in the "footer" region
    And the "title" element should contain "govCMS"
    And the "title" element should not contain "|"
    And the response should contain "/profiles/govcms/themes/govcms/govcms_barton/logo.png"
