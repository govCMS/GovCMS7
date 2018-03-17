Feature: Basic bean

  Ensure that basic bean type is available and displayed correctly

  @api @javascript @beans
  Scenario: Create, view and edit a basic bean
    Given I am logged in as a user with the following permissions:
      """
      create any basic_content bean
      view bean page
      view bean revisions
      edit bean view mode
      """
    When I go to "/block/add/basic-content"
    Then I should see "Create Basic content block"
    And I enter "New bean" for "Label"
    And I enter "Beans are good for you" for "Title"
    And I put "govCMS is the best!" into WYSIWYG of "Body" field
    And press "Save"
    And I go to "/block/new-bean"
    Then I should see the heading "Beans are good for you"
    And I should see "govCMS is the best!"
    Then I logout
    Given I am logged in as a user with the following permissions:
      """
      edit any basic_content bean
      view bean page
      administer beans
      edit bean view mode
      """
    When I am on "/block/new-bean/edit"
    Then I enter "New block revision" for "log"
    And I enter "Beans are great for you" for "Title"
    And press "Save"
    And I go to "/block/new-bean"
    Then I should see the heading "Beans are great for you"
    And I should see "govCMS is the best!"
    Then I logout
    Given I am logged in as a user with the following permissions:
      """
      edit any basic_content bean
      view bean page
      view bean revisions
      """
    When I am on "/block/new-bean/revisions"
    And I click "set active"
    Then I should see "This action cannot be undone."
    And press "Set Default"
    Given I am on "/block/new-bean"
    Then I should see the heading "Beans are good for you"
    And I should see "govCMS is the best!"
