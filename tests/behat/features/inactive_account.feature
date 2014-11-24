Feature: Inactive Account

  ISM Control 0430: - Remove or suspend inactive accounts after a specified number of days

  #@api
  #Scenario: Suspend account
  #  Given I am logged in as a user with the "Content editor" role
  #  Then account should be scheduled to be blocked
  #  Then adjust scheduled suspend date to now
  #  Then I run cron
  #  Then account should be blocked
  #  Given I am on the homepage
  #  Then I should be logged out

  @api
  Scenario: Login change suspend account schedule
    Given I am logged in as a user with the "Content editor" role
    Then account should be scheduled to be blocked
    Then relogin adjust suspend account to later
