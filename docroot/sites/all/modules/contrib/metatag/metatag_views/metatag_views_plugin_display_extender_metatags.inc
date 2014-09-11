<?php
/**
 * @file
 * Custom display extender plugin for Views.
 */

class metatag_views_plugin_display_extender_metatags extends views_plugin_display_extender {

  protected function has_metatags() {
    return metatag_views_views_display_has_metatags($this->display);
  }

  function options_definition_alter(&$options) {
    $options['metatags'] = array('default' => array());
  }

  function options_summary(&$categories, &$options) {
    if ($this->has_metatags()) {
      $categories['metatags'] = array(
        'title' => t('Meta tags'),
        'column' => 'second',
      );
      $metatags = $this->display->get_option('metatags');
      $options['metatags'] = array(
        'category' => 'metatags',
        'title' => t('Meta tags'),
        'value' => !empty($metatags) ? t('Overridden') : t('Using defaults'),
      );
    }
  }

  function options_form(&$form, &$form_state) {
    if ($form_state['section'] == 'metatags') {
      $form['#title'] .= t('The meta tags for this display');
      $instance = 'view:' . $form_state['view']->name;
      $metatags = $this->display->get_option('metatags');
      $metatags = !empty($metatags) ? $metatags : array();
      $options['token types'] = array('view');
      $options['context'] = 'view';
      metatag_metatags_form($form, $instance, $metatags, $options);
      $form['metatags']['#type'] = 'container';
    }
  }

  function options_submit(&$form, &$form_state) {
    if ($form_state['section'] == 'metatags') {
      $metatags = $form_state['values']['metatags'];
      metatag_filter_values_from_defaults($metatags);
      $this->display->set_option('metatags', $metatags);
    }
  }
}
