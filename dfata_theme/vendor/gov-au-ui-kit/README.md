# GOV.AU UI-Kit

![CircleCI build status](https://circleci.com/gh/AusDTO/gov-au-ui-kit.svg?style=shield) ![MIT license](https://img.shields.io/badge/license-MIT-brightgreen.svg) ![Current Release](https://img.shields.io/github/release/AusDTO/gov-au-ui-kit.svg?maxAge=2592000)

## What is this?

UI-Kit is 2 things:

1. a draft design guide to build an accessible standardised look and feel for GOV.AU projects: [gov-au-ui-kit.apps.staging.digital.gov.au](http://gov-au-ui-kit.apps.staging.digital.gov.au/)
 common-use [HTML templates](/examples)
2. a lean and frugal CSS & JS framework (found in `assets/`) that you can
include in your project:

**Link to precompiled minified files**

```
<link rel="stylesheet" type="text/css" href="https://gov-au-ui-kit.apps.staging.digital.gov.au/latest/ui-kit.min.css"/>
<script type="text/javascript" src="https://gov-au-ui-kit.apps.staging.digital.gov.au/latest/ui-kit.min.js"></script>
```

GOV.AU UI-Kit is currently in early draft release. You can help us build it by [contributing](CONTRIBUTING.md).

The [/docs/](https://github.com/AusDTO/gov-au-ui-kit/tree/develop/docs) folder contains draft documentation on experimental work. For example, how to install UI-Kit for use with `webpack`.

### Features

- <a href="https://necolas.github.io/normalize.css/" rel="external">Normalize</a>.
- <a href="http://bourbon.io/" rel="external">Bourbon</a>, version 4.2.7.
- <a href="http://neat.bourbon.io/" rel="external">Neat</a>, and settings for a grid framework with some good defaults.
- Basic styling for content with some good typographic coverage.
- Basic styling for UI elements (eg `input`, `label`, etc).

For a full list of features see the [CHANGELOG](CHANGELOG.md).

### Accessibility

The framework is built on a solid accessible HTML foundation. We follow a philosophy of <a href="https://en.wikipedia.org/wiki/Progressive_enhancement" rel="external">progressive enhancement</a> over <a href="https://en.wikipedia.org/wiki/Fault_tolerance" rel="external">graceful degradation</a> to produce accessible components by default.

UI Kit aims to be WCAG2 AA compliant, and AAA where possible.

We use automated testing:
- WCAG 2.0 criteria using <a href="http://squizlabs.github.io/HTML_CodeSniffer/" rel="external">HTML_CodeSniffer</a>
- HTML validation using <a href="http://validator.github.io/validator/" rel="external">Nu HTML Checker</a>.

We are working on:
- manual evaluation using <a href="http://wave.webaim.org/" rel="external">Wave by WebAIM</a>
- manual checking of page structure, content and keyboard navigation
- testing with users and assistive technologies
- an audit.

### Browser support
Read [cross browser and device support](BROWSER-SUPPORT.md) table.

The kit uses a [conditional styling mixin for specific versions of IE](https://github.com/AusDTO/gov-au-ui-kit/tree/develop/assets/sass/_ie.scss). Use this when extending the kit.

We are working on:

- automated browser testing as part of our build process
- manual testing of all CSS, JS and markup
- documenting browser support for each component.

## What this isn't

This is not yet a complete design or design system. This is the starting point that will develop with your help.

## Who is this for?

Teams building Australian Government sites. This was designed for GOV.AU teams, but we welcome use outside of federal government.

## How is this related to the Digital Service Standard?

The <a href="https://www.dto.gov.au/standard/" rel="external">Digital Service Standard</a> requires teams to <a href="https://www.dto.gov.au/standard/6-consistent-and-responsive/" rel="external">build services using common design patterns</a>. This is draft work on the framework and guidance that will eventually become the design patterns for digital content.

You should use this with the <a href="http://content-style-guide.apps.staging.digital.gov.au/" rel="external">draft <strong>Content Style Guide</strong></a> for Digital Transformation Office projects.

## Build the Guide yourself

We have a build process for the development of the framework which uses gulp on node.js.

To build it yourself, begin by installing the system dependencies:
- Node.js v5.0.0+

Install node package dependencies:

```
npm install
```

Run a build:

```
npm run-script build
```

Run a build with livereloading:

```
npm start
```

Run accessibility tests:

```
npm test
```

**Note:** Check [Pa11y's requirements](https://github.com/pa11y/pa11y#requirements) to make sure you have the necessary dependencies installed to run the automated accessibility tests.

The compiled style guide can be found at `./build/index.html` and the UI Kit CSS
at `./build/latest/ui-kit.css`.

We have automated the build, with a few additions:

- `sass-lint` for <a href="https://en.wikipedia.org/wiki/Lint_(software)" rel="external">linting</a>
- `cssnano` for <a href="http://cssnano.co/" rel="external">CSS compression</a>
- `autoprefixer` for adding <a href="https://autoprefixer.github.io/" rel="external">CSS vendor prefixes</a>
- `AusDTO/gulp-html` for <a href="https://github.com/AusDTO/gulp-html" rel="external">HTML validation</a>
- `kss` for auto-building a <a href="http://warpspire.com/kss/" rel="external">living style guide</a>

Our CI build is available as a shell script at `bin/cibuild.sh`.

### Dependencies

We use Bourbon 4.2.7. We include its `.scss` files directly rather than calling it via its node (or gem) package. Bourbon and Neat live under `/assets/sass/vendor`.

Some of the key libraries we use are:
- `gulp ^3.9.1`
- `gulp-sass ^2.3.1`
- `kss ^3.0.0-beta.14`
- `sass-lint ^1.7.0`

`^` = compatible with version (see <a href="https://docs.npmjs.com/misc/semver#caret-ranges-123-025-004" rel="external">semver</a>).

## Make GOV.AU UI-Kit better

- Contribute to our <a href="https://github.com/AusDTO/gov-au-ui-kit/issues" rel="external">GitHub issue register</a> by logging new issues and joining the discussion.
- Contribute to this repository. Please see [CONTRIBUTING.md](CONTRIBUTING.md), [Contributor Code of Conduct](code_of_conduct.md) and [our code Conventions](conventions.md), (also see <a href="http://getbem.com/" rel="external">Block Element Modifier</a>), first.
- Contact us via the DTO slack in `#guides-uikit`.

## Project goal

This framework is in active development.

Goal: build a lean and frugal CSS/SCSS framework to make building GOV.AU easier. It should:

- provide base consistency
- allow for easier rapid prototyping directly in the browser
- should not get in the way of customised design needs.

### Releases

See [RELEASING.md](RELEASING.md) and [CHANGELOG.md](CHANGELOG.md).

We aim to provide stable, usable releases at the end of each sprint.

### Deprecation

We are wary about breaking changes. We will work to ensure we will gracefully deprecate any changes that cause things to break.

### Installer/wrapper

We may create an installer wrapper (likely node-based), or release via git submodules.

## Copyright & license

Copyright Digital Transformation Office. <a href="(https://github.com/AusDTO/gov-au-ui-kit/blob/master/LICENSE" rel="external license">Licensed under the MIT license</a>.

This repository includes <a href="http://bourbon.io/" rel="external">Bourbon</a>, <a href="http://neat.bourbon.io/" rel="external">Neat</a> and <a href="https://necolas.github.io/normalize.css/" rel="external">Normalize.css</a>. All also use the MIT license.

![Australian Government Digital Transformation Office logo](https://www.dto.gov.au/images/govt-crest.png)

GOV.AU UI-Kit is maintained and funded by the <a href="https://www.dto.gov.au/" rel="external">Digital Transformation Office</a>.
