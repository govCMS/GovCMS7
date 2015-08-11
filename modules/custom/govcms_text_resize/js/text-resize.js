/**
 * @file
 * This file controls accessibility functions on the theme layer.
 * Based on: http://www.acfonline.org.au/sites/all/themes/acf/js/acf.accessibility.js
 */

(function ($) {

/*
 * @function govAccessibilityTextSize
 * Controls the text resizer
 */
Drupal.behaviors.govAccessibilityTextSize = {
  attach: function (context, settings) {

      $('.font-large').click(function() {
        $('body').addClass('large-fonts');
        return false;
      });
      $('.font-small, a.reset').click(function() {
        $('body').removeClass('large-fonts');
        return false;
      });
    }
};

}(jQuery));
