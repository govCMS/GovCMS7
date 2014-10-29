# govcms drupal site
set :app_name, "govcms"
set :location, "#{app_name}.qa.previousnext.com.au"
set :application, "#{app_name}.qa.previousnext.com.au"
set :scm, 'git'
set :repository,  "git@github.com:previousnext/#{app_name}.git"
set :user, "deployer"
set :runner, "deployer"
set :branch, "master"
set :port, 2222
# set :git_enable_submodules, 1
ssh_options[:forward_agent] = true
if ENV["PNX_SSH_KEY"] != ""
  ssh_options[:keys] = ENV["PNX_SSH_KEY"]
end
set :default_stage, "dev"
set :use_sudo, false

namespace :drupal do
  desc "Symlink settings and files to shared directory. This allows the settings.php and \
    and sites/default/files directory to be correctly linked to the shared directory on a new deployment."
  task :symlink_shared do
    ["files", "private", "settings.php"].each do |asset|
      run "rm -rf #{app_path}/sites/default/#{asset} && ln -nfs #{shared_path}/#{asset} #{app_path}/sites/default/#{asset}"
    end
  end
end

namespace :govcms do
  desc "Build the GovCMS site."
  task :build do
    run "cd #{release_path} && phing build"
  end

  desc "Install the GovCMS site."
  task :install do
    run "cd #{release_path} && phing drupal:install -Ddrush.install.db_url='mysql://drupal:drupal@localhost/drupal'"
  end
end
