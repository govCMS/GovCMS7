<?php

class WorkbenchModerationMigrateDestinationHandler extends MigrateDestinationHandler {

  public function __construct() {}

  public function handlesType($destination) {
    return ($destination == 'Node');
  }

  public function fields($entity_type, $bundle_type) {
     $fields = array();

    if (workbench_moderation_node_type_moderated($bundle_type)) {
      $fields['workbench_moderation_state_new'] = t('Moderation state');
    }
    return $fields;
  }
}
