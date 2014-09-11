<?php

/**
 * Interface for plugin objects registered with hook_crumbs_plugins().
 *
 */
interface crumbs_MultiPlugin extends crumbs_PluginInterface {

  /**
   * @param crumbs_InjectedAPI_describeMultiPlugin $api
   *   Injected API object, with methods that allow the plugin to further
   *   describe itself.
   *   The plugin is supposed to tell Crumbs about all possible rule keys, and
   *   can give a label and a description for each.
   *
   * @return
   *   As an alternative to the API object's methods, the plugin can simply
   *   return a key-value array, where the keys are the available rules, and the
   *   values are their respective labels.
   */
  function describe($api);
}
