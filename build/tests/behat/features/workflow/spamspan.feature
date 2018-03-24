Feature: Spamspan is operational.

  Linked email addresses are obfuscated.

  @api
  Scenario: Users without javascript enabled should not see mailto: links.
    Given I am logged in as a user named "sarah" with the "Content editor" role
    And I go to "node/add/page"
    And I enter "Spamspan" for "Title"
    And I enter "<a href='mailto:example@test.com'>Email link.</a>" for "Body"
    And press "Save"
    Then I should not see "example@test.com"
    And the response should not contain "mailto:example@test.com"

  @api @javascript
  Scenario: Legitimate users with javascript enabled should see mailto: links.
    Given I am logged in as a user named "russ" with the "Content editor" role
    And I go to "node/add/page"
    And I enter "Spamspan" for "Title"
    And I put "<a href=\'mailto:example@test.com\'>Email link.</a>" into WYSIWYG of "Body"
    And press "Save"
    Then I should not see "example@test.com"
    And I should see "Email link."
    And the response should contain "mailto:example@test.com"
