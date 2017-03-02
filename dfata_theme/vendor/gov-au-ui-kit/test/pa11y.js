'use strict';

const glob = require('glob'),
  path = require('path'),
  express = require('express'),
  chalk = require('chalk'),
  async = require('async'),
  pa11y = require('pa11y');

const options = {
  outputHTML: './build/**/*.html',
  pa11y: path.join(process.cwd(), 'pa11y.js'),
  host: 'localhost',
  port: 3000,
  concurrency: 2
};

const msg = {
  info: chalk.blue,
  error: chalk.red,
  success: chalk.green
};

function buildUrls(files) {
  return files.map(function(file) {
    return path.join(options.host + ':' + options.port, file);
  });
}

function htmlFiles() {
  let pattern = path.join(options.outputHTML);
  return glob.sync(pattern);
}

function errorsFromResults(results) {
  return results.filter(result => result.type === 'error');
}

function displayResults(results) {
  let errors = errorsFromResults(results);
  if (errors.length) {
    while (errors.length) {
      testErrors++;
      let error = errors.shift();
      console.log(msg.error('✘', 'Error found at ' + error.selector), '\n' + error.context + '\n' + error.message);
    }
  } else {
    console.log(msg.success('✔', 'No errors'));
  }
}

function runTest(url, done) {
  test.run(url, function(error, results) {
    console.log(msg.info('Testing page:', url));
    if (error) {
      console.log(msg.error(error));
    } else {
      displayResults(results);
      done();
    }
  });
}

function buildTestQueue() {
  let queue = async.queue(runTest, options.concurrency),
      urls = buildUrls(htmlFiles());

  console.log(msg.success('Starting tests for', urls.length, 'pages', '\n'));
  queue.drain = testsFinished(urls);
  queue.push(urls);
}

function testsFinished(urls) {
  return function() {
    console.log(msg.success('All done!', testErrors, 'errors found on', urls.length, 'pages.'));
    server.close();
  }
}

const test = pa11y(require(options.pa11y));

var testErrors = 0;

const app = express();
app.use('/build', express.static('build'));

const server = app.listen(options.port, buildTestQueue);
