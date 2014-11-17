# -*- mode: ruby -*-
# vi: set ft=ruby :

##
# Variables.
##

box      = 'pnx-ubuntu-i386'
url      = 'https://s3-ap-southeast-2.amazonaws.com/pnx-vagrant/boxes/ubuntu-12.04.3-server-i386_virtualbox.box'
hostname = 'govcms'
domain   = 'dev'
cpus     = '2'
ram      = '768'

# These allow for puppet facts to be set. We use these for
# assigning roles.
# eg. "drupal" => "true" could setup a Drupal site.
facts    = {
  "fqdn"         => hostname + '.' + domain,
  "drupal"       => "true",
  "settings_php" => "settings.local.php",
  "vagrant_user" => Process.uid,
  "docroot"      => "/vagrant/docroot",
}

##
# Configuration.
##

Vagrant.configure("2") do |config|
  config.vm.box      = box
  config.vm.hostname = hostname + '.' + domain
  config.vm.box_url  = url

  # Network configured as per bit.ly/1e0ZU1r
  if Vagrant.has_plugin?('vagrant-auto_network')
    # Network configured as per bit.ly/1e0ZU1r
    config.vm.network :private_network, :ip => "0.0.0.0", :auto_network => true
  else
    config.vm.network :private_network, :ip => "192.168.50.10"
  end

  # We want to cater for both Unix and Windows.
  if RUBY_PLATFORM =~ /linux|darwin/
    config.vm.synced_folder(
      ".",
      "/vagrant",
      :nfs => true,
      :map_uid => 0,
      :map_gid => 0,
     )
  else
    config.vm.synced_folder ".", "/vagrant"
  end

  # Virtualbox provider configuration.
  config.vm.provider :virtualbox do |vb|
    vb.customize ["modifyvm",     :id, "--cpus", cpus]
    vb.customize ["modifyvm",     :id, "--memory", ram]
    vb.customize ["modifyvm",     :id, "--natdnshostresolver1", "on"]
    vb.customize ["modifyvm",     :id, "--natdnsproxy1", "on"]
    vb.customize ["modifyvm",     :id, "--nicpromisc1", "allow-all"]
    vb.customize ["modifyvm",     :id, "--nicpromisc2", "allow-all"]
    vb.customize ["modifyvm",     :id, "--nictype1", "Am79C973"]
    vb.customize ["modifyvm",     :id, "--nictype2", "Am79C973"]
    vb.customize ["setextradata", :id, "VBoxInternal2/SharedFoldersEnableSymlinksCreate/v-root", "1"]
  end

  config.vm.provision :shell, :path => "vendor/previousnext/puppet-dev/puppet/provision-vagrant.sh"
  config.vm.provision :puppet do |puppet|
    puppet.facter         = facts
    puppet.manifests_path = "vendor/previousnext/puppet-dev"
    puppet.manifest_file  = "puppet/site.pp"
    puppet.module_path    = "vendor/previousnext/puppet-dev/puppet/modules"
  end

end
