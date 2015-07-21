Feature: Role delegation
  So user management can be delegated to site editors   As a site editor I can alter user roles   except for users that have the administrator role

  @api @role_delegation @javascript
  Scenario: Account alteration protection
    Given a user named "joe" with role "administrator" exists
    Given a user named "bob" with role "Content editor" exists
    And I am logged in as a user named "adam" with the "Site editor" role that doesn't force password change
    And I visit the user edit page for "bob"
    Then I should be able to change the "Site editor" role
    And I should be able to block the user
    Given I visit the user edit page for "joe"
    Then I should not be able to change the "administrator" role
    And I should not be able to block the user
    #Given I visit "/admin/people"
    #Then I visit the user cancel page for "joe"
    #Then I should see text matching "You are not authorized to access this page."
    #And I visit "/admin/people"
    #Then I should be able to cancel the account "bob" 
