api = 2
core = 7.x
; Include the definition for how to build Drupal core directly, including patches:
includes[] = drupal-org-core.make

; Download the govCMS install profile and recursively build all its dependencies:
projects[govcms][version] = "merge"
projects[govcms][type] = "profile"
projects[govcms][download][type] = "git"
projects[govcms][download][branch] = "merge"
projects[govcms][download][url] = "git@bitbucket.org:gollyg/govcms_merge.git"
projects[govcms][patch][] = "patches/govcms_govcms_govcms_tweak_enable_v1.patch"


