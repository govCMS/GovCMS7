# A webserver class.

class drupal::webserver (
  $port = $drupal::params::port,
) {
  # We setup a user for Apache.
  $user_name = "drupal"
  user { $user_name:
    ensure => present,
    home => "/home/${user_name}",
    managehome => true,
    comment => "${user_name} User",
    gid => $vagrant_uid,
    groups => [ $user_name ],
    require => Group[ $user_name ],
    uid => $vagrant_uid,
    shell => '/bin/bash',
  }
  group { $user_name:
    gid => $vagrant_uid,
  }

  class { 'apache':
    default_vhost => false,
    mpm_module => 'prefork',
    manage_user => false,
    manage_group => false,
    user => $user_name,
    group => $vagrant_group,
  }
  apache::listen { $port: }
  # apache::mod { 'php5': }
  apache::mod { 'rewrite': }
  apache::mod { 'headers': }

  # @todo, work out how we can remove this symlink.
  file { "${apache::params::httpd_dir}/modules":
    ensure  => 'link',
    target  => $apache::params::lib_path,
    require => Class['apache'],
    notify  => Service['httpd'],
  }

  # Xdebug.
  file { '/etc/php5/conf.d/20-xdebug.ini':
    ensure  => present,
    mode    => '0644',
    content => template('drupal/20-xdebug.ini.erb'),
    require => Package['php5-xdebug'],
    notify  => Service['httpd'],
  }
}
