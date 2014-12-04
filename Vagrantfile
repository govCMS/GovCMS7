# -*- mode: ruby -*-
# vi: set ft=ruby :

##
# Variables.
##

box      = 'precise64'
url      = 'http://files.vagrantup.com/' + box + '.box'
hostname = ENV['AGOV_HOSTNAME'] || 'agov'
domain   = ENV['AGOV_DOMAIN'] || 'dev'
cpus     = ENV['AGOV_CPUS'] || '1'
ram      = ENV['AGOV_RAM'] || '768'
ip_fall  = ENV['AGOV_FALLBACK_IP'] || '192.168.50.10'

# These allow for puppet facts to be set. We use these for
# assigning roles.
# eg. "drupal" => "true" could setup a Drupal site.
facts = {
  'fqdn'          => hostname + '.' + domain,
  # We set these so we can marry up permissions.
  'vagrant_uid'   => ENV['AGOV_UID'] || Process.uid,
  'vagrant_group' => ENV['AGOV_GROUP'] || 'dialout',
}

##
# Configuration.
##

Vagrant.configure("2") do |config|
  config.vm.box      = box
  config.vm.hostname = hostname + '.' + domain
  config.vm.box_url  = url

  if Vagrant.has_plugin?('vagrant-auto_network')
    # Network configured as per bit.ly/1e0ZU1r
    config.vm.network :private_network, :ip => "0.0.0.0", :auto_network => true
  else
    config.vm.network :private_network, :ip => ip_fall
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
    config.vm.synced_folder "./../agov-build", "/vagrant"
  end

  # Virtualbox provider configuration.
  config.vm.provider :virtualbox do |vb|
    vb.customize ["modifyvm",     :id, "--cpus",                cpus ]
    vb.customize ["modifyvm",     :id, "--memory",              ram ]
    vb.customize ["modifyvm",     :id, "--natdnshostresolver1", "on" ]
    vb.customize ["modifyvm",     :id, "--natdnsproxy1",        "on" ]
    vb.customize ["modifyvm",     :id, "--nicpromisc1",         "allow-all" ]
    vb.customize ["modifyvm",     :id, "--nicpromisc2",         "allow-all" ]
    vb.customize ["modifyvm",     :id, "--nictype1",            "Am79C973" ]
    vb.customize ["modifyvm",     :id, "--nictype2",            "Am79C973" ]
    vb.customize ["setextradata", :id, "VBoxInternal2/SharedFoldersEnableSymlinksCreate/v-root", "1" ]
  end

  # Provisioners.
  config.vm.provision :shell, :path => "puppet/provision.sh"
  config.vm.provision :puppet do |puppet|
    puppet.facter = facts
    puppet.manifests_path = "puppet"
    puppet.manifest_file  = "site.pp"
    puppet.module_path    = "puppet/modules"
  end
end
