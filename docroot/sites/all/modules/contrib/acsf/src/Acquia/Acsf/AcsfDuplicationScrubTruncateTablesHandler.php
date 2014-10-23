<?php

/**
 * @file
 * Contains AcsfDuplicationScrubTruncateTablesHandler.
 */

namespace Acquia\Acsf;

/**
 * Truncates various undesirable Drupal core tables.
 */
class AcsfDuplicationScrubTruncateTablesHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    drush_print(dt('Entered @class', array('@class' => get_class($this))));

    $tables = array();

    // Invalidate search indexes. If the search module has never been enabled,
    // then it's not enabled now and this block is skipped.
    if (module_exists('search')) {
      // Call this function to ensure that the necessary search hooks get
      // called.
      search_reindex();

      // Calling search_reindex globally (with no parameters) invokes hooks, but
      // does not truncate the following tables:
      $tables[] = 'search_dataset';
      $tables[] = 'search_index';
      $tables[] = 'search_node_links';
      $tables[] = 'search_total';
    }

    $tables[] = 'accesslog';
    $tables[] = 'node_counter';
    $tables[] = 'batch';
    $tables[] = 'queue';
    $tables[] = 'semaphore';
    $tables[] = 'sessions';
    $tables[] = 'themebuilder_session';

    $this->truncateTables($tables);
  }

  /**
   * Truncates database tables.
   *
   * @param array $tables
   *   The list of tables to be truncated.
   */
  public function truncateTables(array $tables = array()) {
    foreach ($tables as $table) {
      if (db_table_exists($table)) {
        db_delete($table)->execute();
      }
    }
  }

}
