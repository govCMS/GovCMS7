<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

/**
 * Extend the defaults.
 */
class BeanMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['label'] = array(
      'label' => t('Label'),
      'description' => t('The bean label'),
      'getter callback' => 'entity_property_getter_method',
      'setter callback' => 'entity_property_verbatim_set',
      'schema field' => 'label',
    );

    $properties['title'] = array(
      'label' => t('Title'),
      'description' => t('The bean title'),
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'schema field' => 'title',
    );

    $properties['view_mode'] = array(
      'label' => t('View Mode'),
      'description' => t('View mode of the bean'),
      'getter callback' => 'entity_property_verbatim_get',
      'schema field' => 'view_mode',
      'required' => TRUE,
    );

    $properties['delta'] = array(
      'getter callback' => 'entity_property_verbatim_get',
      'description' => t('The delta of the block'),
      'label' => t('Block Delta'),
      'required' => TRUE,
      'schema field' => 'delta',
    );

    $properties['type'] = array(
      'type' => 'bean_type',
      'getter callback' => 'entity_property_verbatim_get',
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer beans',
      'required' => TRUE,
      'description' => t('The bean type.'),
    ) + $properties['type'];

    return $info;
  }
}
