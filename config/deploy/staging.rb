# govcms development deployment config
set :deploy_to, "/var/www"
set :branch, 'releases'
role :app, "#{app_name}.staging.previousnext.com.au"
set :app_path, "#{release_path}/app"
set :port, '11064'

after "deploy", "govcms:build"
after "deploy", "drupal:symlink_shared"
after "deploy", "govcms:install"
