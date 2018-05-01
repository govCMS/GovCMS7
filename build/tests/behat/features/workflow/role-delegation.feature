Feature: Role delegation
  So user management can be delegated to site editors   As a site editor I can alter user roles   except for users that have the administrator role

  @api @javascript
  Scenario: Account alteration protection
    Given I am logged in as a user with the "Site editor" role
    And a user named "joe" with role "administrator" exists
    And a user named "bob" with role "Content editor" exists
    When I visit the user edit page for "bob"
    Then I should be able to change the "Site editor" role
    And I should be able to block the user
    When I visit the user edit page for "joe"
    Then I should not be able to change the "administrator" role
    And I should not be able to block the user
    #Given I visit "/admin/people"
    #Then I visit the user cancel page for "joe"
    #Then I should see text matching "You are not authorized to access this page."
    #And I visit "/admin/people"
    #Then I should be able to cancel the account "bob" 
