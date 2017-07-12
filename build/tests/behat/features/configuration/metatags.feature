Feature:Meta tags

  So content contains relevant SEO
  As an editor
  I can create content and provide metatags
  And default govCMS metatags are set
  And changing the sitename/slogan affects default govCMS metatags.

  @api @javascript
  Scenario: Meta-tags are auto set
    Given I am logged in as a user with the "Content editor" role
    When I go to "/node/add/page"
    Then I should see "Create Standard page"
    And I enter "test" for "Title"
    And I put "When tweetle beetles fight, its called a tweetle beetle battle." into WYSIWYG of "Body" field
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
    Given I am logged in as a user with the "Content editor" role
    When I go to "/node/add/page"
    Then I should see "Create Standard page"
    And I enter "test" for "Title"
    And I put "When tweetle beetles fight, its called a tweetle beetle battle." into WYSIWYG of "Body" field
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

  @api @javascript
  Scenario: govCMS core successfully applies default meta-tags configuration.
    Given I am logged in as a user with the "administer meta tags" permission
    When I go to "/admin/config/search/metatags/config/global"
    Then the "edit-metatags-und-dctermscreator-item-value" field should contain "[site:name]"
    And the "edit-metatags-und-dctermsdate-item-value" field should contain "[current-date:custom:Y-m-d\TH:iP]"
    And the "edit-metatags-und-dctermsdescription-item-value" field should contain "[site:slogan]"
    And the "edit-metatags-und-dctermslanguage-item-value" field should contain "en"
    And the "edit-metatags-und-dctermspublisher-item-value" field should contain "[site:name]"
    And the "edit-metatags-und-dctermssubject-item-value" field should contain "[site:slogan]"
    And the "edit-metatags-und-dctermstype-item-value" field should contain "other"
    And the "edit-metatags-und-generator-value" field should contain "Drupal 7 (http://drupal.org) + govCMS (http://govcms.gov.au)"
    When I go to "/admin/config/search/metatags/config/node"
    Then the "edit-metatags-und-dctermslanguage-item-value" field should contain "en"

  @api @javascript
  Scenario: Meta-tags are modified when the site name and/or slogan change
    Given I am logged in as a user with the following permissions:
      """
      administer meta tags
      administer site configuration
      """
    When I go to "/admin/config/system/site-information"
    And I fill in "My Sitename" for "Site name"
    And I fill in "Everything is Awesome!!!" for "Slogan"
    And press "Save configuration"
    Given the cache has been cleared
    When I go to homepage
    Then the response should contain "<meta name=\"dcterms.creator\" content=\"My Sitename\">"
    And the response should contain "<meta name=\"dcterms.publisher\" content=\"My Sitename\">"
    And the response should contain "<meta name=\"dcterms.subject\" content=\"Everything is Awesome!!!\">"
    When I go to "/admin/config/system/site-information"
    And I fill in "govCMS" for "Site name"
    And I fill in "" for "Slogan"
    And press "Save configuration"
    Given the cache has been cleared
    When I go to homepage
    Then the response should contain "<meta name=\"dcterms.creator\" content=\"govCMS\">"
    And the response should not contain "<meta name=\"dcterms.subject\""
