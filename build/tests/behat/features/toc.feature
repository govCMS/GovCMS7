Feature: Table of contents

  Users can add a table of contents

  @api @javascript
  Scenario: Insert table of contents token and render
    Given I am logged in as a user named "john" with the "Content editor" role that doesn't force password change
    And I go to "node/add/page"
    And I enter "Test" for "Title"
    Given the iframe in element "cke_edit-body-und-0-value" has id "body-wysiwyg"
    And I fill in "[TOC:ol Table of contents]<h2>Item 1</h2><h2>Item 2</h2><h2>Item 3</h2>" in WYSIWYG editor "body-wysiwyg"
    And I press "Save"
    Then I should see an "div.toc-filter" element
    And I should see "Table of contents"
