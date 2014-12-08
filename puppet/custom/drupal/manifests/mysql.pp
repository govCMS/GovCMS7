# The mysql configuration for Drupal.

class drupal::mysql {
  class { 'mysql::server':
    # The following has been added so we can access the database
    # from our host.
    override_options => {
      'mysqld' => {
        'bind_address' => '0.0.0.0',
      }
    }
  }
  include 'mysql::server::mysqltuner'
  include 'mysql::client'
  class { 'mysql::bindings':
    php_enable => true,
  }
}
