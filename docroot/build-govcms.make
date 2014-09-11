api = 2
core = 7.x

; Include the definition for how to build Drupal core directly, including patches:
includes[core] = profiles/agov/drupal-org-core.make

; Install profile and recursively build all its dependencies:
includes[agov] = profiles/agov/drupal-org.make

;defaults[projects][subdir] = "contrib"

;projects[acquia_connector][version] = "2.14"

