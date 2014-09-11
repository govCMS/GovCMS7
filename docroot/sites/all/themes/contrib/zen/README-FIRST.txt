WHERE TO START
--------------

Yay! You opened the correct file first. The first thing that people notice when
they download the Zen theme is that there are A LOT of files -- way more than
other themes.

Don't worry! You don't need to learn everything all at once in order to make a
Drupal theme. Zen will do the bits you haven't learned and patiently wait for
you to discover the documentation and inline comments about them.


WHAT ARE BASE THEMES, SUB-THEMES AND STARTER THEMES?
----------------------------------------------------

Often the best way to learn a system is to take an existing example and modify
it to see how it works. One big disadvantage of this learning method is that if
you break something and the original example worked before you hacked it,
there's very little incentive for others to help you.

Drupal's theming system has a solution to this problem: parent themes and
sub-themes. A "sub-theme" will inherit all its HTML markup, CSS, and PHP code
from its "parent theme" (also called a "base theme".) And with Drupal themes,
it's easy for a sub-theme to override just the parts of the parent theme it
wants to modify.

A "starter theme" is a sub-theme designed specifically to be a good starting
point for developing a custom theme for your website. It is usually paired with
a base theme.

So how do you create a theme with Zen?

The Zen theme includes the Zen base theme as well as a starter theme called
"STARTERKIT". You shouldn't modify any of the CSS or PHP files in the zen/
folder; but instead you should create a sub-theme of zen and put it in a folder
outside of the root zen/ folder.


SUGGESTED READING
-----------------

Installation
  If you don't know how to install a Drupal theme, there is a quick primer later
  in this document.

Building a theme with Zen
  See the STARTERKIT/README.txt file for full instructions.

Theme .info file
  Your sub-theme's .info file holds the basic information about your theme that
  Drupal needs to know: its name, description, features, template regions, CSS
  files, and JavaScript. Don't worry about all these lines just yet.

CSS
  Once you have created your sub-theme, look at the README.txt in your
  sub-theme's css folder. Don't freak out about all the files in this directory;
  just read the README.txt file for an explanation.

Templates
  Now take a look at the README.txt in your sub-theme's templates folder.


ONLINE READING
--------------

Full documentation on the Zen theme can be found in Drupal's Handbook:
  https://drupal.org/documentation/theme/zen

Excellent documentation on Drupal theming can be found in the Theme Guide:
  https://drupal.org/theme-guide


INSTALLATION
------------

 1. Download Zen from https://drupal.org/project/zen

 2. Unpack the downloaded file, take the entire zen folder and place it in your
    Drupal installation under sites/all/themes. (Additional installation folders
    can be used; see https://drupal.org/getting-started/install-contrib/themes
    for more information.)

    For more information about acceptable theme installation directories, read
    the sites/default/default.settings.php file in your Drupal installation.

 3. Log in as an administrator on your Drupal site and go to the Appearance page
    at admin/appearance. You will see the Zen theme listed under the Disabled
    Themes heading with links on how to create your own sub-theme. You can
    optionally make Zen the default theme.

 4. Now build your own sub-theme by reading the STARTERKIT/README.txt file.
