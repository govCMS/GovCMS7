Feature: Password Policy

  In order to have a secure website the password policy should be configured securely.

  @api @javascript
  Scenario: Check that the policies are available, enabled and properly configured.
    Given I am logged in as a user with the "administer password policies" permission
    When I go to "/admin/config/people/password_policy/list"
    Then I should see "Australian Government ISM Policy (Strong)"
    And I should see "Australian Government ISM Policy (Weak)"
    And the checkbox named "enabled" in table row with text "Australian Government ISM Policy (Strong)" should be checked
    And the checkbox named "enabled" in table row with text "Australian Government ISM Policy (Weak)" should be checked
    When I click "edit" in the "Australian Government ISM Policy (Strong)" row
    Then the "authenticated user" checkbox should be checked
    And the "Content editor" checkbox should be checked
    And the "Content approver" checkbox should be checked
    And the "Site builder" checkbox should be checked
    And the "Site editor" checkbox should be checked
    And the "administrator" checkbox should be checked
    And the "expiration" field should contain "90"
    And the "warning" field should contain "7"
    And the "constraint_username" field should contain "1"
    And the "constraint_delay" field should contain "24"
    And the "constraint_digit_placement" field should contain "1"
    And the "constraint_length" field should contain "11"
    And the "constraint_letter" field should contain "1"
    And the "constraint_history" field should contain "8"
    And the "constraint_alphanumeric" field should contain "1"
    And the "constraint_character_types" field should contain "3"
    When I go to "/admin/config/people/password_policy/list"
    And I click "edit" in the "Australian Government ISM Policy (Weak)" row
    Then the "authenticated user" checkbox should not be checked
    And the "Content editor" checkbox should not be checked
    And the "Content approver" checkbox should not be checked
    And the "Site builder" checkbox should not be checked
    And the "Site editor" checkbox should not be checked
    And the "administrator" checkbox should not be checked
    And the "expiration" field should contain "90"
    And the "warning" field should contain "7"
    And the "constraint_username" field should contain "1"
    And the "constraint_delay" field should contain "24"
    And the "constraint_digit_placement" field should contain "1"
    And the "constraint_length" field should contain "15"
    And the "constraint_letter" field should contain "1"
    And the "constraint_history" field should contain "8"
    And the "constraint_alphanumeric" field should contain "1"

  @api @javascript
  Scenario: Check that the ASD password warning is hidden.
    Given I am logged in as a user with the "administer password policies" permission
    When I go to "admin/config/people/password_policy/govcms"
    Then the "edit-govcms-password-policy-ready" select list should be set to "1"

  @api @javascript
  Scenario: Check that password changes are forced for first-time logins and not forced for any of the roles.
    Given I am logged in as a user with the "force password change" permission
    When I go to "admin/config/people/password_policy/password_change"
    Then the "edit-password-policy-new-login-change" checkbox should be checked

  @api @javascript
  Scenario: Check the password policies are actually applied
    Given I am logged in as a user with the password "abc123^*" and the "change own password" permission
    When I go to "/user"
    And I click "Edit"
    And I fill in "edit-current-pass" with "abc123^*"
    And I fill in "edit-pass-pass1" with "invalid"
    And I fill in "edit-pass-pass2" with "invalid"
    And I press "Save"
    Then I should see the error message containing "Your password has not met the following requirement(s)"
    And I fill in "edit-current-pass" with "abc123^*"
    And I fill in "edit-pass-pass1" with "abc123^*foobarBash"
    And I fill in "edit-pass-pass2" with "abc123^*foobarBash"
    And I press "Save"
    Then I should see the success message containing "The changes have been saved"
