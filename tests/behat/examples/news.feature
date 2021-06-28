Feature: Sample test for News listing

  Ensure the News listing page is rendering correctly

  @api
  Scenario: Anonymous user visits the News page
    Given I am an anonymous user
    And I am on "/news-media/news"
    Then save screenshot
    # The News page should have the page heading.
    And I should see the heading "News" in the "content" region
    # Each news item should have a title, date, and a summary.
    And I should see an "h2.node-title" element
    And I should see an "span.date-display-single" element
    And I should see an ".field-name-body" element
    # It should also have a Read more link.
    And I should see the link "Read more" in the "content" region
    # The News listing has a View more news link.
    And I should see the link "View more news" in the "content" region
