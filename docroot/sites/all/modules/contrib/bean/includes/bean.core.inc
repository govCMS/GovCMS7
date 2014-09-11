<?php

/**
 * @file
 * Bean classes and plugin interface
 */

/**
 * Interface for Plugin Classes
 */
interface BeanTypePluginInterface {

  /**
   * Constructor
   *
   * Plugin info should be called using bean_fetch_plugin_info().
   *
   * @abstract
   *
   * @param  $plugin_info array of information from the ctools plugin.
   */
  public function __construct($plugin_info);

  /**
   * Get the ctools plugin info.
   *
   * If you pass in a key, then the key from the plugin info will be returned
   * otherwise the entire plugin will be returned
   *
   * @abstract
   *
   * @param  $key
   * @return array of plugin info for value froma key
   */
  public function getInfo($key = NULL);

  /**
   * Build the URL string for the plugin
   *
   * @abstract
   *
   * @return url
   */
  public function buildURL();

  /**
   * Get the label name of the plugin
   *
   * @abstract
   *
   * @return label of the type
   */
  public function getLabel();

  /**
   * Get the description of the plugin
   *
   * @abstract
   *
   * @return
   *  description of the type
   */
  public function getDescription();

  /**
   * Set the Bean object for later use
   *
   * @abstract
   *
   * @param Bean $bean
   */
  public function setBean($bean);

  /**
   * Is this type editable?
   *
   * @abstract
   *
   * @return boolean
   */
  public function isEditable();

  /**
   * Define the form values and their defaults
   */
  public function values();

  /**
   * The Plugin Form
   *
   * The Bean object will be either loaded from the database or filled with the defaults.
   *
   * @param $bean
   * @param $form
   * @param $form_state
   * @return array
   *  form array
   */
  public function form($bean, $form, &$form_state);

  /**
   * Validate function for bean type form
   *
   * @abstract
   *
   * @param  $values
   * @param $form_state
   */
  public function validate($values, &$form_state);

  /**
   * React to a bean being saved
   *
   * @abstract
   *
   * @param Bean $bean
   */
  public function submit(Bean $bean);

  /**
   * Return the block content.
   *
   * @abstract
   *
   * @param        $bean
   *   The bean object being viewed.
   * @param        $content
   *   The default content array created by Entity API.  This will include any
   *   fields attached to the entity.
   * @param string $view_mode
   *   The view mode passed into $entity->view().
   *
   * @param null   $langcode
   *
   * @return
   *   Return a renderable content array.
   */
  public function view($bean, $content, $view_mode = 'default', $langcode = NULL);
}

/**
 * The Bean entity class
 */
class Bean extends Entity {
  public $label;
  public $description;
  public $title;
  public $type;
  public $data;
  public $delta;
  public $view_mode;
  public $bid;
  public $vid;
  public $created;
  public $changed;
  public $log;
  public $uid;
  public $default_revision;
  public $revisions = array();
  protected $plugin;

  /**
   * Get Plugin info
   *
   * @param $key
   *  The plugin key to get the info for.
   *
   * @return array|null
   */
  public function getInfo($key = NULL) {
    if ($this->plugin instanceof BeanTypePluginInterface) {
      return $this->plugin->getInfo($key);
    }

    return NULL;
  }

  public function __construct(array $values = array()) {
    // If this is new then set the type first.
    if (isset($values['is_new'])) {
      $this->type = isset($values['type']) ? $values['type'] : '';
    }

    parent::__construct($values, 'bean');
  }

  public function adminTitle() {
    return check_plain($this->label);
  }

  protected function setUp() {
    parent::setUp();

    if (!empty($this->type)) {
      $plugin = bean_load_plugin_class($this->type);
      $this->loadUp($plugin);
    }
    return $this;
  }

  /**
   * This is a work around for version of PDO that call __construct() before
   * it loads up the object with values from the DB.
   */
  public function loadUp($plugin) {
    if (empty($this->plugin)) {
      // If the plugin has been disabled, the $plugin will be a boolean.
      // just load the base plugin so something will render.
      if (!($plugin instanceof BeanTypePluginInterface)) {
        $plugin = bean_load_plugin_class('bean_default');
      }

      $this->setPlugin($plugin)->setFields();
    }
    return $this;
  }

  /**
   * Load and set the plugin info.
   * This can be called externally via loadUP()
   */
  protected  function setPlugin($plugin) {
    $this->plugin = $plugin;

    return $this;
  }

  /**
   * Set the fields from the defaults and plugin
   * This can be called externally via loadUP()
   */
  protected function setFields() {
    // NOTE: When setFields is called externally $this->data is already unserialized.
    if (!empty($this->plugin) && !empty($this->type)) {
      $values = is_array($this->data) ? $this->data : unserialize($this->data);
      foreach ($this->plugin->values() as $field => $default) {
        $this->$field = isset($values[$field]) ? $values[$field] : $default;
      }
    }
    return $this;
  }

  /**
   * Override this in order to implement a custom default URI and specify
   * 'entity_class_uri' as 'uri callback' hook_entity_info().
   */
  protected function defaultUri() {
    return array('path' => 'block/' . strtolower($this->identifier()));
  }

  /**
  * Get the default label
  *
  * @return string
  */
  protected function defaultLabel() {
    if (empty($this->title)) {
      return $this->label;
    }

    return $this->title;
  }

