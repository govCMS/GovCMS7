Feature: Text resize

  As a user browsing a site
  I can see 3 default links for text resize options available
  And clicking on them alters the default styles for fonts

  @api @javascript
  Scenario: Text resize links are present on a page
    Given I am an anonymous user
    When I go to homepage
    Then I should see a ".block-govcms-text-resize" element
    And the ".block-govcms-text-resize" element should contain "Smaller text"
    And the ".block-govcms-text-resize" element should contain "Larger text"
    And the ".block-govcms-text-resize" element should contain "Reset text size"
    When I click "Larger text"
    Then I should see a "body.large-fonts" element
    When I click "Reset text size"
    Then I should not see a "body.large-fonts" element
