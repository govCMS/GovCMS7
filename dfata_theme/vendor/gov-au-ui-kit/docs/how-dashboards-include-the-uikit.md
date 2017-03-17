# How dto-dashboards include the GOV.AU UI-Kit

We want to include UI-Kit as the raw dependency in [DTO Dashboards](https://github.com/AusDTO/dto-dashboard) so we get access to Sass scope and individual JS modules and images so we can include them in any combination, extend them to suit our project or use a different version of Bourbon or Neat.

We did this by installing the module as an npm and including parts as granularly as possible.

## Installation steps

Install GOV.AU UI-Kit as an npm from the tag release:

`package.json`:

```json
deps: {
  "gov-au-ui-kit": "git@github.com:AusDTO/gov-au-ui-kit.git#1.7.4",
}
```

Next, include node_modules in Sass compile path:

`gulpfile.js`:

```javascript
var path = require('path');
var sass = require('gulp-sass');

var DIR_NPM = path.join(__dirname, 'node_modules');
var DIR_SRC_STYLES = path.join(DIR_SRC, 'styles');
var DIR_DIST_STYLES = path.join(DIR_DIST, 'stylesheets');

gulp.task('sass', function() {
  return gulp.src(DIR_SRC_STYLES + '/**/*.scss')
    .pipe(sass({
      includePaths: [
        DIR_NPM
      ]
    }).on('error', sass.logError))
    .pipe(gulp.dest(DIR_DIST_STYLES));
});
```

Next, duplicate UI-Kit's import file in our local project, make sure you save it as a partial instead of an import file (prefixed filename with `_`)

`$ dto-dashboard/lib/assets/src`

```
styles
├── main.scss
└── _vendor
    ├── bourbon
    ├── gov-au-ui-kit
    │   └── _ui-kit.scss
    └── neat
```

Finally, update the duplicate file's file paths so they make sense for our project. And include or exclude which partials we need from UI-Kit. This means we will get the ui-kit inside the Sass compilation scope so I can access variables, mixins and all the elements that UI-Kit offers.

`dto-dashboard/lib/assets/src/styles/_vendor/gov-au-ui-kit/_ui-kit.scss`:

```scss
/*

UI-Kit version: 1.7.4

*/

@import 'gov-au-ui-kit/assets/sass/vendor/entity';
//@import 'gov-au-ui-kit/assets/sass/vendor/normalize';
//@import 'gov-au-ui-kit/assets/sass//vendor/bourbon/bourbon';

//@import 'gov-au-ui-kit/assets/sass/grid-settings';
//@import 'gov-au-ui-kit/assets/sass/vendor/neat/neat';

//@import 'gov-au-ui-kit/assets/sass/variables';
//@import 'gov-au-ui-kit/assets/sass/accessibility';

//@import 'gov-au-ui-kit/assets/sass/icons';
//@import 'gov-au-ui-kit/assets/sass/colours';
//@import 'gov-au-ui-kit/assets/sass/typography';
//@import 'gov-au-ui-kit/assets/sass/grid-layout';
//@import 'gov-au-ui-kit/assets/sass/buttons';
//@import 'gov-au-ui-kit/assets/sass/links';
//@import 'gov-au-ui-kit/assets/sass/tables';
//@import 'gov-au-ui-kit/assets/sass/forms';
//@import 'gov-au-ui-kit/assets/sass/navigation';
//@import 'gov-au-ui-kit/assets/sass/lists';
//@import 'gov-au-ui-kit/assets/sass/accordions';
//@import 'gov-au-ui-kit/assets/sass/images';
//@import 'gov-au-ui-kit/assets/sass/video';
//@import 'gov-au-ui-kit/assets/sass/page-header';
//@import 'gov-au-ui-kit/assets/sass/page-footer';

//@import 'gov-au-ui-kit/assets/sass/ie';
//@import 'gov-au-ui-kit/assets/sass/print';
```

Now we can run `gulp sass` as usual and the UI-Kit will compile into our single `.css` export resource.
