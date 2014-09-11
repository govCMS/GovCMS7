<?php

/**
 * @file
 * Metatag support for Migrate.
 */

/**
 * Basic usage of the Migrate integration.
 *
 * This example assumes the custom module's name is "example_migrate".
 * 
 * example_migrate.inc:
 * 
 * class MetatagTestMigration extends DynamicMigration {
 * 
 *   public function __construct() {
 *     parent::__construct();
 * 
 *     $this->description = t('Migrate test.');
 * 
 *     $this->map = new MigrateSQLMap(
 *       $this->machineName,
 *       array(
 *         'id' => array(
 *           'type' => 'varchar',
 *           'not null' => TRUE,
 *           'length' => 254,
 *           'description' => 'ID of record.',
 *         ),
 *       ),
 *       MigrateDestinationNode::getKeySchema()
 *     );
 * 
 *     $this->source = new MigrateSourceCSV(
 *       drupal_get_path('module', 'example_migrate') . '/sample.csv',
 *       array(),
 *       array('header_rows' => TRUE)
 *     );
 * 
 *     $this->destination = new MigrateDestinationNode('article');
 * 
 *     $this->addFieldMapping('metatag_description', 'description');
 *     $this->addFieldMapping('metatag_keywords', 'keywords');
 *   }
 * }
 * 
 * example_migrate.migrate.inc:
 * 
 * /**
 *  * Implements hook_migrate_api().
 *  * /
 * function example_migrate_migrate_api() {
 *   $api = array(
 *     'api' => 2,
 *     'migrations' => array(
 *       'MetatagTest' => array('class_name' => 'MetatagTestMigration'),
 *     ),
 *   );
 * 
 *   return $api;
 * }
 */

/**
 * Implements hook_migrate_api().
 */
function metatag_migrate_api() {
  $api = array(
    'api' => 2,
    'destination handlers' => array(
      'MigrateMetatagHandler',
    ),
  );

  return $api;
}

/**
 * Metatag destination handler.
 */
class MigrateMetatagHandler extends MigrateDestinationHandler {

  public function __construct() {
    $types = array();
    foreach (entity_get_info() as $entity_type => $entity_info) {
      if (isset($entity_info['metatags']) && $entity_info['metatags']) {
        $types[] = $entity_type;
      }
    }

    $this->registerTypes($types);
  }

  /**
   * Implements MigrateDestinationHandler::fields().
   */
  public function fields() {
    $fields = array();
    $elements = metatag_get_info();

    foreach ($elements['tags'] as $value) {
      $metatag_field = 'metatag_' . $value['name'];
      $fields[$metatag_field] = $value['description'];
    }

    return $fields;
  }

  /**
   * Implements MigrateDestinationHandler::prepare().
   */
  public function prepare($entity, stdClass $row) {
    $elements = metatag_get_info();

    foreach ($elements['tags'] as $value) {
      $metatag_field = 'metatag_' . $value['name'];
      if (isset($entity->$metatag_field)) {
        $entity->metatags[$value['name']]['value'] = $entity->$metatag_field;
        unset($entity->$metatag_field);
      }
    }
  }
}
