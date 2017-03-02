'use strict';

var gulp = require('gulp'),
    sass = require('gulp-sass'),
    rename = require('gulp-rename'),
    cssnano = require('gulp-cssnano'),
    kss = require('kss'),
    sassLint = require('gulp-sass-lint'),
    autoprefixer = require('gulp-autoprefixer'),
    gitVersion = require('gulp-gitversion'),
    scssMerge = require('./lib/gulp-scss-merge.js'),
    uglify = require('gulp-uglify'),
    del = require('del'),
    runSequence = require('run-sequence'),
    connect = require('gulp-connect'),
    svg2png = require('gulp-svg2png'),
    webpack = require('webpack-stream'),
    zip = require('gulp-zip'),
    wrap = require('gulp-wrap'),
    imagemin = require('gulp-imagemin'),
    handlebars = require('gulp-compile-handlebars')
    ;

var paths = {
    assets: './assets/**/*.*',
    assetsDir: './assets',
    scssDir: './assets/sass/**/*.scss',
    scssTemplatesDir: './assets/sass/components/templates',
    kssScssDir: './kss-builder/kss-assets/*.scss',
    kssCssDir: './kss-builder/kss-assets',
    examples: './examples/*.hbs',
    examplePartialsDir: './examples/partials',
    kssBuilderDir: './kss-builder/**/*.*',
    images: './assets/img/**/*.+(png|svg|jpg)',
    scss: './assets/sass/ui-kit.scss',
    js: './assets/js/ui-kit.js',
    markdown: './*.md',
    readme: './README.md',
    outputAssets: './build/latest',
    outputCSS: './build/latest/*.css',
    outputHTML: './build'
};

var options = {
    autoprefixer: {
        browsers: ['last 2 versions', 'ie 7-10', 'iOS >= 4']
    },
    sass: {
        functions: {
            'image-url($img)': function(img) {
              var sass = require('node-sass');
              var String = sass.types.String;
              return new String('/latest/img/' + img.getValue());
            }
        },
        includePaths: [
          './node_modules'
        ]
    },
    webpack: {
        output: {
            filename: 'ui-kit.js',
        }
    },
    handlebars: {
      batch: [ paths.scssTemplatesDir, paths.examplePartialsDir ]
    }
};

gulp.task('lint', function () {
    return gulp.src([paths.scssDir, paths.kssScssDir, '!./assets/sass/vendor/**/*.scss'])
        .pipe(sassLint({
            configFile: '.sass-lint.yml'
        }))
        .pipe(sassLint.format())
        .pipe(sassLint.failOnError());
});

gulp.task('ui-kit', function () {
    gulp.start(['ui-kit.scss', 'ui-kit.js']);
});

gulp.task('ui-kit.scss', function () {
  return gulp.src(paths.scssDir)
    .pipe(sass.sync().on('error', sass.logError))
    .pipe(autoprefixer(options.autoprefixer))
    .pipe(gitVersion())
    .pipe(gulp.dest(paths.outputAssets));
});

gulp.task('ui-kit.js', function () {
    return gulp.src(paths.js)
        .pipe(webpack(options.webpack))
        .pipe(gitVersion())
        .pipe(gulp.dest(paths.outputAssets));
});

gulp.task('ui-kit.scssmerge', function () {
    return gulp.src(paths.scss)
        .pipe(scssMerge('_ui-kit.scss'))
        .pipe(gulp.dest(paths.outputAssets));
});

gulp.task('ui-kit.min', function () {
    gulp.start(['ui-kit.min.scss', 'ui-kit.min.js']);
});

gulp.task('ui-kit.min.scss', ['ui-kit.scss'], function () {
    return gulp.src([paths.outputCSS, '!./**/*.min.css'])
        .pipe(cssnano())
        .pipe(gitVersion())
        .pipe(rename({
            suffix: '.min'
        }))
        .pipe(gulp.dest(paths.outputAssets));
});

