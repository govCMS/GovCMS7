(function ($) {
  Drupal.behaviors.event_log_admin = {
    attach: function (context) {
      // Hides the extra info, provides a 'click' button.
      $('.event-log-info', context).each(function (index, element) {
        $('pre', element).hide();
        var span = $('<button></button>').text(Drupal.t("show"));
        $(element).prepend(span);
        span.click(function (e) {
          $('pre', element).toggle();
          e.preventDefault();
        });
      });
    }
  }
})(jQuery);