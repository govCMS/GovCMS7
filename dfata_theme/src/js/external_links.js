/**
 * External Link detector.
 */
(function($, Drupal, window, document, undefined) {

  var current_domain = '';
  var domainRe = /https?:\/\/((?:[\w\d-]+\.)+[\w\d]{2,})/i;

  function domain(url) {
    var arr = domainRe.exec(url);
    return (arr !== null) ? arr[1] : current_domain;
  }

  function isExternalRegexClosure(url) {
    return current_domain !== domain(url);
  }

  Drupal.behaviors.dfata_theme_external_links = {
    attach: function(context, settings) {
      // Get current domain.
      current_domain = domain(location.href);

      // Find all links and apply a rel if external.
      $('a', context).each(function() {
        var $this = $(this);
        if (isExternalRegexClosure($this.attr('href'))) {
          $this.attr('rel', 'external');
        }
      })
    }
  };

})(jQuery, Drupal, this, this.document);
