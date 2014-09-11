
/**
 *  @file
 *  Attach Media WYSIWYG behaviors.
 */

(function ($) {

Drupal.media = Drupal.media || {};

/**
 * Register the plugin with WYSIWYG.
 */
Drupal.wysiwyg.plugins.media = {

  /**
   * Determine whether a DOM element belongs to this plugin.
   *
   * @param node
   *   A DOM element
   */
  isNode: function(node) {
    return $(node).is('img.media-element');
  },
  /**
   * Execute the button.
   *
   * @param data
   *   An object containing data about the current selection:
   *   - format: 'html' when the passed data is HTML content, 'text' when the
   *     passed data is plain-text content.
   *   - node: When 'format' is 'html', the focused DOM element in the editor.
   *   - content: The textual representation of the focused/selected editor
   *     content.
   * @param settings
   *   The plugin settings, as provided in the plugin's PHP include file.
   * @param instanceId
   *   The ID of the current editor instance.
   */
  invoke: function (data, settings, instanceId) {
    if (data.format == 'html') {
      var insert = new InsertMedia(instanceId);
      if (this.isNode(data.node)) {
        // Change the view mode for already-inserted media.
        var media_file = extract_file_info($(data.node));
        insert.onSelect([media_file]);
      }
      else {
        // Insert new media.
        insert.prompt(settings.global);
      }
    }
  },

  /**
   * Attach function, called when a rich text editor loads.
   * This finds all [[tags]] and replaces them with the html
   * that needs to show in the editor.
   *
   * This finds all JSON macros and replaces them with the HTML placeholder
   * that will show in the editor.
   */
  attach: function (content, settings, instanceId) {
    ensure_tagmap();

    var tagmap = Drupal.settings.tagmap,
        matches = content.match(/\[\[.*?\]\]/g),
        media_definition;

    if (matches) {
      for (var index in matches) {
        var macro = matches[index];

        if (tagmap[macro]) {
          var media_json = macro.replace('[[', '').replace(']]', '');

          // Make sure that the media JSON is valid.
          try {
            media_definition = JSON.parse(media_json);
          }
          catch (err) {
            media_definition = null;
          }
          if (media_definition) {
            // Apply attributes.
            var element = create_element(tagmap[macro], media_definition);
            var markup = outerHTML(element);

            content = content.replace(macro, markup);
          }
        }
        else {
          debug.debug("Could not find content for " + macro);
        }
      }
    }
    return content;
  },

  /**
   * Detach function, called when a rich text editor detaches
   */
  detach: function (content, settings, instanceId) {
    ensure_tagmap();
    var tagmap = Drupal.settings.tagmap,
        i = 0,
        markup,
        macro;

    // Replace all media placeholders with their JSON macro representations.
    //
    // There are issues with using jQuery to parse the WYSIWYG content (see
    // http://drupal.org/node/1280758), and parsing HTML with regular
    // expressions is a terrible idea (see http://stackoverflow.com/a/1732454/854985)
    //
    // WYSIWYG editors act wacky with complex placeholder markup anyway, so an
    // image is the most reliable and most usable anyway: images can be moved by
    // dragging and dropping, and can be resized using interactive handles.
    //
    // Media requests a WYSIWYG place holder rendering of the file by passing
    // the wysiwyg => 1 flag in the settings array when calling
    // media_get_file_without_label().
    //
    // Finds the media-element class.
    var classRegex = 'class=[\'"][^\'"]*?media-element';
    // Image tag with the media-element class.
    var regex = '<img[^>]+' + classRegex + '[^>]*?>';
    // Or a span with the media-element class (used for documents).
    // \S\s catches any character, including a linebreak; JavaScript does not
    // have a dotall flag.
    regex += '|<span[^>]+' + classRegex + '[^>]*?>[\\S\\s]+?</span>';
    var matches = content.match(RegExp(regex, 'gi'));
    if (matches) {
      for (i = 0; i < matches.length; i++) {
        markup = matches[i];
        macro = create_macro($(markup));
        tagmap[macro] = markup;
        content = content.replace(markup, macro);
      }
    }

    return content;
  }
};
/**
 * Defining InsertMedia object to manage the sequence of actions involved in
 * inserting a media element into the WYSIWYG.
 * Keeps track of the WYSIWYG instance id.
 */
var InsertMedia = function (instance_id) {
  this.instanceId = instance_id;
  return this;
};

InsertMedia.prototype = {
  /**
   * Prompt user to select a media item with the media browser.
   *
   * @param settings
   *    Settings object to pass on to the media browser.
   *    TODO: Determine if this is actually necessary.
   */
  prompt: function (settings) {
    Drupal.media.popups.mediaBrowser($.proxy(this, 'onSelect'), settings);
  },

  /**
   * On selection of a media item, display item's display configuration form.
   */
  onSelect: function (media_files) {
    this.mediaFile = media_files[0];
    Drupal.media.popups.mediaStyleSelector(this.mediaFile, $.proxy(this, 'insert'), {});
  },

  /**
   * When display config has been set, insert the placeholder markup into the
   * wysiwyg and generate its corresponding json macro pair to be added to the
   * tagmap.
   */
  insert: function (formatted_media) {
    var element = create_element(formatted_media.html, {
          fid: this.mediaFile.fid,
          view_mode: formatted_media.type,
          attributes: formatted_media.options,
          fields: formatted_media.options
        });

    var markup = outerHTML(element),
        macro = create_macro(element);

    // Insert placeholder markup into wysiwyg.
    Drupal.wysiwyg.instances[this.instanceId].insert(markup);
    // Store macro/markup pair in the tagmap.
    ensure_tagmap();
    Drupal.settings.tagmap[macro] = markup;
  }
};

/** Helper functions */

/**
 * Ensures the tag map has been initialized.
 */
function ensure_tagmap () {
  Drupal.settings.tagmap = Drupal.settings.tagmap || {};
}

/**
 * Serializes file information as a url-encoded JSON object and stores it as a
 * data attribute on the html element.
 *
 * @param html (string)
 *    A html element to be used to represent the inserted media element.
 * @param info (object)
 *    A object containing the media file information (fid, view_mode, etc).
 */
function create_element (html, info) {
  if ($('<div></div>').append(html).text().length === html.length) {
    // Element is not an html tag. Surround it in a span element
    // so we can pass the file attributes.
    html = '<span>' + html + '</span>';
  }
  var element = $(html);

  // Move attributes from the file info array to the placeholder element.
  if (info.attributes) {
    $.each(Drupal.settings.media.wysiwyg_allowed_attributes, function(i, a) {
      if (info.attributes[a]) {
        element.attr(a, info.attributes[a]);
      }
    });
    delete(info.attributes);
  }

  // Important to url-encode the file information as it is being stored in an
  // html data attribute.
  info.type = info.type || "media";
  element.attr('data-file_info', encodeURI(JSON.stringify(info)));

  // Adding media-element class so we can find markup element later.
  var classes = ['media-element'];

  if(info.view_mode){
    classes.push('file-' + info.view_mode.replace(/_/g, '-'));
  }
  element.addClass(classes.join(' '));

  return element;
}

/**
 * Create a macro representation of the inserted media element.
 *
 * @param element (jQuery object)
 *    A media element with attached serialized file info.
 */
function create_macro (element) {
  var file_info = extract_file_info(element);
  if (file_info) {
    return '[[' + JSON.stringify(file_info) + ']]';
  }
  return false;
}

/**
 * Extract the file info from a WYSIWYG placeholder element as JSON.
 *
 * @param element (jQuery object)
 *    A media element with attached serialized file info.
 */
function extract_file_info (element) {
  var file_json = $.data(element, 'file_info') || element.data('file_info'),
      file_info,
      value;

  try {
    file_info = JSON.parse(decodeURIComponent(file_json));
  }
  catch (err) {
    file_info = null;
  }

  if (file_info) {
    file_info.attributes = {};

    // Extract whitelisted attributes.
    $.each(Drupal.settings.media.wysiwyg_allowed_attributes, function(i, a) {
      if (value = element.attr(a)) {
        file_info.attributes[a] = value;
      }
    });
    delete(file_info.attributes['data-file_info']);

    // Extract the link text, if there is any.
    if (link_text = element.find('a').html()) {
      file_info.link_text = link_text;
    }
    else {
      file_info.link_text = null;
    }
  }

  return file_info;
}

/**
 * Gets the HTML content of an element.
 *
 * @param element (jQuery object)
 */
function outerHTML (element) {
  return $('<div>').append(element.eq(0).clone()).html();
}

})(jQuery);
