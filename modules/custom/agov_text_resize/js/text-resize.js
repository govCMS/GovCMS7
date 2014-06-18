/*
 * @function govAccessibilityTextSize
 * Controls the text resizer
 */
(function ($) {
Drupal.behaviors.govAccessibilityTextSize = {
  attach: function (context, settings) {
    $('a.font-large').click(function() {
      $('body').addClass('large-fonts');
      return false;
    });

    $('a.font-small ,a.reset').click(function() {
      $('body').removeClass('large-fonts');
      return false;
    });
  }
};

}(jQuery));
