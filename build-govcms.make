core = 7.x
api = 2

; Include the definition for how to build Drupal core directly, including patches:
includes[] = drupal-org-core.make

; Download the govCMS install profile and recursively build all its dependencies:
projects[govcms][type] = profile
projects[govcms][version] = master
projects[govcms][download][type] = git
projects[govcms][download][branch] = master
projects[govcms][download][url] = git@github.com:govCMS/govcms-merge.git

