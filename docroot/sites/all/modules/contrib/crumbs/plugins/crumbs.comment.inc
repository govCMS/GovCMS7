<?php

/**
 * Implements hook_crumbs_plugins().
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function comment_crumbs_plugins($api) {
  $api->monoPlugin('reply');
  $api->monoPlugin('comment');
  $api->monoPlugin('skip');
}

class comment_CrumbsMonoPlugin_reply implements crumbs_MonoPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t("The comment's node"), t('Parent'));
  }

  /**
   * findParent callback for comment/reply/%.
   * Actually, system paths cam look more like comment/reply/%/%, but the router
   * path is comment/reply/%. Complain to the people who wrote comment module.
   *
   * @param string $path
   * @param array $item
   *
   * @return string
   */
  function findParent__comment_reply_x($path, $item) {
    $nid = $item['fragments'][2];
    return 'node/'. $nid;
  }
}

class comment_CrumbsMonoPlugin_comment implements crumbs_MonoPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t("The comment's node"), t('Parent'));
  }

  /**
   * Make node/% the parent for comment/%.
   * This also completes the breadcrumb for other comment/%/* paths.
   *
   * @param string $path
   * @param array $item
   *
   * @return string
   */
  function findParent__comment_x($path, $item) {
    $comment = comment_load($item['original_map'][1]);
    if (!empty($comment->nid)) {
      return 'node/' . $comment->nid;
    }

    return NULL;
  }

}

class comment_CrumbsMonoPlugin_skip implements crumbs_MonoPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    return t('Skip comment/% in the breadcrumb.');
  }

  /**
   * The default title for comment/% is "Comment permalink",
   * so not very useful to have in the breadcrumb.
   *
   * @param string $path
   * @param array $item
   *
   * @return false
   *   A value of FALSE indicates that the breadcrumb item should be skipped.
   */
  function findTitle__comment_x($path, $item) {
    return FALSE;
  }
}
