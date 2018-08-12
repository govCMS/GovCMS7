Feature: Image and Text bean

  Ensure that Image and Text bean type is available and displayed as expected

  @api @javascript @beans
  Scenario: Create, view and edit a new Image and Text bean
    Given I am logged in as a user with the following permissions:
      """
      create any image_and_text bean
      view bean page
      access media browser
      create files
      bypass file access
      """
    When I go to "/block/add/image-and-text"
    Then I should see "Create Image and Text block"
    And I fill in the following:
      | Label | Cool beans             |
      | Title | Beans are good for you |
    When I open the "Image" media browser
    And I attach the file "autotest.jpg" to "files[upload]"
    And I press "Next"
    Then I select the radio button "Public local files served by the webserver."
    And I press "Next"
    And I enter "Behold, a generic logo" for "Name"
    And I submit the media browser
    Then I should see a "[name=field_bean_image_und_0_remove_button]" element
    And I put "govCMS is the best!" into WYSIWYG of "Text" field
    And I press "Save"
    Then I should see the success message containing "Image and Text Beans are good for you has been created."
    Given I am logged in as a user with the following permissions:
      """
      edit any image_and_text bean
      view bean page
      administer blocks
      edit bean view mode
      """
    When I go to "/admin/structure/block/manage/bean/cool-beans/configure"
    And I select "Second sidebar" from "govCMS (Barton) (default theme)"
    And I press "Save block"
    Then I should see the success message "The block configuration has been saved."
    And I go to homepage
    Then I should see the heading "Beans are good for you" in the "sidebar_second" region
    And the "#block-bean-cool-beans" element should contain "/image_and_text_bean_small/public/autotest.jpg"
    And I should see "govCMS is the best!"
    And I should see a ".entity.default" element
    When I go to "/block/cool-beans/edit"
    Then I should see the heading "Edit Image and Text: Cool beans"
    And for "URL" I enter "www.govcms.gov.au"
    And I select "Highlight" from "View Mode"
    And I press "Save"
    Then I should see the success message containing "Image and Text Beans are good for you has been updated."
    Given I am on homepage
    Then I should see the heading "Beans are good for you" in the "sidebar_second" region
    And the response should contain "<h2><a href=\"http://www.govcms.gov.au\">Beans are good for you</a></h2>"
    And the "#block-bean-cool-beans" element should contain "/image_and_text_bean_large/public/autotest.jpg"
    And I should see "govCMS is the best!"
    And I should see a ".entity.highlight" element
