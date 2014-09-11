<?php

/**
 * @file
 * Provides the search administration form for search_config.
 */

/**
 * Called from search_config_form_search_admin_settings_alter().
 */
function _search_config_form_search_admin_settings_alter(&$form, $form_state) {

  $settings = search_config_node_settings();
  $string_overrides = search_config_string_overrides();

  $role_options = array_map('check_plain', user_roles());
  $form['content_node_search_config'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('Additional Node Search Configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => (bool) variable_get('search_config', FALSE),
    'info' => array(
      '#markup' => t('<p>The basic search form is the keyword and search button that is shown to all users. The additional fields are all part of the advanced search form that is only shown to users that have the "%advsearch" permission. <em>This module does not override these permissions!</em></p>',
          array('%usesearch' => t('Use search'), '%advsearch' => t('Use advanced search'))),
    ),
    'forms' => array(
      '#type' => 'item',
      '#title' => t('Form control'),
      'toggle_forms' => array(
        '#type' => 'checkbox',
        '#title' => t('Only show one form at a time'),
        '#description' => t('This will hide the basic search form if the advanced search form is present.'),
        '#default_value' => $settings['forms']['toggle_forms'],
      ),
      'move_keyword_search' => array(
        '#type' => 'checkbox',
        '#title' => t('Move basic keyword search'),
        '#description' => t('This will move the keyword search field, (%label), into the advanced form and hide the rest of the basic form.'),
        '#default_value' => $settings['forms']['move_keyword_search'],
      ),
      'advanced_populate' => array(
        '#type' => 'checkbox',
        '#title' => t('Populate the advanced form with default values'),
        '#description' => t('By default the advanced form is always empty after a submission. This option will pull the values from the basic search form and use these to populate the advanced search form fields. <span style="color: #ff0000; font-style: italic;">Experimental</span>'),
        '#default_value' => $settings['forms']['advanced_populate'],
      ),
      'remove_containing_wrapper' => array(
        '#type' => 'radios',
        '#title' => t('Remove all <em>Containing ...</em> keyword options'),
        '#default_value' => $settings['forms']['remove_containing_wrapper'],
        '#options' => array(
          'default' => t('No change'),
          'remove' => t('Remove unconditionally'),
          'empty' => t('Remove wrapper if no containing fields'),
        ),
      ),
      'advanced_expand' => array(
        '#type' => 'radios',
        '#title' => t('Control how the advanced form initially renders'),
        '#default_value' => $settings['forms']['advanced_expand'],
        '#options' => array(
          'default' => t('Always collapsed (no modification)'),
          'remove' => t('Remove the collapsible wrapper and title'),
          'expand_always' => t('Force it to stay open, but keep the open look and feel'),
          'expand_on_first' => t('Expand initially, then collapsed'),
          'expand_if_empty' => t('Expand initially or when there are zero results'),
        )
      ),
    ),
    'string_overrides' => array(
      '#type' => 'fieldset',
      '#theme' => 'search_config_admin_label_form',
      '#title' => t('Labels and string overrides'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'labels' => array(),
      'title_display' => array(),
    ),
    'fields' => array(
      '#type' => 'item',
    ),
  );

  $title_display_options = array(
    'default' => t('Default'),
    'invisible' => t('Hidden'),
    'description' => t('Below'),
  );
  $slabels = array(
    'basic' => array(t('Keywords'), t('Enter your keywords')),
    'basic_with_keys' => array(t('Keywords (with search keys)'), t('Enter your keywords')),
    'basic_submit' => array(t('Submit button'), t('Search')),
    'advanced_fieldset' => array(t('Wrapping fieldset'), t('Advanced search')),
    'advanced_fieldset_with_keys' => array(t('Wrapping fieldset (with search keys)'), t('Advanced search')),
    'advanced_any' => array(t('Containing any ...'), t('Containing any of the words')),
    'advanced_phrase' => array(t('Containing the phrase'), t('Containing the phrase')),
    'advanced_none' => array(t('Containing none ...'), t('Containing none of the words')),
    'advanced_type' => array(t('Types'), t('Only of the type(s)')),
    'advanced_language' => array(t('Language selector'), t('Languages')),
    'advanced_submit' => array(t('Submit button'), t('Advanced search')),
  );
  $form['content_node_search_config']['string_overrides']['#field-labels'] = $slabels;
  foreach ($slabels as $skey => $slabel) {
    $form['content_node_search_config']['string_overrides']['labels'] += array(
      $skey => array(
        '#type' => 'textfield',
        '#title' => $slabel[0],
        '#title_display' => 'invisible',
        '#default_value' => $string_overrides['labels'][$skey],
        '#description' => t('t() string: !translation' ,
            array('%label' => $slabel[1], '!translation' => '!search_config:' . $skey)),
        '#size' => 40,
      ),
    );
    if (isset($string_overrides['title_display'][$skey])) {
      $form['content_node_search_config']['string_overrides']['title_display'] += array(
        $skey => array(
          '#type' => 'radios',
          '#title' => $slabel[0],
          '#title_display' => 'invisible',
          '#default_value' => $string_overrides['title_display'][$skey],
          '#options' => $title_display_options,
        ),
      );
    }
  }

  $fields = array(
    'containing_any' => t('Containing any of the words'),
    'containing_phrase' => t('Containing the phrase'),
    'containing_none' => t('Containing none of the words'),
    'types' => t('Only of the type(s)'),
    'category' => t('By category'), // @todo: Find correct field naming
  );
  foreach ($fields as $key => $label) {
    $form['content_node_search_config']['fields'][$key] = array(
      '#type' => 'fieldset',
      '#title' => t('%field settings', array('%field' => $label)),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'remove' => array(
        '#type' => 'checkbox',
        '#title' => t('Hide this field', array('%field' => $label)),
        '#default_value' => $settings['fields'][$key]['remove'],
      ),
      'roles' => array(
        '#type' => 'checkboxes',
        '#title' => t('Override the above option by selecting one or more roles that should see this field:'),
        '#options' => $role_options,
        '#default_value' => $settings['fields'][$key]['roles'],
      ),
    );
    // @todo: Remove this once implemented
    if ($key == 'category') {
      $form['content_node_search_config']['fields'][$key]['#access'] = FALSE;
    }
    if ($key == 'types') {
      $groupings = array();
      foreach ($settings['fields'][$key]['groupings'] as $gtypes => $glabels) {
        $groupings [] = $gtypes . '|' . $glabels;
      }
      $groupings_type_help_items = array();
      foreach (search_config_content_types() as $gtype => $glabel) {
        $groupings_type_help_items[] = t('!type|%label', array('!type' => $gtype, '%label' => $glabel));
      }
      $groupings_type_help_items[] = t('&lt;other-types&gt;|Search for all other content types not used already in a grouping that is allowed by the type filter.');
      $groupings_type_help_items[] = t('&lt;all-types&gt;|Search for every content types allowed by the type filter.');

      $groupings_type_help = t('<p>Enter one grouping per line, in the format "%format". The key, %key, is a comma separated list of node content types. The %label is used in the search form display. There are two special key values, &lt;other-types&gt; and &lt;all-types&gt;, described below. A full list of value options are:</p>',
          array('%format' => t('machine name(s)') . '|' . t('label'), "%key" => t('machine name(s)'), '%label' => t('label')));
      $groupings_type_help .= theme('item_list', array('items' => $groupings_type_help_items));
      $groupings_type_help .= t('<p>Leave empty to use the standard type options.</p>');
      $form['content_node_search_config']['fields'][$key] += array(
        'filter' => array(
          '#type' => 'checkboxes',
          '#title' => t('Hide the following content types from the %field filter:', array('%field' => $label)),
          '#description' => t('<strong>This only limits the filter options</strong>. You must set the <a href="!url">permissions here</a> to enforce search restrictions per content types. These premissions are also used to filter the options shown to the user.',
              array('!url' => url('admin/people/permissions'))),
          '#options' => search_config_content_types(),
          '#default_value' => $settings['fields'][$key]['filter'],
        ),
        'groupings' => array(
          '#title' => t('Replace type options with custom type groups'),
          '#type' => 'textarea',
          '#rows' => 5,
          '#default_value' => implode("\n", $groupings),
          '#element_validate' => array('element_node_search_config_groupings_validate'),
          '#description' => $groupings_type_help,
        ),
      );
    }
  }

  // Provide some additional help for groupings setting.


// Phase three or four
//  // Summary of node level restrictions.
//  $form['content_node_search_config']['restrictions'] = array(
//    '#type' => 'fieldset',
//    '#title' => t('Individual node restrictions settings', array('%field' => $label)),
//    '#collapsible' => TRUE,
//    '#collapsed' => TRUE,
//    'flagable_types' => array(
//      '#type' => 'checkboxes',
//      '#title' => t('Enable "%exclude" option on these content types', array('%exclude' => t('Exclude from search results'))),
//      '#options' => search_config_content_types(),
//      '#default_value' => $settings['restrictions']['flagable_types'],
//      '#description' => t('This option will create a new checkbox on the node edit page to hide the content from the search.<br/>Only users with "%permission" permission can able to access this checkbox.', array('%permission' => t('Administer node "Exclude from search results" flag'))),
//    ),
//    'node_level_restrictions_overview' => array(
//      '#markup' => t('The following list is a summary of restricted content.')
//        . theme('item_list', array('items' => $items)),
//    ),
//  );

  $permissions = array();
  $roles = array_map('check_plain', user_roles());
  $search_config_permission = search_config_permission();
  foreach ($search_config_permission as $permission => $info) {
    $permissions[$permission] = array();
    foreach (search_config_get_roles_by_permission($permission) as $rid) {
      $permissions[$permission][$rid] = $roles[$rid];
    }
  }
  $items = array();
  $all_permissions = array(
    DRUPAL_ANONYMOUS_RID => $roles[DRUPAL_ANONYMOUS_RID],
    DRUPAL_AUTHENTICATED_RID => $roles[DRUPAL_AUTHENTICATED_RID],
  );
  $search_all = array();
  foreach ($permissions['search all content'] as $rid => $role) {
    $search_all[$rid] = $role . '<sup>*</sup>';
    if (isset($all_permissions)) {
      $all_permissions[$rid] = $search_all[$rid];
    }
  }
  foreach ($permissions as $perm_key => $permission) {
    $t_args = array(
      '!permission' => $search_config_permission[$perm_key]['title']
    );
    $permission = $search_all + $permission;
    if (count($permission)) {
      // We can reduce this down to just the two roles.
      if (isset($permission[DRUPAL_AUTHENTICATED_RID])) {
        $permission = array_intersect_key($all_permissions, $permission);
      }

      if (isset($permission[DRUPAL_AUTHENTICATED_RID]) && isset($permission[DRUPAL_ANONYMOUS_RID])) {
        $items[] = t('!permission<br /><strong><em>Everyone</em></strong>', $t_args);
      }
      else {
        // Remove the note flag on these.
        if ($perm_key == 'search all content') {
          $permission = array_intersect_key($roles, $permission);
        }
        $t_args['!roles'] = implode(', ', $permission);
        $items[] = t('!permission<br />!roles', $t_args);
      }
    }
    else {
      $items[] = t('!permission<br /><strong><em>No one</em></strong>', $t_args);
    }
  }

  // Restrictions and a summary of search config permissions
  $form['content_node_search_config']['restrictions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Restrictions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'admin_bypass' => array(
      '#type' => 'checkbox',
      '#title' => t('Admin bypass (primary user with id 1)'),
      '#description' => t('This option bypasses the form configuration settings. This user always be able to search all content types irrespective of this setting.'),
      '#default_value' => $settings['restrictions']['admin_bypass'],
    ),
    'type_restrictions' => array(
      '#type' => 'fieldset',
      '#title' => t('Content type permission overview', array('%field' => $label)),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      'permissions' => array(
        '#markup' => t('This is an overview of what roles can search each content type.')
            . theme('item_list', array('items' => $items))
            . t('<p><strong><sup>*</sup></strong>Note: These users are allowed to search all content items.</p><p>To update these, edit the %module module <a href="!url">permissions</a>.</p>',
                array('%module' => t('Search configuration'), '!url' => url('admin/people/permissions', array('fragment' => 'module-search_config'))))
            ,
      ),
    ),
  );
}

/**
 * Element validate callback for groupings list.
 *
 * User friendly display of key|value listings element validation.
 */
function element_node_search_config_groupings_validate($element, &$form_state) {
  $list = explode("\n", $element['#value']);
  // Pre-tidy the options list.
  $list = array_filter(array_map('trim', $list), 'strlen');

  $values = array();
  $content_types = search_config_content_types();
  $found_types = array();
  $errors = array();
  $empty_pairs = array();
  foreach ($list as $text) {
    if (preg_match('/([a-z0-9_,\-<>]{1,})\|(.{1,})/', $text, $matches)) {
      $key = trim($matches[1]);
      $value = trim($matches[2]);
      if (empty($key) || empty($value)) {
        $empty_pairs []= check_plain($matches[0]);
      }
      else {
        $found_types = array();
        $unknown_types = array();
        $types = array_filter(array_map('trim', explode(',', $key)), 'strlen');

        foreach ($types as $name) {
          if (isset($content_types[$name]) || $name == '<other-types>' || $name == '<all-types>') {
            $found_types[] = $name;
          }
          else {
            $unknown_types[] = $name;
          }
        }
        if (count($unknown_types)) {
          $errors[] = t('The key contains one or more invalid content types: %types [line: %line]',
              array('%types' => implode(', ', $unknown_types), '%line' => $matches[0]));
        }
        elseif (count($found_types)) {
          $values[implode(',', $found_types)] = $value;
        }
        else {
          $errors[] = t('No types could be found. [line: %line]',
              array('%line' => $matches[0]));
        }
      }
    }
    else {
      $empty_pairs []= check_plain($text);
    }
  }

  if (!empty($empty_pairs)) {
    $errors [] = t('Each line must contain a "type|value" pair. Types must contain one or more content type machine codes separated by commas and values must be non-empty strings. This error was seen on the following lines: !list',
        array('!list' => theme('item_list', array('items' => $empty_pairs))));
  }
  if (!empty($errors)) {
    form_error($element, t('The following errors were detected in the group options: !list',
        array('!list' => theme('item_list', array('items' => $errors)))));
  }
  else {
    form_set_value($element, $values, $form_state);
  }
}
