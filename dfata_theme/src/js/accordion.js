/**
 * Accordion behaviour.
 */
(function($, Drupal, window, document, undefined) {

  Drupal.behaviors.dfata_content_accordion = {
    attach: function(context, settings) {
      // Initialise the accordion for the Page Content paragraph bundle.
      if ($.fn.accordion) {
        $('.field-name-field-page-content').find('.field-items').accordion({
          header: ".field-name-field-title",
          heightStyle: "fill"
        })
      }
    }
  };

})(jQuery, Drupal, this, this.document);
