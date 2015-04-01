api = 2
core = 7.x
; Include the definition for how to build Drupal core directly, including patches:
includes[] = drupal-org-core.make
; Download the govCMS install profile and recursively build all its dependencies:
projects[govcms][version] = 1.x-dev