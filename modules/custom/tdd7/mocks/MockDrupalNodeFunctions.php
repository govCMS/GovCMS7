<?php
/**
 * @file
 * @author Edward Murrell <edward@catalyst-au.net>
 * Mocked up Drupal node functions.
 */

namespace tdd7\testframework\mocks {
  class MockDrupalNodeFunctions {
    /**
     * List of nodes, indexed by Node ID.
     * @var array
     */
    private static $nodes = array();

    /**
     * Return a mock node object.
     *
     * @param int $nid
     *   The node ID to load.
     * @param int $vid
     *   The revision ID. NOT YET IMPLMENTED IN MOCK.
     * @param bool $reset
     *   Whether to reset the node_load_multiple cache. IGNORED IN MOCK.
     *
     * @return mixed
     *   A fully-populated node object, or FALSE if the node is not found.
     */
    public static function node_load($nid = NULL, $vid = NULL, $reset = FALSE) {
      if (array_key_exists($nid, self::$nodes)) {
        return self::$nodes[$nid];
      }
      return FALSE;
    }

    /**
     * Loads multiple mock nodes.
     *
     * @param array $nids
     *   An anonymous array of node IDs.
     * @param array $conditions
     *   NOT IMPLEMENTED IN MOCK.
     * @param bool $reset
     *   NOT IMPLEMENTED IN MOCK
     *
     * @return array
     *   An array of node objects indexed by nid.
     */
    public static function node_load_multiple(array $nids = array(), $conditions = array(), $reset = FALSE) {
      $result = array();
      foreach ($nids as $nid) {
        $node = self::node_load($nid);
        if ($node != FALSE) {
          $result[$nid] = $node;
        }
      }
      return $result;
    }

    /**
     * Add basic node to fake node list with field as parameters.
     *
     * @param int $nid
     *   Node ID of this node.
     * @param string $type
     *   Node type of this node. eg; "page".
     * @param string $title
     *   Optional title of node.
     * @param string $language
     *   Optional node setting of language, defaults to LANGUAGE_NONE.
     */
    public static function AddMockNode($nid, $type, $title = '', $language = LANGUAGE_NONE) {
      $node = new \stdClass();
      $node->nid = $nid;
      $node->type = $type;
      $node->title = $title;
      $node->language = $language;
      self::$nodes[$nid] = $node;
    }

    /**
     * Add an attribute value to the node.
     *
     * This can be any of the columns from the the node table, except nid or
     * language. The mock node must have already been added via AddMockNode().
     *
     * @param int $nid
     *   The nid of an existing mock node.
     * @param string $attribute
     *   The attribute to set the value on. This may be one of: type, title,
     *   uid, status, created, changed, comment, promote, sticky, tnid, or
     *   translate.
     * @param string|int $value
     *   The value to set the attribute to. Existing values will be overwritten.
     */
    public static function AddNodeAttribute($nid, $attribute, $value) {
      $valid_attrs = array('type', 'title', 'uid', 'status', 'created',
        'changed', 'comment', 'promote', 'sticky', 'tnid', 'translate');
      if (!array_key_exists($nid, self::$nodes)) {
        throw new \Exception('Mock node does not exist.');
      }
      if (!in_array($attribute, $valid_attrs)) {
        throw new \Exception('Attribute name is invalid.');
      }
      self::$nodes[$nid]->$attribute = $value;
    }

    /**
     * Add field data to the node.
     *
     * The nodes language attribute will be used in the result field array, and
     * the field will be created if it does not exist.
     *
     * @param int $nid
     *   The nid of the node to add. An exception will be raised if this does
     *   not exist.
     * @param string $field
     *   The field name. eg; field_first_name
     * @param array $value
     *   The value to be set for this field. This is an array, often with a one
     *   key that points to the target value. ie; array('target_id' => 55);
     * @param int $delta
     *   The delta to update. If set to null, the data will be added to the end
     *   of the values array.
     * @param string $language
     *   The language to set this field to. If set to null, the default language
     *   for this node will be used.
     */
    public static function AddNodeField($nid, $field, array $value, $delta = NULL, $language = NULL) {
      if (!array_key_exists($nid, self::$nodes)) {
        throw new \Exception('Mock node does not exist.');
      }
      $node = self::$nodes[$nid];

      // Use the node language if no language defined in arguements.
      if ($language === NULL) {
        $lang = $node->language;
      } else {
        $lang = $language;
      }

      if (!property_exists(self::$nodes[$nid], $field)) {
        $node->$field = array($lang => array());
      }

      $fielddata = $node->$field;
      if ($delta === NULL) {
        $fielddata[$lang][] = $value;
      }
      else {
        $fielddata[$lang][$delta] = $value;
      }
      $node->$field = $fielddata;

      self::$nodes[$nid] = $node;
    }

    /**
     * Delete all saved mock data.
     */
    public static function ResetMockData() {
      self::$nodes = array();
    }
  }
}
