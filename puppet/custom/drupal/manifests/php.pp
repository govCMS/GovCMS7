# A Drupal PHP class.

class drupal::php (
  $display_errors      = $drupal::params::display_errors,
  $memory_limit        = $drupal::params::memory_limit,
  $post_max_size       = $drupal::params::post_max_size,
  $upload_max_filesize = $drupal::params::upload_max_filesize,
  $max_execution_time  = $drupal::params::max_execution_time,
  $date_timezone       = $drupal::params::date_timezone,
  $error_log           = $drupal::params::error_log,
) {
  class { 'php::mod_php5': inifile => '/etc/php5/apache2/php.ini' }
  php::ini { '/etc/php5/apache2/php.ini':
    display_errors      => $display_errors,
    memory_limit        => $memory_limit,
    post_max_size       => $post_max_size,
    upload_max_filesize => $upload_max_filesize,
    max_execution_time  => $max_execution_time,
    date_timezone       => $date_timezone,
    error_log           => $error_log,
    require             => Package['libapache2-mod-php5'],
  }
  php::ini { '/etc/php5/cli/php.ini':
    display_errors      => $display_errors,
    memory_limit        => $memory_limit,
    post_max_size       => $post_max_size,
    upload_max_filesize => $upload_max_filesize,
    max_execution_time  => $max_execution_time,
    date_timezone       => $date_timezone,
    error_log           => $error_log,
  }
}
