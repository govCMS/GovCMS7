<?php

/**
 * Interface for plugin objects registered with hook_crumbs_plugins().
 */
interface crumbs_MonoPlugin extends crumbs_PluginInterface {

  /**
   * @param crumbs_InjectedAPI_describeMonoPlugin $api
   *   Injected API object, with methods that allows the plugin to further
   *   describe itself.
   *
   * @return string|void
   *   As an alternative to the API object's methods, the plugin can simply
   *   return a string label.
   */
  function describe($api);
}
