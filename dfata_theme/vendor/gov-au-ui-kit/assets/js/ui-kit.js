var smoothScroll = require('smoothscroll');
var responsiveNav = require('responsive-nav');
var Velocity = require('velocity-animate');

(function (document) {

  initResponsiveNav = function(elementSelector) {
    if (document.querySelector(elementSelector)) {
      responsiveNav(elementSelector);
    }
  }

  initAccordions = function(elems) {
    for (var i = 0; i < elems.length; i++) {
      var toggle = elems[i].querySelector('.accordion-button, summary');
      var panel = elems[i].querySelector('.accordion-panel');

      if (elems[i].getAttribute('data-label')) {
        panelLabel = elems[i].getAttribute('data-label');
      } else {
        panelLabel = elems[i].className;
      }

      initToggle(elems[i], toggle, panel, panelLabel);
      initPanel(elems[i], panel, panelLabel);

    }
  }

  initToggle = function(elem, toggle, panel, label) {
    toggle.targetElem = elem;
    toggle.targetPanel = panel;
    toggle.setAttribute('aria-controls', label);
    toggle.addEventListener('click', togglePanel);
  }

  initPanel = function(elem, panel, label) {
    elem.id = label;

    if (elem.getAttribute('aria-expanded') === 'false') {
      slidePanel(panel, true);
    }
  }

  togglePanel = function(event) {
    var toggle = event.target,
        elem = event.target.targetElem,
        panel = event.target.targetPanel,
        expanded = elem.getAttribute('aria-expanded') === 'true';

    event.preventDefault();

    toggle.setAttribute('aria-expanded', expanded ? 'false' : 'true');
    elem.setAttribute('aria-expanded', expanded ? 'false' : 'true');

    slidePanel(panel, expanded);
  }

  slidePanel = function(panel, bool) {
    Velocity(panel, bool ? 'slideUp' : 'slideDown', { duration: 300 });
  }

  // Kick of the JavaScript party when the DOM is ready
  document.addEventListener('DOMContentLoaded', function() {

    initResponsiveNav('.global-nav');
    initResponsiveNav('.local-nav');
    initResponsiveNav('.local-nav-demo');

    initAccordions(document.querySelectorAll('.accordion, details'));
  });

})(document);


// This code is legacy as of v1.2
// Marked for removal in v2.0
$(document).ready(function () {
    $('.js-accordion-trigger').bind('touchstart click', function (e) {

        jQuery(this).parent().find('ul').slideToggle('fast');
        jQuery(this).find(".chevron").toggleClass('top bottom');
        // apply the toggle to the ul
        jQuery(this).parent().toggleClass('is-expanded');

        // https://www.w3.org/WAI/GL/wiki/Using_the_WAI-ARIA_aria-expanded_state_to_mark_expandable_and_collapsible_regions
        if (jQuery(this).attr('aria-expanded') == 'false') { // region is collapsed
            // update the aria-expanded attribute of the region
            jQuery(this).attr('aria-expanded', 'true');
            // move focus to the region
            jQuery(this).find('ul').focus();
            jQuery(this).find('span').text("Show menu");
        }
        else { // region is expanded
            // update the aria-expanded attribute of the region
            jQuery(this).attr('aria-expanded', 'false');
            jQuery(this).find('span').text("Hide menu");
        }

        e.preventDefault();
    });
});
