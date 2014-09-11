<?php


class crumbs_CrumbsEntityPlugin_TokenDisabled implements crumbs_EntityPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api, $entity_type, $keys) {
    $patterns = variable_get('crumbs_' . $entity_type . '_parent_patterns', array());
    foreach ($keys as $key => $title) {
      if (empty($patterns[$key])) {
        unset($keys[$key]);
      }
      else {
        $api->addRule($key, $title);
        $api->descWithLabel('"' . check_plain($patterns[$key]) . '"', t('Parent'), $key);
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  function entityFindCandidate($entity, $entity_type, $distinction_key) {

    // This is cached..
    $patterns = variable_get('crumbs_' . $entity_type . '_parent_patterns', array());

    if (!empty($patterns[$distinction_key])) {
      $parent = $patterns[$distinction_key];
      // Only accept candidates where all tokens are fully resolved.
      // This means we can't have literal '[' in the path - so be it.
      if (FALSE === strpos($parent, '[')) {
        return $parent;
      }
    }

    return NULL;
  }

}
