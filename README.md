# Project overview

## Installation

### Project installation

From project root, run the following commands in this order:

* ```composer install --prefer-dist```
* ```phing``` or ```phing build```
* ```vagrant up```
* ```phing drupal:install```

If you are running it on your local machine just run:
* ```phing build```

### General installation

The following are once off setup instructions. If you have performed these on other projects you will not need to run them again.

### Composer

See https://redmine.previousnext.com.au/projects/all-in/wiki/Installing_local_dev_tools_with_composer

```
brew install composer
echo "~/.composer/vendor/bin" | sudo tee -a /etc/paths.d/composer
```

### Phing

composer global require phing/phing:~2.7

## Setup project

### Phing

As this is a phing based project 

Here is an example build.properties:

```
; local build properties

; The uri of the site.
app.uri='http://example.local:8080'
```

### Setup tools

All tools for this project are setup via the command:

```
phing
```

### Using the tools

All tasks in this project can be listed via the command:

```
phing -l
```

## Structure

### General

*app* - The Drupal root. This can be either a directory or a symlink (eg. symlink to "pressflow" dir).
*README.md* - Project documentation written in markdown.
*composer.json* - Project specific vendor packages and repositories.
*composer.lock* - Locked in version of vendor packages. To ensure consistency across the project.
*.gitignore* - A list of files to be ignored by git. This is typically used for excluding local development modules.

### Behat 

**behat.yml** - Provides all project specific behat configuration. Including regions and context configuration.
**behat.local.yml** - Local configuration to override *behat.yml*. Typically this will only be the url of the current environment.
**tests/behat** - The directory where behat .feature files are stored.
**Documentation** - Documentation for behat is available here https://redmine.previousnext.com.au/projects/pnx-docs/wiki/Behat_guide

### Phing

**build.xml** - Contains project specific configuration and tasks that can be executed across this projects team.
**build.standard.xml** - Contains common build functionality across all PNX projects.
**build.properties** - Environment specific configuration. Just like *behat.local.yml*, typically this will only assign the url of the current environment.
**build/logs** - Where CI tasks store task logs.

### Capistrano

**Capfile** - Instructions for capistrano deployments.
**config/deploy.rb** - Global capistrano configuration.
**config/deploy** - Environment specific capistrano configuration. You will see files like "dev.rb", "staging.rb" or "prod.rb". These are a good indication of what environments require capistrano deployments.

### Skipfish

You can run basic vulnerability tests against the project using the skipfish tool. The phing targets require you to install a few tools first, though:

```
brew install skipfish
brew install coreutils
```

And now you can run the scans. Note this may take over an hour, depending on the size of the site!

```
phing skipfish
```
