<?php
/**
 * @file
 * govcms_consultation.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function govcms_consultation_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Comment count',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => '140c20d0-4704-4090-bb76-e0ebcb1d4d13',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_comment.png',
          'uri' => 'public://update_comment.png',
          'filemime' => 'image/png',
          'filesize' => 21170,
          'status' => 1,
          'type' => 'image',
          'uuid' => '3ddc2360-f9de-4270-8b3e-b914efef27f5',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 300,
            'width' => 300,
          ),
          'alt' => '',
          'title' => '',
          'height' => 300,
          'width' => 300,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_comment.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Documentation update',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => '1cc6a78d-a829-4bf4-8eb1-d3ad9d4e6854',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_update.png',
          'uri' => 'public://update_update_0.png',
          'filemime' => 'image/png',
          'filesize' => 5061,
          'status' => 1,
          'type' => 'image',
          'uuid' => 'b84a1f0d-39c8-43ff-9e16-a6d2e3c7322a',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 300,
            'width' => 255,
          ),
          'alt' => '',
          'title' => '',
          'height' => 300,
          'width' => 255,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_update_0.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Number of formal submissions',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => '2123a700-48d8-4b20-aacd-4b3dd8dca832',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_formal.png',
          'uri' => 'public://update_formal.png',
          'filemime' => 'image/png',
          'filesize' => 4222,
          'status' => 1,
          'type' => 'image',
          'uuid' => '99d24fc4-7785-43e5-b16d-a4ff7a8c2e92',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 300,
            'width' => 249,
          ),
          'alt' => '',
          'title' => '',
          'height' => 300,
          'width' => 249,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_formal.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Consultation update',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => '240e290c-c114-4eea-a4fe-7f2450bc9f72',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_update.png',
          'uri' => 'public://update_update.png',
          'filemime' => 'image/png',
          'filesize' => 5061,
          'status' => 1,
          'type' => 'image',
          'uuid' => 'a4ddc003-524c-40a5-bf3c-fe0500f34a2f',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 300,
            'width' => 255,
          ),
          'alt' => '',
          'title' => '',
          'height' => 300,
          'width' => 255,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_update.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Consultation ended',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => '4671e734-7b59-48c1-9377-7529ddef62df',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_end_consultation.png',
          'uri' => 'public://update_end_consultation.png',
          'filemime' => 'image/png',
          'filesize' => 23891,
          'status' => 1,
          'type' => 'image',
          'uuid' => '99a3dc67-2df1-4b89-bcf2-b1f770c69e3d',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 300,
            'width' => 273,
          ),
          'alt' => '',
          'title' => '',
          'height' => 300,
          'width' => 273,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_end_consultation.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Number of social shares',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => '48f6a5e0-0fc4-4034-913d-55e5e2304732',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_social.png',
          'uri' => 'public://update_social.png',
          'filemime' => 'image/png',
          'filesize' => 23172,
          'status' => 1,
          'type' => 'image',
          'uuid' => 'e8b00427-5cfe-4b59-a88d-634bb0661029',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 300,
            'width' => 300,
          ),
          'alt' => '',
          'title' => '',
          'height' => 300,
          'width' => 300,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_social.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Number of consultation views',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => '8805e943-d5a4-4c01-91bb-2db6c8448e07',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_views.png',
          'uri' => 'public://update_views.png',
          'filemime' => 'image/png',
          'filesize' => 21443,
          'status' => 1,
          'type' => 'image',
          'uuid' => '9206bfc3-e164-4500-91c6-4cfefa611580',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 162,
            'width' => 300,
          ),
          'alt' => '',
          'title' => '',
          'height' => 162,
          'width' => 300,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_views.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Consultation started',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => 'a314c8c8-f58c-4d44-ab6e-14d8f04b853f',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_consultation.png',
          'uri' => 'public://update_consultation.png',
          'filemime' => 'image/png',
          'filesize' => 15946,
          'status' => 1,
          'type' => 'image',
          'uuid' => '7518f6d9-54d0-4420-896c-ea29cc71becb',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 300,
            'width' => 195,
          ),
          'alt' => '',
          'title' => '',
          'height' => 300,
          'width' => 195,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_consultation.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  $terms[] = array(
    'name' => 'Poll result',
    'description' => '',
    'format' => 'rich_text',
    'weight' => 0,
    'uuid' => 'ee957486-df0a-4128-a2d9-f34440da6ec2',
    'vocabulary_machine_name' => 'update_type',
    'field_pbundle_image' => array(
      'und' => array(
        0 => array(
          'uid' => 1,
          'filename' => 'update_poll.png',
          'uri' => 'public://update_poll.png',
          'filemime' => 'image/png',
          'filesize' => 19519,
          'status' => 1,
          'type' => 'image',
          'uuid' => '52caf652-5561-4e77-8e69-0c9df2f38714',
          'field_file_image_alt_text' => array(),
          'field_file_image_title_text' => array(),
          'metatags' => array(),
          'rdf_mapping' => array(),
          'metadata' => array(
            'height' => 300,
            'width' => 300,
          ),
          'alt' => '',
          'title' => '',
          'height' => 300,
          'width' => 300,
          'uuid_features_file_path' => 'profiles/govcms/modules/features/govcms_consultation/assets/update_poll.png',
        ),
      ),
    ),
    'metatags' => array(
      'und' => array(
        'AGLSTERMS.act' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.aggregationLevel' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.availability' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.case' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.category' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.dateLicenced' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.documentType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.function' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasisFor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.isBasedOn' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.jurisdiction' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.mandate' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.protectiveMarking' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.regulation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'AGLSTERMS.serviceType' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'robots' => array(
          'value' => array(
            'index' => 0,
            'follow' => 0,
            'noindex' => 0,
            'nofollow' => 0,
            'noarchive' => 0,
            'nosnippet' => 0,
            'noodp' => 0,
            'noydir' => 0,
            'noimageindex' => 0,
            'notranslate' => 0,
          ),
        ),
        'dcterms.title' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.creator' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.subject' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.description' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.publisher' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.contributor' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.date' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.modified' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.type' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.format' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.identifier' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.source' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.language' => array(
          'item' => array(
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.relation' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.coverage' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
        'dcterms.rights' => array(
          'item' => array(
            'value' => '',
            'scheme' => '',
            'lang' => '',
            'dir' => 0,
          ),
        ),
      ),
    ),
    'path' => array(
      'pathauto' => 1,
    ),
  );
  return $terms;
}
