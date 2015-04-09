Feature: Text formats

  So users can format text
  Provide a number of text format options
  # @TODO this is fixed with https://www.drupal.org/node/2304037

  @api
  Scenario: Users can access plain text
    Given I am logged in as a user named "richard" with the "Content editor" role that doesn't force password change
    And I go to "node/add/page"
    Then I should see "Plain Text"
    And I should not see "Filtered html"
    And I should not see "Full HTML"
    And I enter "Test node" for "Title"
    And I enter "<p><h1>Testing</h1><p>" for "Body"
    And I select "Plain text" from "Text format"
    And I press "Save"
    Then I should see "Testing"
    And I should not see the heading "Testing"

  @api
  Scenario: Users can access Rich text
    Given I am logged in as a user named "sally" with the "Content editor" role that doesn't force password change
    And I go to "node/add/page"
    Then I should see "Rich text"
    And I enter "Test node" for "Title"
    And I enter "<p><h2>Testing</h2></p>" for "Body"
    And I select "Rich text" from "Text format"
    And I press "Save"
    Then I should see the heading "Testing"
