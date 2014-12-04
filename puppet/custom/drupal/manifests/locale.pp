# Locale configuration for common Drupal host.

class drupal::locale {
  # EN and DE locales will be generated.
  class { 'locales':
    locales => [
      'en_AU.UTF-8 UTF-8',
      'en_US.UTF-8 UTF-8',
      'en_GB.UTF-8 UTF-8',
    ],
  }

  # Set to Sydney for timezone.
  class { 'timezone':
    timezone => 'Australia/Sydney',
  }

  # Ensure the clock is kept up to date.
  class { '::ntp':
    servers  => [ 'ntp.ubuntu.com' ],
    restrict => ['127.0.0.1'],
  }
}
