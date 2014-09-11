<?php


/**
 * Implements hook_crumbs_plugins().
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function entityreference_prepopulate_crumbs_plugins($api) {
  foreach (field_info_fields() as $field_name => $field_info) {
    if (0
      || $field_info['type'] !== 'entityreference'
      || empty($field_info['bundles']['node'])
      || empty($field_info['settings']['target_type'])
    ) {
      continue;
    }

    $target_type = $field_info['settings']['target_type'];

    foreach ($field_info['bundles']['node'] as $node_type) {
      $instance = field_info_instance('node', $field_name, $node_type);
      if (0
        || empty($instance['default_value_function'])
        || 'entityreference_prepopulate_field_default_value' !== $instance['default_value_function']
      ) {
        continue;
      }

      $route = 'node/add/' . str_replace('_', '-', $node_type);
      $plugin = new entityreference_prepopulate_CrumbsMonoPlugin_node($node_type, $field_name, $target_type);
      $api->routeMonoPlugin($route, "node.$field_name.$node_type", $plugin);
    }
  }
}

class entityreference_prepopulate_CrumbsMonoPlugin_node implements crumbs_MonoPlugin_FindParentInterface {

  /**
   * @var string
   *   The node type, e.g. 'article'.
   */
  protected $nodeType;

  /**
   * @var string
   *   Field name of the entityreference field.
   */
  protected $fieldName;

  /**
   * @var string
   *   The target entity type for the entityreference field.
   */
  protected $targetType;

  /**
   * @param string $node_type
   * @param string $field_name
   * @param string $target_type
   */
  function __construct($node_type, $field_name, $target_type) {
    $this->nodeType = $node_type;
    $this->fieldName = $field_name;
    $this->targetType = $target_type;
  }

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t('!field_name from request', array(
      '!field_name' => '<code>?' . $this->fieldName . '=*</code>',
    )), t('Parent'));
  }

  /**
   * {@inheritdoc}
   */
  function findParent($path, $item) {
    if (empty($_GET[$this->fieldName])) {
      return NULL;
    }

    $v = $_GET[$this->fieldName];
    if (!($v > 0)) {
      return NULL;
    }

    $target_entities = entity_load($this->targetType, array($v));
    if (empty($target_entities[$v])) {
      return NULL;
    }

    $uri = entity_uri($this->targetType, $target_entities[$v]);
    if (empty($uri['path'])) {
      return NULL;
    }

    return $uri['path'];
  }
}
