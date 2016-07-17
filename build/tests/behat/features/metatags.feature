Feature:Meta tags

  So content contains relevant SEO
  As an editor
  I can create content and provide metatags

  @api @javascript
  Scenario: Meta-tags are auto set
    Given I am logged in as a user named "peter" with the "Content editor" role that doesn't force password change
    When I go to "/node/add/page"
    Then I should see "Create Standard page"
    And I enter "test" for "Title"
    Given the iframe in element "cke_edit-body-und-0-value" has id "body-wysiwyg"
    And I fill in "When tweetle beetles fight, its called a tweetle beetle battle." in WYSIWYG editor "body-wysiwyg"
    And I follow "Show Dublin Core Basic Tags"
    And I follow "Show Type"
    And I enter "Text" for "edit-metatags-und-dctermstype-item-value"
    And press "Save"
    Then I should see "Standard page test has been created"
    And the response should contain "<meta name=\"description\" content=\"When tweetle beetles fight, its called a tweetle beetle battle.\">"
    And the response should contain "<title>test | govCMS</title>"
    And the response should contain "<meta name=\"dcterms.type\" content=\"Text\">"
    And the response should contain "<meta name=\"dcterms.title\" content=\"test\">"

  @api @javascript
  Scenario: Meta-tags can be edited
    Given I am logged in as a user named "paul" with the "Content editor" role that doesn't force password change
    When I go to "/node/add/page"
    Then I should see "Create Standard page"
    And I enter "test" for "Title"
    Given the iframe in element "cke_edit-body-und-0-value" has id "body-wysiwyg"
    And I fill in "When tweetle beetles fight, its called a tweetle beetle battle." in WYSIWYG editor "body-wysiwyg"
    And I follow "Show Dublin Core Basic Tags"
    And I follow "Show Description"
    And I enter "And when they battle in a puddle, its a tweetle beetle puddle battle" for "edit-metatags-und-description-value"
    And I enter "Fox in socks" for "Page title"
    And I follow "Show Title"
    And I enter "Fox in socks" for "edit-metatags-und-dctermstitle-item-value"
    And press "Save"
    Then I should see "Standard page test has been created"
    And the response should contain "<meta name=\"description\" content=\"And when they battle in a puddle, its a tweetle beetle puddle battle\">"
    And the response should contain "<title>Fox in socks</title>"
    And the response should contain "<meta name=\"dcterms.title\" content=\"Fox in socks\">"
