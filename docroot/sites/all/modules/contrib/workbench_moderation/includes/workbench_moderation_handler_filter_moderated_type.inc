<?php

/**
 * @file
 *  Provides moderation filters for Views.
 */

/**
 * Filter by whether a node type has moderation enabled or not.
 */
class workbench_moderation_handler_filter_moderated_type extends views_handler_filter_boolean_operator {
  function query() {
    if (!isset($this->value) || $this->value === NULL) {
      return;
    }

    $node_types = workbench_moderation_moderate_node_types();

    // If there are no node types using moderation set this variable to an array with a blank value.
    // This will force the query to return no values.
    if (empty($node_types)) {
      $node_types = array('');

      // Tell users to configure content types for moderation
      // It's conceivable that a hook_menu_alter has changed the permission needed to get to admin/structure/types
      // and as such, perhaps a better check should be used here.
      if (user_access('administer content types')) {
        $message = t('<a href="@settings" title="Content type administration">No content types have been configured to use Workbench Moderation.</a>', array('@settings' => url('admin/structure/types')));
        $type = 'error';
      }
      // Non admins get a different message.
      else {
        $message = t('Moderation is not ready to for use at this time. Please contact your administrator.');
        $type = 'warning';
      }

      drupal_set_message($message, $type, $repeat = FALSE);
    }

    $operator = ($this->value ? "IN" : "NOT IN");
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $node_types, $operator);
  }
}
