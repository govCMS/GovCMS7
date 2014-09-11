<?php


/**
 * Implements hook_crumbs_plugins()
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function taxonomy_crumbs_plugins($api) {

  $api->multiPlugin('termParent');

  foreach (field_info_fields() as $field_name => $field_info) {
    if ($field_info['type'] === 'taxonomy_term_reference') {
      $plugin = new crumbs_EntityPlugin_Field_TermReference($field_name, $field_info['bundles']);
      $api->entityParentPlugin('termReference.' . $field_name, $plugin, array_keys($field_info['bundles']));
    }
  }
  $api->disabledByDefault('termReference.*');
}


class taxonomy_CrumbsMultiPlugin_termParent implements crumbs_MultiPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    foreach (taxonomy_get_vocabularies() as $voc) {
      $api->ruleWithLabel($voc->machine_name, $voc->name, t('Vocabulary'));
    }
    // Now set a generic title for the entire plugin.
    $api->descWithLabel(t('The parent term'), t('Parent'));
  }

  /**
   * Terms get their parent terms as breadcrumb parent.
   * The method name matches the router path "taxonomy/term/%".
   *
   * @param string $path
   * @param array $item
   *
   * @return array
   */
  function findParent__taxonomy_term_x($path, $item) {
    if (FALSE === $term = crumbs_Util::itemExtractEntity($item, 'taxonomy_term', 2)) {
      return NULL;
    }

    $parents = taxonomy_get_parents($term->tid);
    foreach ($parents as $parent_tid => $parent_term) {
      if ($parent_term->vocabulary_machine_name == $term->vocabulary_machine_name) {
        $uri = entity_uri('taxonomy_term', $parent_term);
        if (!empty($uri)) {
          return array($term->vocabulary_machine_name => $uri['path']);
        }
      }
    }

    return NULL;
  }
}
