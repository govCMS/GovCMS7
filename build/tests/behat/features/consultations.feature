Feature: Consultations

  Ensure govCMS Consultations Feature is available

  @drush @feature
  Scenario: Enable govCMS Consultations
  Given I run drush "en" "govcms_consultation -y"
  When I run drush "pm-info" "govcms_consultation --format=yaml"
  Then drush output should contain "status: enabled"

  @drush @feature
  Scenario: Disable govCMS Consultations
  Given I run drush "dis" "govcms_consultation uuid_features field_group ds_extras -y"
  When I run drush "pm-info" "govcms_consultation --format=yaml"
  Then drush output should contain "status: disabled"

  @drush @feature
  Scenario: Uninstall govCMS Consultations
  Given I run drush "pm-uninstall" "govcms_consultation -y"
  When I run drush "pm-info" "govcms_consultation --format=yaml"
  Then drush output should contain "status: 'not installed'"

  @api @drush @javascript
  Scenario: Creating a consultation that starts in the future
    Given I run drush "en" "govcms_consultation -y"
    Given I am logged in as a user named "roger" with the "administrator" role that doesn't force password change
    When I go to "/node/add/consultation"
    Then I should see "Create Consultation"
    And I enter "This is the title" for "Consultation Title"
    And for "edit-field-consultation-date-und-0-value-datepicker-popup-0" I enter "1 Jan 2021"
    And for "edit-field-consultation-date-und-0-value-timeEntry-popup-1" I enter "09:00am"
    And for "edit-field-consultation-date-und-0-value2-datepicker-popup-0" I enter "31 Jan 2021"
    And for "edit-field-consultation-date-und-0-value2-timeEntry-popup-1" I enter "05:00pm"
    Given the iframe in element "cke_edit-field-consultation-summary-und-0-value" has id "summary-wysiwyg"
    And I fill in "This is the summary" in WYSIWYG editor "summary-wysiwyg"
    Given the iframe in element "cke_edit-field-consultation-issue-text-und-0-value" has id "issue-wysiwyg"
    And I fill in "This is the issue" in WYSIWYG editor "issue-wysiwyg"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I follow "URL path settings"
    And I uncheck the box "Generate automatic URL alias"
    And I enter "consultation/test/1" for "URL alias"
    When I press "Save"
    Then I should see "Consultation This is the title has been created."
    Then I logout
    Given I am on "consultation/test/1"
    Then I should see "Start Friday, January 1, 2021 - 09:00"
    Then I should see "End Sunday, January 31, 2021 - 17:00"
    Then I should see "Days Remaining 31 of 31"

  @api @drush @javascript
  Scenario: Creating a consultation that finishes in the past
    Given I run drush "en" "govcms_consultation -y"
    Given I am logged in as a user named "sidney" with the "administrator" role that doesn't force password change
    When I go to "/node/add/consultation"
    Then I should see "Create Consultation"
    And I enter "This is the title" for "Consultation Title"
    And for "edit-field-consultation-date-und-0-value-datepicker-popup-0" I enter "1 Jan 2016"
    And for "edit-field-consultation-date-und-0-value-timeEntry-popup-1" I enter "09:00am"
    And for "edit-field-consultation-date-und-0-value2-datepicker-popup-0" I enter "31 Jan 2016"
    And for "edit-field-consultation-date-und-0-value2-timeEntry-popup-1" I enter "05:00pm"
    Given the iframe in element "cke_edit-field-consultation-summary-und-0-value" has id "summary-wysiwyg"
    And I fill in "This is the summary" in WYSIWYG editor "summary-wysiwyg"
    Given the iframe in element "cke_edit-field-consultation-issue-text-und-0-value" has id "issue-wysiwyg"
    And I fill in "This is the issue" in WYSIWYG editor "issue-wysiwyg"
    And I follow "Publishing options"
    And I select "Published" from "Moderation state"
    And I follow "URL path settings"
    And I uncheck the box "Generate automatic URL alias"
    And I enter "consultation/test/2" for "URL alias"
    When I press "Save"
    Then I should see "Consultation This is the title has been created."
    Then I logout
    Given I am on "consultation/test/2"
    Then I should see "Start Friday, January 1, 2016 - 09:00"
    Then I should see "End Sunday, January 31, 2016 - 17:00"
    Then I should see "Days Remaining 0 of 31"
