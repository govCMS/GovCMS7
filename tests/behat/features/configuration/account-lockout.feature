Feature: Account lockout

  Test the global login flood control.

  Background:
    Given users:
    | name     | pass          | mail                 | roles          | status |
    | joe.user | GovCMS1234!@# | joe.user@example.com | Content editor | 1      |
    And the flood table has been cleared
    And the user named "joe.user" who triggered the flood control

  @api @javascript @account
  Scenario: User can login as a normal case.
    Given I visit "/user/login"
    And the flood table has been cleared
    When I fill in the following:
      | Username | joe.user      |
      | Password | GovCMS1234!@# |
    And I press "Log in"
    Then I should see "Member for"

  @api @javascript @account
  Scenario: Login blocked after 5 failed login attempts.
    Given I visit "/user/login"
    When I fill in the following:
      | Username | joe.user      |
      | Password | GovCMS1234!@# |
    And I press "Log in"
    Then I should see the message containing "Sorry, there have been more than 5 failed login attempts for this account. It is temporarily blocked. Try again later or request a new password."

  @api @javascript @account
  Scenario: The blocked user can reset the password after 5 failed login attempts.
    Given I am on "/user"
    Then I should see the link "Request new password"
    When I click "Request new password"
    Then I should see the button "E-mail new password"
    And for "Username or e-mail address" I enter "joe@example.com"
    When I press "E-mail new password"
    Then I should see "Further instructions have been sent to your e-mail address."
    And I should not see "Notice: Undefined index"

  @api @javascript @account
  Scenario: The blocked user can reset the password then logout and login after 5 failed login attempts.
    Given I visit "/user/login"
    When I fill in the following:
      | Username | joe.user      |
      | Password | GovCMS1234!@# |
    And I press "Log in"
    Then I should see the message containing "Sorry, there have been more than 5 failed login attempts for this account. It is temporarily blocked. Try again later or request a new password."
    Given user "joe.user" log in with the One Time Login Url
    Then I should see the heading "Reset password"
    And I should see "This login can be used only once."
    When I press the "Log in" button
    Then I should see "You have just used your one-time login link. It is no longer necessary to use this link to log in. Please change your password."
    When I fill in "GovCMS123456!@#" for "Password"
    And I fill in "GovCMS123456!@#" for "Confirm password"
    And I press "Save"
    Then I should see "The changes have been saved."
    Then I logout
    Given I visit "/user/login"
    When I fill in the following:
      | Username | joe.user      |
      | Password | GovCMS123456!@# |
    And I press "Log in"
    Then I should see "Member for"
