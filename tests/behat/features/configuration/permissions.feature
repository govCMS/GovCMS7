Feature: Permissions
  Check that permissions are as expected.

  @api @javascript
  Scenario: Check anonymous user permissions
    Given I am logged in as a user with the "administer permissions" permission
    When I go to "/admin/people/permissions/roles"
    And I click "edit permissions" in the "anonymous user" row
    Then the "anonymous user" role should have permission to:
      """
      access comments
      post comments
      view any basic_content bean
      view any image_and_text bean
      access comments
      post comments
      edit own comments
      access contextual links
      access content
      search content
      access site map
      access service links
      """
    And the "anonymous user" role should not have permission to:
      """
      administer theme settings checkbox
      administer search_api
      administer bean types
      administer beans
      access bean overview
      edit bean view mode
      view bean page
      administer bean settings
      view bean revisions
      create any basic_content bean
      edit any basic_content bean
      delete any basic_content bean
      create any image_and_text bean
      edit any image_and_text bean
      delete any image_and_text bean
      administer blocks
      administer comments
      skip comment approval
      administer contact forms
      administer crumbs
      admin_display_suite
      access draggableviews
      access event log
      administer fields
      bypass file access
      administer files
      use the rich text text format
      administer google analytics
      administer image styles
      access broken links report
      access own broken links report
      administer maintenance mode
      add media from remote sources
      administer menu
      administer meta tags
      edit meta tags
      bypass node access
      administer content types
      administer nodes
      access content overview
      view own unpublished content
      view revisions
      revert revisions
      create webform content
      edit own webform content
      edit any webform content
      delete own webform content
      delete any webform content
      use page manager
      use panels dashboard
      view pane admin links
      administer pane access
      use panels in place editing
      change layouts in place editing
      administer advanced pane settings
      use panels caching features
      use panels locks
      use ipe with page manager
      unblock expired accounts
      force password change
      administer url aliases
      create url aliases
      administer quicktabs
      administer redirects
      assign all roles
      assign Content editor role
      assign Content approver role
      assign Site builder role
      assign Site editor role
      administer scheduler
      schedule publishing of nodes
      override default scheduler time
      administer search
      administer shield
      administer shortcuts
      customize shortcut links
      switch shortcut sets
      administer themes
      administer actions
      access administration pages
      access site in maintenance mode
      view the administration theme
      access site reports
      administer taxonomy
      edit terms in 1
      delete terms in 1
      edit terms in 2
      delete terms in 2
      administer users
      access user profiles
      view user actions
      view any unpublished content
      administer views
      access all views
      access all webform results
      access own webform results
      edit all webform submissions
      delete all webform submissions
      access own webform submissions
      edit own webform submissions
      delete own webform submissions
      set webform_clear times
      view all unpublished content
      administer workbench moderation
      bypass workbench moderation
      view moderation history
      view moderation messages
      use workbench_moderation my drafts tab
      use workbench_moderation needs review tab
      moderate content from draft to needs_review
      moderate content from needs_review to draft
      moderate content from needs_review to published
      administer xmlsitemap
      """

  @api @javascript
  Scenario: Check authenticated user permissions
    Given I am logged in as a user with the "administer permissions" permission
    When I go to "/admin/people/permissions/roles"
    And I click "edit permissions" in the "authenticated user" row
    Then the "authenticated user" role should have permission to:
      """
      view any basic_content bean
      view any image_and_text bean
      access comments
      post comments
      skip comment approval
      edit own comments
      access contextual links
      use text format rich_text
      access content
      view own unpublished content
      search content
      access service links
      access site map
      """
    And the "authenticated user" role should not have permission to:
      """
      administer theme settings
      administer bean types
      administer beans
      access bean overview
      edit bean view mode
      view bean page
      administer bean settings
      view bean revisions
      create any basic_content bean
      edit any basic_content bean
      delete any basic_content bean
      create any image_and_text bean
      edit any image_and_text bean
      delete any image_and_text bean
      administer blocks
      administer comments
      administer contact forms
      administer crumbs
      admin_display_suite
      access draggableviews
      access event log
      administer fields
      bypass file access
      administer files
      administer google analytics
      administer image styles
      access broken links report
      access own broken links report
      administer maintenance mode
      add media from remote sources
      administer menu
      administer meta tags
      edit meta tags
      bypass node access
      administer content types
      administer nodes
      access content overview
      view revisions
      revert revisions
      create webform content
      edit own webform content
      edit any webform content
      delete own webform content
      delete any webform content
      use page manager
      use panels dashboard
      view pane admin links
      administer pane access
      use panels in place editing
      change layouts in place editing
      administer advanced pane settings
      use panels caching features
      use panels locks
      use ipe with page manager
      unblock expired accounts
      force password change
      administer url aliases
      create url aliases
      administer quicktabs
      administer redirects
      assign all roles
      assign Content editor role
      assign Content approver role
      assign Site builder role
      assign Site editor role
      administer scheduler
      schedule publishing of nodes
      override default scheduler time
      administer search
      administer search_api
      administer shield
      administer shortcuts
      customize shortcut links
      switch shortcut sets
      administer themes
      administer actions
      access administration pages
      access site in maintenance mode
      view the administration theme
      access site reports
      administer taxonomy
      edit terms in 1
      delete terms in 1
      edit terms in 2
      delete terms in 2
      administer users
      access user profiles
      view user actions
      view any unpublished content
      administer views
      access all views
      access all webform results
      access own webform results
      edit all webform submissions
      delete all webform submissions
      access own webform submissions
      edit own webform submissions
      delete own webform submissions
      set webform_clear times
      view all unpublished content
      administer workbench moderation
      bypass workbench moderation
      view moderation history
      view moderation messages
      use workbench_moderation my drafts tab
      use workbench_moderation needs review tab
      moderate content from draft to needs_review
      moderate content from needs_review to draft
      moderate content from needs_review to published
      administer xmlsitemap
      """

  @api @javascript
  Scenario: Check Content editor user permissions
    Given I am logged in as a user with the "administer permissions" permission
    When I go to "/admin/people/permissions/roles"
    And I click "edit permissions" in the "Content editor" row
    Then the "Content editor" role should have permission to:
      """
      create any basic_content bean
      edit any basic_content bean
      delete any basic_content bean
      create any image_and_text bean
      edit any image_and_text bean
      delete any image_and_text bean
      administer files
      add media from remote sources
      edit meta tags
      access content overview
      view revisions
      revert revisions
      create webform content
      edit any webform content
      delete any webform content
      override default scheduler time
      access administration pages
      access site in maintenance mode
      view the administration theme
      view any unpublished content
      access all webform results
      access own webform results
      access own webform submissions
      edit own webform submissions
      delete own webform submissions
      view all unpublished content
      view moderation history
      view moderation messages
      use workbench_moderation my drafts tab
      use workbench_moderation needs review tab
      moderate content from draft to needs_review
      moderate content from needs_review to draft
      """
    And the "Content editor" role should not have permission to:
     """
      administer theme settings
      administer bean types
      administer beans
      access bean overview
      edit bean view mode
      view bean page
      administer bean settings
      view bean revisions
      administer blocks
      administer comments
      administer contact forms
      administer crumbs
      admin_display_suite
      access draggableviews
      access event log
      administer fields
      bypass file access
      administer google analytics
      administer image styles
      access broken links report
      access own broken links report
      administer maintenance mode
      administer menu
      administer meta tags
      bypass node access
      administer content types
      administer nodes
      edit own webform content
      delete own webform content
      use page manager
      use panels dashboard
      view pane admin links
      administer pane access
      use panels in place editing
      change layouts in place editing
      administer advanced pane settings
      use panels caching features
      use panels locks
      use ipe with page manager
      unblock expired accounts
      force password change
      administer url aliases
      create url aliases
      administer quicktabs
      administer redirects
      assign all roles
      assign Content editor role
      assign Content approver role
      assign Site builder role
      assign Site editor role
      administer scheduler
      schedule publishing of nodes
      administer search
      administer search_api
      administer shield
      administer shortcuts
      customize shortcut links
      switch shortcut sets
      administer themes
      administer actions
      access site reports
      administer taxonomy
      edit terms in 1
      delete terms in 1
      edit terms in 2
      delete terms in 2
      administer users
      access user profiles
      view user actions
      administer views
      access all views
      edit all webform submissions
      delete all webform submissions
      administer workbench moderation
      set webform_clear times
      bypass workbench moderation
      moderate content from needs_review to published
      administer xmlsitemap
      """

  @api @javascript
  Scenario: Check Content approver user permissions
    Given I am logged in as a user with the "administer permissions" permission
    When I go to "/admin/people/permissions/roles"
    And I click "edit permissions" in the "Content approver" row
    Then the "Content approver" role should have permission to:
      """
      create any basic_content bean
      edit any basic_content bean
      delete any basic_content bean
      create any image_and_text bean
      edit any image_and_text bean
      delete any image_and_text bean
      administer files
      add media from remote sources
      edit meta tags
      access content overview
      view revisions
      revert revisions
      create webform content
      edit any webform content
      delete any webform content
      override default scheduler time
      access administration pages
      access site in maintenance mode
      view the administration theme
      view any unpublished content
      access all webform results
      access own webform results
      access own webform submissions
      edit own webform submissions
      delete own webform submissions
      view all unpublished content
      view moderation history
      view moderation messages
      use workbench_moderation my drafts tab
      use workbench_moderation needs review tab
      moderate content from draft to needs_review
      moderate content from needs_review to draft
      moderate content from needs_review to published
      """
    And the "Content approver" role should not have permission to:
      """
      administer theme settings
      administer bean types
      administer beans
      access bean overview
      edit bean view mode
      view bean page
      administer bean settings
      view bean revisions
      administer blocks
      administer comments
      administer contact forms
      administer crumbs
      admin_display_suite
      access draggableviews
      access event log
      administer fields
      bypass file access
      administer google analytics
      administer image styles
      access broken links report
      access own broken links report
      administer maintenance mode
      administer menu
      administer meta tags
      bypass node access
      administer content types
      administer nodes
      edit own webform content
      delete own webform content
      use page manager
      use panels dashboard
      view pane admin links
      administer pane access
      use panels in place editing
      change layouts in place editing
      administer advanced pane settings
      use panels caching features
      use panels locks
      use ipe with page manager
      unblock expired accounts
      force password change
      administer url aliases
      create url aliases
      administer quicktabs
      administer redirects
      assign all roles
      assign Content editor role
      assign Content approver role
      assign Site builder role
      assign Site editor role
      administer scheduler
      schedule publishing of nodes
      administer search
      administer search_api
      administer shield
      administer shortcuts
      customize shortcut links
      switch shortcut sets
      administer themes
      administer actions
      access site reports
      administer taxonomy
      edit terms in 1
      delete terms in 1
      edit terms in 2
      delete terms in 2
      administer users
      access user profiles
      view user actions
      administer views
      access all views
      edit all webform submissions
      delete all webform submissions
      set webform_clear times
      administer workbench moderation
      bypass workbench moderation
      administer xmlsitemap
      """

  @api @javascript
  Scenario: Check Site Builder user permissions
    Given I am logged in as a user with the "administer permissions" permission
    When I go to "/admin/people/permissions/roles"
    And I click "edit permissions" in the "Site builder" row
    Then the "Site builder" role should have permission to:
      """
      administer theme settings
      administer bean types
      administer beans
      access bean overview
      edit bean view mode
      view bean page
      administer bean settings
      view bean revisions
      create any basic_content bean
      edit any basic_content bean
      delete any basic_content bean
      create any image_and_text bean
      edit any image_and_text bean
      delete any image_and_text bean
      administer blocks
      administer contact forms
      administer crumbs
      admin_display_suite
      access draggableviews
      access event log
      administer fields
      bypass file access
      administer files
      administer google analytics
      administer image styles
      access broken links report
      access own broken links report
      administer maintenance mode
      administer menu
      administer meta tags
      edit meta tags
      bypass node access
      administer content types
      administer nodes
      access content overview
      view revisions
      revert revisions
      create webform content
      edit any webform content
      delete any webform content
      use page manager
      use panels dashboard
      view pane admin links
      administer pane access
      use panels in place editing
      change layouts in place editing
      administer advanced pane settings
      use panels caching features
      use panels locks
      use ipe with page manager
      unblock expired accounts
      force password change
      administer url aliases
      create url aliases
      administer quicktabs
      administer redirects
      administer scheduler
      override default scheduler time
      administer search
      administer search_api
      administer shield
      administer themes
      administer actions
      access administration pages
      access site in maintenance mode
      view the administration theme
      access site reports
      administer taxonomy
      edit terms in 1
      delete terms in 1
      administer users
      access user profiles
      view user actions
      view any unpublished content
      administer views
      access all views
      access all webform results
      access own webform results
      edit all webform submissions
      delete all webform submissions
      access own webform submissions
      set webform_clear times
      view all unpublished content
      administer workbench moderation
      bypass workbench moderation
      view moderation history
      view moderation messages
      use workbench_moderation my drafts tab
      use workbench_moderation needs review tab
      administer xmlsitemap
      """
    And the "Site builder" role should not have permission to:
      """
      administer comments
      edit own webform content
      delete own webform content
      assign all roles
      assign Content editor role
      assign Content approver role
      assign Site builder role
      assign Site editor role
      administer shortcuts
      customize shortcut links
      switch shortcut sets
      edit terms in 2
      delete terms in 2
      schedule publishing of nodes
      edit own webform submissions
      delete own webform submissions
      moderate content from draft to needs_review
      moderate content from needs_review to draft
      moderate content from needs_review to published
      """

  @api @javascript
  Scenario: Check Site editor user permissions
    Given I am logged in as a user with the "administer permissions" permission
    When I go to "/admin/people/permissions/roles"
    And I click "edit permissions" in the "Site editor" row
    Then the "Site editor" role should have permission to:
    """
      administer beans
      administer theme settings
      access bean overview
      edit bean view mode
      view bean page
      view bean revisions
      create any basic_content bean
      edit any basic_content bean
      delete any basic_content bean
      create any image_and_text bean
      edit any image_and_text bean
      delete any image_and_text bean
      administer blocks
      administer comments
      administer contact forms
      access draggableviews
      access event log
      bypass file access
      administer files
      administer google analytics
      access broken links report
      access own broken links report
      administer maintenance mode
      administer menu
      administer meta tags
      edit meta tags
      bypass node access
      administer nodes
      access content overview
      view revisions
      revert revisions
      create webform content
      edit any webform content
      delete any webform content
      use page manager
      use panels dashboard
      view pane admin links
      administer pane access
      use panels in place editing
      change layouts in place editing
      administer advanced pane settings
      use panels caching features
      use panels locks
      use ipe with page manager
      unblock expired accounts
      force password change
      administer url aliases
      create url aliases
      administer quicktabs
      administer redirects
      assign Content editor role
      assign Content approver role
      assign Site builder role
      assign Site editor role
      administer scheduler
      override default scheduler time
      administer search
      administer search_api
      administer shield
      administer shortcuts
      customize shortcut links
      switch shortcut sets
      administer themes
      administer actions
      access administration pages
      access site in maintenance mode
      view the administration theme
      access site reports
      administer taxonomy
      edit terms in 1
      delete terms in 1
      administer users
      access user profiles
      view user actions
      view any unpublished content
      administer views
      access all views
      access all webform results
      access own webform results
      edit all webform submissions
      delete all webform submissions
      access own webform submissions
      edit own webform submissions
      delete own webform submissions
      set webform_clear times
      view all unpublished content
      administer workbench moderation
      bypass workbench moderation
      view moderation history
      view moderation messages
      use workbench_moderation my drafts tab
      use workbench_moderation needs review tab
      moderate content from draft to needs_review
      moderate content from needs_review to draft
      moderate content from needs_review to published
      administer xmlsitemap
      """
    And the "Site editor" role should not have permission to:
      """
      administer fields
      administer bean types
      administer bean settings
      administer crumbs
      admin_display_suite
      administer image styles
      administer content types
      edit own webform content
      delete own webform content
      assign all roles
      schedule publishing of nodes
      edit terms in 2
      delete terms in 2
  """

  @api @javascript
  Scenario: Check Administrator user permissions
    Given I am logged in as a user with the "administer permissions" permission
    When I go to "/admin/people/permissions/roles"
    And I click "edit permissions" in the "administrator" row
    Then the "administrator" role should have permission to:
    """
      administer theme settings
      administer bean types
      administer beans
      access bean overview
      edit bean view mode
      view bean page
      administer bean settings
      view bean revisions
      create any basic_content bean
      edit any basic_content bean
      delete any basic_content bean
      create any image_and_text bean
      edit any image_and_text bean
      delete any image_and_text bean
      administer blocks
      administer comments
      administer contact forms
      administer crumbs
      admin_display_suite
      access draggableviews
      access event log
      administer fields
      bypass file access
      administer files
      administer google analytics
      administer image styles
      access broken links report
      access own broken links report
      administer maintenance mode
      add media from remote sources
      administer menu
      administer meta tags
      edit meta tags
      bypass node access
      administer content types
      administer nodes
      access content overview
      view revisions
      revert revisions
      create webform content
      edit own webform content
      edit any webform content
      delete own webform content
      delete any webform content
      use page manager
      use panels dashboard
      view pane admin links
      administer pane access
      use panels in place editing
      change layouts in place editing
      administer advanced pane settings
      use panels caching features
      use panels locks
      use ipe with page manager
      unblock expired accounts
      force password change
      administer url aliases
      create url aliases
      administer quicktabs
      administer redirects
      assign all roles
      assign Content editor role
      assign Content approver role
      assign Site builder role
      assign Site editor role
      administer scheduler
      schedule publishing of nodes
      override default scheduler time
      administer search
      administer search_api
      administer shield
      administer shortcuts
      customize shortcut links
      switch shortcut sets
      administer themes
      administer actions
      access administration pages
      access site in maintenance mode
      view the administration theme
      access site reports
      administer taxonomy
      edit terms in 1
      delete terms in 1
      administer users
      access user profiles
      view user actions
      view any unpublished content
      administer views
      access all views
      access all webform results
      access own webform results
      edit all webform submissions
      delete all webform submissions
      access own webform submissions
      edit own webform submissions
      delete own webform submissions
      set webform_clear times
      view all unpublished content
      administer workbench moderation
      bypass workbench moderation
      view moderation history
      view moderation messages
      use workbench_moderation my drafts tab
      use workbench_moderation needs review tab
      moderate content from draft to needs_review
      moderate content from needs_review to draft
      moderate content from needs_review to published
      administer xmlsitemap
      """
    And the "administrator" role should not have permission to:
      """
      edit terms in 2
      delete terms in 2
      """
