var fs = require('fs');
var path = require('path');

function loadExternalGruntSettings(path, setting_type) {
  try {
    var data = fs.readFileSync(path, 'utf8');
    var ob = JSON.parse(data);
    console.log('* Using ' + setting_type + ' Settings');
    return ob;
  }
  catch(e) {
    console.log('* ' + setting_type + ' settings not found. Using defaults.');
    return false;
  }
}

module.exports = function(grunt) {

  console.log("================================================");
  console.log("Grunt for Drupal - v2.6");
  console.log("================================================");
  var localSettings         = loadExternalGruntSettings('.local_grunt_settings.json', 'Local');
  var projectSettings       = loadExternalGruntSettings('project_grunt_settings.json', 'Project');
  var PHPCS_BIN_DIR         = localSettings.phpcs_bin || null;
  var THEME_DIR             = localSettings.theme_directory || projectSettings.theme_directory || '../';
  var MODULE_DIR            = localSettings.custom_modules_directory || projectSettings.custom_modules_directory || null;
  var PROFILE_MODULE_DIR    = localSettings.profile_modules_directory || projectSettings.profile_modules_directory || null;
  var USE_COMPASS           = localSettings.use_compass || projectSettings.use_compass || false;
  var USE_IMAGE_COMPRESSION = localSettings.use_image_compression || projectSettings.use_image_compression || false;
  var USE_PREFIXER          = localSettings.use_prefixer || projectSettings.use_prefixer || true;
  var PREFIXER_BROWSERS     = localSettings.prefixer_browsers || projectSettings.prefixer_browsers || ['last 2 versions', 'not ie <= 8'];
  var DRUPAL_VERSION        = localSettings.drupal_version || projectSettings.drupal_version || 7;
  // Get theme path
  var path_dir              = path.resolve(THEME_DIR).split(path.sep);
  var THEME_NAME            = path_dir[path_dir.length - 1];
  // Some helpful output
  console.log('* Drupal version: ' + DRUPAL_VERSION);
  console.log('* Theme: ' + THEME_NAME);
  console.log("------------------------------------------------");

  // =========================================================
  // GLOBAL CONFIG
  // =========================================================
  var REGISTERED_TASKS = [];
  var GRUNT_CONFIG = {
    pkg: grunt.file.readJSON('package.json'),
    watch: {}
  };

  // ================================================
  // JavaScript / SASS Beautifier
  // ================================================
  grunt.loadNpmTasks("grunt-jsbeautifier");
  REGISTERED_TASKS = REGISTERED_TASKS.concat(['jsbeautifier']);

  var script_files = [THEME_DIR + "src/js/**/*.js"];
  var style_files = [THEME_DIR + "src/sass/**/*.scss"];
  if (MODULE_DIR !== null) {
    script_files = script_files.concat([
      MODULE_DIR + "**/*.js"
    ]);
  }
  if (PROFILE_MODULE_DIR !== null) {
    script_files = script_files.concat([
      PROFILE_MODULE_DIR + "**/*.js"
    ]);
  }
  var jsbeautifier_files = script_files.concat(style_files);

  GRUNT_CONFIG['jsbeautifier'] = {
    files : jsbeautifier_files,
    options : {
      html: {
        braceStyle: "end-expand",
        indentChar: " ",
        indentScripts: "keep",
        indentSize: 2,
        maxPreserveNewlines: 10,
        preserveNewlines: true,
        unformatted: ["a", "sub", "sup", "b", "i", "u"],
        wrapLineLength: 0
      },
      css: {
        fileTypes: [".scss"],
        indentChar: " ",
        indentSize: 2,
        selectorSeparatorNewline: false,
        end_with_newline: true
      },
      js: {
        braceStyle: "end-expand",
        breakChainedMethods: false,
        e4x: false,
        evalCode: false,
        indentChar: " ",
        indentLevel: 0,
        indentSize: 2,
        indentWithTabs: false,
        jslintHappy: false,
        keepArrayIndentation: false,
        keepFunctionIndentation: false,
        maxPreserveNewlines: 10,
        preserveNewlines: true,
        spaceBeforeConditional: true,
        spaceInParen: false,
        unescapeStrings: false,
        wrapLineLength: 0,
        endWithNewline: true
      }
    }
  };

  GRUNT_CONFIG.watch['scripts'] = {
    files: script_files,
    tasks: ['jsbeautifier'],
    options: {
      spawn: false,
    },
  };

  GRUNT_CONFIG.watch['styles'] = {
    files: style_files,
    tasks: ['jsbeautifier'],
    options: {
      spawn: false,
    }
  };

  // ================================================
  // IMAGE OPTIMISATION
  // ================================================
  if (USE_IMAGE_COMPRESSION) {
    grunt.loadNpmTasks('grunt-contrib-copy');
    grunt.loadNpmTasks('grunt-svgmin');
    grunt.loadNpmTasks('grunt-pngmin');
    grunt.loadNpmTasks('grunt-contrib-imagemin');
    REGISTERED_TASKS = REGISTERED_TASKS.concat(['svgmin', 'pngmin', 'imagemin', 'copy']);

    GRUNT_CONFIG['svgmin'] = {
      options: {
        plugins: [{
          removeViewBox: false
        }, {
          removeUselessStrokeAndFill: false
        }]
      },
      dist: {
        files: [{
          expand: true,
          cwd: THEME_DIR + 'src/images/svg/optimise/',
          src: ['**/*.svg'],
          dest: THEME_DIR + 'dist/images/svg/'
        }]
      }
    };

    GRUNT_CONFIG['pngmin'] = {
      compile: {
        options: {
          ext: '.png',
          force: true
        },
        files: [
          {
            expand: true,
            cwd: THEME_DIR + 'src/images/png/optimise/',
            src: '**/*.png',
            dest: THEME_DIR + 'dist/images/png/',
            filter: 'isFile'
          }
        ]
      }
    };

    GRUNT_CONFIG['imagemin'] = {
      jpg: {
        files: [
          {
            expand: true,
            cwd: THEME_DIR + 'src/images/jpg/optimise/',
            src: '**/*.jpg',
            dest: THEME_DIR + 'dist/images/jpg/',
            filter: 'isFile'
          }
        ]
      }
    };

    GRUNT_CONFIG['copy'] = {
      png: {
        expand: true,
        cwd: THEME_DIR + 'src/images/png/raw/',
        src: '**',
        dest: THEME_DIR + 'dist/images/png/',
        flatten: true,
        filter: 'isFile'
      },
      svg: {
        expand: true,
        cwd: THEME_DIR + 'src/images/svg/raw/',
        src: '**',
        dest: THEME_DIR + 'dist/images/svg/',
        flatten: true,
        filter: 'isFile'
      },
      jpg: {
        expand: true,
        cwd: THEME_DIR + 'src/images/jpg/raw/',
        src: '**',
        dest: THEME_DIR + 'dist/images/jpg/',
        flatten: true,
        filter: 'isFile'
      },
    };
  }

  // ================================================
  // SCRIPT CONCAT
  // ================================================
  grunt.loadNpmTasks('grunt-contrib-concat');
  REGISTERED_TASKS = REGISTERED_TASKS.concat(['concat']);

  GRUNT_CONFIG['concat'] = {
    options: {
      separator: '\n\n',
    },
    dist: {
      src: [THEME_DIR + 'src/js/**/*.js'],
      dest: THEME_DIR + 'dist/js/script.js'
    }
  };

  GRUNT_CONFIG.watch.scripts.tasks.push('concat');

  // ================================================
  // SASS
  // ================================================
  if (USE_COMPASS) {
    grunt.loadNpmTasks('grunt-contrib-compass');
    REGISTERED_TASKS = REGISTERED_TASKS.concat(['compass']);

    GRUNT_CONFIG['compass'] = {
      dist: {
        options: {
          basePath: THEME_DIR,
          config: THEME_DIR + 'config.rb'
        }
      }
    };

    GRUNT_CONFIG.watch.styles.tasks.push('compass');
  }
  else {
    grunt.loadNpmTasks('grunt-sass');
    REGISTERED_TASKS = REGISTERED_TASKS.concat(['sass']);

    var sass_config = {
      options: {
        sourceMap: true,
        outputStyle: 'expanded'
      },
      dist: {
        files: {}
      }
    };
    sass_config.dist.files[THEME_DIR + 'dist/css/styles.css'] = THEME_DIR + 'src/sass/styles.scss';
    sass_config.dist.files[THEME_DIR + 'dist/css/custom_twitter_theme.css'] = THEME_DIR + 'src/sass/custom_twitter_theme.scss';

    GRUNT_CONFIG['sass'] = sass_config;

    GRUNT_CONFIG.watch.styles.tasks.push('sass');
  }

  // ================================================
  // Auto prefixer
  // ================================================
  if (USE_PREFIXER) {
    grunt.loadNpmTasks('grunt-postcss');
    REGISTERED_TASKS = REGISTERED_TASKS.concat(['postcss:dist']);
    console.log(THEME_DIR);

    GRUNT_CONFIG['postcss'] = {
      options: {
        map: true,
        processors: [
          require('autoprefixer')({browsers: PREFIXER_BROWSERS}),
          require('postcss-object-fit-images')
        ]
      },
      dist: {
        src: THEME_DIR + 'dist/css/styles.css'
      }
    };

    GRUNT_CONFIG.watch.styles.tasks.push('postcss:dist');
  }

  // ================================================
  // Drupal Code Sniffer
  // ================================================
  if (PHPCS_BIN_DIR !== null) {
    // Set up Grunt
    grunt.loadNpmTasks('grunt-phpcs');
    REGISTERED_TASKS = REGISTERED_TASKS.concat(['phpcs']);

    var phpcs_src_files = [];

    if (DRUPAL_VERSION == 8) {
      phpcs_src_files = [
        THEME_DIR + THEME_NAME + '.theme'
      ];
    }
    else {
      phpcs_src_files = [
        THEME_DIR + 'template.php',
        THEME_DIR + 'templates/*.php'
      ];
    }

    if (MODULE_DIR !== null) {
      phpcs_src_files = phpcs_src_files.concat([
        MODULE_DIR + '**/*.inc',
        MODULE_DIR + '**/*.install',
        MODULE_DIR + '**/*.module',
        MODULE_DIR + '**/*.php'
      ]);
    }

    if (PROFILE_MODULE_DIR !== null) {
      phpcs_src_files = phpcs_src_files.concat([
        PROFILE_MODULE_DIR + '**/*.inc',
        PROFILE_MODULE_DIR + '**/*.install',
        PROFILE_MODULE_DIR + '**/*.module',
        PROFILE_MODULE_DIR + '**/*.php'
      ]);
    }

    // Config Settings
    GRUNT_CONFIG['phpcs'] = {
      application: {
        src: phpcs_src_files
      },
      options: {
        bin: PHPCS_BIN_DIR,
        standard: 'Drupal',
        severity: 1,
        errorSeverity: 1,
        warningSeverity: 0
      }
    };

    // Watch settings
    GRUNT_CONFIG.watch['templates'] = {
      files: phpcs_src_files,
      tasks: ['phpcs'],
      options: {
        spawn: false,
      },
    };
  }

  // =========================================================
  // GRUNT SETUP
  // =========================================================
  grunt.initConfig(GRUNT_CONFIG);
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.registerTask('default', REGISTERED_TASKS);
};
