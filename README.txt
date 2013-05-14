INSTALLATION
------------

aGov is available as a full drupal site in tgz and zip format at:

  http://drupal.org/project/agov

Those familiar with drush make can find a build-agov.make file available
in this folder that can be used to build aGov with a command such as:

drush make --prepare-install build-agov.make INSTALL_PATH


INSTALLING WITH AEGIR
---------------------
(Thanks to dman!)

I pull my makefile bases into /var/aegir/makefiles as a place to store them. This is not a convention, just a convenience. Substitute paths as you see fit...

I run drush5 as an alternative version on my hostmaster, although Aegir D6 prefers to be locked to Drush 4. I found that the drush5 build worked better, drush4 didn't recognize install profiles right. I have both available, drush (5) and drush5

# RUNNING AS aegir USER! This in infinitely important.
cd /var/aegir/makefiles
git clone --branch 7.x-1.x http://git.drupal.org/project/agov.git
drush5 make -v /var/aegir/makefiles/agov/build-agov.make /var/www/agov/dev

I have become paranoid about losing my Aegir site again [#1678528]

So right now I also run:

# Use drush5, as it drush4 may fail silently if there is a problem. drush5 tells you.
drush5 @hostmaster sql-dump --result-file=/var/aegir/backups/hostmaster-`date +'%Y%m%d'`.sql


And we can make a new aGov instance! Normally that would be on the Admin console, but I'm already <a href="http://mig5.net/content/manage-your-aegir-system-command-line#comment-822">on the commandline so lets drush it</a>...

You can go to the Hostmaster console now and import the platform if you like., If not, read on...

Scripting the import of a platform+site into Aegir without the front-end
------------------------------------------------------------------------

You don't need to do this this way, in fact it's probably better not to, but I'm setting up for some scripted roll-outs, so it's handy to know how..

Import and verify the platform.
-------------------------------

drush --root="/var/www/agov/dev" provision-save @agov7xdev --context_type='platform' --strict=0
drush @agov7xdev provision-verify
drush @hostmaster hosting-import @agov7xdev


Create and install the site instance
------------------------------------

drush provision-save @dev.agov.coders.co.nz --context_type='site' \
 --uri="dev.agov.coders.co.nz" --platform="@agov7xdev" \
 --server='@server_master' --db_server='@server_localhost' \
 --profile='agov' --client_name='admin' --strict=0
drush -v  @dev.agov.coders.co.nz provision-install
# I THINK this next step is the correct one to eventually register the new site on the hostmaster frontend.
drush @agov7xdev provision-verify
# Other lower level attempts seemed to work, but then get re-run anyway when the platform noticed the new site.


