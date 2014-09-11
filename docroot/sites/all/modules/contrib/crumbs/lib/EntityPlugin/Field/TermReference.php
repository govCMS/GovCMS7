<?php

class crumbs_EntityPlugin_Field_TermReference extends crumbs_EntityPlugin_Field_Abstract {

  /**
   * {@inheritdoc}
   */
  function fieldFindCandidate(array $items) {

    $terms = array();
    foreach ($items as $item) {
      $terms[$item['tid']] = TRUE;
    }

    if (count($terms) > 1) {
      $walk = $terms;
      $visited = array();
      while (!empty($walk)) {
        $visited += $walk;
        foreach ($walk as $tid => $true) {
          $parents = taxonomy_get_parents($tid);
          unset($walk[$tid]);
          foreach ($parents as $parent_tid => $parent) {
            unset($terms[$parent_tid]);
            if (!isset($visited[$parent_tid])) {
              $walk[$parent_tid] = $parent;
            }
          }
        }
      }
    }

    // Return the path of the first found term, if any.
    foreach ($terms as $tid => $term_info) {
      $term = taxonomy_term_load($tid);
      if (!empty($term)) {
        $uri = entity_uri('taxonomy_term', $term);
        if (!empty($uri)) {
          return $uri['path'];
        }
      }
    }

    return NULL;
  }

}
