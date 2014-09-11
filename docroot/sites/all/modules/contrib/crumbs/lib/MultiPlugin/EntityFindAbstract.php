<?php

abstract class crumbs_MultiPlugin_EntityFindAbstract implements crumbs_MultiPlugin {

  /**
   * @var crumbs_EntityPlugin
   */
  protected $plugin;

  /**
   * Helper method for describe()
   *
   * @param crumbs_InjectedAPI_describeMultiPlugin $api
   * @param string $entity_type
   * @param string $label
   * @return array
   */
  protected function describeGeneric($api, $entity_type, $label) {
    $info = entity_get_info($entity_type);
    $keys = array();
    foreach ($info['bundles'] as $bundle_key => $bundle) {
      $keys[$bundle_key] = t('!key: !value', array(
        '!key' => $label,
        '!value' => $bundle['label'],
      ));
    }
    if (method_exists($this->plugin, 'describe')) {
      $keys = $this->plugin->describe($api, $entity_type, $keys);
      return $keys;
    }
    else {
      return $keys;
    }
  }

  /**
   * @param crumbs_EntityPlugin $plugin
   *   The object that can actually determine a parent path for the entity.
   */
  function __construct($plugin) {
    $this->plugin = $plugin;
  }
}
