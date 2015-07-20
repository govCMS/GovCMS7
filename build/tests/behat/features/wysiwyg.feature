Feature: Use ckeditor4 WYSIWYG editor

  Users can use the WYSIWYG editor

  @api @javascript
  Scenario: WYSIWYG editor is operational
    Given I am logged in as a user named "steve" with the "Content editor" role that doesn't force password change
    And I go to "node/add/page"
    Then I should see "Create Standard page"
    And I enter "test" for "Title"
    Given the iframe in element "cke_edit-body-und-0-value" has id "body-wysiwyg"
    Then I should see a "div.cke" element
    And I should see an "a.cke_button__bold" element
    And I should see an "a.cke_button__italic" element
    And I should see an "a.cke_button__bulletedlist" element
    And I should see an "a.cke_button__numberedlist" element
    And I should see an "a.cke_button__link" element
    And I should see an "a.cke_button__unlink" element
    And I should see an "a.cke_button__blockquote" element
    And I should see an "a.cke_button__pastefromword" element
    And I should see an "a.cke_button__removeformat" element
    And I should see a "span.cke_combo__format" element
    And I should see an "a.cke_button__table" element
    And I should see an "a.cke_button__scayt" element
    And I should see an "a.cke_button__linkit" element
    And I should see an "a.cke_button__scayt" element
    And I should see an "a.cke_button__media" element
