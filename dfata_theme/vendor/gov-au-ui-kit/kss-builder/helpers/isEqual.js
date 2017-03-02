/**
 * Registers the "Package Settings" Handlebars helper.
 *
 * @param {object} handlebars The global Handlebars object used by kss-node's kssHandlebarsGenerator.
 */
module.exports.register = function(handlebars) {
  handlebars.registerHelper('if_equal', function(a, b, opts) {
    if(a == b)
      return opts.fn(this);
    else
      return opts.inverse(this);
  });
};
