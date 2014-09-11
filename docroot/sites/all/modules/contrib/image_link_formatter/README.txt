This module is the result of the discussions around a requested feature to
allow an image field to be displayed with a link to a custom URL:
- Add a link option to an image field
- #1570072: Ability to customize image links


1 - Implementation:

The code is greatly inspired from the post:
#1570072: Ability to customize image links where a patch has been proposed,
against the Drupal 7 Core Image field.
See: http://drupal.org/node/1570072#comment-6369564
So this module is simply a copy of the Image core formatter functions, with
the patch applied and a few more fixes, mostly to support field translation.

It seems this function could also be achieved by using Custom Formatters
(See module's tracker page for more information, image with custom link
formatter is a recurring topic).
Another solution would be to use the Linked Field module which pretty much
allows linking any field to custom URL targets with Token patterns.
In other words, almost the same functionality could be obtained with a little
bit more complicated setup with the Linked Field module configured with Tokens
(Main difference would be the handling of the Link field settings
upon display of the formatter).
But since this is a recurring request with such a simple and light
implementation, it could be considered as a standalone module.


2 - Integration

This module plays well and has been tested with:
Bean, Field Collection and Entity Translation.

A pretty cool and simple setup or application of this module would be,
for example, to build a simple ads block, with an image linking to a
custom URL in a block:
Add a Bean block type with Image and Link fields. Then configure the display
formatter of the image field in the bean block to display wrapped
in the link (Image Link Formatter).
On top of that, add Field Collection and Entity Translation to have multiple
images with links, in multiple languages, which pretty much rounds this up
(very flexible and granular configuration of blocks with image links).


3 - Installation and configuration:
a. Prerequisite:
Requires Link and Image (Drupal 7.x Core) field modules to be installed.

b. Download the module and simply copy it into your contributed modules folder:
[for example, your_drupal_path/sites/all/modules] and
enable it from the modules administration/management page.
More information at: Installing contributed modules (Drupal 7)
[http://drupal.org/documentation/install/modules-themes/modules-7]

c. Configuration:
After successful installation, browse to the "Manage Display" settings page,
for the entity (Node content type, for example) with an image and a link field,
to configure the formatter (See attached screenshot).
For example: the page content type:
Home » Administration » Structure » Content types » Page » Manage display


4 - Important notes:
a. Entity translation support:
For field translation to work, both fields translation need to be enabled.
If only one of the two fields has translation enabled (and not the other),
the formatter will not work and the link will not be displayed properly
on the image. Both image and link fields have to be translation enabled.

b. Link field settings:
Link field configuration settings will all be applied to the link wrapping the
image. For example, if the field is configured to allow user to select to open
the link URL in a new window, then this setting will also be applied
to the image link.

c. Multiple values:
Multiple field instances will work based on field delta.
For example: value 0 of field link will be wrapped around value 0 of field
image. Value 1 of field link will be wrapped around value 1 of field image
.... and so forth.


5 - Future developments:
There are already plans to open a 2.x branch which should be based on the
Field Formatter Settings (See: #945524: Field formatter settings hooks in core)
module to allow altering core Image module formatter.
This would reduce the amount of necessary code and increase compatibility with
core module, but add a new dependency to Field formatter settings.


6 - Contributions are welcome!!

Feel free to follow up in the issue queue for any contributions, 
bug reports, feature requests.
Tests, feedback or comments in general are highly appreciated.
