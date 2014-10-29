# Theme customisation and override documentation

## What is a sub-theme

Sub-themes allow Drupal themes to inherit stylesheets, template files, regions, screen shots, logo, favicon, and theme/preprocess functions from a parent. The ins and out on how this inheritance works is documented on Drupal.org:
https://www.drupal.org/node/225125

Starter-kits are pre-built sub-theme templates that allow you run a find/replace on the uppercase name of the theme e.g. "STARTERKIT" and replace with your theme's machine name e.g. "my_theme"

## What sub-theme should I use?

*agov_zen* is a sub-theme of the zen base-theme. The Zen contrib theme which is Drupal's most widely used base theme.
http://drupal.org/project/zen - In aGov 1.x the Omega base theme is used.

*AGOV_STARTERKIT* is an example sub-theme that you can use as a starting point to creating a sub-theme for your website.

*agov_barton* is a ready made example of a theme that has been lightly customized.

Zen's *STARTERKIT* should be used if the design components of your custom theme deviate strongly from those in aGov.

## Theme Hierarchy diagram:

<pre>
+----------+        +--------+
|          |        |        |
|   zen    |        | STARTERKIT
|          |------> |        |
|          |        |        |
+-----+----+        +--------+
      |
      |
      v

+----------+        +----------+
|          |        |          |
| agov_zen |        |  agov_barton
|          +------> |          |
|          |        |          |
+-----+----+        +----------+
      |
      |
      v
+----------+
|          |
| AGOV_STARTERKIT
|          |
|          |
+----------+
</pre>

## Prerequisite knowledge

* Sass Preprocessor
* Ruby dependencies and bundler
* SMACSS


