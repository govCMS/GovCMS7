<?php

/**
 * Note: We could achieve the same with the nodeParent / entityParent,
 * but we do it with a custom plugin for a showcase.
 */
class crumbs_example_CrumbsMultiPlugin_ListOfNews implements crumbs_MultiPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    // We will have a separate rule per node type on Admin > Structure > Crumbs.
    foreach (node_type_get_types() as $type_name => $type) {
      $api->addRule($type_name, $type->name);
    }
  }

  /**
   * Set news/(year)/(month)/(day) as the parent for a node.
   * You can use the weights config at Admin > Structure > Crumbs to specify
   * which node types this should apply to.
   *
   * @param string $path
   * @param array $item
   *   The loaded router item for $path.
   *
   * @return string[]|NULL
   *   Candidates for the parent path, or NULL.
   */
  function findParent__node_x($path, $item) {
    if (FALSE === $node = crumbs_Util::itemExtractEntity($item, 'node', 1)) {
      return NULL;
    }

    if (!empty($node->created)) {
      list($year, $month, $day) = explode('-', date('Y-m-d', $node->created));
      $path = "news/$year/$month/$day";
      return array($node->type => $path);
    }

    return NULL;
  }
}
