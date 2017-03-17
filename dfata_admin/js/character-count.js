/**
 * Count characters in textarea.
 */
(function($, Drupal, window, document, undefined) {

  Drupal.behaviors.dfata_character_count = {
    attach: function(context, settings) {
      if (context == document) {
        var $textArea = $('.add-character-count');
        var $label;

        var setCharacterCount = function (count) {
          if ($label) {
            $label.find('.character-count').html('(Character count: ' + count + ')');
          }
        };

        if ($textArea.parent() && $textArea.parent().prev()) {
          $label = $textArea.parent().prev();
          $label.append('<span class="character-count" style="font-weight: normal"></span>');
          setCharacterCount($textArea.val().length);
        }

        $textArea.keyup(function(e) {
          setCharacterCount(this.value.length)
        });
      }
    }
  };

})(jQuery, Drupal, this, this.document);
