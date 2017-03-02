# Including GOV.AU UI-Kit via npm

Simple guide for installing UI-Kit via npm for use with `webpack` or any build process that uses `node-sass`.

## Installation steps

Find the latest release at: [gov-au-ui-kit/releases](https://github.com/AusDTO/gov-au-ui-kit/releases)

Install via npm (substitute `1.7.6` for latest release tag):
```bash
$ npm install https://github.com/AusDTO/gov-au-ui-kit.git#1.7.6
```

#### Configuring `node-sass`:


`node-sass` exposes an option for [includePaths](https://github.com/sass/node-sass#includepaths), you want to provide the absolute path to `node_modules` to `node-sass`.

e.g.
```javascript
const sass = require('node-sass')
const path = require('path')
const nodeSassOptions = {
  includePaths: [
    path.join(__dirname, 'node_modules')
  ]
}
sass(nodeSassOptions)
```

## Consuming via webpack

Webpack's [sass-loader plugin](https://github.com/jtangelder/sass-loader) provides a helper function for including `sass` files from `node_modules`.

You can include the kit with a `~` in front of the package name.

e.g.
```scss
@import "~gov-au-ui-kit";
```


## Consuming via other build tools with node-sass

If you have added the `includePaths` to your `node-sass` options, you can import the kit via the package name

e.g.
```scss
@import "gov-au-ui-kit";
```

### Caveats

The current build doesn't expose all required images to compile the provided SASS.

A sass variable (`$gov-ui-kit-image-base-url`) has been exposed to work around this issue.

You can point it to a URL or a local copy of the assets to compile correctly.

***Note: this variable needs to come before the `@import`***

e.g.
```scss
// Point to a URL until fallback image assets are available by other means.
$gov-ui-kit-image-base-url: 'https://gov-au-ui-kit.apps.staging.digital.gov.au/latest/img/';
```