gulp.task('ui-kit.min.js', function () {
    return gulp.src(paths.js)
        .pipe(webpack({
            output: {
                filename: 'ui-kit.min.js',
            }
        }))
        .pipe(uglify())
        .pipe(gitVersion())
        .pipe(gulp.dest(paths.outputAssets));
});

gulp.task('ui-kit.img', ['svg2png'], function () {
    return gulp.src(paths.images)
        .pipe(imagemin())
        .pipe(gulp.dest(paths.outputAssets + '/img/'));
});

gulp.task('ui-kit.img.zip', ['ui-kit.img'], function () {
    return gulp.src(paths.outputAssets + '/img/**/*')
        .pipe(zip('images.zip'))
        .pipe(gulp.dest(paths.outputAssets));
});

gulp.task('svg2png', function () {
    return gulp.src(paths.assetsDir + '/img/icons/*.svg')
        .pipe(svg2png())
        .pipe(gulp.dest(paths.outputAssets + '/img/icons/'));
});

gulp.task('examples', function () {

    return gulp.src(paths.examples)
      .pipe(handlebars({}, options.handlebars))
      .pipe(rename({
        extname: '.html'
      }))
      .pipe(gulp.dest(paths.outputHTML + '/examples')).pipe(connect.reload());
});

gulp.task('markdown', function () {
    return gulp.src(paths.markdown)
        .pipe(gulp.dest(paths.outputHTML));
});

gulp.task('nginx', function () {
    return gulp.src('nginx.conf')
        .pipe(gulp.dest(paths.outputHTML));
});

gulp.task('htmlvalidate', ['examples', 'styleguide'], function (cb) {
    try {
        var validator = require('gulp-html');
        return gulp.src(['build/*.html', 'build/**/*.html'])
            .pipe(validator({'verbose': true}));
    } catch (err) {
        if (err.code === 'MODULE_NOT_FOUND') {
            console.log('WARNING: optional HTML validator not installed, to resolve run:');
            console.log('> npm install AusDTO/gulp-html');
            return cb;
        }
        else {
            throw err;
        }
    }
});

gulp.task('styleguide', ['styleguide.scss'], function () {
    var kssresult = kss({
        source: 'assets/sass',
        destination: paths.outputHTML,
        homepage: '../../README.md',
        builder: 'kss-builder'
    });
    kssresult.then(function () {
        gulp.src('./build/*.html').pipe(connect.reload());
    });

});

gulp.task('styleguide.scss', function () {
    return gulp.src(paths.kssScssDir)
        .pipe(sass(options.sass).on('error', sass.logError))
        .pipe(autoprefixer(options.autoprefixer))
        .pipe(gitVersion())
        .pipe(gulp.dest(paths.kssCssDir));
});

gulp.task('clean', function (done) {
    return del([paths.outputAssets, paths.outputHTML], done);
});

gulp.task('default', ['build']);

gulp.task('build', ['lint', 'ui-kit', 'markdown', 'examples', 'styleguide']);

gulp.task('build.prod', function (callback) {
    runSequence('clean',
        ['lint', 'nginx', 'ui-kit', 'ui-kit.min', 'ui-kit.img.zip', 'ui-kit.scssmerge', 'markdown', 'htmlvalidate'],
        callback);
});

gulp.task('watch', ['watch.build']);

gulp.task('watch.build', function () {
    gulp.watch([
            paths.assets,
            paths.examples,
            paths.readme,
            paths.kssBuilderDir,
            '!./kss-builder/kss-assets/kss.css'
        ],
        {verbose: true},
        ['build']);
});

gulp.task('serve', ['webserver', 'build', 'watch.build', 'livereload']);

gulp.task('livereload', function () {
    gulp.watch(['./build/latest/'], () => {
        gulp.src('./build/latest/**/*').pipe(connect.reload());
    });
});

gulp.task('webserver', function () {
    connect.server({
        livereload: true,
        root: 'build'
    });
});
