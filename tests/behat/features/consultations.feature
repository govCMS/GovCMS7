Feature: Consultations

  Ensure govCMS Consultations Feature is available

  @api @feature
  Scenario: Enable govCMS Consultations
  Given I run drush "en" "govcms_consultation -y"
  When I run drush "pm-info" "govcms_consultation --format=yaml"
  Then drush output should contain "status: enabled"

  @api @feature
  Scenario: Disable govCMS Consultations
  Given I run drush "dis" "govcms_consultation uuid_features field_group ds_extras -y"
  When I run drush "pm-info" "govcms_consultation --format=yaml"
  Then drush output should contain "status: disabled"

  @api @feature
  Scenario: Uninstall govCMS Consultations
  Given I run drush "pm-uninstall" "govcms_consultation -y"
  When I run drush "pm-info" "govcms_consultation --format=yaml"
  Then drush output should contain "status: 'not installed'"
