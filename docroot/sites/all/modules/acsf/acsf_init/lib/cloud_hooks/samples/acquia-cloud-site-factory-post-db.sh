#!/bin/sh
#
# Cloud Hook: post-db-copy
#
# The post-db-copy hook is run whenever you use the Workflow page to copy a
# database from one environment to another. See ../README.md for
# details.
#
# Usage: post-db-copy site target-env db-role source-env

site="$1"
target_env="$2"
db_role="$3"
source_env="$4"

# You need the URI of the site factory website in order for drush to target that
# site. Without it, the drush command will fail. The uri.php file below will
# locate the URI based on the site, environment and db role arguments.
uri=`/usr/bin/env php /mnt/www/html/$site.$target_env/hooks/acquia/uri.php $site $target_env $db_role`

# Print a statement to the cloud log.
echo "$site.$target_env: Received copy of database $db_name from $source_env."

# Retrieve a variable called "site_name" - remember to use the --uri argument!
drush5 @$site.$target_env --uri=$uri vget site_name
