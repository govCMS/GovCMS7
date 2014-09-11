<?php


class crumbs_Admin_DebugTable {

  /**
   * @var crumbs_UI_Table
   */
  private $table;

  /**
   * @var array[]
   */
  private $trail;

  /**
   * @var string[]
   */
  private $paths;

  function __construct() {
    $this->table = new crumbs_UI_Table();
    $this->table
      ->addColGroup('candidate', array('key', 'weight'))
      ->addRowName('path')
      ->addRowName('route')
      ->addRowName('link')
      ->td('path', 'candidate', t('Trail paths'))
      ->td('route', 'candidate', t('Router path'))
      ->td('link', 'candidate', t('Breadcrumb items'))
    ;
  }

  /**
   * @return string
   */
  function render() {
    return $this->table->render();
  }

  /**
   * @param array[] $trail
   *   Format: $[$path] = $trailItem
   * @param array[] $breadcrumbItems
   *   Format: $[] = $breadcrumbItem
   */
  function setTrail($trail, $breadcrumbItems) {
    $this->trail = $trail;
    $this->paths = array_reverse(array_keys($this->trail));
    $titles = $this->getTitles($trail, $breadcrumbItems);

    foreach ($this->paths as $i => $path) {
      $title = isset($titles[$path]) ? $titles[$path] : NULL;
      $this->addTrailItemColumns($i, $path, $i + 1 >= count($trail), $title);
      $route_code = '<code>' . $trail[$path]['route'] . '</code>';
      $this->table->td('route', "item.$i", $route_code);
    }
  }

  /**
   * @param array[] $trail
   *   Format: $[$path] = $trailItem
   * @param array[] $breadcrumbItems
   *   Format: $[] = $breadcrumbItem
   *
   * @return string[]
   *   Format: $[$path] = $title
   */
  private function getTitles($trail, $breadcrumbItems) {
    $titles = array();
    foreach ($breadcrumbItems as $item) {
      $path = $item['link_path'];
      if (isset($trail[$path]) && isset($item['title'])) {
        $titles[$path] = $item['title'];
      }
    }
    return $titles;
  }

  /**
   * Add columns and header cells for a given trail item.
   *
   * @param int $i
   * @param string $path
   * @param bool $is_last
   * @param string|null $title
   */
  private function addTrailItemColumns($i, $path, $is_last, $title) {

    $separator = ($i > 0) ? '&laquo;' : ':';
    $this->table
      ->addColName("separator.$i")
      ->td('', "separator.$i", $separator)
    ;

    if (!$is_last) {
      $this->table->addColGroup("item.$i", array('title', 'parent'));
      $path_eff = $path;
    }
    else {
      $this->table->addColGroup("item.$i", array('title'));
      $path_eff = '<front>';
    }

    $path_code = '<code>' . check_plain($path_eff) . '</code>';
    # $path_link = l($path_code, $path_eff, array('html' => TRUE));
    $this->table->td('path', "item.$i", $path_code);

    if (isset($title)) {
      $this->table->td('link', "item.$i", l($title, $path_eff));
    }
    else {
      // No title - the breadcrumb item will be skipped.
      $this->table->td('link', "item.$i", 'no title, skipped');
    }
  }

  /**
   * @param string $name
   * @param string|null $title
   */
  private function addLegendRow($name = 'legend', $title = NULL) {
    $this->table->addRowName($name);
    if (!isset($title)) {
      $this->table
        ->th($name, 'candidate.key', t('Candidate key'))
        ->th($name, 'candidate.weight', t('Weight'))
      ;
    }
    else {
      $this->table->th($name, 'candidate', $title);
    }
    foreach ($this->paths as $i => $path) {
      $this->table->th($name, "item.$i.title", t('Title'));
      if ($i + 1 < count($this->trail)) {
        $this->table->th($name, "item.$i.parent", t('Parent'));
      }
    }
  }

  /**
   * @param crumbs_PluginSystem_PluginEngine $unfilteredPluginEngine
   * @param crumbs_Container_WeightMap $weightMap
   */
  function addPluginResults($unfilteredPluginEngine, $weightMap) {
    list($candidates_all, $candidateKeys) = $this->getAllCandidates($unfilteredPluginEngine);
    list($enabledKeys, $disabledKeys) = $weightMap->sortCandidateKeys($candidateKeys);

    // Add table rows.
    $this->addLegendRow();
    $odd = TRUE;
    $this->addResultRows($enabledKeys, $odd);
    $this->addDefaultRow($odd);

    // Add rows for disabled candidates.
    $this->table->addRowName('blank');
    $this->addLegendRow('legend_disabled', t('Disabled keys'));
    $odd = TRUE;
    $this->addResultRows($disabledKeys, $odd);

    // Add table cells.
    $this->addCandidateCells($candidates_all, $weightMap);
  }

