<?php

class crumbs_EntityPlugin_Field_Text extends crumbs_EntityPlugin_Field_Abstract {

  /**
   * {@inheritdoc}
   */
  function fieldFindCandidate(array $items) {
    foreach ($items as $item) {
      return $item['value'];
    }

    return NULL;
  }

}
