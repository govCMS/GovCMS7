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

; Context Security patch
projects[agov][patch][] = https://github.com/previousnext/agov/commit/b20a0f17a9a90365479bd73b5a78288a76e5b726.patch

; Linkit Security patch
projects[agov][patch][] = https://github.com/previousnext/agov/commit/d5e970513dc92c1d8a671599970effda34008ba0.patch

; Webform Security patch
projects[agov][patch][] = https://github.com/previousnext/agov/commit/4171239e4cef9bd38208e996502c7012504cc39c.patch

; Google Analytics Security Patch
projects[agov][patch][] = patches/google_analytics_version-2.1.patch

; Update entity api to 7.x-1.6
projects[agov][patch][] = https://github.com/previousnext/agov/commit/1d2e89f6ea0a6b65c95cc2086baafc274671862a.patch

; Views security update
projects[agov][patch][] = https://github.com/previousnext/agov/commit/cfb38c35f98fcaf0505d98046f79faf6962ae738.patch

; Contrib modules.
projects[acsf][version] = 1.4
projects[acquia_connector][version] = 2.15
projects[clamav][version] = 1.0-alpha2
projects[clamav][patch][] = https://www.drupal.org/files/issues/clamav-scan_all_files-1630604-13.patch
projects[search_api_solr][version] = 1.6
projects[search_api_acquia][version] = 2.1
