#!/bin/sh
# Usage example: . xdebug.sh vendor/bin/behat path/to/test.feature
env PHP_IDE_CONFIG="serverName=govcms.docker.amazee.io" XDEBUG_CONFIG="idekey=PHPSTORM remote_host=host.docker.internal" $@
