Feature: Disabled modules

  Ensure deprecated modules are not available for install

  @api @disabled-modules
  Scenario: View the module page
    Given I am logged in as a user named "sean" with the "administrator" role that doesn't force password change
    When I go to "/admin/modules"
    Then I should not see "Iconomist"
    Then I should not see "Favicon"
