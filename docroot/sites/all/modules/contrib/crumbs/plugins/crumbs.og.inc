<?php

/**
 * Implements hook_crumbs_plugins().
 *
 * This is the version for the og-7.x-1.x branch.
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function og_crumbs_plugins($api) {
  $api->multiPlugin('group_post');
  $api->monoPlugin('groups_overview_title');

  $api->multiPlugin('groups_overview',
    new og_CrumbsMultiPlugin_groups_overview('group-list'));
  $api->multiPlugin('my_groups_overview',
    new og_CrumbsMultiPlugin_my_groups_overview('user-groups'));
}

/**
 * Use the group node as a parent for group posts.
 * The priorities can be configured per group content type.
 */
class og_CrumbsMultiPlugin_group_post implements crumbs_MultiPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $types = node_type_get_types();
    foreach ($types as $type) {
      if (og_is_group_content_type('node', $type->type)) {
        $api->addRule($type->type);
      }
    }
  }

  function findParent__node_x($path, $item) {
    if (FALSE === $node = crumbs_Util::itemExtractEntity($item, 'node', 1)) {
      return NULL;
    }

    $items = field_get_items('node', $node, 'group_audience');
    if (is_array($items)) {
      foreach ($items as $item) {
        $row = db_query("SELECT * FROM {og} WHERE gid = :gid", array(':gid' => $item['gid']))->fetchObject();
        if ($row && $row->entity_type === 'node') {
          $parent_path = $this->getParentPath($row->etid, $node);
          return array($node->type => $parent_path);
        }
      }
    }

    return NULL;
  }

  /**
   * This method can be overridden by custom plugins that inherit from this one,
   * e.g. to set a different parent for group events than for group discussions.
   *
   * @param int $group_nid
   * @param object $group_post
   *
   * @return string
   */
  protected function getParentPath($group_nid, $group_post) {
    return 'node/' . $group_nid;
    /*
     * Example:
     * switch ($group_post->type) {
     *   case 'event':
     *     return 'node/' . $group_nid . '/events';
     *   case 'discussion':
     *     return 'node/' . $group_nid . '/forum';
     *   default:
     *     return 'node/' . $group_nid;
     * }
     */
  }

}

/**
 * Make $groups_overview_path the parent path for group nodes.
 * The priorities can be configured per group node type.
 */
class og_CrumbsMultiPlugin_groups_overview implements crumbs_MultiPlugin {

  protected $groupsOverviewPath;

  /**
   * @param string $groups_overview_path
   *   The path to be used as parent for all group nodes.
   */
  function __construct($groups_overview_path) {
    $this->groupsOverviewPath = $groups_overview_path;
  }

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $types = node_type_get_types();
    foreach ($types as $type) {
      if (og_is_group_type('node', $type->type)) {
        $api->addRule($type->type);
      }
    }
  }

  /**
   * @param string $path
   * @param array $item
   *
   * @return array|null
   */
  function findParent__node_x($path, $item) {
    if (FALSE === $node = crumbs_Util::itemExtractEntity($item, 'node', 1)) {
      return NULL;
    }

    $items = field_get_items('node', $node, 'group_group');
    if ($items) {
      return array($node->type => 'group-list');
    }

    return NULL;
  }

}

/**
 * Make t('Groups') the title for '/group-list'.
 */
class og_CrumbsMonoPlugin_groups_overview_title implements crumbs_MonoPlugin_FindTitleInterface {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    return t('Set "Group" as the title for item for "group-list".');
  }

  /**
   * {@inheritdoc}
   */
  function findTitle($path, $item) {
    if ($item['route'] === 'group-list') {
      return t('Groups');
    }

    return NULL;
  }

}

/**
 * Make $my_groups_path the parent path for group nodes where the current user
 * is a member.
 * The priorities can be configured per group node type.
 */
class og_CrumbsMultiPlugin_my_groups_overview implements crumbs_MultiPlugin {

  /**
   * @var string
   */
  protected $myGroupsPath;

  /**
   * @param string $my_groups_path
   *   The path to be used as parent for all group nodes where the current user
   *   is a member.
   */
  function __construct($my_groups_path) {
    $this->myGroupsPath = $my_groups_path;
  }

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $types = node_type_get_types();
    foreach ($types as $type) {
      if (og_is_group_type('node', $type->type)) {
        $api->addRule($type->type);
      }
    }
  }

  /**
   * @param string $path
   *   The path that we want to find a parent for.
   * @param array $item
   *   Loaded router item, as returned from crumbs_get_router_item()
   *
   * @return array
   *   Parent path candidates
   */
  function findParent__node_x($path, $item) {
    if (FALSE === $node = crumbs_Util::itemExtractEntity($item, 'node', 1)) {
      return NULL;
    }

    if (og_is_group_type('node', $node->type)) {
      $group = og_get_group('node', $node->nid);
      if (!empty($group)) {
        if (og_is_member($group->gid)) {
          return array($node->type => 'user-groups');
        }
      }
    }

    return NULL;
  }

}
