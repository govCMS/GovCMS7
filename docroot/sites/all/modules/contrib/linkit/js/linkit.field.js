/**
 * @file
 * Linkit field ui functions
 */

(function ($) {

Drupal.behaviors.linkit_field = {
  attach : function(context, settings) {
    // If there is no fields, just stop here.

    if (settings.linkit.fields == null) {
      return false;
    }

    $.each(settings.linkit.fields, function(field_name, field) {
      $('#' + field_name, context).once('linkit_field', function() {
        $('.linkit-field-' + field_name).click(function() {
          // Set profile.
          Drupal.settings.linkit.currentInstance.profile = Drupal.settings.linkit.fields[field_name].profile;

          // Set the name of the source field..
          Drupal.settings.linkit.currentInstance.source = field_name;

          // Set the source type.
          Drupal.settings.linkit.currentInstance.helper = 'field';

          // Only care about selection if the element is a textarea.
          if ($('textarea#' + field_name).length) {
            var selection =  Drupal.linkit.getDialogHelper('field').getSelection($('#' + field_name).get(0));
            // Save the selection.
            Drupal.settings.linkit.currentInstance.selection = selection;
          }

          // Suppress profile changer.
          Drupal.settings.linkit.currentInstance.suppressProfileChanger = true;

          // Create the modal.
          Drupal.linkit.createModal();

         return false;
        });
      });
    });
  }
};

/**
 * Linkit field dialog helper.
 */
Drupal.linkit.registerDialogHelper('field', {
  init : function() {},
  afterInit : function () {},

  /**
   * Insert the link into the field.
   *
   * @param {Object} link
   *   The link object.
   */
  insertLink : function(data) {
    var source = $('#' + Drupal.settings.linkit.currentInstance.source),
      field_settings = Drupal.settings.linkit.fields[Drupal.settings.linkit.currentInstance.source],

    // Call the insert plugin.
    link = Drupal.linkit.getInsertPlugin(field_settings.insert_plugin).insert(data, field_settings);

    if (typeof Drupal.settings.linkit.currentInstance.selection != 'undefined') {
      // Replace the selection and insert the link there.
      this.replaceSelection(source.get(0), Drupal.settings.linkit.currentInstance.selection, link);
    }
    else {
      // Replace the field value.
      this.replaceFieldValue(source.get(0), link);
    }

    // Link field can have a title field. If they have, we populate the title
    // field with the search result title if any.
    if (typeof field_settings.title_field != 'undefined' && typeof Drupal.settings.linkit.currentInstance.linkContent != 'undefined') {
      this.replaceFieldValue($('#' + field_settings.title_field).get(0), Drupal.settings.linkit.currentInstance.linkContent);
    }
  },

  /**
   * Get field selection.
   */
  getSelection : function(e) {
    // Mozilla and DOM 3.0.
    if ('selectionStart' in e) {
        var l = e.selectionEnd - e.selectionStart;
        return { start: e.selectionStart, end: e.selectionEnd, length: l, text: e.value.substr(e.selectionStart, l) };
    }
    // IE.
    else if(document.selection) {
        e.focus();
        var r = document.selection.createRange(),
          tr = e.createTextRange(),
          tr2 = tr.duplicate();
        tr2.moveToBookmark(r.getBookmark());
        tr.setEndPoint('EndToStart',tr2);

        if (r == null || tr == null) {
          return { start: e.value.length, end: e.value.length, length: 0, text: '' };
        }

        // For some reason IE doesn't always count the \n and \r in the length.
        var text_part = r.text.replace(/[\r\n]/g,'.'),
          text_whole = e.value.replace(/[\r\n]/g,'.'),
          the_start = text_whole.indexOf(text_part, tr.text.length);
        return { start: the_start, end: the_start + text_part.length, length: text_part.length, text: r.text };
    }
    // Browser not supported.
    else {
      return { start: e.value.length, end: e.value.length, length: 0, text: '' };
    }
  },

   /**
   * Replace the field selection.
   */
  replaceSelection : function (e, selection, text) {
    var start_pos = selection.start;
    var end_pos = start_pos + text.length;
    e.value = e.value.substr(0, start_pos) + text + e.value.substr(selection.end, e.value.length);
  },

   /**
   * Replace the field value.
   */
  replaceFieldValue : function (e, text) {
    e.value = text;
  }
});

})(jQuery);