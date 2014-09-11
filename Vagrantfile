# -*- mode: ruby -*-
# vi: set ft=ruby :

##
# Variables.
##

box      = 'precise32'
url      = 'http://files.vagrantup.com/' + box + '.box'
hostname = 'govcms'
domain   = 'dev'
ram      = '1024'
# The ports to be forwarded from the guest to the host.
ports    = [
  { :guest => 8080, :host => 8080 },
  { :guest => 3306, :host => 3306 },
]
# These allow for puppet facts to be set. We use these for
# assigning roles.
# eg. "drupal" => "true" could setup a Drupal site.
facts    = {
  "fqdn"   => hostname + '.' + domain,
  "drupal" => "true",
  "vagrant_user"  => Process.uid,
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

  # Map the guest ports to the host.
  ports.each do |port|
    config.vm.network :forwarded_port, guest: port[:guest], host: port[:host]
  end

  # We want to cater for both Linux and Mac OS X.
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
    vb.customize ["modifyvm",     :id, "--memory", ram]
    vb.customize ["setextradata", :id, "VBoxInternal2/SharedFoldersEnableSymlinksCreate/v-root", "1"]
  end

  config.vm.provision :shell, :path => "vendor/previousnext/puppet-dev/provision-vagrant.sh"
  config.vm.provision :puppet do |puppet|
    puppet.facter         = facts
    puppet.manifests_path = "vendor/previousnext/puppet-dev"
    puppet.manifest_file  = "init.pp"
    puppet.module_path    = "vendor/previousnext/puppet-dev/modules"
  end

end
