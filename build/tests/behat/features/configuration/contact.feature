Feature: Contact

  Ensure that printable version of Contact information functionality is intact.

  @api @javascript
  Scenario: Check that print version can be attached.
    Given I am logged in as a user with the "administer content types" permission
    When I visit "admin/structure/contact/print"
    Then I should see the heading "Add printable version"
    And I should see "Provide a printable version of the contact form."
    Given I attach the file "autotest.pdf" to "Provide a printable version of the contact form."
    When I press "Save"
    Then I should see the button "Remove"
    And I should see the link "autotest.pdf"
    And the response should contain "/contact/autotest.pdf"
    And I logout
    Given I am an anonymous user
    When I visit "/contact"
    Then I should see the message containing "Get a printable version of the Contact form"
    And I should see the link "here"
    And the response should contain "<div class=\"messages download\">"
    And the response should contain "/contact/autotest.pdf"
