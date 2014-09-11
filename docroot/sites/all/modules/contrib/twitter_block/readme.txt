CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Installation
 * Permissions
 * Usage

INTRODUCTION
------------

Current Maintainers:

 * ZenDoodles http://drupal.org/user/226976
 * cweagans http://drupal.org/user/404732
 * Devin Carlson http://drupal.org/user/290182

Twitter Block is a lightweight module which allows administrators to create
blocks which display embedded timelines.

Twitter Block will never provide advanced Twitter integration such as OAuth
user authentication or the ability to tweet from Drupal. These capabilities are
provided by other modules such as Twitter (http://drupal.org/project/twitter).

REQUIREMENTS
------------

Twitter Block has one dependency.

Drupal core modules
 * Block

INSTALLATION
------------

Twitter Block can be installed via the standard Drupal installation process
(http://drupal.org/documentation/install/modules-themes/modules-7).

PERMISSIONS
------------

The ability to create, edit and delete Twitter Block blocks relies on the block
module's "Administer blocks" permission.

USAGE
-----

Administrators can visit the Blocks administration page where they can create
new Twitter Block blocks and update or delete existing Twitter Block blocks.

Administrators can also position Twitter Block blocks as they can with standard
or custom blocks provided by the core Block module.

Each Twitter Block block requires a unique widget ID which determines, among
other things, the source (user timeline, favourites, list or search) of the
tweets to display.

You can view a list of your existing embedded timeline widgets (and their
widget IDs) or create new embedded timeline widgets by visiting
https://twitter.com/settings/widgets (make sure that you're logged in).

You can determine a widget's ID by editing it and inspecting the URL (which
should be in the form of https://twitter.com/settings/widgets/WIDGET_ID/edit)
or by looking at the widget's embed code (look for
data-widget-id="WIDGET_ID").