  /**
   * Get the plugin form
   */
  public function getForm($form, &$form_state) {
    return $this->plugin->form($this, $form, $form_state);
  }

  /**
   * Validate the plugin form
   */
  public function validate($values, &$form_state) {
    $this->plugin->validate($values, $form_state);
  }

  /**
   * URL string
   */
  public function url() {
    $uri = $this->defaultUri();
    return $uri['path'];
  }

  /**
   * Build the URL string
   */
  protected function buildURL($type) {
    $url = $this->url();
    return $url . '/' . $type;
  }

  /**
   * View URL
   */
  public function viewURL() {
    return $this->buildURL('view');
  }

  /**
   * View URL
   */
  public function editURL() {
    return $this->buildURL('edit');
  }

  /**
   * View URL
   */
  public function deleteURL() {
    return $this->buildURL('delete');
  }

  /**
   * Type name
   */
  public function typeName() {
    return $this->getInfo('label');
  }

  /**
   * Set the values from a plugin
   */
  public function setValues($values) {
    $this->data = array();
    foreach ($this->plugin->values() as $field => $value) {
      $this->data[$field] = $values[$field];
    }

    return $this;
  }

  /**
   * Generate an array for rendering the entity.
   *
   * @see entity_view()
   */
  public function view($view_mode = 'default', $langcode = NULL, $page = NULL) {
    $content = parent::view($view_mode, $langcode);
    if (empty($this->plugin)) {
      return $content;
    }
    return $this->plugin->view($this, $content, $view_mode, $langcode);
  }

  /**
   * Override the save to add clearing of caches
   */
  public function save() {
    $this->setUid()->checkDelta();

    if (empty($this->created)) {
      $this->created = REQUEST_TIME;
    }

    $this->changed = REQUEST_TIME;

    $this->plugin->submit($this);

    $return = parent::save();
    bean_reset(TRUE, TRUE);

    return $return;
  }

  /**
   * Get the user
   */
  protected function setUid() {
    global $user;

    $this->uid = empty($this->uid) ? $user->uid : $this->uid;

    return $this;
  }

  /**
   * Set the delta function
   */
  protected  function checkDelta() {
    if (empty($this->delta)) {
      $max_length = 32;

      // Base it on the label and make sure it isn't too long for the database.
      if (module_exists('transliteration')) {
        $delta = drupal_clean_css_identifier(transliteration_get($this->label));
      }
      else {
        $delta = drupal_clean_css_identifier(strtolower($this->label));;
      }

      // Add 'bean-' prefix when it's need to avoid a purely numeric delta.
      if (is_numeric($delta)) {
        $delta = 'bean-' . $delta;
      }

      $this->delta = substr($delta, 0, $max_length);

      // Check if delta is unique.
      if (bean_load_delta($this->delta)) {
        $i = 0;
        $separator = '-';
        $original_delta = $this->delta;
        do {
          $unique_suffix = $separator . $i++;
          $this->delta = substr($original_delta, 0, $max_length - drupal_strlen($unique_suffix)) . $unique_suffix;
        } while (bean_load_delta($this->delta));
      }
    }

    return $this;
  }

  /**
   * Load the revisions from the DB
   */
  public function loadRevisions() {
    $this->revisions = db_select('bean_revision', 'br')
                        ->condition('delta', $this->identifier())
                        ->fields('br')
                        ->execute();

    return $this;
  }
}

class BeanEntityAPIController extends EntityAPIControllerExportable {
  protected function setPlugin(Bean $bean) {
    static $plugins = array();

    if (empty($plugins[$bean->type])) {
      $plugins[$bean->type] = bean_load_plugin_class($bean->type);
      $bean->loadUp($plugins[$bean->type]);
    }
  }

  protected function attachLoad(&$queried_entities, $revision_id = FALSE) {
    foreach ($queried_entities as $entity) {
      $this->setPlugin($entity);
    }
    parent::attachLoad($queried_entities, $revision_id);
  }

  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    $beans = $ids ? $this->load($ids) : array();

    $deltas = array();
    foreach ($beans as $bean) {
      if ($bean->internalIdentifier()) {
        field_attach_delete('bean', $bean);

        $deltas[] = $bean->identifier();
      }
    }

    if (!empty($deltas)) {
      try {
        // @see block_custom_block_delete_submit()
        if (module_exists('block')) {
          db_delete('block')
            ->condition('module', 'bean')
            ->condition('delta', $deltas)
            ->execute();
          db_delete('block_role')
            ->condition('module', 'bean')
            ->condition('delta', $deltas)
            ->execute();

          // @see node_form_block_custom_block_delete_submit()
          db_delete('block_node_type')
            ->condition('module', 'bean')
            ->condition('delta', $deltas)
            ->execute();
        }
      }
      catch (Exception $e) {
        if (isset($transaction)) {
          $transaction->rollback();
        }
        watchdog_exception('bean', $e);
        throw $e;
      }
    }
    parent::delete($ids, $transaction);
  }

  protected function saveRevision($entity) {
    global $user;

    $org_uid = $entity->uid;
    $entity->uid = $user->uid;
    $return = parent::saveRevision($entity);
    $entity->uid = $org_uid;

    return $return;
  }
}

class BeanException extends Exception {};
