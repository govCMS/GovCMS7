<?php
/**
 * Filter by bean type
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_bean_type extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Block types');
      $bean_info = entity_get_info('bean');
      $options = array();
      foreach ($bean_info['bundles'] as $type => $info) {
        $options[$type] = t($info['label']);
      }
      asort($options);
      $this->value_options = $options;
    }
  }
}
