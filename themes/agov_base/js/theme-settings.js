/* This file adds required functionality to the theme settings page */
(function ($) {
  
  // Adds required classes to radio buttons for theming.
  Drupal.behaviors.aGovColourClasses = {
    attach:function (context, settings) {
      
      $('#edit-colour-scheme .form-type-radio', context).each(function(){
        // Get ID to use as class
        var elementName = $(this).children('input').attr('id');
        $(this).addClass(elementName);
        
      })
      
    }
  };
  
}(jQuery));