  /**
   * @param int[] $keys
   *   Format: $[$candidateKey] = $weight
   * @param bool $odd
   *
   * @throws Exception
   */
  private function addResultRows(array $keys, &$odd) {
    foreach ($keys as $candidateKey => $weight) {
      $this->table
        ->addRowName("row.$candidateKey")
        ->addRowClass("row.$candidateKey", $odd ? 'odd' : 'even')
      ;
      if (false !== $weight) {
        $this->table
          ->td("row.$candidateKey", 'candidate.key', $candidateKey)
          ->td(
            "row.$candidateKey",
            'candidate.weight',
            var_export($weight, TRUE)
          );
      }
      else {
        $this->table->td("row.$candidateKey", 'candidate', $candidateKey);
      }
      $odd = !$odd;
    }
  }

  /**
   * @param bool $odd
   */
  private function addDefaultRow(&$odd) {
    $this->table
      ->addRowName('default')
      ->addRowClass('default', $odd ? 'odd' : 'even')
      ->td('default', 'candidate.key', '(default)')
      ->td('default', 'candidate.weight', '-')
    ;
    $odd = !$odd;
  }

  /**
   * @param string[][][] $candidates_all
   *   Format: $['parent'|'title'][][$candidateKey] = $candidate
   * @param crumbs_Container_WeightMap $weightMap
   */
  private function addCandidateCells(array $candidates_all, $weightMap) {
    foreach ($candidates_all as $type => $candidates_type) {
      foreach ($candidates_type as $i => $candidates) {
        $path = $this->paths[$i];
        $item = $this->trail[$path];
        $bestCandidateKey = $weightMap->findBestCandidateKey($candidates);
        foreach ($candidates as $candidateKey => $candidate) {
          $this->addCandidateCell($candidate, $type, $i, $candidateKey, $bestCandidateKey);
        }
        if ($type === 'parent') {
          $defaultCandidate = isset($paths[$i + 1])
            ? $paths[$i + 1]
            : NULL;
        }
        else {
          $defaultCandidate = isset($item['title'])
            ? $item['title']
            : NULL;
        }
        $this->addCandidateCell($defaultCandidate, $type, $i, NULL, $bestCandidateKey);
      }
    }
  }

  /**
   * @param string $candidate
   * @param string $type
   * @param int $i
   * @param string $candidateKey
   * @param string $bestCandidateKey
   */
  private function addCandidateCell($candidate, $type, $i, $candidateKey, $bestCandidateKey) {
    $cellContent = check_plain($candidate);
    if ('parent' === $type) {
      $cellContent = '<code>' . $cellContent . '</code>';
    }
    if ($candidateKey === $bestCandidateKey) {
      $cellContent = '<strong>' . $cellContent . '</strong>';
    }
    $this->table->td(
      $candidateKey !== NULL
        ? "row.$candidateKey"
        : 'default',
      "item.$i.$type",
      $cellContent);
  }

  /**
   * @param crumbs_PluginSystem_PluginEngine $unfilteredPluginEngine
   *
   * @return array
   */
  private function getAllCandidates($unfilteredPluginEngine) {
    $candidates_all = array(
      'parent' => array(),
      'title' => array(),
    );
    $candidateKeys = array();
    $breadcrumb = array();
    foreach ($this->paths as $i => $path) {

      $candidates = $unfilteredPluginEngine->findAllTitles($path, $this->trail[$path], $breadcrumb);
      $candidates_all['title'][$i] = $candidates;
      foreach ($candidates as $candidateKey => $candidate) {
        $candidateKeys[$candidateKey] = TRUE;
      }
      if ($i + 1 < count($this->trail)) {
        $candidates = $unfilteredPluginEngine->findAllParents($path, $this->trail[$path]);
        $candidates_all['parent'][$i] = $candidates;
        foreach ($candidates as $candidateKey => $candidate) {
          $candidateKeys[$candidateKey] = TRUE;
        }
      }
    }

    return array($candidates_all, $candidateKeys);
  }

} 
