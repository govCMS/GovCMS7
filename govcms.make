; GovCMS

; Core version
; The make file always begins by specifying the core version of Drupal for
; which each package must be compatible.
core = 7.x

; API version
; The make file must specify which Drush Make API version it uses.
api = 2

; Drupal core.
projects[drupal][version] = 7.35
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-7.x-allow_profile_change_sys_req-1772316-28.patch
projects[drupal][patch][] = https://www.drupal.org/files/issues/drupal-1470656-26.patch
projects[drupal][patch][] = patches/govcms_force_ssl_v1.patch

; govCMS profile.
projects[govcms][version] = 2.0-alpha5
projects[govcms][patch][] = patches/govcms_govcms_govcms_tweak_enable_v1.patch

; Context Security patch
projects[govcms][patch][] = https://github.com/previousnext/govcms/commit/b20a0f17a9a90365479bd73b5a78288a76e5b726.patch

; Ctools Security patch
projects[govcms][patch][] = patches/govcms-ctools1.7.patch

; Linkit Security patch
projects[govcms][patch][] = https://github.com/previousnext/govcms/commit/d5e970513dc92c1d8a671599970effda34008ba0.patch

; Avoid mix mode for video URLs
projects[govcms][patch][] = https://github.com/previousnext/govcms/commit/dd2d245d70c78db4fe3d778a4a79ae4add9f6e34.patch

; Google Analytics Security Patch
projects[govcms][patch][] = patches/google_analytics_version-2.1.patch

; Update entity api to 7.x-1.6
projects[govcms][patch][] = patches/govcms-entity1.6.patch

; Views security update
projects[govcms][patch][] = https://github.com/previousnext/govcms/commit/cfb38c35f98fcaf0505d98046f79faf6962ae738.patch

; Webform Security patch
projects[govcms][patch][] = patches/govcms-webform1.5.patch

; Contrib modules.
projects[acsf][version] = 1.4
projects[acquia_connector][version] = 2.15
projects[clamav][version] = 1.0-alpha2
projects[clamav][patch][] = https://www.drupal.org/files/issues/clamav-scan_all_files-1630604-13.patch
projects[search_api_solr][version] = 1.6
projects[search_api_acquia][version] = 2.1
