/**
 * @file
 * Plugin for inserting links with Linkit.
 */

(function ($) {

  tinymce.create('tinymce.plugins.linkit', {
    init : function(editor, url) {

      // Register commands
      editor.addCommand('mceLinkit', function() {
        if (typeof Drupal.settings.linkit === 'undefined') {
          alert(Drupal.t('Could not find the Linkit profile.'));
          return ;
        }

        // Set the editor object.
        Drupal.settings.linkit.currentInstance.editor = editor;
        // Set profile.
        Drupal.settings.linkit.currentInstance.profile = Drupal.settings.linkit.fields[editor.id].profile;

        // Set the name of the source field..
        Drupal.settings.linkit.currentInstance.source = editor.id;

        // Set the source type.
        Drupal.settings.linkit.currentInstance.helper = 'tinymce';

        // Stores the current editor selection for later restoration. This can
        // be useful since some browsers looses it's selection if a control
        // element is selected/focused inside the dialogs.
        editor.windowManager.bookmark = editor.selection.getBookmark(1);

        // Create the modal.
        Drupal.linkit.createModal();
      });

      // Register buttons
      editor.addButton('linkit', {
        title : 'Linkit',
        cmd : 'mceLinkit',
        image : url + '/images/linkit.png'
      });

      // We need the real contextmenu in order to make this work.
      if (editor && editor.plugins.contextmenu) {
        // Contextmenu gets called - this is what we do.
        editor.plugins.contextmenu.onContextMenu.add(function(th, m, e, col) {
          // Only if selected node is an link do this.
          if (e.nodeName == 'A' || !col) {
            // Remove all options from standard contextmenu.
            m.removeAll();
            th._menu.add({
              title : 'Linkit',
              cmd : 'mceLinkit',
              icon : 'linkit'
            });
            //m.addSeparator();
          }
        });
      }
    },

    getInfo : function() {
      return {
        longname : 'Linkit',
        author : 'Emil Stjerneman',
        authorurl : 'http://www.stjerneman.com',
        infourl : 'http://drupal.org/project/linkit',
        version : tinymce.majorVersion + "." + tinymce.minorVersion
      };
    }
  });

  // Register plugin
  tinymce.PluginManager.add('linkit', tinymce.plugins.linkit);

})(jQuery);