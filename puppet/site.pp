# Default Drupal 8 development site.

node default {

  # Basic includes.	
  include drupal

  # Advanced includes.
  drupal::site { 'govcms':
    mysql_host => '%',
  }

}

