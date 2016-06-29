<?php
/**
 * @file
 * govcms_consultation.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function govcms_consultation_taxonomy_default_vocabularies() {
  return array(
    'update_type' => array(
      'name' => 'Update type',
      'machine_name' => 'update_type',
      'description' => 'Types of updates for Milestones/Updates attached to a consultation',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
