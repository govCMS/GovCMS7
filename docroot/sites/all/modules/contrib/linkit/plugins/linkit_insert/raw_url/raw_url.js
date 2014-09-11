/**
 * @file
 * Raw HTML insert plugin for Linkit.
 */
(function ($) {
Drupal.linkit.registerInsertPlugin('raw_url',  {
  insert : function(data, settings) {
    return data.path;
  }
});
})(jQuery);
