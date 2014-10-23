/* Based on overlay-parent.js,v 1.22 2010/01/14 04:06:54 webchick */

(function ($) {

// Only act if overlay is found and we are supposed to show OpenID in overlays.
if (!Drupal.overlay) {
  return;
}

/**
 * Event handler: opens or closes the overlay based on the current URL fragment.
 *
 * @param event
 *   Event being triggered, with the following restrictions:
 *   - event.type: hashchange
 *   - event.currentTarget: document
 *
 * Overrides the same method from overlay-parent.js
 */
Drupal.overlay.eventhandlerOperateByURLFragment = function (event) {
  // If we changed the hash to reflect an internal redirect in the overlay,
  // its location has already been changed, so don't do anything.
  if ($.data(window.location, window.location.href) === 'redirect') {
    $.data(window.location, window.location.href, null);
    return;
  }

  // Get the overlay URL from the current URL fragment.
  var state = $.bbq.getState('overlay');
  if (state) {
    // Append render variable, so the server side can choose the right
    // rendering and add child frame code to the page if needed.
    var url = $.param.querystring(Drupal.settings.basePath + state, { render: 'overlay' });

    this.open(url);
    this.resetActiveClass(this.getPath(Drupal.settings.basePath + state));

    // This is the code section that extends the original overlay javascript
    // function.
    var isFactory = (state.indexOf('acsf-openid-factory/') > -1);
    if (isFactory) {
      // Ok, now we can tell the parent window we're ready.
      // @todo revisit this to use the overlay API more properly.
      $(this.inactiveFrame).addClass('overlay-active');
    }
  }
  // If there is no overlay URL in the fragment and the overlay is (still)
  // open, close the overlay.
  else if (this.isOpen && !this.isClosing) {
    this.close();
    this.resetActiveClass(this.getPath(window.location));
  }
};

})(jQuery);
