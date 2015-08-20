Feature: Chosen library applies to tags

  Users can use chosen to select tags

  @api @javascript
  Scenario: Chosen library is installed correctly
    Given I am logged in as a user named "stuart" with the "administrator" role that doesn't force password change
    And I go to "admin/reports/status"
    Then I should see "Chosen JavaScript file"
    And I should not see "You need to download the Chosen JavaScript file"
