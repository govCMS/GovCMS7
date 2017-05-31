Feature: Use the Canberra timezone

  The Canberra timezone is available in timezone options and usable

  @api @javascript
  Scenario: The Canberra timezone is available in site timezone options
    Given I am logged in as a user named "tz_richard" with the "administrator" role
    When I go to "/admin/config/regional/settings"
    Then the response should contain "<option value=\"Australia/Canberra\""
    And I logout

  @api @javascript
  Scenario: The Canberra timezone may be selected as the default time zone for the site
    Given I am logged in as a user named "tz_emarty" with the "administrator" role
    When I go to "/admin/config/regional/settings"
    And I select "Australia/Canberra" from "Default time zone"
    And I press "Save"
    Then the response should contain "<option value=\"Australia/Canberra\" selected=\"selected\">"
