/**
 * @file
 * Linkit dashboard functions
 */

(function ($) {

Drupal.behaviors.linkitDashboard = {
  attach: function (context, settings) {
    // Bind the insert link button.
    $('.linkit-insert', context).once('linkit-insert', function() {
      $('.linkit-insert', context).click(function() {
        // Call the insertLink() function.
        Drupal.linkit.getDialogHelper(Drupal.settings.linkit.currentInstance.helper).insertLink(Drupal.linkit.getLink());

        // Close the dialog.
        Drupal.linkit.modalClose();
        return false;
      });
    });

    // Bind the close link.
    $('#linkit-cancel', context).once('linkit-cancel', function() {
      $('#linkit-cancel', context).bind('click', Drupal.linkit.modalClose);
    });

    // Run the validation if the path field is populated directly.
    $('#edit-linkit-path', context).keyup(function(){
      Drupal.linkit.requiredFieldsValidation();
    });

    $(".ui-dialog-titlebar").show();

    // Run required field validation.
    Drupal.linkit.requiredFieldsValidation();

    if (!Drupal.settings.linkit.currentInstance.suppressProfileChanger) {
      // Make the profile changer
      Drupal.linkit.profileChanger(context);
    }
    if (Drupal.settings.linkit.IMCEurl && !$('#linkit-imce', context).length) {
      var $imceButton = $('<input />')
        .attr({type: 'button', id: 'linkit-imce', name: 'linkit-imce'})
        .addClass('form-submit')
        .val(Drupal.t('Open file browser'))
        .insertAfter($('.form-item-linkit-search', context))
        .click(function(e) {
          e.preventDefault();
          Drupal.linkit.openFileBrowser();
        });
    }
  }
};

/**
 * Check for mandatory fields in the form and disable for submissions
 * if any of the fields are empty.
 */
Drupal.linkit.requiredFieldsValidation = function() {
  var allowed = true;
  $('#linkit-modal .required').each(function() {
    if (!$(this).val()) {
      allowed = false;
      return false;
    }
  });
  if (allowed) {
    $('#linkit-modal .linkit-insert')
      .removeAttr('disabled')
      .removeClass('form-button-disabled');
  }
  else {
    $('#linkit-modal .linkit-insert')
      .attr('disabled', 'disabled')
      .addClass('form-button-disabled');
  }
};

/**
 * Open the IMCE file browser
 */
Drupal.linkit.openFileBrowser = function () {
  window.open(decodeURIComponent(Drupal.settings.linkit.IMCEurl), '', 'width=760,height=560,resizable=1');
};

/**
 * When a file is inserted through IMCE, this function is called.
 * See IMCE api for details.
 *
 * @param file
 *   The file object that was selected inside IMCE
 * @param win
 *   The IMCE window object
 */
Drupal.linkit.IMCECallback = function(file, win) {
  Drupal.linkit.populateFields({
     path: win.imce.decode(Drupal.settings.basePath +
         Drupal.settings.linkit.publicFilesDirectory + '/' + file.relpath)
  });
  win.close();
};

/**
 * Populate fields on the dashboard.
 *
 * @param link
 *   An object with the following properties (all are optional):
 *   - path: The anchor's href.
 *   - attributes: An object with additional attributes for the anchor element.
 */
Drupal.linkit.populateFields = function(link) {
  link = link || {};
  link.attributes = link.attributes || {};

  $('#linkit-modal .linkit-path-element').val(link.path);

  $.each(link.attributes, function(name, value) {
    $('#linkit-modal .linkit-attributes .linkit-attribute-' + name).val(value);
  });

  // Run required field validation.
  Drupal.linkit.requiredFieldsValidation();
};

/**
 * Retrieve a link object by extracting values from the form.
 *
 * @return
 *   The link object.
 */
 Drupal.linkit.getLink = function() {
    var link = {
      path: $('#linkit-modal .linkit-path-element ').val(),
      attributes: {}
    };
    $.each(Drupal.linkit.additionalAttributes(), function(f, name) {
     link.attributes[name] = $('#linkit-modal .linkit-attributes .linkit-attribute-' + name).val();
    });
  return link;
};

/**
 * Retrieve a list of the currently available additional attributes in the
 * dashboard. The attribute "href" is excluded.
 *
 * @return
 *   An array with the names of the attributes.
 */
Drupal.linkit.additionalAttributes = function() {
  var attributes = [];
  $('#linkit-modal .linkit-attributes .linkit-attribute').each(function() {
    // Remove the 'linkit_' prefix.
    attributes.push($(this).attr('name').substr(7));
  });
  return attributes;
};

Drupal.linkit.profileChanger = function(context) {
  $('#linkit-profile-changer > div.form-item', context).once('linkit-change-profile', function() {
    var target = $(this);
    var toggler = $('<div id="linkit-profile-changer-toggler"></div>')
    .html(Drupal.t('Change profile'))
    .click(function() {
      target.slideToggle();
    });
    $(this).after(toggler);
  });

  $('#linkit-profile-changer .form-radio', context).each(function() {
    var id = $(this).attr('id');
    var profile = $(this).val();
    if (typeof Drupal.ajax[id] != 'undefined') {
      // @TODO: Jquery 1.5 accept success setting to be an array of functions.
      // But we have to wait for jquery to get updated in Drupal core.
      // In the meantime we have to override it.
      Drupal.ajax[id].options.success = function (response, status) {
        if (typeof response == 'string') {
          response = $.parseJSON(response);
        }

        // Update the autocomplete url.
        Drupal.settings.linkit.currentInstance.autocompletePathParsed = Drupal.settings.linkit.autocompletePath.replace('___profile___', profile);

        // Call the ajax success method.
        Drupal.ajax[id].success(response, status);
        $('#linkit-profile-changer > div.form-item').slideToggle();
      };
    }
  });
};

Drupal.behaviors.linkitSearch = {
  attach: function(context, settings) {

    $('.linkit-search-element').once('linkit-search', function() {
      // Create a synonym for this to reduce code confusion.
      var searchElement = $('.linkit-search-element');
      var callbacks = {
        constructURL: function(path, search) {
          return path + encodeURIComponent(search);
        },

        insertSuggestionList: function($results, $input) {
          var top = $input.position().top + $input.outerHeight() - 5;

          $results.width($input.outerWidth()).css({
            position: 'absolute',
            left: $input.position().left,
            top: top,
            // High value because of other overlays like
            // wysiwyg fullscreen (TinyMCE) mode.
            zIndex: 211000,
            maxHeight: $(window).height() - (top + 20)
          })
          .hide()
          .insertAfter($input);
        },

        select: function(result) {
          if (typeof result == 'undefined') {
            return false;
          }
          // Only change the link text if it is empty.
          if (typeof result.disabled != 'undefined' && result.disabled) {
            return false;
          }

          Drupal.linkit.populateFields({
            path: result.path
          });

          // Store the result title (Used when no selection is made by the user).
          Drupal.settings.linkit.currentInstance.linkContent = result.title;

          $('.linkit-path-element', context).focus();
        }
      }

      searchElement.betterAutocomplete('init', Drupal.settings.linkit.currentInstance.autocompletePathParsed, Drupal.settings.linkit.currentInstance.autocomplete, callbacks);
    });
  }
};


})(jQuery);