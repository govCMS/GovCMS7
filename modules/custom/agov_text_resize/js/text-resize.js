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

      $('#resize-buttons .font-large a').click(function() {
        $('body').addClass('large-fonts');
        return false;
      });

      $('#resize-buttons .font-small a, #resize-buttons .reset a').click(function() {
        $('body').removeClass('large-fonts');
        return false;
      });
    }
};

}(jQuery));
