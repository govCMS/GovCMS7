# govCMS
[![CircleCI](https://circleci.com/gh/govCMS/govCMS/tree/7.x-3.x.svg?style=svg)](https://circleci.com/gh/govCMS/govCMS/tree/7.x-3.x)

**Note:**
**This release is not Acquia specific. Please continue to use 2.x release if you are in Acquia.**

## Installation

### Packaged installation

govCMS exists as packaged versions on both the [Github](https://github.com/govCMS/govCMS) and [Drupal.org](https://www.drupal.org/project/govcms) project pages. These compressed archives are available in both zip and tar.gz format to download and use as needed.

## Local development environment setup

1. Make sure that you have [Docker](https://www.docker.com/), [Pygmy](https://docs.amazee.io/local_docker_development/pygmy.html) and [Ahoy](https://github.com/ahoy-cli/ahoy)installed.
2. Checkout project repository `git clone git@github.com:govCMS/govCMS.git`
3. `ahoy up`
4. `ahoy make`
5. `ahoy install`
6. http://govcms.docker.amazee.io

This will construct a copy of the govCMS Drupal codebase in the `docroot` directory using instructions from the `govcms.make` file.

Once built, the profile files will be symlinked into `/app/profiles/govcms`.

## List of available Ahoy workflow commands:

```
   build        Build project.
   cli          Start a shell inside CLI container.
   drush        Run drush commands in the CLI service container.
   install      Install the profile.
   lint         Lint code
   login        Login to a website.
   logs         Show Docker logs.
   make         Install local dependencies.
   ps           List running Docker containers.
   pull         Pull latest docker images.
   push         Push all docker images.
   release      Push all docker images.
   restart      Restart Docker containers.
   run          Run command inside CLI container.
   stop         Stop Docker containers.
   test         Run all tests.
   test-behat   Run behat tests.
   test-phpunit Run phpunit tests.
   up           Build project.
```

## Structure

### General

- `docroot` - The Drupal root. This can be either a directory or a symlink.
- `README.md` - Project documentation written in markdown.
- `composer.json` - Project specific vendor packages and repositories.
- `composer.lock` - Locked in version of vendor packages. To ensure consistency across the project.
- `.gitignore` - A list of files to be ignored by git. This is typically used for excluding local development modules and may create files to ignore that an IDE creates.

### Behat

- `behat.yml` - Provides all project specific behat configuration. Including regions and context configuration.
- `tests/behat` - The directory where behat `*.feature` files are stored.

The ability to test a govCMS build is built into the repository with all tests run by [Circle CI](https://cirlceci.com/) able to be run locally. Any changes made should be added and committed to your local repository and the following commands run:

```
ahoy test-behat
ahoy test-phpunit
```

Individual tests may be run by specifying the target for commands:

```
ahoy test-behat -- tests/behat/features/home.feature
```

### Debugging CLI

To debug CLI commands, such as Behat tests, using XDEBUG:
1. `ahoy cli` to get into `test` container.
4. `cd tests/behat`
3. `. xdebug.sh ../../vendor/bin/behat path/to/test.feature`

## Patching govCMS

Because govCMS is a [Drupal distribution](https://www.drupal.org/documentation/build/distributions), modules and configurations are not added directly to the codebase. Rather, they are referenced within the `govcms.make` file.

Any alterations to Drupal core or contributed modules must have an associated [drupal.org](https://www.drupal.org) issue filed against the project in question. Modifications should be made directly to the project in question and patched into govCMS rather than made directly against govCMS.

It is a requirement for any patches to govCMS to pass all automated testing prior to manual review. The automated testing checks for PHP syntax, coding standards, build completion and runs behavioural tests. It is also desirable that additions to the codebase add behat tests to ensure no regressions occur once committed.

To submit a patch, the govCMS project should be forked and changes applied to a branch on the forked repository. Once all changes are applied, a pull request between govCMS/master and the branch of the fork may be created.

## Releasing govCMS
See [RELEASE.md](RELEASE.md)

## Contributing to govCMS

All contributions to govCMS are welcome. Issues and pull requests may be submitted against the govCMS project on github where they will be addressed by the govCMS team.

More information may be found in CONTRIBUTING.md.
