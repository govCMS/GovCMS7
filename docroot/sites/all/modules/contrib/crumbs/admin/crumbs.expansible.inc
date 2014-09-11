<?php

/**
 * Theme callback for form elements with "#type" = "crumbs_weights_expansible".
 *
 * @param array &$vars
 * @return string
 *   Rendered HTML
 */
function theme_crumbs_weights_expansible(&$vars) {

  $element = $vars['element'];

  $rows = array();
  foreach (element_children($element) as $key) {
    $cells = array();
    $cells[] = $key;
    $cells[] = render($element[$key]);

    /** @var crumbs_Container_MultiWildcardDataOffset $meta */
    $meta = $element[$key]['#crumbs_rule_info'];

    $methods = array();
    $routes = array();
    if (is_array($meta->routeMethods)) {
      foreach ($meta->routeMethods as $method => $method_routes) {
        foreach ($method_routes as $route => $method_with_suffix) {
          $methods[] = $method . '()';
          $routes[] = $route;
        }
      }
    }
    if (is_array($meta->basicMethods)) {
      foreach ($meta->basicMethods as $method) {
        $methods[] = $method . '()';
        $routes[] = '-';
      }
    }

    $cells[] = '<code class="crumbs-admin-meta">' . implode('<br/>', $methods) . '</code>';
    $cells[] = '<code class="crumbs-admin-meta">' . implode('<br/>', $routes) . '</code>';

    if ($descriptions = $meta->descriptions) {
      $cells[] = '<div class="crumbs-admin-meta">' . implode('<br/>', $descriptions) . '</div>';
    }
    else {
      $cells[] = '';
    }

    $rows[] = $cells;
  }

  return theme('table', array(
    'rows' => $rows,
    'attributes' => array('id' => 'crumbs_weights_expansible'),
  ));
}
