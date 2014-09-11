<?php
/**
 * @file
 * Define Linkit node search plugin class.
 */

/**
 * Reprecents a Linkit node search plugin.
 */
class LinkitSearchPluginNode extends LinkitSearchPluginEntity {

  /**
   * Overrides LinkitSearchPluginEntity::createRowClass().
   *
   * Adds an extra class if the node is unpublished.
   */
  function createRowClass($entity) {
    if ($this->conf['include_unpublished'] && $entity->status == NODE_NOT_PUBLISHED) {
      return 'unpublished-node';
    }
  }

  /**
   * Overrides LinkitSearchPluginEntity::getQueryInstance().
   */
  function getQueryInstance() {
    // Call the parent getQueryInstance method.
    parent::getQueryInstance();
    // If we don't want to include unpublished nodes, add a condition on status.
    if ($this->conf['include_unpublished'] == 0) {
      $this->query->propertyCondition('status', NODE_PUBLISHED);
    }
  }

  /**
   * Overrides LinkitSearchPlugin::buildSettingsForm().
   */
  function buildSettingsForm() {
    // Get the parent settings form.
    $form = parent::buildSettingsForm();

    $form[$this->plugin['name']]['include_unpublished'] = array(
      '#title' => t('Include unpublished nodes'),
      '#type' => 'checkbox',
      '#default_value' => isset($this->conf['include_unpublished']) ? $this->conf['include_unpublished'] : 0,
      '#description' => t('In order to see unpublished nodes, the user most also have permissions to do so. '),
    );

    return $form;
  }
}