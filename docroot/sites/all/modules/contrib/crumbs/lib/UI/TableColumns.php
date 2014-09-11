<?php


class crumbs_UI_TableColumns {

  /**
   * @var mixed[]
   */
  private $cols = array();

  /**
   * @var string[][]
   */
  private $colGroups = array();

  /**
   * @return mixed[]
   */
  public function getCols() {
    return $this->cols;
  }

  /**
   * @return string[][]
   */
  public function getColGroups() {
    return $this->colGroups;
  }

  /**
   * @param string $colName
   *
   * @throws Exception
   */
  function addColName($colName) {
    if (isset($this->cols[$colName])) {
      throw new \Exception("Column '$colName' already exists.");
    }
    $this->cols[$colName] = TRUE;
  }

  /**
   * @param string $groupName
   * @param string[] $colNameSuffixes
   *
   * @throws Exception
   */
  function addColGroup($groupName, array $colNameSuffixes) {
    if (empty($colNameSuffixes)) {
      throw new Exception("Suffixes cannot be empty.");
    }
    foreach ($colNameSuffixes as $colNameSuffix) {
      $colName = $groupName . '.' . $colNameSuffix;
      if (isset($this->cols[$colName])) {
        throw new Exception("Column '$colName' already exists.");
      }
      $this->cols[$colName] = $groupName;
    }
    $this->colGroups[$groupName] = $colNameSuffixes;
  }

  public function verifyColName($colName) {
    if (1
      && !isset($this->cols[$colName])
      && !isset($this->colGroups[$colName])
      && '' !== $colName
    ) {
      throw new Exception("Unknown column name '$colName'.");
    }
  }

} 
