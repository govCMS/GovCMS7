<?php
/**
 * @file
 *
 * Is an alter plugin for defaultcontent
 *
 * Handles the exporting and importing of file fields
 */

$plugin = array();

/**
 * Prepares file field for export to code
 */
function file_export_alter(&$node) {
  $fields = get_file_fields();
  foreach ($fields as $field_name => $field) {
    if (isset($node->{$field_name})) {
      foreach ($node->{$field_name} as $lang => $items) {
        foreach ($items as $key => $item) {
          $imgfile = drupal_realpath($item['uri']);
          if ($imgfile && ($handle = fopen($imgfile, 'rb')) && (filesize($imgfile) > 0)) {
            $imgbinary = fread($handle, filesize($imgfile));
            $node->{$field_name}[$lang][$key]['image'] = base64_encode($imgbinary);
          }
          $filename = $node->{$field_name}[$lang][$key]['filename'];
          $node->{$field_name}[$lang][$key]['uri'] = 'public://' . $filename;
          unset($node->{$field_name}[$lang][$key]['fid']);
          unset($node->{$field_name}[$lang][$key]['uid']);
          unset($node->{$field_name}[$lang][$key]['timestamp']);
        }
      }
    }
  }
}

/**
 * Prepares file field for import.
 *
 * Create the file and attach the new file object in the file field.
 */
function file_import_alter(&$node) {
  $fields = get_file_fields();
  foreach ($fields as $field_name => $field) {
    if (isset($node->{$field_name})) {
      foreach ($node->{$field_name} as $lang => $items) {
        foreach ($items as $key => $item) {
          if (isset($item['filename'])) {
            $file = (object) $item;

            // Reuse any already imported files
            $fids = db_select('file_managed', 'f')
              ->condition('uri', $file->uri)
              ->fields('f', array('fid'))
              ->execute()
              ->fetchCol();
            if (!empty($fids) && isset($fids[0])) {
              $result = $file;
              $result->fid = $fids[0];
            }
            else {

              // There is no file, so prepare to save. Exports store all file
              // data in the 'image' key.
              if (isset($file->image)) {
                // Decode file data. Older versions exported binary data
                // so if this fails we assume that is the reason.
                $data = base64_decode($file->image);
                if (!isset($data) || empty($data)) {
                  $data = $file->image;
                }
              }

              // For images, save data, for files, just save.
              if (isset($data) && !empty($data)) {
                $result = file_save_data($data, $file->uri);
              }
              else {
                $result = file_save($file);
              }
            }

            // Add the file to the node for saving.
            if (isset($result) || !empty($result)) {
              $result->display = 1;

              // Ensure alt and title fields are set for images.
              if ($field['type'] == 'image') {
                $result->alt = $item['alt'];
                $result->title = $item['title'];
              }

              $node->{$field_name}[$lang][$key] = (array) $result;
            }
            else {
              watchdog('defaultcontent', 'Import of file failed.', array(), WATCHDOG_ERROR);
            }
          }
          else {
            // This export is probably broken. Remove it so the node can be
            // saved.
            unset($node->{$field_name}[$lang][$key]);
            watchdog('defaultcontent', 'Could not import file. The imported data was incomplete.', array(), WATCHDOG_ERROR);
          }
        }
      }
    }
  }
}

/**
 * Helper function to get all file fields
 */
function get_file_fields() {
  $ref_fields = array();
  foreach (field_info_fields() as $id => $field) {
    if (in_array($field['type'], array('image', 'file'))) {
      $ref_fields[$id] = $field;
    }
  }
  return $ref_fields;
}
