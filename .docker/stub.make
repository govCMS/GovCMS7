core = 7.x
api = 2

; Include the definition for how to build Drupal core directly.
includes[] = drupal-org-core.make

; Download the govCMS install profile and build all its dependencies.
projects[govcms][type] = profile
projects[govcms][download][type] = copy
projects[govcms][download][url] = "/tmp/src"
