<?php

class crumbs_MultiPlugin_EntityFindSomething extends crumbs_MultiPlugin_EntityFindAbstract {

  /**
   * @var string
   *   The entity type, e.g. 'node' or 'taxonomy_term'.
   */
  protected $entityType;

  /**
   * @var string
   *   The key on the $entiy object to determine the bundle.
   *   E.g. 'type' for nodes, or 'vocabulary_machine_name' for taxonomy terms.
   */
  protected $bundleKey;

  /**
   * @var string
   *   The label for the bundle, e.g. "Node type" or "Vocabulary".
   *   This is an untranslated string.
   */
  protected $bundleName;

  /**
   * @var array
   *   Plugin key weight per user role id.
   *   This is empty for entity types other than user.
   */
  protected $weights = array();

  /**
   * @param crumbs_EntityPlugin $plugin
   *   The object that can actually determine a parent path for the entity.
   * @param string $entity_type
   *   The entity type.
   * @param string $bundle_key
   *   The key on the $entiy object to determine the bundle.
   * @param string $bundle_name
   *   The label for the bundle, e.g. "Node type" or "Vocabulary".
   *   This is an untranslated string.
   */
  function __construct($plugin, $entity_type, $bundle_key, $bundle_name) {
    $this->entityType = $entity_type;
    $this->bundleKey = $bundle_key;
    $this->bundleName = $bundle_name;
    parent::__construct($plugin);
  }

  /**
   * @param crumbs_Container_WeightMap $localWeightMap
   */
  function initWeights($localWeightMap) {

    if ('user' !== $this->entityType) {
      return;
    }

    foreach (user_roles(TRUE) as $rid => $role) {
      $weight = $localWeightMap->valueAtKey($role);
      if (FALSE !== $weight) {
        $this->weights[$rid] = $weight;
      }
    }
    asort($this->weights);
  }

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    return $this->describeGeneric($api, $this->entityType, t($this->bundleName));
  }

  /**
   * @param string $path
   * @param array $item
   * @return array
   */
  protected function find($path, $item) {
    if (FALSE === $entity = crumbs_Util::itemExtractEntity($item, $this->entityType)) {
      return NULL;
    }

    if ('user' === $this->entityType) {
      return $this->userFind($entity);
    }
    else {
      return $this->entityFind($entity);
    }
  }

  /**
   * @param stdClass $entity
   * @return array
   */
  protected function entityFind(stdClass $entity) {
    if (!empty($this->bundleKey) && !empty($entity->{$this->bundleKey})) {
      $distinction_key = $entity->{$this->bundleKey};
    }
    else {
      $distinction_key = $this->entityType;
    }

    $parent = $this->plugin->entityFindCandidate($entity, $this->entityType, $distinction_key);
    if (!empty($parent)) {
      return array($distinction_key => $parent);
    }

    return NULL;
  }

  /**
   * @param stdClass $user
   * @return array
   */
  protected function userFind(stdClass $user) {
    $candidates = array();
    foreach ($this->weights as $rid => $weight) {
      if (!empty($user->roles[$rid])) {
        $role = $user->roles[$rid];
        $parent = $this->plugin->entityFindCandidate($user, 'user', $role);
        if (!empty($parent)) {
          $candidates[$role] = $parent;
        }
      }
    }
    return $candidates;
  }

}
