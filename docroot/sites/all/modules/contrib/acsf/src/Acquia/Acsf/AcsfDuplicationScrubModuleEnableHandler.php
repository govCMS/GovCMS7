<?php

/**
 * @file
 * Contains AcsfDuplicationScrubModuleEnableHandler.
 */

namespace Acquia\Acsf;

/**
 * Enables modules necessary for the scrubbing process.
 */
class AcsfDuplicationScrubModuleEnableHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));

    // Enable any modules that are currently disabled, but were once enabled, so
    // that their data cleanup hooks (e.g. hook_user_delete) and functions
    // (e.g. search_reindex) can be invoked.
    //
    // Note: These modules will all be uninstalled. Uninstalling them should
    // really take care of all the cleanup these modules should be doing. But
    // enable them here for good measure just incase there's some cleanup
    // depending on these hooks.
    require_once DRUPAL_ROOT . '/includes/install.inc';
    $modules = system_rebuild_module_data();

    $enable_for_scrub = array();
    foreach ($modules as $module) {
      // Disabled modules with schema_version > -1 have not been uninstalled.
      if (empty($module->status) && $module->schema_version > SCHEMA_UNINSTALLED) {
        $enable_for_scrub[] = $module->name;
      }
    }

    // Get a list of disabled dependencies. These will get automatically enabled
    // during module_enable(), but we want to be able to disable and uninstall
    // them explicitly later.
    foreach ($enable_for_scrub as $dependent) {
      foreach (array_keys($modules[$dependent]->requires) as $dependency) {
        // Use isset() to make sure the module is still in the filesystem before
        // trying to enable it. (Historically there have been modules in Gardens
        // which were disabled but then removed from the codebase without ever
        // uninstalling them, and we don't want to try to enable those now,
        // because it will fail.)
        if (isset($modules[$dependency]) && empty($modules[$dependency]->status)) {
          $enable_for_scrub[] = $dependency;
        }
      }
    }

    module_enable($enable_for_scrub);
    acsf_vset('acsf_duplication_enable_for_scrub', $enable_for_scrub, 'acsf_duplication_scrub');
  }

}
