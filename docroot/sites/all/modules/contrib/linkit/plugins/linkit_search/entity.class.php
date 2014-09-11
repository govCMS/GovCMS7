<?php
/**
 * @file
 * Define Linkit entity search plugin class.
 */

/**
 * Reprecents a Linkit entity search plugin.
 */
class LinkitSearchPluginEntity extends LinkitSearchPlugin {

  /**
   * Entity field query instance.
   *
   * @var EntityFieldQuery Resource
   */
  var $query;

  /**
   * The entity info array of an entity type.
   *
   * @var array
   */
  var $entity_info = array();

  /**
   * The name of the property that contains the entity label.
   *
   * @var string
   */
  var $entity_field_label;

  /**
   * The name of the property of the bundle object that contains the name of
   * the bundle object.
   *
   * @var string
   */
  var $entity_key_bundle;

  /**
   * Plugin specific settings.
   *
   * @var array
   */
  var $conf = array();

  /**
   * Overrides LinkitSearchPlugin::__construct().
   *
   * Initialize this plugin with the plugin, profile, and entity specific
   * variables.
   *
   * @param array $plugin
   *   The plugin array.
   *
   * @param LinkitProfile object $profile
   *   The Linkit profile to use.
   */
  function __construct($plugin, LinkitProfile $profile) {
    parent::__construct($plugin, $profile);

    // Load the corresponding entity info.
    $this->entity_info = entity_get_info($this->plugin['entity_type']);

    // Set bundle key name.
    if (isset($this->entity_info['entity keys']['bundle']) &&
      !isset($this->entity_key_bundle)) {
      $this->entity_key_bundle = $this->entity_info['entity keys']['bundle'];
    }

    // Set the label field name.
    if (!isset($this->entity_field_label)) {
      // Check that the entity has a label in entity keys.
      // If not, Linkit don't know what to search for.
      if (!isset($this->entity_info['entity keys']['label'])) {
        // This is only used when building the plugin list.
        $this->unusable = TRUE;
      }
      else {
        $this->entity_field_label = $this->entity_info['entity keys']['label'];
      }
    }

    // Make a shortcut for the profile data settings for this plugin.
    $this->conf = isset($this->profile->data[$this->plugin['name']]) ?
            $this->profile->data[$this->plugin['name']] : array();
  }

  /**
   * Create a label of an entity.
   *
   * @param $entity
   *   The entity to get the label from.
   *
   * @return
   *   The entity label, or FALSE if not found.
   */
  function createLabel($entity) {
    return entity_label($this->plugin['entity_type'], $entity);
  }

   /**
   * Create a search row description.
   *
   * If there is a "result_description", run it thro token_replace.
   *
   * @param object $data
   *   An entity object that will be used in the token_place function.
   *
   * @return
   *   A string containing the row description.
   *
   * @see token_replace()
   */
  function createDescription($data) {
    $description = token_replace(check_plain($this->conf['result_description']), array(
      $this->plugin['entity_type'] => $data,
    ), array('clear' => TRUE));
    return $description;
  }

  /**
   * Create an uri for an entity.
   *
   * @param $entity
   *   The entity to get the path from.
   *
   * @return
   *   A string containing the path of the entity, NULL if the entity has no
   *   uri of its own.
   */
  function createPath($entity) {
    // Create the URI for the entity.
    $uri = entity_uri($this->plugin['entity_type'], $entity);

    $options = array();
    // Handle multilingual sites.
    if (isset($entity->language) && $entity->language != LANGUAGE_NONE && drupal_multilingual() && language_negotiation_get_any(LOCALE_LANGUAGE_NEGOTIATION_URL)) {
      $languages = language_list('enabled');
      // Only use enabled languages.
      $languages = $languages[1];

      if ($languages && isset($languages[$entity->language])) {
        $options['language'] = $languages[$entity->language];
      }
    }
    // Process the uri with the insert pluing.
    $path = linkit_get_insert_plugin_processed_path($this->profile, $uri['path'], $options);
    return $path;
  }

  /**
   * Create a group text.
   *
   * @param $entity
   *   The entity object.
   *
   * @return
   *   When "group_by_bundle" is active, we need to add the bundle name to the
   *   group, else just return the entity label.
   */
  function createGroup($entity) {
    // Get the entity label.
    $group = $this->entity_info['label'];

    // If the entities by this entity should be grouped by bundle, get the
    // name and append it to the group.
    if (isset($this->conf['group_by_bundle']) && $this->conf['group_by_bundle']) {
      $bundles = $this->entity_info['bundles'];
      $bundle_name = $bundles[$entity->{$this->entity_key_bundle}]['label'];
      $group .= ' - ' . check_plain($bundle_name);
    }
    return $group;
  }

  /**
   * Create a row class to appaned to the search result row.
   *
   * @param $entity
   *   The entity object.
   *
   * @return
   *   A string to with classes.
   */
  function createRowClass($entity) {
    return '';
  }

