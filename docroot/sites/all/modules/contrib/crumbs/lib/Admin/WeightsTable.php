<?php

/**
 * This class is a helper for theme_crumbs_weights_tabledrag()
 */
class crumbs_Admin_WeightsTable {

  /**
   * @var crumbs_PluginSystem_PluginInfo
   */
  protected $pluginInfo;

  /**
   * @var array[]
   */
  protected $sections = array();

  /**
   * @var array
   */
  protected $sortEnabled = array();

  /**
   * @var array
   */
  protected $descriptions = array();

  /**
   * @param crumbs_PluginSystem_PluginInfo $plugin_info
   */
  function __construct($plugin_info) {
    $this->pluginInfo = $plugin_info;
  }

  /**
   * @return array
   */
  function getRows() {

    array_multisort($this->sortEnabled, $this->sections['enabled']);

    list($grid, $n_grid_columns) = $this->gridOfDescriptions();
    $n = 4 + $n_grid_columns;
    $rows = array();
    foreach ($this->sections as $section_key => $section_rows) {
      foreach ($section_rows as $row_key => &$row) {
        $cells =& $row['data'];
        if (4 === count($cells)) {
          // Regular row
          if (isset($grid[$row_key])) {
            $cells = array_merge($cells, $grid[$row_key]);
          }
          else {
            $cells[] = array(
              'data' => '',
              'colspan' => $n_grid_columns,
            );
          }
        }
        elseif (1 === count($cells)) {
          // Section header row
          $cells[0]['colspan'] = $n;
        }
      }
      $rows = array_merge($rows, array_values($section_rows));
    }
    return $rows;
  }

  /**
   * @return array
   */
  protected function gridOfDescriptions() {
    $offsets = array();
    $n = 0;
    foreach ($this->descriptions as $row_key => $row_descriptions) {
      $offset = 0;
      foreach ($row_descriptions as $key => $descriptions) {
        if (0
          || !isset($offsets[$key])
          || $offsets[$key] < $offset
        ) {
          $offsets[$key] = $offset;
        }
        $offset += count($descriptions);
      }
      $n = max($n, $offset);
    }

    $empty_row = array_fill(0, $n, '');
    $grid = array();
    foreach ($this->descriptions as $row_key => $row_descriptions) {
      $row = $empty_row;
      $cell_offset = 0;
      foreach ($row_descriptions as $key => $descriptions) {
        $offset = $offsets[$key];
        foreach ($descriptions as $i => $description) {
          $cell_offset = $offset + $i;
          $row[$cell_offset] = $description;
        }
      }
      $colspan = $n - $cell_offset;
      if ($colspan > 1) {
        $row[$cell_offset] = array(
          'colspan' => $colspan,
          'data' => $row[$cell_offset],
        );
        $row = array_slice($row, 0, $cell_offset + 1);
      }
      $rule_key = substr($row_key, 6);
      $row_weight = $this->pluginInfo->weightMap->valueAtKey($rule_key);
      $row[] = is_numeric($row_weight) ? t('!key:&nbsp;!value', array(
        '!key' => t('Weight'),
        '!value' => $row_weight,
      )) : t('Disabled');
      $grid[$row_key] = $row;
    }

    return array($grid, $n + 1);
  }

  /**
   * @param string $key
   * @param array $child
   */
  function addElement($key, $child) {

    $section_key = $child['#section_key'];

    if ($child['weight']['#type'] === 'hidden') {
      $this->addSectionHeader($section_key, $key, $child);
    }
    else {
      $this->addRow($section_key, $key, $child);
    }

    $weight = $child['weight']['#value'];
    if ($section_key === 'enabled') {
      $this->sortEnabled[$key] = $weight;
    }
  }

  /**
   * @param string $section_key
   * @param string $key
   * @param array $child
   */
  function addSectionHeader($section_key, $key, $child) {
    $title = $child['#title'];
    unset($child['#description']);
    unset($child['#title']);
    $header = '<h3>' . $title . '</h3>' . drupal_render($child);
    $this->sections[$section_key][$key]['data'][]['data'] = $header;
  }

  /**
   * @param string $section_key
   * @param string $key
   * @param array $child
   */
  protected function addRow($section_key, $key, $child) {

    /** @var crumbs_Container_MultiWildcardDataOffset $meta */
    $meta = $child['#crumbs_rule_info'];
    $child['weight']['#attributes']['class'][] = 'crumbs-weight-element';
    $title = $child['#title'];
    unset($child['#title']);
    $cells = array(
      '<code>' . $title . '</code>  ',
      drupal_render($child),
    );

    $this->rowAddMethodInfo($cells, $meta);

    $this->sections[$section_key][$key] = array(
      'data' => $cells,
      'class' => array('draggable'),
    );

    $this->descriptions[$key] = $meta->getAll('descriptions');
  }

  /**
   * @param array $cells
   * @param crumbs_Container_MultiWildcardDataOffset $meta
   */
  protected function rowAddMethodInfo(&$cells, $meta) {
    $methods = array();
    $routes = array();
    if (is_array($meta->routeMethods)) {
      foreach ($meta->routeMethods as $method => $method_routes) {
        foreach ($method_routes as $route => $cTrue) {
          $methods[] = $method . '()';
          $routes[] = $route;
        }
      }
    }
    if (is_array($meta->basicMethods)) {
      foreach ($meta->basicMethods as $method => $cTrue) {
        $methods[] = $method . '()';
        $routes[] = '-';
      }
    }
    $cells[] = '<code>' . implode('<br/>', $methods) . '</code>';
    $cells[] = '<code>' . implode('<br/>', $routes) . '</code>';
  }
}
