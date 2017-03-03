/**
 * Home page slider.
 * An implementation of the Owl Carousel with custom controls.
 */
(function($, Drupal, window, document, undefined) {

  function isDesktop() {
    if ($('.mobile-expand-menu').is(':visible')) {
      return false;
    }
    else {
      return true;
    }
  }

  Drupal.behaviors.front_page_news_carousel = {
    attach: function(context, settings) {

      // Init Owl Carousel
      var owl = $(".view-latest-news.view-display-id-block_1 .view-content");
      owl.owlCarousel({
        singleItem: true,
        autoPlay: 5000,
        transitionStyle: 'fade',
        addClassActive: true,
        mouseDrag: false,
        items: 1,
        autoHeight: true,
        afterUpdate: function() {
          grabTitles();
        }
      });

      // Pause on Item Click
      $('.owl-controls').find('.owl-pagination').click(function() {
        owl.trigger('owl.stop');
        $(".owl-pause").hide();
        $(".owl-play").show();
      });

      // Create Pause and play Buttons
      $('.news-information').append(
        '<span class="owl-pause"></span><span style="display:none;" class="owl-play"></span>');

      // Functions to handle pause/play behaviour
      $(".owl-pause").click(function() {
        owl.trigger('owl.stop');
        $('.owl-pause').hide();
        $(".owl-play").show();
      });

      $(".owl-play").click(function() {
        owl.trigger('owl.play', 5000);
        $('.owl-play').hide();
        $(".owl-pause").show();
      });

      function grabTitles() {
        if (isDesktop()) {
          // Grab the Carousel Titles and place them into pagination inside a wrapper div
          var titles = [];
          $('.news-information h3').each(function(index) {
            titles[index] = $(this).text();
          });

          $('.owl-page').each(function(index) {
            $(this).html('<div class="carousel-desk-title">' + titles[index] + '</div>');
          });
        }
      }

      grabTitles();
    }
  };

})(jQuery, Drupal, this, this.document);
