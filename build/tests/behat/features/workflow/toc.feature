Feature: Table of contents

  Users can add a table of contents

  @api @javascript
  Scenario: Insert table of contents token and render
    Given I am logged in as a user named "john" with the "Content editor" role
    And I go to "node/add/page"
    And I enter "Test" for "Title"
    And I put "[TOC:ol Table of contents]<h2>Item 1</h2><h2>Item 2</h2><h2>Item 3</h2>" into WYSIWYG of "Body"
    And I press "Save"
    Then I should see an "div.toc-filter" element
    And I should see "Table of contents"
