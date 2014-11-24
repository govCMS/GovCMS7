/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {


// To understand behaviors, see https://drupal.org/node/756722#behaviors
Drupal.behaviors.mainMenuTinyNav = {
  attach: function(context, settings) {
    $(".region-navigation .block__content > .menu").tinyNav({
      active: 'active-trail:last'
    });
    $('select.tinynav').prepend('<option value="#">Menu</option>');
  }
};

Drupal.behaviors.mainMenuSuperfish = {
  attach: function(context, settings) {

    var superfish_menu = $(".region-navigation .block__content > .menu");

    superfish_menu.addClass('sf-menu');
    superfish_menu.superfish({
      autoArrows:  false
    });
  }
};

Drupal.behaviors.responsiveSlides = {
    attach: function(context, settings) {

        $(".view-slideshow ul:not(.contextual-links)").responsiveSlides({
            "auto": false,
            "pager": true,         // Boolean: Show pager, true or false
            "pauseButton": false   // Boolean: Create Pause Button
        });

    }
};


})(jQuery, Drupal, this, this.document);
