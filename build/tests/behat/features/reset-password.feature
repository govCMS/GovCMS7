Feature: Reset Password

  Ensure the reset password functionality works

  @api
  Scenario: Reset my password
    Given I am logged in as a user named "paul" with the "Content editor" role that doesn't force password change
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
    Given I access the reset password link for "paul"
    Then I should see "Reset password"
    And I press "Log in"
    Then I should see "You have just used your one-time login link. It is no longer necessary to use this link to log in. Please change your password."
    And for "Password" I enter "FDXdfjkfsdhju31321!"
    And for "Confirm password" I enter "notthesame"
    And I press "Save"
    Then I should see "An error of some kind"
    And for "Password" I enter "aFDchsgy@3221!"
    And for "Confirm password" I enter "aFDchsgy@3221!"
    And I press "Save"
    Then I should see "A success message of some kind"


