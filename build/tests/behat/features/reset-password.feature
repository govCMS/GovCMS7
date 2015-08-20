Feature: Reset Password

  Ensure the reset password functionality works

  @api @javascript
  Scenario: Reset my password
    Given I am logged in as a user named "peskypaul" with the "Content editor" role that doesn't force password change
    Then I logout
    Given I am on "/user"
    Then I should see the link "Request new password"
    Given I click "Request new password"
    Then I should see the button "E-mail new password"
    And for "Username or e-mail address" I enter "paulnotexist@example.com"
    And I press "E-mail new password"
    Then I should see "Further instructions have been sent to your e-mail address."
    And I should not see "Notice: Undefined index"
    Given I click "Request new password"
    Then I should see the button "E-mail new password"
    And for "Username or e-mail address" I enter "paul@example.com"
    And I press "E-mail new password"
    Then I should see "Further instructions have been sent to your e-mail address."
    And I should not see "Notice: Undefined index"


