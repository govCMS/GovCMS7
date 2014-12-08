# Webserver configuration.

class drupal inherits drupal::params {
  
  include drupal::packages
  include drupal::webserver
  include drupal::mysql
  include drupal::locale
  include drupal::php

}
