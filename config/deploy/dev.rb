# govcms development deployment config
set :deploy_to, "/var/www/#{app_name}.qa.previousnext.com.au"
set :branch, 'master'
role :app, "#{app_name}.qa.previousnext.com.au"
set :app_path, "#{release_path}/app"
