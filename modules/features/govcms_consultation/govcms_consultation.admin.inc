<?php
/**
 * @file
 * Administrative forms and functions for govCMS Consultation.
 */

function govcms_consultation_admin_form() {
  $form = array();

  $form['consultation_enable_private'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow private submissions'),
    '#default_value' => variable_get('consultation_enable_private', 0),
    '#description' => t("By checking this box you agree to the storage of potentially sensitive data on your govCMS site. For more information, please read the help page."),
  );

  $form['consultation_enable_disqus'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Disqus integration (informal discussion)'),
    '#default_value' => variable_get('consultation_enable_disqus', 0),
    '#description' => t("Enable informal discussion on a per-Consultation basis (Disqus account required)."),
  );

  $form['consultation_disqus_account'] = array(
    '#type' => 'textfield',
    '#title' => t('Disqus shortname'),
    '#default_value' => variable_get('consultation_disqus_account', ''),
    '#description' => t("Disqus shortname."),
  );

  $form['consultation_enable_twitter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Twitter integration'),
    '#default_value' => variable_get('consultation_enable_twitter', 0),
    '#description' => t("Enable embedded Twitter discussion (Twitter account required)."),
  );

  $form['consultation_twitter_account'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter account id'),
    '#default_value' => variable_get('consultation_twitter_account', ''),
    '#description' => t("Twitter account id (leave out @ symbol)."),
  );

  return system_settings_form($form);
}


/**
 * Implements hook_form_validate().
 */
function govcms_consultation_admin_form_validate($form, &$form_state) {
  if ($form_state['values']['consultation_enable_disqus'] && empty($form_state['values']['consultation_disqus_account'])) {
    form_set_error('consultation_disqus_account', 'You must provide a Disqus shortname.');
  }

  if ($form_state['values']['consultation_enable_twitter'] && empty($form_state['values']['consultation_twitter_account'])) {
    form_set_error('consultation_twitter_account', 'You must provide a Twitter username.');
  }

}