  /**
   * Start a new EntityFieldQuery instance.
   */
  function getQueryInstance() {
    $this->query = new EntityFieldQuery();
    $this->query->entityCondition('entity_type', $this->plugin['entity_type']);

    // Add the default sort on the enity label.
    $this->query->propertyOrderBy($this->entity_field_label, 'ASC');
  }

  /**
   * Implements LinkitSearchPluginInterface::fetchResults().
   */
  public function fetchResults($search_string) {
    // If the $search_string is not a string, something is wrong and an empty
    // array is returned.
    $matches = array();

    // Get the EntityFieldQuery instance.
    $this->getQueryInstance();

    // Add the search condition to the query object.
    $this->query->propertyCondition($this->entity_field_label,
            '%' . db_like($search_string) . '%', 'LIKE')
        ->addTag('linkit_entity_autocomplete')
        ->addTag('linkit_' . $this->plugin['entity_type'] . '_autocomplete');

    // Add access tag for the query.
    // There is also a runtime access check that uses entity_access().
    $this->query->addTag($this->plugin['entity_type'] . '_access');

    // Bundle check.
    if (isset($this->entity_key_bundle) && isset($this->conf['bundles']) ) {
      $bundles = array_filter($this->conf['bundles']);
      if ($bundles) {
        $this->query->propertyCondition($this->entity_key_bundle, $bundles, 'IN');
      }
    }

    // Execute the query.
    $result = $this->query->execute();

    if (!isset($result[$this->plugin['entity_type']])) {
      return array();
    }

    $ids = array_keys($result[$this->plugin['entity_type']]);

    // Load all the entities with all the ids we got.
    $entities = entity_load($this->plugin['entity_type'], $ids);

    foreach ($entities AS $entity) {
      // Check the access againt the definded entity access callback.
      if (entity_access('view', $this->plugin['entity_type'], $entity) === FALSE) {
        continue;
      }

      $matches[] = array(
        'title' => $this->createLabel($entity),
        'description' => $this->createDescription($entity),
        'path' => $this->createPath($entity),
        'group' => $this->createGroup($entity),
        'addClass' => $this->createRowClass($entity),
      );

    }
    return $matches;
  }

  /**
   * Overrides LinkitSearchPlugin::buildSettingsForm().
   */
  function buildSettingsForm() {
    $form[$this->plugin['name']] = array(
      '#type' => 'fieldset',
      '#title' => t('!type plugin settings', array('!type' => $this->ui_title())),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => TRUE,
      '#states' => array(
        'invisible' => array(
          'input[name="data[search_plugins][' . $this->plugin['name'] . '][enabled]"]' => array('checked' => FALSE),
        ),
      ),
    );
    // Get supported tokens for the entity type.
    $tokens = linkit_extract_tokens($this->plugin['entity_type']);

    // A short description in within the search result for each row.
    $form[$this->plugin['name']]['result_description'] = array(
      '#title' => t('Result description'),
      '#type' => 'textfield',
      '#default_value' => isset($this->conf['result_description']) ? $this->conf['result_description'] : '',
      '#size' => 120,
      '#maxlength' => 255,
      '#description' => t('Available tokens: %tokens.', array('%tokens' => implode(', ', $tokens))),
    );

    // If the token module is installed, lets make some fancy stuff with the
    // token chooser.
    if (module_exists('token')) {
      // Unset the regular description if token module is enabled.
      unset($form[$this->plugin['name']]['result_description']['#description']);

      // Display the user documentation of placeholders.
      $form[$this->plugin['name']]['token_help'] = array(
        '#title' => t('Replacement patterns'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form[$this->plugin['name']]['token_help']['help'] = array(
        '#theme' => 'token_tree',
        '#token_types' => array($this->plugin['entity_type']),
      );
    }

    // If there is bundles, add some default settings features.
    if (count($this->entity_info['bundles']) > 1) {
      $bundles = array();
      // Extract the bundle data.
      foreach ($this->entity_info['bundles'] as $bundle_name => $bundle) {
        $bundles[$bundle_name] = $bundle['label'];
      }

      // Filter the possible bundles to use if the entity has bundles.
      $form[$this->plugin['name']]['bundles'] = array(
        '#title' => t('Type filter'),
        '#type' => 'checkboxes',
        '#options' => $bundles,
        '#default_value' => isset($this->conf['bundles']) ? $this->conf['bundles'] : array(),
        '#description' => t('If left blank, all types will appear in autocomplete results.'),
      );

      // Group the results with this bundle.
      $form[$this->plugin['name']]['group_by_bundle'] = array(
        '#title' => t('Group by bundle'),
        '#type' => 'checkbox',
        '#default_value' => isset($this->conf['group_by_bundle']) ? $this->conf['group_by_bundle'] : 0,
      );
    }
    return $form;
  }
}