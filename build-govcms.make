core = 7.x
api = 2

; Include the definition for how to build Drupal core directly, including patches:
includes[] = drupal-org-core.make

; Download the govCMS install profile and recursively build all its dependencies:
projects[govcms][version] = 2.x-dev
projects[govcms][download][revision] = "c43f52e7b5792a54eb0bb16e10aaf29293fb7698"
