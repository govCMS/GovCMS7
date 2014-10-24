/**
 * @file
 * Adds smooth scrolling to TOC anchor links.
 *
 * From: Scroll window smoothly in jQuery - Animated scroll
 *       http://blog.freelancer-id.com/2009/03/26/scroll-window-smoothly-in-jquery/
 */

(function ($) {

Drupal.tocFilterScrollToOnClick = function() {
  // Make sure links still has hash.
  if (!this.hash || this.hash == '#') {
    return true;
  }

  // Make sure the href is pointing to an anchor link on this page.
  var href = this.href.replace(/#[^#]*$/, '');
  var url = window.location.toString();
  if (href && url.indexOf(href) === -1) {
    return true;
  }

  // Find hash target.
  var $a = $('a[name=' + this.hash.substring(1) + ']');

  // Make hash target is on the current page.
  if (!$a.length) {
    return true;
  }

  // Scroll to hash target
  var duration = Drupal.settings.toc_filter_smooth_scroll_duration || 'medium';
  $('html, body').animate({scrollTop: $a.offset().top}, duration);
  return false;
}

Drupal.behaviors.tocFilterSmoothScroll = {
  attach: function (context) {
    // Only map <a href="#..."> links
    $('a[href*="#"]', context).once('toc-filter').click(Drupal.tocFilterScrollToOnClick);
  }
};

})(jQuery)
