<?php

/**
 * @file
 * Native handler join handler.
 */

/**
 * Join handler for extra join conditions.
 */
class draggableviews_join_handler extends views_join {
  /**
   * Build the SQL for the join this object represents.
   */
  function build_join($select_query, $table, $view_query) {
    if (empty($this->definition['table formula'])) {
      $right_table = $this->table;
    }
    else {
      $right_table = $this->definition['table formula'];
    }

    if ($this->left_table) {
      $left = $view_query->get_table_info($this->left_table);
      $left_field = "$left[alias].$this->left_field";
    }
    else {
      // This can be used if left_field is a formula or something. It should be used only *very* rarely.
      $left_field = $this->left_field;
    }

    $condition = "$left_field = $table[alias].$this->field";

    // Check whether setting view is set.
    $arguments = array();
    $weight_key = draggable_views_get_draggable_sort($view_query->view);
    if (!empty($view_query->view->sort[$weight_key]->options['draggableviews_setting_view'])) {
      $condition .= " AND $table[alias].view_name = :view_name";
      $condition .= " AND $table[alias].view_display = :view_display";

      // If it is setting view, set current view name and display name.
      if ($view_query->view->sort[$weight_key]->options['draggableviews_setting_view'] == 'self') {
        $arguments[':view_name'] = $view_query->view->name;
        $arguments[':view_display'] = $view_query->view->current_display;
      }
      else {
        list($setting_view_name, $setting_view_display) = explode(':', $view_query->view->sort[$weight_key]->options['draggableviews_setting_view']);
        $arguments[':view_name'] = $setting_view_name;
        $arguments[':view_display'] = $setting_view_display;
      }

      // Arguments passed to view (including exposed filters).
      $view_arguments = $view_query->view->args;
      if (isset($view_query->view->exposed_raw_input)) {
        $view_arguments += $view_query->view->exposed_raw_input;
        ksort($view_arguments);
      }
      // Alter arguments according to sort criteria settings.
      if ($view_query->view->sort[$weight_key]->options['draggableviews_setting_arguments'] == 'none') {
        $view_arguments = array();
      }
      // If PHP arguments processing is set.
      if ($view_query->view->sort[$weight_key]->options['draggableviews_setting_arguments'] == 'php') {
        $view_arguments = draggableviews_eval_return($view_query->view->sort[$weight_key]->options['draggableviews_setting_arguments_php'], $view_arguments);
      }
      $condition .= " AND $table[alias].args = :view_arguments";
      $arguments[':view_arguments'] = json_encode($view_arguments);
    }

    $select_query->addJoin($this->type, $right_table, $table['alias'], $condition, $arguments);
  }
}