# govCMS
***

## Installation

### Packaged installation

govCMS exists as packaged versions on both the [Github](https://github.com/govCMS/govCMS) and [Drupal.org](https://www.drupal.org/project/govcms) project pages. These compressed archives are available in both zip and tar.gz format to download and use as needed.


### Installation from source

**Dependencies**

- [git](http://git-scm.com/)
- [composer](https://getcomposer.org/)

To develop on or patch against govCMS, the source files should be downloaded and the project built.

govCMS source may be downloaded using git

```
git clone git@github.com:govCMS/govCMS-Core.git
```

Enter the project root, and run the following commands in order:

```
cd govCMS-Core
composer install --prefer-dist
phing -f build.xml build
```

This will construct a copy of the govCMS Drupal codebase in the `docroot` directory using instructions from the govcms.make file.


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

*docroot* - The Drupal root. This can be either a directory or a symlink.
*README.md* - Project documentation written in markdown.
*composer.json* - Project specific vendor packages and repositories.
*composer.lock* - Locked in version of vendor packages. To ensure consistency across the project.
*.gitignore* - A list of files to be ignored by git. This is typically used for excluding local development modules and may create files to ignore that an IDE creates.

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


## Patching govCMS

@TODO


## Contributing to govCMS

@TODO