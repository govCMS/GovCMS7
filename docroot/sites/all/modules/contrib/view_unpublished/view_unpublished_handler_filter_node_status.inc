<?php

/**
 * @file
 * Provides integration with the Views module.
 */

/**
 * Filter by view all unpublished permissions granted by view_unpublished
 * Takes over the Published or Admin filter query.
 */
class view_unpublished_handler_filter_node_status extends views_handler_filter_node_status {
  function query() {
    $table = $this->ensure_my_table();
    $where_per_type = array();
    foreach (node_type_get_types () as $type => $name) {
      $where_per_type[] = "($table.type = '$type' AND ***VIEWUNPUBLISHED_$type*** = 1)";
    }
    $where_per_type = implode(' OR ', $where_per_type);
    $this->query->add_where_expression($this->options['group'], "$table.status = 1 OR ($table.uid = ***CURRENT_USER*** AND ***CURRENT_USER*** <> 0 AND ***VIEW_OWN_UNPUBLISHED_NODES*** = 1) OR ***ADMINISTER_NODES*** = 1 OR $where_per_type");
  }
}
