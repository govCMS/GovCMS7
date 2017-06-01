Feature:Menu blocks

  Given I am logged in as "Site Builder"
  When I navigate to the list of the blocks
  Then I can see the options for 3 default menu blocks

  @api @javascript
  Scenario: 3 default govCMS menu blocks appear in the list of menu blocks.
    Given I am logged in as a user named "menu_amy" with the "Site editor" role that doesn't force password change
    When I go to "/admin/structure/block"
    Then I should see "Main menu (levels 2-3)"
    And I should see "Main Menu (Expanded)"
    And I should see "Footer Menu"

  @api @javascript
  Scenario: The main menu is configured as expected.
    Given I am logged in as a user named "menu_brian" with the "Site editor" role that doesn't force password change
    When I go to "/admin/structure/block/manage/menu_block/govcms_menu_block-main-menu/configure"
