<?php

/**
 * @file
 * Metatag integration for the agls module.
 *
 * This implements alot of code that will make it into core metatag
 * module at a later date.
 *
 * http://drupal.org/node/1491616
 *
 * So for now we will support.
 *
 */

/**
 * Implements hook_metatag_config_default_alter().
 */
function agls_metatag_config_default_alter(array &$configs) {
  foreach ($configs as &$config) {
    switch ($config->instance) {
      case 'global':
        $config->config += array(
          'DCTERMS.title' => array('value' => '[current-page:title]'),
          'DCTERMS.type' => array('value' => 'Text'),
          'DCTERMS.format' => array('value' => 'text/html'),
        );
        break;

      case 'global:frontpage':
        $config->config += array(
          'DCTERMS.title' => array('value' => '[site:name]'),
          'DCTERMS.identifier' => array('value' => '[site:url]'),
        );
        break;

      case 'node':
        $config->config += array(
          'DCTERMS.title' => array('value' => '[node:title]'),
          'DCTERMS.description' => array('value' => '[node:summary]'),
          'DCTERMS.date' => array('value' => '[node:created:custom:Y-m-d\TH:iP]'),
          'DCTERMS.identifier' => array('value' => '[site:url]node/[node:nid]'),
          'DCTERMS.language' => array('value' => '[node:language]'),
          'DCTERMS.creator' => array('value' => '[node:author]'),
          'DCTERMS.type' => array('value' => 'Text'),
        );
        break;

      case 'taxonomy_term':
        $config->config += array(
          'DCTERMS.title' => array('value' => '[term:name]'),
          'DCTERMS.identifier' => array('value' => '[site:url]taxonomy/term/[term:tid]'),
          'DCTERMS.description' => array('value' => '[term:description]'),
        );
        break;

      case 'user':
        $config->config += array(
          'DCTERMS.title' => array('value' => '[user:name]'),
          'DCTERMS.date' => array('value' => '[user:created:custom:Y-m-d\TH:iP]'),
          'DCTERMS.identifier' => array('value' => '[site:url]user/[user:uid]'),
          'DCTERMS.creator' => array('value' => '[user:name]'),
        );
        break;
    }
  }
}
 
/**
 * Implements hook_metatag_info().
 */
