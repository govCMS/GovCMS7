; GovCMS

; Core version
; The make file always begins by specifying the core version of Drupal for
; which each package must be compatible.
core = 7.x

; API version
; The make file must specify which Drush Make API version it uses.
api = 2

; Drupal core.
projects[drupal][version] = 7.34
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-7.x-allow_profile_change_sys_req-1772316-28.patch
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-1470656-26.patch
projects[drupal][patch][] = patches/govcms_force_ssl_v1.patch

; aGov profile.
projects[agov][version] = 2.0-alpha5
projects[agov][patch][] = patches/govcms_agov_govcms_tweak_enable_v1.patch

; Contrib modules.
projects[acsf][version] = 1.4
projects[acquia_connector][version] = 2.15
projects[clamav][version] = 1.0-alpha2
projects[clamav][patch][] = https://www.drupal.org/files/issues/clamav-scan_all_files-1630604-13.patch
projects[search_api_acquia][version] = 2.1
