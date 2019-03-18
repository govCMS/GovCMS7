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
    Given I click "Request new password"
    Then I should see the button "E-mail new password"
    And for "Username or e-mail address" I enter "joe@example.com"
    And I press "E-mail new password"
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
    And I logout
    Given I visit "/user/login"
    When I fill in the following:
      | Username | joe.user      |
      | Password | GovCMS1234!@# |
    And I press "Log in"
    Then I should see "Member for"
