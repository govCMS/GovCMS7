Feature: Search

  So that all users can search
  As an anonymous user I can use search
  Exclude Unpublished content from search index

  @api @javascript
  Scenario: Search API block is present
    Given I am on the homepage
    Then I should see an "div#block-search-api-page-default-search" element

  @api @javascript
  Scenario: Searching for a content that is published return result
    Given I am logged in as a user named "mary" with the "Content editor" role that doesn't force password change
    When I go to "/node/add/news-article"
    Then I should see "Create News Article"
    And I enter "govCMS is the best" for "Title"
    Given the iframe in element "cke_edit-body-und-0-value" has id "body-wysiwyg"
    And I fill in "the whole of government content management and website hosting service for Australian Government agencies" in WYSIWYG editor "body-wysiwyg"
    When I press "Save"
    Then I should see "News Article govCMS is the best has been created"
    Then I logout
    Given I am on "search/govCMS"
    Then I should see the heading "Search"
    And I should see "Your search yielded no results"
    Given I am logged in as a user named "jason" with the "Content approver" role that doesn't force password change
    Given I am on "news-media/news/govcms-best"
    Then I select "Needs Review" from "state"
    When I press "Apply"
    Then I should see "Revision state: Needs Review"
    Then I logout
    Given I am logged in as a user named "grace" with the "Content approver" role that doesn't force password change
    Given I am on "news-media/news/govcms-best"
    Then I select "published" from "state"
    When I press "Apply"
    Then I logout
    Given I am on "search/govCMS"
    Then I should see the heading "Search"
    And I should see "The search found 1 result"
    And I should see "govCMS is the best"

  @api @javascript
  Scenario: Searching for a content that is NOT published return no results
    Given I am logged in as a user named "joseph" with the "Content editor" role that doesn't force password change
    When I go to "/node/add/news-article"
    Then I should see "Create News Article"
    Then I enter "govCMS is the best" for "Title"
    Given the iframe in element "cke_edit-body-und-0-value" has id "body-wysiwyg"
    Then I fill in "the whole of government content management and website hosting service for Australian Government agencies" in WYSIWYG editor "body-wysiwyg"
    When I press "Save"
    Then I should see "News Article govCMS is the best has been created"
    Then I logout
    Given I am on "search/govCMS"
    Then I should see the heading "Search"
    And I should see "Your search yielded no results"
    Given I am logged in as a user named "claire" with the "Content approver" role that doesn't force password change
    Given I am on "news-media/news/govcms-best"
    Then I select "Needs Review" from "state"
    When I press "Apply"
    Then I should see "Revision state: Needs Review"
    Then I logout
    Given I am on "search/govCMS"
    Then I should see the heading "Search"
    And I should see "Your search yielded no results"
