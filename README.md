# govCMS

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
git clone git@github.com:govCMS/govCMS.git
```

Enter the project root, and run the following commands in order:

```
cd <project_directory>
composer install --prefer-dist --working-dir=build
build/bin/phing -f build/phing/build.xml build
```

This will construct a copy of the govCMS Drupal codebase in the `docroot` directory using instructions from the govcms.make file.



## Structure

### General

- **docroot** - The Drupal root. This can be either a directory or a symlink.
- **README.md** - Project documentation written in markdown.
- **build** - Project specific files for building and testing govCMS.
- **composer.json** - Project specific vendor packages and repositories.
- **composer.lock** - Locked in version of vendor packages. To ensure consistency across the project.
- **.gitignore** - A list of files to be ignored by git. This is typically used for excluding local development modules and may create files to ignore that an IDE creates.

### Behat

- **behat.yml** - Provides all project specific behat configuration. Including regions and context configuration.
- **behat.local.yml** - Local configuration to override *behat.yml*. Typically this will only be the url of the current environment.
- **tests/behat** - The directory where behat .feature files are stored.

The *behat.local.yml* file is provided empty and ignored from the repository so changes can be made to run behat in the local environment. The structure of the file follows that of *behat.yml*, to set the local target URL to *http://govcms.local/* for behat, the following may be placed in *behat.local.yml*:

```
# Local behat settings.
default:
  extensions:
    Behat\MinkExtension:
      base_url: http://govcms.local/
```

Behat parameters may also be added by altering the BEHAT_PARAMS variable. This will only affect direct behat runs, rather than those run through Phing.

```
export BEHAT_PARAMS='{"extensions" : {"Behat\\MinkExtension" : {"base_url" : "http://govcms.local/"}}}'
```

### Phing

- **build.xml** - Contains project specific configuration and tasks that can be executed across this projects team.
- **build.properties** - Environment specific configuration. Just like *behat.local.yml*, typically this will assign the url of the current environment. 

The variables that Phing uses are configured at the top of build.xml. If there are alterations to these parameters to allow Phing to run locally, these may be placed in the *build.properties* file. This file is ignored from git so local modifications will not be committed. To alter the base URL for the Drupal site the following may be added to *build.properties*.

```
; local build properties

; The uri of the site.
drupal.base_url='http://govcms.local/'

; The database settings.
; db.host=DB_HOST
; db.name=DB_NAME
; db.username=DB_USER
; db.password=DB_PASS
; db.port=DB_PORT
```

If you are making changes to the make file, you can tell the build process to build from your local make file, instead of the one in the profile repository.

From the build/phing folder:

```
../bin/phing build:no-clean
```

## Testing govCMS
The ability to test a govCMS build is built into the repository with all tests run by [Travis CI](https://travis-ci.com/) able to be run locally. Any changes made should be added and committed to your local repository and the following commands run:

```
phing -f build/phing/build.xml build
phing -f build/phing/build.xml run-tests
```

Individual tests may be run by specifying the target for Phing. If just the behat tests need to be run, the target can be changed:

```
phing -f build/phing/build.xml test:behat
```

All tasks in this project can be listed via the command:

```
phing -f build/phing/build.xml -l
```


## Patching govCMS

Because govCMS is a [Drupal distribution](https://www.drupal.org/documentation/build/distributions), modules and configurations are not added directly to the codebase. Rather, they are referenced within the govcms.make file.

Any alterations to Drupal core or contributed modules must have an associated [drupal.org](https://www.drupal.org) issue filed against the project in question. Modifications should be made directly to the project in question and patched into govCMS rather than made directly against govCMS.

It is a requirement for any patches to govCMS to pass all automated testing prior to manual review. The automated testing checks for PHP syntax, coding standards, build completion and runs behavioural tests. It is also desirable that additions to the codebase add behat tests to ensure no regressions occur once committed.

To submit a patch, the govCMS project should be forked and changes applied to a branch on the forked repository. Once all changes are applied, a pull request between govCMS/master and the branch of the fork may be created.


## Contributing to govCMS

All contributions to govCMS are welcome. Issues and pull requests may be submitted against the govCMS project on github where they will be addressed by the govCMS team.

More information may be found in CONTRIBUTING.md.
