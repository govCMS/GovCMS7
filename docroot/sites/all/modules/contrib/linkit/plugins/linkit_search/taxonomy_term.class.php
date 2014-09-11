<?php
/**
 * @file
 * Define Linkit term search plugin class.
 */

/**
 * Reprecents a Linkit term search plugin.
 */
class LinkitSearchPluginTaxonomy_Term extends LinkitSearchPluginEntity {

  /**
   * Overrides LinkitSearchPluginEntity::__construct().
   */
  function __construct($plugin, $profile) {
    /**
     * The term entity doesn't use the same column name as in the entity keys
     * bundle definition, so lets add it our self.
     */
    $this->entity_key_bundle = 'vid';
    parent::__construct($plugin, $profile);
  }

  /**
   * Overrides LinkitSearchPluginEntity::createDescription().
   */
  function createDescription($data) {
    $description = token_replace(check_plain($this->conf['result_description']), array(
      'term' => $data,
    ), array('clear' => TRUE));
    return $description;
  }

  /**
   * Overrides LinkitSearchPluginEntity::createGroup().
   */
  function createGroup($entity) {
    // Get the entity label.
    $group = $this->entity_info['label'];

    if (isset($this->conf['group_by_bundle']) && $this->conf['group_by_bundle']) {
      $bundles = $this->entity_info['bundles'];
      $bundle_name = $bundles[$entity->vocabulary_machine_name]['label'];
      $group .= ' - ' . check_plain($bundle_name);
    }
    return $group;
  }

  /**
   * Overrides LinkitSearchPluginEntity::fetchResults().
   */
  function fetchResults($search_string) {
    // The term entity doesn't use the entity keys bundle definition, its using
    // the vid instead, so lets 'translate' the bundle names to vids.
    if (isset($this->entity_key_bundle) && isset($this->conf['bundles']) ) {
      $bundles = array_filter($this->conf['bundles']);

      // Get all vocabularies.
      $vocabularies = taxonomy_vocabulary_get_names();
      // Temp storage for values.
      $tmp_bundles = array();
      foreach ($bundles as $bundle) {
        $tmp_bundles[] = $vocabularies[$bundle]->{$this->entity_key_bundle};
      }

      // Assign the new values as the bundles.
      $this->conf['bundles'] = $tmp_bundles;
    }
    // Call the parent.
    return parent::fetchResults($search_string);
  }

  /**
   * Overrides LinkitSearchPlugin::buildSettingsForm().
   */
  function buildSettingsForm() {
    $form = parent::buildSettingsForm();

    // The entity plugin uses the entity name for the #token_types, but terms
    // is a special case, its name is "Taxonomy_term" and the tokens are defined
    // (in the taxonomy module) with just "term".

    // If the token modules is installed.
    if (isset($form[$this->plugin['name']]['token_help']['help']['#token_types'])) {
      $form[$this->plugin['name']]['token_help']['help']['#token_types'] = array('term');
    }
    // If the token module is not installed, use the orignal tokens provided by
    // Drupal core.
    else {
      // Get supported tokens for the term entity type.
      $tokens = linkit_extract_tokens('term');
      $form[$this->plugin['name']]['result_description']['#description'] = t('Available tokens: %tokens.', array('%tokens' => implode(', ', $tokens)));
    }
    return $form;
  }
}