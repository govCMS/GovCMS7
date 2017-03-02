/*
 https://github.com/arcxyz/gulp-scss-merge

 Copyright (c) 2016 Alejandro Rodríguez

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 */

const through = require('through2'),
  gutil = require('gulp-util'),
  fs = require('fs'),
  Path = require('path'),
  PluginError = gutil.PluginError;

// Plugin Constants
const PLUGIN_NAME = 'gulp-scss-merge';
// RegExp to get the import path
const IMPORTS_REGEX = /(?:@(?:\bimport\b).)(?:[\"|\'](.*)[\"|\'])(?:\;)/gm;

/**
 * Take a stream and resolve all the scss imports based on its own path
 *
 * @param {string} [fileName] - Name of the output file
 *
 * @return {stream} Stream with all the @imports resolved
 */
function gulpScssMerge(fileName) {

  /**
   * Synchronous function that returns the content of a file
   *
   * @param {string} filePath - Path to a file
   *
   * @returns {string} The content of the file
   */
  function getFileContent(filePath) {
    // I need more tests to read the file Asynchronously
    // it break some @imports on our setup.
    var content = fs.readFileSync(filePath, 'utf8');

    if(content.indexOf('@import') >= 0) {
      content = getImports(content, filePath);
    }
    return content;
  }

  /**
   * Return the absolute url of a scssImport based on
   * the parent path and the @import line on the parent
   *
   * @param {string} scssImport - The import declaration on the scss file
   * @param {string} path - Path of the file that contains the @import
   *
   * @returns {string} Path to the @import
   */
  function getImportPath(scssImport, path) {
    // If the input path comes also with a file name
    // take only the directory
    path = Path.parse(path).ext === '.scss'
      ? Path.parse(path).dir
      : path;

    // Join the path to the parent file with the dirname
    // of the import and the resolved filename (with .scss)
    return Path.parse(scssImport).ext === '.scss'
      ? Path.join(path, Path.dirname(scssImport), Path.basename(scssImport))
      : Path.join(path, Path.dirname(scssImport), '_' + Path.basename(scssImport) + '.scss');
  }

  /**
   * Takes a content with @import's and replace it with the content of the
   * import
   *
   * @param {string} content - Scss file content with or without @imports
   * @param {string} filePath - Path to the file containing the @imports
   *
   * @returns {string} The content string with the resolved @imports
   */
  function getImports(content, filePath) {
    // Match all the @imports in the content param
    var match = IMPORTS_REGEX.exec(content);

    var imports = [];
    // Walk through all RegExp matches and store groups
    // in the imports array
    while(match != null) {
      imports.push({
        lineContent: match[0],
        filePath   : getImportPath(match[1], filePath)
      });

      match = IMPORTS_REGEX.exec(content);
    }

    // For each @import found replace the @import line
    // with the resolved @import content
    imports.forEach(function(line) {
      content = content.replace(line.lineContent, getFileContent(line.filePath));
    });

    return content;
  }

  // Creating a stream through which each file will pass
  return through.obj(function(file, enc, cb) {
    if(file.isNull()) {
      // return empty file
      return cb(null, file);
    }
    if(file.isBuffer()) {
      file.contents = new Buffer(getImports(file.contents.toString(), file.base));
      file.path = Path.join(Path.dirname(file.path), fileName);
    }
    if(file.isStream()) {
      // I need to test streams to make sure that it works.
      throw new PluginError(PLUGIN_NAME, 'Streams not supported');
    }

    cb(null, file);

  });

}

module.exports = gulpScssMerge;