Feature: Menu blocks

  Given I am logged in as a user with blocks administration permission
  When I navigate to the list of the blocks
  Then I can see 3 default menu blocks available

  @api @javascript
  Scenario: 3 default govCMS menu blocks appear in the list of blocks and are configured as expected.
    Given I am logged in as a user with the "administer blocks" permission
    When I go to "/admin/structure/block"
    Then the response should contain "id=\"edit-blocks-menu-block-govcms-menu-block-sidebar-region\""
    And the response should contain "id=\"edit-blocks-menu-block-govcms-menu-block-main-menu-region\""
    And the response should contain "id=\"edit-blocks-menu-block-govcms-menu-block-footer-region\""
    When I click "edit-blocks-menu-block-govcms-menu-block-sidebar-configure"
    Then I should see "Configuration is being provided by code."
    When I go to "/admin/structure/block/manage/menu_block/govcms_menu_block-main-menu/configure"
    Then I should see "Configuration is being provided by code."
    When I go to "/admin/structure/block/manage/menu_block/govcms_menu_block-footer/configure"
    Then I should see "Configuration is being provided by code."
