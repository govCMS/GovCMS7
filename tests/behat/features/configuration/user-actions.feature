Feature: User Actions

  Ensure the user actions are being logged

  @api @javascript
  Scenario: Perform typical user account actions and verify that they are logged.
    Given I am logged in as a user "roman" with the "administer users" permission
    When I am on "/admin/people/create"
    Then I fill in the following:
      | name        | MyUser             |
      | mail        | myuser@example.com |
      | pass[pass1] | /123456789A        |
      | pass[pass2] | /123456789A        |
    And I press "Create new account"
    Then I should see the success message containing "Created a new user account"
    And I logout
    Given I am logged in as a user "barbun" with the "administer users" permission
    And I visit the user edit page for "MyUser"
    And I press "Cancel account"
    And I select the radio button "Disable the account and unpublish its content."
    And I press "Cancel account"
    Then I should see the success message containing "MyUser has been disabled."
    And I logout
    When a user named "MyUser" is deleted
    Given I am logged in as a user with the "Site editor" role
    And I am on "/admin/reports/user-actions"
    Then I should see "login" in a table row containing the text "roman"
    And I should see "logout" in a table row containing the text "roman"
    And I should see "login" in a table row containing the text "barbun"
    And I should see "logout" in a table row containing the text "barbun"
    And I should see "insert" in a table row containing the text "User: MyUser"
    And I should see "update" in a table row containing the text "User: MyUser"

  @api @javascript
  Scenario: Perform typical node actions and verify that they are logged.
    Given I am logged in as a user named "danielle" with the "Content editor" role
    When I go to "/node/add/news-article"
    Then I should see "Create News Article"
    And I enter "govCMS News" for "Title"
    And I put "govCMS is the best!" into WYSIWYG of "Body" field
    And press "Save"
    Then I should see "News Article govCMS News has been created"
    Then I logout
    Given I am logged in as a user named "jodie" with the "Content approver" role
    When I go to "/news-media/news/govcms-news"
    Then I click "Edit draft"
    And I enter "govCMS Updates" for "Title"
    And press "Save"
    Then I should see "News Article govCMS Updates has been updated."
    Then I logout
    Given I am logged in as a user named "janette" with the "administrator" role
    When I go to "/news-media/news/govcms-updates"
    Then I click "Edit draft"
    And I press "Delete"
    Then I should see "Are you sure you want to delete govCMS Updates?"
    And I press "Delete"
    Then I should see the success message "News Article govCMS Updates has been deleted."
    And I logout
    Given I am logged in as a user with the "Site editor" role
    And I am on "/admin/reports/user-actions"
    Then I should see "insert" in a table row containing the text "news_article: govCMS News"
    And I should see "update" in a table row containing the text "news_article: govCMS Updates"
    And I should see "delete" in a table row containing the text "news_article: govCMS Updates"
