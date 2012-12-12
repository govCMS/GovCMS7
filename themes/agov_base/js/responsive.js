// Opening jQuery wrapper. Now you can use $() instead of $.jQuery() 
(function ($) {
  
  Drupal.behaviors.augovResponsive = {
    attach: function (context, settings) {
      
      // These two actions will trigger: 1) when the pade is loaded, 2) when the window is resized
      $('body').once(function(){
        augovResponsiveClasses(); 
      })
    
      $(window).bind("smartresize", function(){
        augovResponsiveClasses();
      })
      
      // Here we use the awesome modenizr's media query to achieve cross browser media query functionality.
      function augovResponsiveClasses() {
        var layout = '';
        if (Modernizr.mq('only screen and (min-width:980px)')==true) {
          layout = 'normal';
        }           
        else if (Modernizr.mq('only screen and (min-width:740px)')==true) {
          layout = 'narrow';
        }       
        else if (Modernizr.mq('only screen and (max-width:739px)')==true) {
          layout = 'mobile';
        }
        $('body')
          .removeClass('responsive-layout-normal')
          .removeClass('responsive-layout-narrow')
          .removeClass('responsive-layout-mobile')
          .addClass('responsive-layout-' + layout);    
      }
      
        // Add a class to the body telling all it's done
        $('body').addClass('augov-responsive-processed').removeClass('augov-responsive-unprocessed');
      
      }
   };



  /**
   * This adds a few extra classes to the html element to detect ios devices
   */
  Drupal.behaviors.novaDeviceDetection = {
    attach: function (context, settings) {
      
      Modernizr.addTest('ipad', function () {
        return !!navigator.userAgent.match(/iPad/i);
      })

      Modernizr.addTest('iphone', function () {
        return !!navigator.userAgent.match(/iPhone/i);
      })

      Modernizr.addTest('ipod', function () {
        return !!navigator.userAgent.match(/iPod/i);
      })

      
    }
  };


// Closing jQuery wrapper
}(jQuery));