<?php


class crumbs_Debug_CandidateLogger {

  /**
   * @var array
   */
  protected $logFindParent = array();

  /**
   * @var array
   */
  protected $logFindTitle = array();

  /**
   * @var array
   */
  protected $info = array();

  /**
   * @return array
   */
  function getLogFindParent() {
    return $this->logFindParent;
  }

  /**
   * @return array
   */
  function getLogFindTitle() {
    return $this->logFindTitle;
  }

  /**
   * @param array $trail
   * @return array
   */
  function getAsMatrix($trail) {
    $rows = array();
    $weights = array();
    $empty_row = array();
    $default_row = array();
    $paths = array_keys($trail);
    foreach ($paths as $i => $path) {
      $empty_row["$path:title"] = '';
      $default_row["$path:title"] = isset($trail[$path]['title']) ? $trail[$path]['title'] : 'NULL';
      $empty_row["$path:parent"] = '';
      $default_row["$path:parent"] = isset($paths[$i + 1]) ? $paths[$i + 1] : 'END';
    }
    if (isset($path)) {
      // The last item does not have a parent.
      unset($empty_row["$path:parent"]);
      unset($default_row["$path:parent"]);
    }

    $best_cells = array();
    foreach (array(
      'parent' => $this->logFindParent,
      'title' => $this->logFindTitle
    ) as $type => $log) {
      foreach ($log as $info) {
        if (isset($info['bestCandidateKey'])) {
          $best_cells[$info['bestCandidateKey']][$info['path'] . ':' . $type] = TRUE;
        }
        else {
          $best_cells['(default)'][$info['path'] . ':' . $type] = TRUE;
        }
        if (isset($info['candidates'])) {
          foreach ($info['candidates'] as $key => $candidate) {
            if (!isset($rows[$key])) {
              $rows[$key] = $empty_row;
              $weights[$key] = $candidate['weight'];
            }
            if (!isset($candidate['raw'])) {
              $value = '(NULL)';
            }
            elseif (FALSE === $candidate['raw']) {
              $value = '(FALSE)';
            }
            else {
              $value = check_plain($candidate['raw']);
              if ($candidate['processed'] !== $candidate['raw']) {
                $value .= '<br/>->' . check_plain($candidate['processed']);
              }
            }
            $rows[$key][$info['path'] . ':' . $type] = $value;
          }
        }
        if (isset($info['path'])) {
          $cols[$info['path']] = array();
        }
      }
    }

    asort($weights);
    $matrix = array();
    foreach ($weights as $key => $weight) {
      $matrix[$key] = $rows[$key];
    }
    $weights['(default)'] = '-';
    $matrix['(default)'] = $default_row;

    return array($matrix, $best_cells, $weights);
  }

  /**
   * Invoke all relevant plugins to find the parent for a given path.
   *
   * @param string $path
   * @param array $item
   */
  function endFindParent($path, $item) {
    $this->logFindParent[] = $this->info + compact('path', 'item');
    $this->info = array();
  }

  /**
   * Invoke all relevant plugins to find the title for a given path.
   *
   * @param string $path
   * @param array $item
   * @param array $breadcrumb
   */
  function endFindTitle($path, $item, $breadcrumb) {
    $this->logFindTitle[] = $this->info + compact('path', 'item', 'breadcrumb');
    $this->info = array();
  }

  /**
   * @param string $key
   * @param int $weight
   * @param string $raw
   * @param string $processed
   */
  function addCandidate($key, $weight, $raw, $processed) {
    $this->info['candidates'][$key] = compact('weight', 'raw', 'processed');
  }

  /**
   * @param string $key
   */
  function setBestCandidateKey($key) {
    $this->info['bestCandidateKey'] = $key;
    if (isset($this->info['candidates'][$key])) {
      $this->info['bestCandidate'] = $this->info['candidates'][$key];
    }
  }
}
