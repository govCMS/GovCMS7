# govcms development deployment config
set :deploy_to, "/var/www"
set :branch, 'master'
role :app, "#{app_name}.qa.previousnext.com.au"
set :app_path, "#{release_path}/app"
set :port, '11063'