function agls_metatag_info() {
  // Define a AGLS group.
  $info['groups']['agls'] = array(
    'label' => t('AGLS'),
    'description' => t('Provides AGLS metadata.'),
    'form' => array(
      '#weight' => 95,
    ),
  );
  
  // AGLS specific terms.
  $info['tags']['aglsterms:availability'] = array(
    'label' => t('AGLS: Availability'),
    'description' => t('How the resource can be obtained or accessed, or contact information (Mandatory for offline resources).'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag',
    ),
  );
  $info['tags']['aglsterms:function'] = array(
    'label' => t('AGLS: Function'),
    'description' => t('The business function to which the resource relates (Recommended if dcterms:subject is not used). AGIFT is the recommended thesaurus for Australian government agencies.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag',
    ),
  );
  $info['tags']['aglsterms:mandate'] = array(
    'label' => t('AGLS: Mandate'),
    'description' => t('A specific legal instrument which requires or drives the creation or provision of the resource (Optional).'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag',
    ),
  );

  // Dublin core tags. Remove these once they are in the base metatag module.
  // But then maybe add an alter to add the obligation to the descriptions.
    $info['tags']['DCTERMS.title'] = array(
    'label' => t('Dublin Core Title'),
    'description' => t('The name given to the resource.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.creator'] = array(
    'label' => t('Dublin Core Creator'),
    'description' => t('An entity primarily responsible for making the resource. Examples of a Creator include a person, an organization, or a service. Typically, the name of a Creator should be used to indicate the entity.'),
    'group' => 'agls',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.subject'] = array(
    'label' => t('Dublin Core Subject'),
    'description' => t('The topic of the resource. Typically, the subject will be represented using keywords, key phrases, or classification codes. Recommended best practice is to use a controlled vocabulary. To describe the spatial or temporal topic of the resource, use the Coverage element.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.description'] = array(
    'label' => t('Dublin Core Description'),
    'description' => t('An account of the resource. Description may include but is not limited to: an abstract, a table of contents, a graphical representation, or a free-text account of the resource.'),
    'group' => 'agls',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.publisher'] = array(
    'label' => t('Dublin Core Publisher'),
    'description' => t('An entity responsible for making the resource available. Examples of a Publisher include a person, an organization, or a service. Typically, the name of a Publisher should be used to indicate the entity.'),
    'group' => 'agls',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.contributor'] = array(
    'label' => t('Dublin Core Contributor'),
    'description' => t('An entity responsible for making contributions to the resource. Examples of a Contributor include a person, an organization, or a service. Typically, the name of a Contributor should be used to indicate the entity.'),
    'group' => 'agls',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.date'] = array(
    'label' => t('Dublin Core Date'),
    'description' => t('A point or period of time associated with an event in the lifecycle of the resource. Date may be used to express temporal information at any level of granularity.  Recommended best practice is to use an encoding scheme, such as the W3CDTF profile of ISO 8601 [W3CDTF].'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag_agls',
      '#schema' => 'DCTERMS.W3CDTF',
    ),
  );
  $info['tags']['DCTERMS.type'] = array(
    'label' => t('Dublin Core Type'),
    'description' => t('The nature or genre of the resource. Recommended best practice is to use a controlled vocabulary such as the DCMI Type Vocabulary [DCMITYPE]. To describe the file format, physical medium, or dimensions of the resource, use the Format element.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'form' => array(
      '#type' => 'select',
      '#options' => _agls_dcmi_type_vocabulary_options(),
      '#empty_option' => t('- None -'),
    ),
    'element' => array(
      '#theme' => 'metatag_agls',
      '#schema' => 'DCTERMS.DCMIType',
    ),
  );
  $info['tags']['DCTERMS.format'] = array(
    'label' => t('Dublin Core Format'),
    'description' => t('The file format, physical medium, or dimensions of the resource. Examples of dimensions include size and duration. Recommended best practice is to use a controlled vocabulary such as the list of Internet Media Types [MIME].'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag_agls',
      '#schema' => 'DCTERMS.IMT',
    ),
  );
  $info['tags']['DCTERMS.identifier'] = array(
    'label' => t('Dublin Core Identifier'),
    'description' => t('An unambiguous reference to the resource within a given context. Recommended best practice is to identify the resource by means of a string conforming to a formal identification system.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.source'] = array(
    'label' => t('Dublin Core Source'),
    'description' => t('A related resource from which the described resource is derived. The described resource may be derived from the related resource in whole or in part. Recommended best practice is to identify the related resource by means of a string conforming to a formal identification system.'),
    'group' => 'agls',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.language'] = array(
    'label' => t('Dublin Core Language'),
    'description' => t('A language of the resource. Recommended best practice is to use a controlled vocabulary such as RFC 4646 [RFC4646].'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'agls',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.relation'] = array(
    'label' => t('Dublin Core Relation'),
    'description' => t('A related resource. Recommended best practice is to identify the related resource by means of a string conforming to a formal identification system.'),
    'group' => 'agls',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.coverage'] = array(
    'label' => t('Dublin Core Coverage'),
    'description' => t('The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant. Spatial topic and spatial applicability may be a named place or a location specified by its geographic coordinates. Temporal topic may be a named period, date, or date range. A jurisdiction may be a named administrative entity or a geographic place to which the resource applies. Recommended best practice is to use a controlled vocabulary such as the Thesaurus of Geographic Names [TGN]. Where appropriate, named places or time periods can be used in preference to numeric identifiers such as sets of coordinates or date ranges.'),
    'group' => 'agls',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  $info['tags']['DCTERMS.rights'] = array(
    'label' => t('Dublin Core Rights'),
    'description' => t('Information about rights held in and over the resource. Typically, rights information includes a statement about various property rights associated with the resource, including intellectual property rights.'),
    'group' => 'agls',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#theme' => 'metatag_agls',
    ),
  );
  // End dublin core tags.

  return $info;
}

/**
 * Function that returns the DCMI type options.
 * Types taken from http://dublincore.org/documents/dcmi-type-vocabulary/.
 */
function _agls_dcmi_type_vocabulary_options() {
  $options = array(
    'Collection',
    'Dataset',
    'Event',
    'Image',
    'InteractiveResource',
    'MovingImage',
    'PhysicalObject',
    'Service',
    'Software',
    'Sound',
    'StillImage',
    'Text',
  );
  return drupal_map_assoc($options);
}
