Feature: Account suspension

  To maintain the security of the website, when a user hasn't logged in for 60 days, then their account should be
  suspended.

  @api @javascript
  Scenario: Check that a user account is blocked after 60 days but may be manually unblocked.
    Given users:
      | name | pass        | mail             | roles          |
      | John | Abcd1234&*( | john@example.com | Content editor |
      | Fred | Abcd1234&*( | fred@example.com | Content editor |
    And the user named "John" has not logged in for "59" days
    And I run cron
    When I visit "/user/login"
    And I fill in the following:
      | Username | John         |
      | Password | Abcd1234&*(  |
    And I press "Log in"
    Then I should not see the message containing "The username John has not been activated or is blocked."
    And I logout
    Given the user named "Fred" has not logged in for "61" days
    And I run cron
    When I visit "/user/login"
    And I fill in the following:
      | Username | Fred         |
      | Password | Abcd1234&*(  |
    And I press "Log in"
    Then I should see the message containing "The username Fred has not been activated or is blocked."
    Given I am logged in as a user with the "administrator" role
    When I visit the user edit page for "Fred"
    Then I select the radio button "Active"
    And I press "Save"
    And I logout
    Given I visit "/user/login"
    When I fill in the following:
      | Username | Fred         |
      | Password | Abcd1234&*(  |
    And I press "Log in"
    Then I should not see the message containing "The username Fred has not been activated or is blocked."
