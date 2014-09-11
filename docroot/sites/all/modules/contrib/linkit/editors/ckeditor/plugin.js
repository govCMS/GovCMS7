/**
 * @file
 * Plugin for inserting links with Linkit.
 */

(function ($) {

  CKEDITOR.plugins.add( 'linkit', {

    requires : [ 'link' ],

    init: function( editor ) {

      // Get the major CKeditor verison.
      // We do not care about minor versions.
      var version = parseInt(CKEDITOR.version);

      // Add Button.
      editor.ui.addButton( 'linkit', {
        label: 'Linkit',
        command: 'linkit',
        icon: this.path + 'linkit.png'
      });

      // Add Command.
      editor.addCommand( 'linkit', {
        // FOR ACF in ckeditor 4.1+, allow everything.
        allowedContent: 'a[*]{*}(*)',
        exec : function () {
          if (typeof Drupal.settings.linkit === 'undefined') {
            alert(Drupal.t('Could not find the Linkit profile.'));
            return ;
          }

          // Set the editor object.
          Drupal.settings.linkit.currentInstance.editor = editor;
          // Set profile.
          Drupal.settings.linkit.currentInstance.profile = Drupal.settings.linkit.fields[editor.name].profile;
          // Set the name of the source field.
          Drupal.settings.linkit.currentInstance.source = editor.name;
          // Set the source type.
          Drupal.settings.linkit.currentInstance.helper = 'ckeditor';

          var selection = editor.getSelection(),
            element = null;

          // If we have selected a link element, we what to grab its attributes
          // so we can inserten them into the Linkit form in the  dialog.
          if ((element = CKEDITOR.plugins.link.getSelectedLink(editor)) && element.hasAttribute('href')) {
            selection.selectElement(element);
          }
          else {
            element = null;
          }

          // Save the selection.
          Drupal.settings.linkit.currentInstance.selection = selection;

          // Lock the selecton for IE.
          if (CKEDITOR.env.ie && typeof selection !== 'undefined') {
            selection.lock();
          }

          // Save the selected element.
          Drupal.settings.linkit.currentInstance.selectedElement = element;

          // Create the modal.
          Drupal.linkit.createModal();
        }
      });

      // If the "menu" plugin is loaded, register the menu items.
      if (editor.addMenuItems) {
        // Use the default link menu group weight and subtract one.
        var defaultMenuGroup = editor._.menuGroups.link;
        editor.addMenuGroup("Linkit", defaultMenuGroup - 1);

        editor.addMenuItems({
          linkit: {
            label: 'Linkit',
            command: 'linkit',
            icon: this.path + 'linkit.png',
            group: 'Linkit',
            order: 0
          }
        });

        // Remove the default link option.
        editor.removeMenuItem('link');
      }

      // If the "contextmenu" plugin is loaded, register the listeners.
      if (editor.contextMenu) {
        editor.contextMenu.addListener(function(element, selection) {
          if (!element || element.isReadOnly() || (selection.getSelectedText().length < 1 && !element.is('a'))) {
            return null;
          }

          return {linkit: CKEDITOR.TRISTATE_OFF};
        });
      }

      // Add a shortcut. Only CKeditor version 4 has this function.
      if (version >= 4) {
        editor.setKeystroke( CKEDITOR.CTRL + 76 /*L*/, 'linkit' );
      }

      // Add event listener.
      editor.on( 'doubleclick', function( evt ) {
        // Delete the default link dialog.
        delete evt.data.dialog;

        var element = CKEDITOR.plugins.link.getSelectedLink( editor ) || evt.data.element;
        if ( !element.isReadOnly() ) {
          if ( element.is( 'a' ) ) {
            editor.getSelection().selectElement( element );
            if (version >= 4) {
              editor.commands.linkit.exec();
            }
            else if(version == 3) {
              editor._.commands.linkit.exec();
            }
          }
        }
      });

      // Register an extra fucntion, this will be used in the modal.
      editor._.linkitFnNum = CKEDITOR.tools.addFunction( insertLink, editor );
    }
  });

  /**
   * Create or update a link element in the editor.
   */
  function insertLink(data, editor) {
    var selection = editor.getSelection();

    data.path = CKEDITOR.tools.trim(data.path);
    // Browser need the "href" for copy/paste link to work. (CKEDITOR ISSUE #6641)
    data.attributes['data-cke-saved-href'] = data.path;

    if (!Drupal.settings.linkit.currentInstance.selectedElement) {
      // We have not selected any link element so lets create a new one.
      var range = selection.getRanges(1)[0];
      if (range.collapsed) {
        var content = (Drupal.settings.linkit.currentInstance.linkContent) ? Drupal.settings.linkit.currentInstance.linkContent : data.path;
        var text = new CKEDITOR.dom.text(content , editor.document );
        range.insertNode(text);
        range.selectNodeContents(text);
      }

      // Delete all attributes that are empty.
      data.attributes.href = data.path;
      for (name in data.attributes) {
        data.attributes[name] ? null : delete data.attributes[name];
      }
      // Apply style.
      var style = new CKEDITOR.style({element : 'a', attributes : data.attributes});
      style.type = CKEDITOR.STYLE_INLINE;
      style.applyToRange(range);
      range.select();
    }
    else {
      var element = Drupal.settings.linkit.currentInstance.selectedElement;
      // We are editing an existing link, so just overwrite the attributes.
      element.setAttribute('href', data.path);
      element.setAttribute('data-cke-saved-href', data.path);
      for (name in data.attributes) {
        data.attributes[name] ?
          element.setAttribute(name, data.attributes[name]) :
          element.removeAttribute(name);
      }
      selection.selectElement( element );
    }

    // Unlock the selection.
    if (CKEDITOR.env.ie && typeof selection !== 'undefined') {
      selection.unlock();
    }
  }

})(jQuery);
