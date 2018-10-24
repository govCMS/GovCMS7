Feature: Sample test for Publications listing

  Ensure the Publications listing page is rendering correctly

  @api @wip
  Scenario: Anonymous user visits the Publications page
    Given I am an anonymous user
    And I am on "/publications"
    Then save screenshot
    # The News page should have the page heading.
    And I should see the heading "Publications" in the "content" region
    # Each publication should have a title, subtitle, and summary text.
    And I should see an "h2.node-title" element
    And I should see an ".field-name-field-subtitle" element
    And I should see an ".field-name-body" element
    And I should see an ".field-name-field-image img" element
    And I should see the link "Read more" in the "content" region
