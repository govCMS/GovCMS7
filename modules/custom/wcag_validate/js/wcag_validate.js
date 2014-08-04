(function ($) {

  Drupal.behaviors.pnxValidate = {
    attach: function (context, settings) {

      $('#wcag_validate_link').click(function() {
        window.open("/wcag-validate-url?url=" + encodeURIComponent(window.location));
      });
    }
  };

})(jQuery);
