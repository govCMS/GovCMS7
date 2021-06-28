Feature: Sample test for Contact form

  Ensure the Contact page is rendering correctly

  @api
  Scenario: Anonymous user visits the Contact page
    Given I am an anonymous user
    And I am on "/contact"
    Then save screenshot
    # The Contact page should have the page heading.
    And I should see the heading "Contact" in the "content" region
    # Test for Contact form fields.
    And I should see the text "Your name"
    And I should see an "#edit-name.required" element
    And I should see the text "Your e-mail address"
    And I should see an "#edit-mail.required" element
    And I should see the text "Subject"
    And I should see an "#edit-subject.required" element
    And I should see the text "Message"
    And I should see an "#edit-message.required" element
