<?php
/**
 * @file
 * This files contains what would be namespaced production code. We use it here
 * to demonstrate the use of the DrupalNodeMock class.
 */

/**
 * This defines that all code in this file will be in the namespace
 *  tdd7\example. The namespace decleration must be the first code in the file.
 */
namespace tdd7\example;

/**
 * Return the title of the node specified in $nid.
 *
 * @param int $nid
 *   The node ID to the title of.
 *
 * @return string
 *   The title of the node specified in $nid. If no such node exists, an empty
 *   string is returned.
 */
function get_node_title($nid) {
  $node = node_load($nid);
  if ($node === FALSE) {
    return '';
  }
  return $node->title;
}