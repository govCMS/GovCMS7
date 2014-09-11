<?php

/**
 * A class to render HTML tables.
 *
 * This is a small version of the cellbrush library.
 * @link https://github.com/donquixote/cellbrush
 */
class crumbs_UI_Table {

  /**
   * @var crumbs_UI_TableColumns
   */
  private $columns;

  /**
   * @var crumbs_UI_TableSection
   */
  private $thead;

  /**
   * @var crumbs_UI_TableSection
   */
  private $tbody;

  /**
   * @var crumbs_UI_TableSection[]
   */
  private $tbodies = array();

  /**
   * @var crumbs_UI_TableSection
   */
  private $tfoot;

  /**
   * The constructor.
   */
  function __construct() {
    $this->columns = new crumbs_UI_TableColumns();
    $this->thead = new crumbs_UI_TableSection($this->columns);
    $this->tbody = new crumbs_UI_TableSection($this->columns);
    $this->tfoot = new crumbs_UI_TableSection($this->columns);
  }

  /**
   * @param string $colName
   *
   * @return $this
   * @throws Exception
   */
  function addColName($colName) {
    $this->columns->addColname($colName);
    return $this;
  }

  /**
   * @param string $groupName
   * @param string[] $colNameSuffixes
   *
   * @return $this
   * @throws Exception
   */
  function addColGroup($groupName, array $colNameSuffixes) {
    $this->columns->addColGroup($groupName, $colNameSuffixes);
    return $this;
  }

  /**
   * @return crumbs_UI_TableSection
   */
  function thead() {
    return $this->thead;
  }

  /**
   * @param string|null $name
   *   Key to identify the tbody, if another than the main tbody is used.
   *
   * @return crumbs_UI_TableSection
   */
  function tbody($name = NULL) {
    if (!isset($name)) {
      return $this->tbody;
    }
    return isset($this->tbodies[$name])
      ? $this->tbodies[$name]
      : $this->tbodies[$name] = new crumbs_UI_TableSection($this->columns);
  }

  /**
   * @return crumbs_UI_TableSection
   */
  function tfoot() {
    return $this->tfoot;
  }

  /**
   * @param string $rowName
   *
   * @return $this
   * @throws Exception
   */
  function addRowName($rowName) {
    $this->tbody->addRowName($rowName);
    return $this;
  }

  /**
   * @param string $rowName
   * @param string $class
   *
   * @return $this
   */
  public function addRowClass($rowName, $class) {
    $this->tbody->addRowClass($rowName, $class);
    return $this;
  }

  /**
   * @param string $rowName
   * @param string $colName
   * @param string $content
   *
   * @return $this
   */
  function td($rowName, $colName, $content) {
    $this->tbody->td($rowName, $colName, $content);
    return $this;
  }

  /**
   * @param string $rowName
   * @param string $colName
   * @param string $content
   *
   * @return $this
   */
  function th($rowName, $colName, $content) {
    $this->tbody->th($rowName, $colName, $content);
    return $this;
  }

  /**
   * @return string
   *   Rendered table html.
   */
  function render() {
    $html = '';
    $html .= $this->thead->render('thead');
    $html .= $this->tfoot->render('tfoot');
    $html .= $this->tbody->render('tbody');
    foreach ($this->tbodies as $tbody) {
      $html .= $tbody->render('tbody');
    }
    return '<table>' . $html . '</table>';
  }

  /**
   * Get an array that is compatible with Drupal's theme('table').
   *
   * @return array[]
   *   Format:
   *   $[]['data'][]['data'] = $cellHtml
   *   $[]['data'][]['header'] = true|false
   *   $[]['data'][][$cellAttributeName] = $cellAttributeValue
   *   $[][$rowAttributeName] = $rowAttributeValue
   */
  function getDrupalRows() {
    return $this->tbody->getDrupalRows();
  }

} 
