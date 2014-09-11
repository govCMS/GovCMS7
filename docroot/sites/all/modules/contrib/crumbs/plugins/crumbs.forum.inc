<?php


/**
 * Implements hook_crumbs_plugins().
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function forum_crumbs_plugins($api) {

  $api->monoPlugin('forumTerm');
  $api->monoPlugin('forumTermName');
  $api->monoPlugin('forumThread');
  $api->monoPlugin('forumThreadCreate');
  $api->monoPlugin('forumThreadCreateTitle');
}


// -----------------------------------------------------------------------------


class forum_CrumbsMonoPlugin_forumTerm implements crumbs_MonoPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t('The parent forum'), t('Parent'));
  }

  /**
   * Forums get their parent forums as breadcrumb parent.
   * The method name matches the router path "forum/%".
   * Forums are actually taxonomy terms, just the path is different.
   *
   * @param string $path
   * @param array $item
   *
   * @return string|null
   */
  function findParent__forum_x($path, $item) {
    // Load the forum term, even if the wildcard loader has been replaced or
    // removed. This will use entity_load() and not forum_forum_load(), because
    // we don't need the forum stuff here.
    $term = crumbs_Util::itemExtractEntity($item, 'taxonomy_term', 1);
    if (FALSE === $term) {
      return NULL;
    }

    $parents = taxonomy_get_parents($term->tid);
    foreach ($parents as $parent_tid => $parent_term) {
      if ($parent_term->vocabulary_machine_name == $term->vocabulary_machine_name) {
        // The parent forum
        return 'forum/' . $parent_tid;
      }
    }
    // Forum overview
    return 'forum';
  }
}


// -----------------------------------------------------------------------------


class forum_CrumbsMonoPlugin_forumTermName implements crumbs_MonoPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t('The forum\'s term name'), t('Title'));
  }

  /**
   * Forums get their parent forums as breadcrumb parent.
   * The method name matches the router path "forum/%".
   * Forums are actually taxonomy terms, just the path is different.
   *
   * @param string $path
   * @param array $item
   *
   * @return string|null
   */
  function findTitle__forum_x($path, $item) {
    // Load the forum term, even if the wildcard loader has been replaced or
    // removed. This will use entity_load() and not forum_forum_load(), because
    // we don't need the forum stuff here.
    $term = crumbs_Util::itemExtractEntity($item, 'taxonomy_term', 1);
    if (FALSE === $term || empty($term->name)) {
      return NULL;
    }
    return $term->name;
  }
}


// -----------------------------------------------------------------------------


class forum_CrumbsMonoPlugin_forumThread implements crumbs_MonoPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t('The forum the node belongs to'), t('Parent'));
  }

  /**
   * Forum nodes get their forum terms as breadcrumb parents.
   * The method name matches the router path "node/%".
   *
   * @param string $path
   * @param array $item
   *
   * @return string|null
   */
  function findParent__node_x($path, $item) {
    $node = crumbs_Util::itemExtractEntity($item, 'node', 1);
    if ( FALSE === $node
      || empty($node->forum_tid)
      || !_forum_node_check_node_type($node)
    ) {
      return NULL;
    }

    return 'forum/' . $node->forum_tid;
  }
}


// -----------------------------------------------------------------------------


class forum_CrumbsMonoPlugin_forumThreadCreate implements crumbs_MonoPlugin_FindParentInterface {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t('node/add/*/* in a forum'), t('Path'));
    $api->titleWithLabel(t('The forum where the node is going to be created.'), t('Parent'));
  }

  /**
   * Set a parent path for e.g. node/add/(type)/(tid), where
   * - (type) a forum-enabled node type, e.g. "forum".
   * - (tid) is the forum term tid.
   *
   * {@inheritdoc}
   */
  function findParent($path, $item) {
    if (
      // Start with a cheap-to-compute condition,
      // so the regex can be skipped in the average case.
      substr($path, 0, 9) === 'node/add/' &&
      preg_match('#^node/add/([^/]+)/(\d+)$#', $path, $m)
    ) {
      $type = $m[1];
      $tid = (int)$m[2];
      // We need to find out if the node type is forum-enabled.
      // See _forum_node_check_node_type() in forum.module.
      $field = field_info_instance('node', 'taxonomy_forums', $type);
      if (is_array($field)) {
        // That's a node/add/(type)/(tid) page for a forum-enabled node type.
        $term = taxonomy_term_load($item['original_map'][3]);
        if ($term instanceof stdClass && 'forums' === $term->vocabulary_machine_name) {
          return 'forum/' . $term->tid;
        }
      }
    }

    return NULL;
  }

}


class forum_CrumbsMonoPlugin_forumThreadCreateTitle implements crumbs_MonoPlugin_FindTitleInterface {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t('node/add/*/* in a forum'), t('Path'));
    $api->titleWithLabel('"' . t('New topic') . '"', t('Title'));
  }

  /**
   * Set a breadcrumb item title for e.g. node/add/(type)/(tid), where
   * - (type) a forum-enabled node type, e.g. "forum".
   * - (tid) is the forum term tid.
   *
   * {@inheritdoc}
   */
  function findTitle($path, $item) {
    if (
      // Start with a cheap-to-compute condition,
      // so the regex can be skipped in the average case.
      substr($path, 0, 9) === 'node/add/' &&
      preg_match('#^node/add/([^/]+)/(\d+)$#', $path, $m)
    ) {
      $type = $m[1];
      $tid = (int)$m[2];
      // We need to find out if the node type is forum-enabled.
      // See _forum_node_check_node_type() in forum.module.
      $field = field_info_instance('node', 'taxonomy_forums', $type);
      if (is_array($field)) {
        // That's a node/add/(type)/(tid) page for a forum-enabled node type.
        $term = taxonomy_term_load($item['original_map'][3]);
        if ($term instanceof stdClass && 'forums' === $term->vocabulary_machine_name) {
          return $this->newTopicTitle($type);
        }
      }
    }

    return NULL;
  }

  /**
   * Method that can be overwritten by subclasses.
   *
   * @param $type
   *
   * @return null|string
   */
  protected function newTopicTitle($type) {
    return t('New topic');
  }
}
