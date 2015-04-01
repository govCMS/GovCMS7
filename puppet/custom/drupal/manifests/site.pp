# Drupal instance.

define drupal::site (
  $dir               = '/vagrant/app',
  $domain            = 'dev',
  $http_port         = $drupal::params::port,
  $mysql_host        = 'localhost',
) {
  # Local /etc/hosts DNS record.
  host { "${title}.${domain}":
    ip => '127.0.0.1',
  }

  # Apache vHost.
  apache::vhost { "${title}.${domain}":
    port     => $http_port,
    docroot  => $dir,
    override => [ 'ALL' ],
  }

  # Mysql Database.
  mysql::db { "${title}":
    user     => $title,
    password => $title,
    host     => $mysql_host,
    grant    => ['ALL'],
  }

  # We add this to the database so localhost can still connect.
  # @todo, Check for localhost declaration first.
  $user_resource = {
    ensure        => 'present',
    password_hash => mysql_password($title),
    provider      => 'mysql',
    require       => Class['mysql::server'],
  }
  ensure_resource('mysql_user', "${title}@localhost", $user_resource)
}
