/**
 * @file
 * Markdown insert plugin for Linkit.
 *
 * Notes: Markdown dont support any attributes exept "title".
 * [An example](http://example.com/ "Title")
 */
(function ($) {

Drupal.linkit.registerInsertPlugin('markdown', {
  insert : function(data) {
    var pattern = '[!text](!url!title)',
      args = {
        '!url' : data.path,
        '!title' : data.attributes.title ? ' "' + data.attributes.title + '"' : ''
      },
      selection = Drupal.settings.linkit.currentInstance.selection;

    if (typeof selection != 'undefined' &&
      selection.text.length >= 1) {
      args['!text'] = selection.text;
    }
    else {
      args['!text'] = Drupal.settings.linkit.currentInstance.linkContent;
    }

    return Drupal.formatString(pattern, args);
  }
});

})(jQuery);