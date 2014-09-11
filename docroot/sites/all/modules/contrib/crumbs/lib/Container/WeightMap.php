<?php

/**
 * Can determine a weight for a rule key based on wildcard weights.
 *
 * E.g. if the weight settings are
 *   * = 0
 *   crumbs.* = 4
 *   crumbs.nodeParent.* = 5
 * and then we are looking for a weight for
 *   crumbs.nodeParent.page
 * then the weight map will return 5, because crumbs.nodeParent.* is the best
 * matching wildcard.
 */
class crumbs_Container_WeightMap extends crumbs_Container_WildcardData {

  /**
   * @var array
   */
  private $localWeightMaps = array();

  /**
   * @param array $data
   *   Weights with wildcards, as saved in the configuration form.
   */
  function __construct(array $data) {
    asort($data);
    parent::__construct($data);
  }

  /**
   * Get the smallest weight in range.
   *
   * @return int
   *   The smallest weight..
   */
  function smallestValue() {
    foreach ($this->data as $value) {
      if ($value !== FALSE) {
        return $value;
      }
    }
    return FALSE;
  }

  /**
   * Gets a local weight map with a prefix.
   * E.g. if the config contains a weight setting "crumbs.nodeParent.* = 5",
   * then in a local weight map with prefix "crumbs", this will be available as
   * "nodeParent.* = 5".
   *
   * @param string $prefix
   *   The prefix.
   *
   * @return self
   *   The local weight map.
   *
   * @see crumbs_Container_WildcardData::prefixedContainer()
   */
  function localWeightMap($prefix) {
    if (!isset($this->localWeightMaps[$prefix])) {
      $data = $this->buildPrefixedData($prefix);
      $this->localWeightMaps[$prefix] = new self($data);
    }
    return $this->localWeightMaps[$prefix];
  }

  /**
   * @param true[] $candidates
   *   Format: $[$candidateKey] = true
   *
   * @return mixed[][]
   *   Format: $[0|1][$candidateKey] = $weight|false
   */
  function sortCandidateKeys($candidates) {
    $buckets = array();
    $disabledCandidates = array();
    foreach ($candidates as $key => $cTrue) {
      $weight = $this->valueAtKey($key);
      if (FALSE !== $weight) {
        $buckets[$weight][$key] = $weight;
      }
      else {
        $disabledCandidates[$key] = FALSE;
      }
    }
    ksort($buckets);
    $sorted = array();
    foreach ($buckets as $bucket) {
      $sorted += $bucket;
    }
    return array($sorted, $disabledCandidates);
  }

  /**
   * @param mixed[] $candidates
   *   Format: $[$candidateKey] = $candidateValue
   *
   * @return string|null
   *   The candidate key with the smallest weight, or NULL if none found.
   */
  function findBestCandidateKey(array $candidates) {
    $bestKey = NULL;
    $bestWeight = NULL;
    $this->findBetterCandidateKey($bestKey, $bestWeight, $candidates);
    return $bestKey;
  }

  /**
   * Check if the candidates contain a key with better weight than the one
   * given.
   *
   * @param string|null $bestKey
   * @param int|null $bestWeight
   * @param mixed[] $candidates
   *   Format: $[$candidateKey] = $candidateValue
   *
   * @return string|null
   *   The candidate key with the smallest weight, or NULL if none found.
   */
  function findBetterCandidateKey(&$bestKey, &$bestWeight, array $candidates) {
    foreach ($candidates as $key => $value) {
      $weight = $this->valueAtKey($key);
      if ($weight === FALSE) {
        continue;
      }
      if (!isset($bestWeight) || $weight < $bestWeight) {
        $bestWeight = $weight;
        $bestKey = $key;
      }
    }
  }

}
