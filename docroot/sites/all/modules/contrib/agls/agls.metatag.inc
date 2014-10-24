<?php

/**
 * @file
 * Metatag integration for the agls module.
 *
 * @copyright Copyright(c) 2013 Previous Next Pty Ltd
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Kim Pepper kim at previousnext dot com dot au
 * @author Nick Schuch nick at previousnext dot com dot au
 * @author Chris Skene chris at previousnext dot com dot au
 */

/**
 * Implements hook_metatag_config_default_alter().
 *
 * AGLS guidelines recommend several WCAG-relevant tag settings for both
 * DublinCore and AGLS. This function implements those settings on behalf
 * of the metatag_dc module.
 */
function agls_metatag_config_default_alter(array &$configs) {

  foreach ($configs as &$config) {
    switch ($config->instance) {
      case 'node':
        $config->config += array(
          'dcterms.description' => array('item' => array('value' => '[node:summary]')),
          'dcterms.type' => array('item' => array('value' => 'Text')),
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
    'description' => t('The AGLS Metadata Standard provides a set of metadata
     properties and associated usage guidelines to improve the visibility,
     manageability and interoperability of online information and services.'),
    'form' => array(
      '#weight' => 95,
    ),
  );

  // AGLS specific terms.
  $info['tags']['AGLSTERMS.act'] = array(
    'label' => t('AGLS: Act'),
    'description' => t('A specific piece of legislation which requires or drives
     the creation or provision of the resource.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.aggregationLevel'] = array(
    'label' => t('AGLS: Aggregation Level'),
    'description' => t('The level of aggregation of the described resource.
     There are only two valid values for this property—‘item’ or ‘collection’.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
    'form' => array(
      'value' => array(
        '#type' => 'select',
        '#options' => array('item', 'collection'),
        '#empty_option' => t('- None -'),
      ),
    ),
  );
  $info['tags']['AGLSTERMS.availability'] = array(
    'label' => t('AGLS: Availability'),
    'description' => t('How the resource can be obtained or accessed, or contact
     information. The availability property is primarily used for offline
     resources to provide information on how to obtain physical access to the
     resource. <em>Mandatory for offline resources</em>.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
    'form' => array(
      'scheme' => array(
        '#description' => t('Possible values are AglsAgent, GOLD, or URI.'),
      ),
    ),
  );
  $info['tags']['AGLSTERMS.case'] = array(
    'label' => t('AGLS: Case'),
    'description' => t('A specific piece of case law which requires or drives the creation or
     provision of the resource .'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.category'] = array(
    'label' => t('AGLS: Category'),
    'description' => t('The generic type of the resource being described. There
     are only three valid values for this property—‘service’, ‘document’ or
    ‘agency’'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.dateLicenced'] = array(
    'label' => t('AGLS: Date licenced'),
    'description' => t('Date a license was applied or became effective.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.documentType'] = array(
    'label' => t('AGLS: Document type'),
    'description' => t('The form of the described resource where the value of
     category is ‘document’. Document is used in its widest sense and includes
     resources such as text, images, sound files and software .'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.function'] = array(
    'label' => t('AGLS: Function'),
    'description' => t('The business function to which the resource relates
     (Recommended if dcterms:subject is not used). AGIFT is the recommended
     thesaurus for Australian government agencies.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.isBasisFor'] = array(
    'label' => t('AGLS: Is Basis For'),
    'description' => t('A related resource that is a performance, production,
    derivation, translation or interpretation of the described resource.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.isBasedOn'] = array(
    'label' => t('AGLS: Is Based On'),
    'description' => t('A related resource of which the described resource is a
    performance, production, derivation, translation or interpretation.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.jurisdiction'] = array(
    'label' => t('AGLS: Jurisdiction'),
    'description' => t('The name of the political/administrative entity covered
    by the described resource.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.mandate'] = array(
    'label' => t('AGLS: Mandate'),
    'description' => t('A specific legal instrument which requires or drives the
     creation or provision of the resource. The property is useful to indicate
     the specific legal instrument which requires the resource being described to
     be created or provided. The value of this property may a text string
     describing a specific Act, Regulation or Case, or a URI pointing to the
     legal instrument in question'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.protectiveMarking'] = array(
    'label' => t('AGLS: Protective Marking'),
    'description' => t('A protective marking applied to the described resource.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.regulation'] = array(
    'label' => t('AGLS: Regulation'),
    'description' => t('A specific regulation which requires or drives the
     creation or provision of the resource.'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );
  $info['tags']['AGLSTERMS.serviceType'] = array(
    'label' => t('AGLS: ServiceType'),
    'description' => t('The form of the described resource where the value of category is "service".'),
    'class' => 'DrupalExtendedMetaTag',
    'group' => 'agls',
  );

  return $info;
}
