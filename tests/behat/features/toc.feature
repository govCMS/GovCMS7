Feature: Table of contents

  Users can add a table of contents

  @api
  Scenario: Insert table of contents token and render
    Given I am logged in as a user with the "Content editor" role
    And I go to "node/add/page"
    And I enter "Test" for "Title"
    And I enter "[TOC:ol Table of contents]<h3>Item 1</h3><h3>Item 2</h3><h3>Item 3</h3>" for "Body"
    And I press "Save"
    Then I should see an "div.toc-filter" element
    And I should see "Table of contents"
