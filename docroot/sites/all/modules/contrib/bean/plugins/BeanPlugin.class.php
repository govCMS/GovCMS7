<?php

/**
 * @file
 * Base Plugin Class
 */

abstract class BeanPlugin implements BeanTypePluginInterface {
  protected $plugin_info;
  public $type;

  /**
   * Get Plugin info
   */
  public function getInfo($key = NULL) {
    if (!empty($key) && isset($this->plugin_info[$key])) {
      return $this->plugin_info[$key];
    }

    return $this->plugin_info;
  }

  /**
   * Build the URL string
   */
  public function buildURL() {
    return str_replace('_', '-', $this->type);
  }

  /**
   * Get the label
   */
  public function getLabel() {
    return $this->getInfo('label');
  }

  /**
   * Get the description
   */
  public function getDescription() {
    return $this->getInfo('description');
  }

  public function __construct($plugin_info) {
    $this->plugin_info = $plugin_info;
    $this->type = $plugin_info['name'];
  }

  /**
   * Define the form values and their defaults
   *
   * Be sure to call combine the results form the parent::values() with yours
   */
  public function values() {
    return array(
      'view_mode' => 'default',
    );
  }

  public function form($bean, $form, &$form_state) {
    return array();
  }

  /**
   * Add a Bean to the plugin
   */
  public function setBean($bean) {
    $this->bean = $bean;
  }

  /**
   * Is the bean type editable
   */
  public function isEditable() {
    return $this->getInfo('editable');
  }

  /**
   * THe plugin validation function
   */
  public function validate($values, &$form_state) {}

  /**
   * React to the saving of the bean
   */
  public function submit(Bean $bean) {
    return $this;
  }

  /**
   * Return the block content.
   *
   * @param $bean
   *   The bean object being viewed.
   * @param $content
   *   The default content array created by Entity API.  This will include any
   *   fields attached to the entity.
   * @param $view_mode
   *   The view mode passed into $entity->view().
   * @return
   *   Return a renderable content array.
   */
  public function view($bean, $content, $view_mode = 'default', $langcode = NULL) {
    return $content;
  }
}
