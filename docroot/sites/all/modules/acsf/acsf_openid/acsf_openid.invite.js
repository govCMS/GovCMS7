// $Id$
(function ($) {

/**
 * Allow the invitation message for new users to be shown or hidden.
 */
Drupal.behaviors.acsfOpenIDInvitationMessage = {
  attach: function(context) {
    $('.form-item-invitation-message', context).once('acsf-openid-invitation-message', function () {
      // Define the show/hide text we will use below.
      var showMessageLinkText = Drupal.t('View/edit invitation message');
      var hideMessageLinkText = Drupal.t('Hide invitation message');

      // Insert the link for showing the textarea contents, and hide it
      // initially.
      var $textarea_wrapper = $(this);
      var $textarea = $textarea_wrapper.children();
      $textarea_wrapper.prepend('<a href="#" id="acsf-openid-toggle-invitation-message">' + showMessageLinkText + '</a>');
      $textarea.hide();

      // The title is visually distracting once we show the above link, so
      // display it only to screen readers.
      $('label', $textarea_wrapper).addClass('element-invisible');

      // Define functions for toggling the link.
      var showMessage = function () {
        $textarea.show();
        $(this).html(hideMessageLinkText);
        return false;
      };
      var hideMessage = function () {
        $textarea.hide();
        $(this).html(showMessageLinkText);
        return false;
      };

      // Attach handlers to the link so that clicking it toggles the textarea's
      // appearance.
      var $toggle_link = $('#acsf-openid-toggle-invitation-message', $textarea_wrapper);
      $toggle_link.toggle(showMessage, hideMessage);
    });
  }
};

})(jQuery);
