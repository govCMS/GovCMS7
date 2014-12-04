# The packages Drupal requires.

class drupal::packages {
  # We want to ensure apt is always updated first.
  class { 'apt': }

  # Repositories.
  apt::ppa { 'ppa:ondrej/php5-oldstable': }

  # Packages.
  package { 'libapache2-mod-php5': ensure => 'installed', require => Apt::Ppa['ppa:ondrej/php5-oldstable'] }
  package { 'php5-gd':             ensure => 'installed', require => Apt::Ppa['ppa:ondrej/php5-oldstable'] }
  package { 'php5-mcrypt':         ensure => 'installed', require => Apt::Ppa['ppa:ondrej/php5-oldstable'] }
  package { 'php5-curl':           ensure => 'installed', require => Apt::Ppa['ppa:ondrej/php5-oldstable'] }
  package { 'php5-xdebug':         ensure => 'installed', require => Apt::Ppa['ppa:ondrej/php5-oldstable'] }

  # Ensure we have an update to date set of packages.
  exec { 'apt-update':
    command => '/usr/bin/apt-get update'
  }
  Exec["apt-update"] -> Package <| |>

  include pear
  pear::package { 'phing':
    version    => '2.4.13',
    repository => 'pear.phing.info',
  }
  pear::package { 'Console_Table': }
  pear::package { 'drush':
    version    => '5.7.0',
    repository => 'pear.drush.org',
  }
}
