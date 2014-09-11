/**
 * @file
 * HTML Link insert plugin for Linkit.
 */
(function ($) {

Drupal.linkit.registerInsertPlugin('html_link', {
  insert : function(data) {
    var text,
    selection = Drupal.settings.linkit.currentInstance.selection;

     // Delete all attributes that are empty.
    for (name in data.attributes) {
      (data.attributes[name]) ? null : delete data.attributes[name];
    }

    if (typeof selection != 'undefined' &&
      selection.text.length >= 1) {
      text = selection.text;
    }
    else {
      text = Drupal.settings.linkit.currentInstance.linkContent;
    }

    // Use document.createElement as it is mush fasten then $('<a/>).
    return $(document.createElement('a'))
    .attr(data.attributes)
    .attr('href', data.path)
    .html(text)
    // Convert the element to a string.
    .get(0).outerHTML;
  }
});

})(jQuery);