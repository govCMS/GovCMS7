<?php


/**
 * A hook to register crumbs plugins.
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 *   An object with methods to register plugins.
 *   See the class definition of crumbs_InjectedAPI_hookCrumbsPlugins, which
 *   methods are available.
 */
function hook_crumbs_plugins($api) {
  $api->monoPlugin('something');
  $api->multiPlugin('somethingElse');
}


// ===================================== pseudo-interfaces =====================


/**
 * Pseudo-interface for plugin objects registered with hook_crumbs_plugins().
 * The methods defined here are all optional. We only use this interface for
 * documentation, no class actually implements it.
 */
interface crumbs_MonoPlugin_example extends crumbs_MonoPlugin {

  /**
   * @param string $path
   *   System path that we want to find a parent for.
   * @param array $item
   *   Router item, as returned by menu_get_item(), but with a few convenience
   *   additions added in crumbs_get_router_item().
   *
   * @return string
   *   The parent path suggested by this plugin.
   */
  function findParent($path, $item);

  /**
   * Same signature as findParent()
   * Only called for router path node/%
   *
   * @param string $path
   *   System path that we want to find a parent for.
   * @param array $item
   *   Router item, as returned by menu_get_item(), but with a few convenience
   *   additions added in crumbs_get_router_item().
   *
   * @return string
   *   The parent path suggested by this plugin.
   */
  function findParent__node_x($path, $item);

  /**
   * @param string $path
   *   System path of the breadcrumb item that we want to find a link text for.
   * @param array $item
   *   Router item, as returned by menu_get_item(), but with a few convenience
   *   additions added in crumbs_get_router_item().
   *
   * @return string
   *   A string link text.
   */
  function findTitle($path, $item);

  /**
   * Same signature as findTitle()
   * Only called for router path node/%
   *
   * @param string $path
   *   System path of the breadcrumb item that we want to find a link text for.
   * @param array $item
   *   Router item, as returned by menu_get_item(), but with a few convenience
   *   additions added in crumbs_get_router_item().
   *
   * @return string
   *   A string link text.
   */
  function findTitle__node_x($path, $item);

}


// -----------------------------------------------------------------------------


/**
 * Pseudo-interface for plugin objects registered with hook_crumbs_plugins().
 * The methods defined here are all optional. We only use this interface for
 * documentation, no class actually implements it.
 */
interface crumbs_MultiPlugin_example extends crumbs_MultiPlugin {

  /**
   * @param string $path
   *   System path that we want to find a parent for.
   * @param array $item
   *   Router item, as returned by menu_get_item(), but with a few convenience
   *   additions added in crumbs_get_router_item().
   *
   * @return string[]
   *   A key-value array, where the keys identify crumbs rules, and the values
   *   are candidates for the parent path.
   *   Rule keys are relative to the plugin key.
   */
  function findParent($path, $item);

  /**
   * Same signature as findParent()
   * Only called for router path node/%
   *
   * @param string $path
   * @param array $item
   *
   * @return string[]
   */
  function findParent__node_x($path, $item);

  /**
   * @param string $path
   *   System path of the breadcrumb item that we want to find a link text for.
   * @param array $item
   *   Router item, as returned by menu_get_item(), but with a few convenience
   *   additions added in crumbs_get_router_item().
   *
   * @return string[]
   *   A key-value array, where the keys identify crumbs rules, and the values
   *   are candidates for the link title.
   *   Rule keys are relative to the plugin key.
   */
  function findTitle($path, $item);

  /**
   * Same signature as findParent()
   * Only called for router path node/%
   *
   * @param $path
   *   System path of the breadcrumb item that we want to find a link text for.
   * @param $item
   *   Router item, as returned by menu_get_item(), but with a few convenience
   *   additions added in crumbs_get_router_item().
   *
   * @return string[]
   *   A key-value array, where the keys identify crumbs rules, and the values
   *   are candidates for the link title.
   *   Rule keys are relative to the plugin key.
   */
  function findTitle__node_x($path, $item);

}
