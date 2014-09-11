<?php

/**
 * @file
 * Filter based on moderation privlieges.
 */
class workbench_moderation_handler_filter_user_can_moderate extends views_handler_filter {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    drupal_set_message(t("This filter isn't even possible right now since workbench moderation permissions are incomplete--there's no way to figure out what transitions a user may make for a particular type of content."), 'error');
  }

  function query() {
    // add table, add node table, add where statments like "(n.type = 'blog' AND moderation.state IN ('review', 'approve')) OR (n.type = 'article' AND moderation.state IN ('review'))"
    // $this->ensure_my_table();
    // $node_alias = $this->query->ensure_table('node');
    // $this->query->add_where();
  }
}
