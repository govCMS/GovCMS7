/**
 * Builds a nested accordion widget.
 *
 * Invoke on an HTML list element with the jQuery plugin pattern.
 * - For example, $('.menu').drupalNavbarMenu();
 */

(function ($, Drupal) {

"use strict";

/**
 * Store the open menu tray.
 */

  $.fn.drupalNavbarMenu = function (options) {

    // Merge options onto defaults.
    var settings = $.extend({}, {
      twisties: true,
      activeTrail: true,
      listLevels: true
    }, options);

    var ui = {
      'handleOpen': Drupal.t('Extend'),
      'handleClose': Drupal.t('Collapse')
    };
    /**
     * Handle clicks from the disclosure button on an item with sub-items.
     *
     * @param {Object} event
     *   A jQuery Event object.
     */
    function toggleClickHandler (event) {
      var $toggle = $(event.target).filter('.navbar-handle');
      if ($toggle.length) {
        var $item = $toggle.closest('li');
        // Toggle the list item.
        toggleList($item);
        // Close open sibling menus.
        var $openItems = $item.siblings().filter('.open');
        toggleList($openItems, false);
      }
    }
    /**
     * Toggle the open/close state of a list is a menu.
     *
     * @param {jQuery} $item
     *   The li item to be toggled.
     *
     * @param {Boolean} switcher
     *   A flag that forces toggleClass to add or a remove a class, rather than
     *   simply toggling its presence.
     */
    function toggleList ($item, switcher) {
      var $toggle = $item.children('.navbar-box').children('.navbar-handle');
      switcher = (typeof switcher !== 'undefined') ? switcher : !$item.hasClass('open');
      // Toggle the item open state.
      $item.toggleClass('open', switcher);
      // Twist the toggle.
      $toggle.toggleClass('open', switcher);
      // Adjust the toggle text.
      $toggle
        .find('.action')
        // Expand Structure, Collapse Structure
        .text((switcher) ?  ui.handleClose : ui.handleOpen);
    }
    /**
     * Wrap menu links is standardized markup.
     *
     * Items with sub-elements have a list toggle attached to them. Menu item
     * links and the corresponding list toggle are wrapped with in a div
     * classed with .navbar-box. The .navbar-box div provides a positioning
     * context for the item list toggle twisty.
     *
     * @param {jQuery} $menu
     *   The root of the menu to be initialized.
     */
    function processMenuLinks ($menu, settings) {
      // Initialize items and their links.
      $menu
        .find('li > a, li > span')
        .once('navbar-menu')
        .addClass('navbar-menu-item')
        .wrap('<div class="navbar-box">');
        // Add a handle to each list item if it has a menu.

      if (settings.twisties) {
        var options = {
          'class': 'navbar-icon navbar-handle',
          'action': ui.handleOpen,
          'text': ''
        };
        $menu
          .find('li')
          .each(function (index, element) {
            var $item = $(element);
            var $menus = $item.children('ul.menu').once('navbar-menu');
            if ($menus.length) {
              var $box = $item.children('.navbar-box');
              options.text = Drupal.t('@label', {'@label': $box.find('a').text()});
              $item
                .addClass('navbar-twisty')
                .children('.navbar-box')
                .append(Drupal.theme('navbarMenuItemToggle', options));
            }
          });
      }
    }
    /**
     * Adds a level class to each list based on its depth in the menu.
     *
     * This function is called recursively on each sub level of lists elements
     * until the depth of the menu is exhausted.
     *
     * @param {jQuery} $lists
     *   A jQuery object of ul elements.
     *
     * @param {Integer} level
     *   The current level number to be assigned to the list elements.
     */
    function markListLevels ($lists, level) {
      level = (!level) ? 1 : level;
      $lists = $lists.children('li')
        .addClass('navbar-level-' + level)
        // Retrieve child menus.
        .children('ul');
      if ($lists.length) {
        markListLevels($lists, level + 1);
      }
    }
    /**
     * On page load, open the active menu item.
     *
     * Marks the trail of the active link in the menu back to the root of the
     * menu with .active-trail.
     *
     * @param {jQuery} $menu
     *   The root of the menu.
     */
    function openActiveItem ($menu) {
      var pathname = location.pathname;
      // Get all menu items that start with the location path.
      var $pathItem = $menu.find('a[href^="' + pathname + '"]');

      // Clear any existing menu trails.
      $menu.find('.navbar-active, .navbar-active-trail').removeClass('navbar-active navbar-active-trail');
      /**
       * Adds the navbar-active class active menu item.
       *
       * In addition a navbar-active-trail class is added to all parent menu
       * list items.
       *
       * @param jQuery $pathItem
       *   A jQuery object of the active menu item.
       */
      function markItemTrail ($pathItem) {
        $pathItem.addClass('navbar-active');
        var $activeTrail = $pathItem.parentsUntil('.navbar-root', 'li').addClass('navbar-active-trail');
        toggleList($activeTrail, true);
      }

      if ($pathItem.length) {
        // If the path yields more than one match, try to narrow the items down
        // by the params and hash.
        if ($pathItem.length > 1) {
          for (var i = 0, aspects = ['', location.search, location.hash, (location.search + location.hash)], len = aspects.length; i < len; i++) {
            $pathItem = $menu.find('a[href="' + pathname + aspects[i] + '"]');
            if ($pathItem.length === 1) {
              break;
            }
          }
        }
        if ($pathItem.length === 1) {
          markItemTrail($pathItem);
        }
      }
    }
    // Return the jQuery object.
    return this.each(function (selector) {
      var $menu = $(this);
      var rootNotProcessed = $menu.once('navbar-menu');
      if (rootNotProcessed.length) {
        $menu
          .addClass('navbar-menu-root navbar-root')
          .on('click.navbar', toggleClickHandler);
      }
      // Process components of the menu.
      processMenuLinks($menu, settings);
      // Add a menu level class to each menu item.
      if (settings.listLevels) {
        markListLevels($menu);
      }
      // Restore previous and active states.
      if (settings.activeTrail) {
        openActiveItem($menu);
      }
    });
  };

  /**
   * A toggle is an interactive element often bound to a click handler.
   *
   * @return {String}
   *   A string representing a DOM fragment.
   */
  Drupal.theme.navbarMenuItemToggle = function (options) {
    return '<button class="' + options['class'] + '"><span class="action">' + options.action + '</span><span class="label">' + options.text + '</span></button>';
  };

}(jQuery, Drupal));
