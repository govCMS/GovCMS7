(function ($) {

/**
 *  This file is for developers only.
 *
 *  This tests are made for the javascript functions used in GA module.
 *  These tests verify if the return values are properly working.
 *
 *  Hopefully this can be added somewhere else once Drupal core has JavaScript
 *  unit testing integrated.
 */

"use strict";

Drupal.googleanalytics.test = {};

Drupal.googleanalytics.test.assertSame = function (value1, value2, message) {
  if (value1 === value2) {
    console.info(message);
  }
  else {
    console.error(message);
  }
}

Drupal.googleanalytics.test.assertNotSame = function (value1, value2, message) {
  if (value1 !== value2) {
    console.info(message);
  }
  else {
    console.error(message);
  }
}

Drupal.googleanalytics.test.assertTrue = function (value1, message) {
  if (value1 === true) {
    console.info(message);
  }
  else {
    console.error(message);
  }
}

Drupal.googleanalytics.test.assertFalse = function (value1, message) {
  if (value1 === false) {
    console.info(message);
  }
  else {
    console.error(message);
  }
}

// Run after the documented is ready or Drupal.settings is undefined.
$(document).ready(function() {

  /**
   *  Run javascript tests against the GA module.
   */

  // JavaScript debugging
  var base_url = window.location.protocol + '//' + window.location.host;
  var base_path = window.location.pathname;
  console.dir(Drupal);

  console.group("Test 'isDownload':");
  Drupal.googleanalytics.test.assertFalse(Drupal.googleanalytics.isDownload(base_url + Drupal.settings.basePath + 'node/8'), "Verify that '/node/8' url is not detected as file download.");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isDownload(base_url + Drupal.settings.basePath + 'files/foo1.zip'), "Verify that '/files/foo1.zip' url is detected as a file download.");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isDownload(base_url + Drupal.settings.basePath + 'files/foo1.zip#foo'), "Verify that '/files/foo1.zip#foo' url is detected as a file download.");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isDownload(base_url + Drupal.settings.basePath + 'files/foo1.zip?foo=bar'), "Verify that '/files/foo1.zip?foo=bar' url is detected as a file download.");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isDownload(base_url + Drupal.settings.basePath + 'files/foo1.zip?foo=bar#foo'), "Verify that '/files/foo1.zip?foo=bar#foo' url is detected as a file download.");
  Drupal.googleanalytics.test.assertFalse(Drupal.googleanalytics.isDownload(base_url + Drupal.settings.basePath + 'files/foo2.ddd'), "Verify that '/files/foo2.ddd' url is not detected as file download.");
  console.groupEnd();

  console.group("Test 'isInternal':");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isInternal(base_url + Drupal.settings.basePath + 'node/1'), "Link '" + base_url + Drupal.settings.basePath + "node/2' has been detected as internal link.");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isInternal(base_url + Drupal.settings.basePath + 'node/1#foo'), "Link '" + base_url + Drupal.settings.basePath + "node/1#foo' has been detected as internal link.");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isInternal(base_url + Drupal.settings.basePath + 'node/1?foo=bar'), "Link '" + base_url + Drupal.settings.basePath + "node/1?foo=bar' has been detected as internal link.");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isInternal(base_url + Drupal.settings.basePath + 'node/1?foo=bar#foo'), "Link '" + base_url + Drupal.settings.basePath + "node/1?foo=bar#foo' has been detected as internal link.");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isInternal(base_url + Drupal.settings.basePath + 'go/foo'), "Link '" + base_url + Drupal.settings.basePath + "go/foo' has been detected as internal link.");
  Drupal.googleanalytics.test.assertFalse(Drupal.googleanalytics.isInternal('http://example.com/node/3'), "Link 'http://example.com/node/3' has been detected as external link.");
  console.groupEnd();

  console.group("Test 'isInternalSpecial':");
  Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isInternalSpecial(base_url + Drupal.settings.basePath + 'go/foo'), "Link '" + base_url + Drupal.settings.basePath + "go/foo' has been detected as special internal link.");
  Drupal.googleanalytics.test.assertFalse(Drupal.googleanalytics.isInternalSpecial(base_url + Drupal.settings.basePath + 'node/1'), "Link '" + base_url + Drupal.settings.basePath + "node/1' has been detected as special internal link.");
  console.groupEnd();

  console.group("Test 'getPageUrl':");
  Drupal.googleanalytics.test.assertSame(base_path + 'node/1', Drupal.googleanalytics.getPageUrl(base_url + Drupal.settings.basePath + 'node/1'), "Absolute internal URL '" +  Drupal.settings.basePath + "node/1' has been extracted from full qualified url '" + base_url + base_path + "node/1'.");
  Drupal.googleanalytics.test.assertSame(base_path + 'node/1', Drupal.googleanalytics.getPageUrl(Drupal.settings.basePath + 'node/1'), "Absolute internal URL '" +  Drupal.settings.basePath + "node/1' has been extracted from absolute url '" +  base_path + "node/1'.");
  Drupal.googleanalytics.test.assertSame('http://example.com/node/2', Drupal.googleanalytics.getPageUrl('http://example.com/node/2'), "Full qualified external url 'http://example.com/node/2' has been extracted.");
  Drupal.googleanalytics.test.assertSame('//example.com/node/2', Drupal.googleanalytics.getPageUrl('//example.com/node/2'), "Full qualified external url '//example.com/node/2' has been extracted.");
  console.groupEnd();

  console.group("Test 'getDownloadExtension':");
  Drupal.googleanalytics.test.assertSame('zip', Drupal.googleanalytics.getDownloadExtension(base_url + Drupal.settings.basePath + '/files/foo1.zip'), "Download extension 'zip' has been found in '" + base_url + Drupal.settings.basePath + "files/foo1.zip'.");
  Drupal.googleanalytics.test.assertSame('zip', Drupal.googleanalytics.getDownloadExtension(base_url + Drupal.settings.basePath + '/files/foo1.zip#foo'), "Download extension 'zip' has been found in '" + base_url + Drupal.settings.basePath + "files/foo1.zip#foo'.");
  Drupal.googleanalytics.test.assertSame('zip', Drupal.googleanalytics.getDownloadExtension(base_url + Drupal.settings.basePath + '/files/foo1.zip?foo=bar'), "Download extension 'zip' has been found in '" + base_url + Drupal.settings.basePath + "files/foo1.zip?foo=bar'.");
  Drupal.googleanalytics.test.assertSame('zip', Drupal.googleanalytics.getDownloadExtension(base_url + Drupal.settings.basePath + '/files/foo1.zip?foo=bar#foo'), "Download extension 'zip' has been found in '" + base_url + Drupal.settings.basePath + "files/foo1.zip?foo=bar'.");
  Drupal.googleanalytics.test.assertSame('', Drupal.googleanalytics.getDownloadExtension(base_url + Drupal.settings.basePath + '/files/foo2.dddd'), "No download extension found in '" + base_url + Drupal.settings.basePath + "files/foo2.dddd'.");
  console.groupEnd();

  // List of top-level domains: example.com, example.net
  console.group("Test 'isCrossDomain' (requires cross domain configuration with 'example.com' and 'example.net'):");
  if (Drupal.settings.googleanalytics.trackCrossDomains) {
    console.dir(Drupal.settings.googleanalytics.trackCrossDomains);
    Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isCrossDomain('example.com', Drupal.settings.googleanalytics.trackCrossDomains), "URL 'example.com' has been found in cross domain list.");
    Drupal.googleanalytics.test.assertTrue(Drupal.googleanalytics.isCrossDomain('example.net', Drupal.settings.googleanalytics.trackCrossDomains), "URL 'example.com' has been found in cross domain list.");
    Drupal.googleanalytics.test.assertFalse(Drupal.googleanalytics.isCrossDomain('www.example.com', Drupal.settings.googleanalytics.trackCrossDomains), "URL 'www.example.com' not found in cross domain list.");
    Drupal.googleanalytics.test.assertFalse(Drupal.googleanalytics.isCrossDomain('www.example.net', Drupal.settings.googleanalytics.trackCrossDomains), "URL 'www.example.com' not found in cross domain list.");
  }
  else {
    console.warn('Cross domain tracking is not enabled. Tests skipped.');
  }
  console.groupEnd();

});

})(jQuery);
