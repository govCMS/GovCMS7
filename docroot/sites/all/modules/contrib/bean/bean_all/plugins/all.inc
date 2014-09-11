<?php

class BeanAll extends BeanPlugin {
  protected $block_info;
  protected $block_config_form;

  public function __construct($plugin_info) {
    $this->block_info = $plugin_info['block'];
    parent::__construct($plugin_info);
  }

  public function values() {
    $this->loadBlockConfig();
    $values = array_fill_keys(array_keys($this->block_config_form), array());
    foreach ($values as $key => $nothing) {
      $values[$key] = isset($this->block_config_form[$key]['#default_value']) ?
        $this->block_config_form[$key]['#default_value'] : '';
    }

    return $values;
  }

  public function form($bean, $form, &$form_state) {
    return $this->loadBlockConfig()->block_config_form;
  }

  public function view($bean, $content, $view_mode = 'default', $langcode = NULL) {
    $block_object = $this->getBlockInfo();
    $block_object->title = $block_object->info;
    $block_object->enabled = $block_object->page_match = TRUE;
    $blocks[$this->getBlockInfo('module') . "_" . $this->getBlockInfo('delta')] = $block_object;

    module_load_include('module', 'block', 'block');
    $block_content = _block_render_blocks($blocks);
    $content += _block_get_renderable_array($block_content);

    $build[$this->getBlockInfo('module') . "_" . $this->getBlockInfo('delta')]['#contextual_links']['block']
      = array('block', array($bean->delta));

    return $content;
  }

  public function submit(Bean $bean) {
    $bean_values = (array) $bean;
    module_invoke($this->getBlockInfo('module'), 'block_save', $this->getBlockInfo('delta'), $bean_values);
    return $this;
  }

  protected function getBlockInfo($key = NULL) {
    if (!empty($key) && isset($this->block_info->$key)) {
      return $this->block_info->$key;
    }

    return $this->block_info;
  }

  protected function loadBlockConfig() {
    if (!isset($this->block_config_form)) {
      $this-> block_config_form = array();
      if ($settings = module_invoke($this->getBlockInfo('module'), 'block_configure', $this->getBlockInfo('delta'))) {
        foreach ($settings as $k => $v) {
          $this-> block_config_form[$k] = $v;
        }
      }
    }

    return $this;
  }
}
