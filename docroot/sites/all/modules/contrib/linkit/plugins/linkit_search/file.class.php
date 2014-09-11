<?php
/**
 * @file
 * Define Linkit file search plugin class.
 */

/**
 * Reprecents a Linkit file search plugin.
 */
class LinkitSearchPluginFile extends LinkitSearchPluginEntity {

  /**
   * Overrides LinkitSearchPlugin::ui_title().
   */
  function ui_title() {
    return t('Managed files');
  }

  /**
   * Overrides LinkitSearchPlugin::ui_description().
   */
  function ui_description() {
    return t('Extend Linkit with file support (Managed files).');
  }

  /**
   * Overrides LinkitSearchPluginEntity::createDescription().
   *
   * If the file is an image, a small thumbnail can be added to the description.
   * Also, image dimensions can be shown.
   */
  function createDescription($data) {
    $description_array = array();
    // Get image info.
    $imageinfo = image_get_info($data->uri);

    // Add small thumbnail to the description.
    if ($this->conf['image_extra_info']['thumbnail']) {
      $image = $imageinfo ? theme_image_style(array(
          'width' => $imageinfo['width'],
          'height' => $imageinfo['height'],
          'style_name' => 'linkit_thumb',
          'path' => $data->uri,
        )) : '';
    }

    // Add image dimensions to the description.
    if ($this->conf['image_extra_info']['dimensions'] && !empty($imageinfo)) {
      $description_array[] = $imageinfo['width'] . 'x' . $imageinfo['height'] . 'px';
    }

    $description_array[] = parent::createDescription($data);

    // Add tiel files scheme to the description.
    if ($this->conf['show_scheme']) {
      $description_array[] = file_uri_scheme($data->uri) . '://';
    }

    $description = (isset($image) ? $image : '') . implode('<br />' , $description_array);

    return $description;
  }

  /**
   * Overrides LinkitSearchPluginEntity::createGroup().
   */
  function createGroup($entity) {
    // The the standard group name.
    $group = parent::createGroup($entity);

    // Add the scheme.
    if ($this->conf['group_by_scheme']) {
      // Get all stream wrappers.
      $stream_wrapper = file_get_stream_wrappers();
      $group .= ' - ' . $stream_wrapper[file_uri_scheme($entity->uri)]['name'];
    }
    return $group;
  }

  /**
   * Overrides LinkitSearchPluginEntity::getQueryInstance().
   */
  function getQueryInstance() {
    // Call the parent getQueryInstance method.
    parent::getQueryInstance();
    // Only search for permanent files.
    $this->query->propertyCondition('status', FILE_STATUS_PERMANENT);
  }

  /**
   * Overrides LinkitSearchPluginEntity::buildSettingsForm().
   */
  function buildSettingsForm() {
    $form = parent::buildSettingsForm();

    $form['entity:file']['show_scheme'] = array(
      '#title' => t('Show file scheme'),
      '#type' => 'checkbox',
      '#default_value' => isset($this->conf['show_scheme']) ? $this->conf['show_scheme'] : '',
    );

    $form['entity:file']['group_by_scheme'] = array(
      '#title' => t('Group files by scheme'),
      '#type' => 'checkbox',
      '#default_value' => isset($this->conf['group_by_scheme']) ? $this->conf['group_by_scheme'] : '',
    );

    $image_extra_info_options = array(
      'thumbnail' => t('Show thumbnails <em>(using the image style !linkit_thumb_link)</em>', array('!linkit_thumb_link' => l(t('linkit_thumb'), 'admin/config/media/image-styles/edit/linkit_thumb'))),
      'dimensions' => t('Show pixel dimensions'),
    );

    $form['entity:file']['image_extra_info'] = array(
      '#title' => t('Images'),
      '#type' => 'checkboxes',
      '#options' => $image_extra_info_options,
      '#default_value' => isset($this->conf['image_extra_info']) ? $this->conf['image_extra_info'] : array('thumbnail', 'dimensions'),
    );

    return $form;
  }
}