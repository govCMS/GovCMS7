<?php
/**
 * @file
 * Mocked up Drupal core field functions
 * @author Glen Ji <glen.ji@open.edu.au>
 *
 * @todo: Review. This does not implement good patterns. It needs Add/Reset
 *  methods, and may be completely pointless.
 */

namespace tdd7\testframework\mocks {
  class MockDrupalFieldFunctions {
    /**
     * Array of entity types.
     *
     * @var array Entity types
     */
    public static $entity_types = array();

    /**
     * Mock function for field_get_items.
     *
     * @param string $entity_type
     *   Entity type
     * @param object $entity
     *   Entity object
     * @param string $field_name
     *   Field name
     * @param string $langcode
     *   Language code
     *
     * @return array
     *   Array of field items
     */
    public static function field_get_items($entity_type, $entity, $field_name, $langcode = NULL) {
      $items = FALSE;
      if (in_array($entity_type, self::$entity_types)) {
        if (property_exists($entity, $field_name)) {
          $langcode = is_null($langcode) ? 'und' : $langcode;
          $items = $entity->{$field_name}[$langcode];
        }
      }
      return $items;
    }
  }
}
