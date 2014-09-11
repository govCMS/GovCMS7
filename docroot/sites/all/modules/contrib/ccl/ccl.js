(function ($) {

Drupal.behaviors.ccl = {
  attach: function (context, settings) {
    // This behavior attaches by ID, so is only valid once on a page.
    if ($('#ccl-add-form', context).size()) {
      $('#ccl-add-form .form-radios', context).buttonset();
    }
  }
};

})(jQuery);
