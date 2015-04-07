api = 2
core = 7.x
; Include the definition for how to build Drupal core directly, including patches:
includes[] = drupal-org-core.make

; Download the govCMS install profile and recursively build all its dependencies:
projects[govcms][version] = "1.2.0-alpha5-6"
projects[govcms][download][url] = "git@github.com:govCMS/govCMS-Core.git"
projects[govcms][patch][] = "patches/govcms_govcms_govcms_tweak_enable_v1.patch"


