/**
 * Webform.js
 */
(function($, Drupal, window, document, undefined) {

  var $grid_components = null;
  var is_overflowing = null;

  // Apply a class to grid element if table exceeds overflow width.
  function component_grid_resize() {
    for (var i = 0; i < $grid_components.length; i++) {
      var $grid = $($grid_components[i]);
      var $table = $grid.find('.webform-grid');
      var has_overflow = $grid.width() < $table.width();
      if (has_overflow && !is_overflowing) {
        is_overflowing = true;
        $grid.addClass('is-overflowing');
      }
      else if (!has_overflow && is_overflowing) {
        is_overflowing = false;
        $grid.removeClass('is-overflowing');
      }
    }
  }

  Drupal.behaviors.dfata_theme_webform = {
    attach: function(context, settings) {
      // Flip the order of radio checkboxes with labels.
      // UI Kit styling only works if the label appears after.
      $('.webform-grid-option > .form-type-radio', context).each(function() {
        var $this = $(this);
        $this.append($this.children('label'));
      });

      // Grid overflow - check on resize.
      $grid_components = $('.webform-component-grid');
      $(window).unbind('resize', component_grid_resize);
      if ($grid_components.length > 0) {
        component_grid_resize();
        $(window).bind('resize', component_grid_resize);
      }
    }
  };

})(jQuery, Drupal, this, this.document);
