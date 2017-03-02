/**
 * Registers the "Package Settings" Handlebars helper.
 *
 * @param {object} handlebars The global Handlebars object used by kss-node's kssHandlebarsGenerator.
 */
 module.exports.register = function(handlebars) {
   var packageSettings = require('../../package.json');
   handlebars.registerHelper('package', function(value) {
     return packageSettings[value];
   });
 };
