Feature: Theme settings

  Ensure that only users with a permission have access to the theme's settings page.

  @api @javascript
  Scenario: Visit theme's settings page with the permission.
    Given I am logged in as a user with the "administer theme settings" permission
    When I go to "/admin/appearance/settings"
    Then I should not see "You are not authorised to access this page."
    And I logout

  @api @javascript
  Scenario: Visit theme's settings page without the permission.
    Given I am logged in as a user with the "administer themes" permission
    When I go to "/admin/appearance/settings"
    Then I should see "You are not authorized to access this page."
    And I logout
