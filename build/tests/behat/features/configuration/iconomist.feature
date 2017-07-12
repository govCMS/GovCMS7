Feature: Iconomist

  So users can easily identify the site, as the administrator, I want to have iconomist support.

  @api @javascript
  Scenario: Check that iconomist options exist on the theme settings page.
    Given I am logged in as a user with the "administer theme settings" permission
    When I go to "/admin/appearance/settings/"
    Then I should see "Iconomist settings"
    And I press "Add icon"
    And I wait for AJAX to finish
    Then I should see "Path to custom icon"
    And I fill in "profiles/govcms/modules/contrib/acquia_connector/acquia_agent/acquia.ico" for "iconomist_icons[0][path]"
    And I fill in "100" for "iconomist_icons[0][width]"
    And I fill in "200" for "iconomist_icons[0][height]"
    And I select the radio button "Icon" with the id containing "edit-iconomist-icons-0-rel-icon"
    And I press "Add icon"
    And I wait for AJAX to finish
    Then I should see "Path to custom icon"
    And I fill in "themes/stark/logo.png" for "edit-iconomist-icons-1-path"
    And I fill in "30" for "edit-iconomist-icons-1-width"
    And I fill in "40" for "edit-iconomist-icons-1-height"
    And I select the radio button "Apple Touch" with the id containing "edit-iconomist-icons-1-rel-apple-touch-icon"
    And I press "Save configuration"
    And I logout
    And the cache has been cleared
    And I am on the homepage
    Then the response should contain "acquia.ico\" type=\"image/vnd.microsoft.icon\" sizes=\"100x200\""
    And the response should contain "<link rel=\"apple-touch-icon\""
    And the response should contain "/themes/stark/logo.png\" type=\"image/png\" sizes=\"30x40\">"
    And I am logged in as a user with the "administer theme settings" permission
    When I go to "/admin/appearance/settings/"
    And I press "Remove icon"
    And I wait for AJAX to finish
    And I press "Remove icon"
    And I wait for AJAX to finish
    And I press "Save configuration"
    Then the response should not contain "acquia.ico\" type=\"image/vnd.microsoft.icon\" sizes=\"100x200\""
    And the response should not contain "themes/stark/logo.png\" type=\"image/png\" sizes=\"30x40\">"
