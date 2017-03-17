# Releasing UI Kit

This document describes the release processes and conventions for the Gov.AU Guides UI Kit.

## Versioning

Versioning will be done using [Semantic Versioning](http://semver.org/) and will using the following additional rules for version incrementation:

* Patch: Bug-fixes or small visual changes (margins, colours etc)
* Minor: release includes new features that does NOT affect existing markup or code (new features that provide additional markup can be included here)
* Major: Release includes features that require existing markup must to be changed to satisfy SASS or JS changes in the release

### Naming

Each MAJOR release will come with a code name to ease communication.

| Major Release | Codename | Description |
|----------------:|----------|--------------|
| 0.x.x | Rugby | Pre-release for GovAU projects and for preliminary feedback amongst the Australian Public Service (APS) |
| 1.x.x | Kraken | Stable release target for APS Distribution |
| 2.x.x | Boomerang | TBD |

## Deployment

Two separate deployed versions of the UI Kit will be maintained.

| Branch | Server | URL |
|--------|--------|-----|
| develop | Staging | [http://gov-au-ui-kit-staging.apps.staging.digital.gov.au/](http://gov-au-ui-kit-staging.apps.staging.digital.gov.au/) |
| master | Production | [http://gov-au-ui-kit.apps.staging.digital.gov.au/](http://gov-au-ui-kit.apps.staging.digital.gov.au/)  |

Production will always host the latest release and will be considered stable.
Staging will host the current code at the develop branch and may not necessarily be stable.

## Communications

Release and other announcements will be made via [UI Kit Announce](https://groups.google.com/a/digital.gov.au/forum/#!forum/ui-kit-announce)

## Release Process

Releases will be made using [git-flow](https://github.com/nvie/gitflow)

### Decide on a version

Before commencing the release choose a version based on the criteria described above.

### Start a release branch

Using git-flow create a release branch:

    git flow release start x.x.x # Use the actual release version

### Bump any references to the version

Make sure that wherever the version is stored or set in the code, the version now matches the version for this release.

Files impacted:

- `package.json`, line 3
- `assets/sass/ui-kit.scss`, line 3

### Ensure the changelog is up to date

Describe the version and list changes that we made (review the sprint in Jira if required).

### Commit any changes

Commit any version bump or other last minute changes.

    git commit -am "Bumped version to 0.1.4"

### Close the release branch

    git flow release finish x.x.x # Use the actual release version

### Push to Github

Ensure that you are now in the master branch and do:

    git push origin master
    git push --tags

### Create Release Notes in Github

Open the release in your browser via [UI Kit releases](https://github.com/AusDTO/gov-au-ui-kit/releases).
Click the Tags tab, locate the latest release and click "Add release notes" for that tag.

Enter detailed release notes based on the changelog. In particular, the following should be covered where appropriate:

* Upgrading from older releases (are markup changes required)
* Details of any visual changes
* Details of syntax or semantic changes
* Bug fixes
* New capabilities

### Deploy the Release

Ensure that the master branch has been deployed to the production server and that the current version is displayed somewhere on the page.

### Communicate the Release

Send an email to the [UI Kit Announce Google Group](https://groups.google.com/a/digital.gov.au/forum/#!forum/ui-kit-announce).

The email should contain the release information (copy paste from Github is fine) and where developers can access or download the latest code.

## Changelog Management

Changelogs will be kept in CHANGELOG.md and updated where appropriate. Generally, a changelog entry should form part of the acceptance criteria for a ticket.
