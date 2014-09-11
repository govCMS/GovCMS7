<?php


/**
 * Implements hook_crumbs_plugins().
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function path_crumbs_plugins($api) {
  // Just one plugin for the entire module.
  $api->monoPlugin();
  $api->disabledByDefault();
}


/**
 * Implementation of class hook class_CrumbsParentFinder
 * on the behalf of path module.
 */
class path_CrumbsMonoPlugin implements crumbs_MonoPlugin_FindParentInterface {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    return t('Chop off the last fragment of the path alias, consider the result as the parent path.');
  }

  /**
   * {@inheritdoc}
   */
  function findParent($path, $item) {
    if ($alias = $item['alias']) {
      return crumbs_reduce_path($alias, 1);
    }

    return NULL;
  }
}
