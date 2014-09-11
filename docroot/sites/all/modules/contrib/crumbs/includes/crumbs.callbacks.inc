<?php


// Menu system callbacks
// -----------------------------------------------------------------------------

/**
 * Page callback for 'crumbs/special-menu-item/%menu_link'
 *
 * @param array $menu_link
 */
function crumbs_special_menu_link_page(array $menu_link) {
  drupal_goto('<front>');
}

/**
 * Title callback for 'crumbs/special-menu-item/%menu_link'
 *
 * @param array $menu_link
 */
function crumbs_special_menu_link_title(array $menu_link) {
  return $menu_link['title'];
}


// Form element callbacks
// -----------------------------------------------------------------------------

/**
 * Value callback for tabledrag element ($element['#value_callback']).
 *
 * @param array $element
 * @param array|bool $input
 * @param array $form_state
 *
 * @throws Exception
 * @return array|bool
 */
function _crumbs_element_value_callback(&$element, $input = FALSE, $form_state = array()) {
  return _crumbs_element_object($element)->value_callback($element, $input, $form_state);
}

/**
 * Processor callback for tabledrag element ($element['#process']).
 * See form_process_checkboxes() for an example how these processors work.
 *
 * @param array $element
 * @param array $form_state
 *
 * @throws Exception
 * @return array
 */
function _crumbs_element_process($element, $form_state) {
  return _crumbs_element_object($element)->process($element, $form_state);
}

/**
 * After build callback for tabledrag element ($element['#after_build']).
 *
 * @param array $element
 * @param array $form_state
 *
 * @throws Exception
 * @return array
 */
function _crumbs_element_after_build($element, $form_state) {
  return _crumbs_element_object($element)->after_build($element, $form_state);
}

/**
 * Pre-render callback for tabledrag element ($element['#pre_render']).
 *
 * @param array $element
 *
 * @throws Exception
 * @return array
 */
function _crumbs_element_pre_render($element) {
  return _crumbs_element_object($element)->pre_render($element);
}

/**
 * Validation callback for tabledrag element ($element['#element_validate']).
 *
 * @param array $element
 * @param array $form_state
 *
 * @throws Exception
 */
function _crumbs_element_validate(&$element, &$form_state) {
  _crumbs_element_object($element)->validate($element, $form_state);
}

/**
 * Lazy-create an object representing the form element.
 * This allows to use methods instead of procedural callbacks.
 *
 * There will be one instance per element, so the object can actually hold some
 * state information.
 *
 * This mechanic would even make sense as a reusable module, but for now we just
 * have it crumbs-specific.
 *
 * @param array $element
 *
 * @throws Exception
 * @return crumbs_Admin_ElementObject_WeightsAbstract
 */
function _crumbs_element_object(&$element) {
  if (!isset($element['#crumbs_element_object'])) {
    switch ($element['#type']) {
      case 'crumbs_weights_tabledrag':
        $obj = new crumbs_Admin_ElementObject_WeightsTabledrag($element);
        break;
      case 'crumbs_weights_textual':
        $obj = new crumbs_Admin_ElementObject_WeightsTextual($element);
        break;
      case 'crumbs_weights_expansible':
        $obj = new crumbs_Admin_ElementObject_WeightsExpansible($element);
        break;
      default:
        throw new Exception('Unknown element type "' . $element['#type'] . '".');
    }
    $element['#crumbs_element_object'] = $obj;
  }
  return $element['#crumbs_element_object'];
}


// Other callbacks
// -----------------------------------------------------------------------------

/**
 * Callback for themekey integration.
 *
 * @param string $path
 *
 * @return array
 */
function _crumbs_themekey_path2trailpaths($path) {
  $trail = crumbs_get_trail($path);
  $paths = array();
  foreach ($trail as $k => $item) {
    $paths[$item['alias']] = TRUE;
    $paths[$item['route']] = TRUE;
    $paths[$k] = TRUE;
  }
  return array_keys($paths);
}

/**
 * Submit callback registered on crumbs admin forms in addition to the usual
 * system_settings_form stuff.
 */
function _crumbs_admin_flush_cache() {

  // This will only hit the 'cache_page' and 'cache_block' cache bins.
  cache_clear_all();

  // Clear plugin info in 'cache' cache bin.
  crumbs()->pluginInfo->flushCaches();
}

/**
 * Callback to be registered with ini_set('unserialize_callback_func', *)
 *
 * @param string $class
 * @throws crumbs_UnserializeException
 */
function _crumbs_unserialize_failure($class) {
  throw new crumbs_UnserializeException();
}
