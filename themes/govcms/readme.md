# Theme customisation and override documentation

## Prerequisite knowledge

* Sass Preprocessor http://sass-lang.com/guide
* SMACSS https://smacss.com/
* Responsive layouts with Zen https://www.previousnext.com.au/blog/responsive-layouts-zen-5x

## What is a sub-theme?

Sub-themes allow Drupal themes to inherit stylesheets, template files, regions, screen shots, logo, favicon, and theme/preprocess functions from a parent theme. More information can be found on Drupal.org:
https://www.drupal.org/node/225125

Starterkits are pre-built sub-theme templates that allow you to replace the uppercase name of the theme e.g. "STARTERKIT" with your theme's machine name e.g. "my_theme"

## Themes that come with govcms

**zen**
The [Zen](http://drupal.org/project/zen) base theme is Drupal's most popular contributed theme. This theme is rarely (if ever) enabled as it is just a collection of template and css files that improve Drupal's default markup and styling. *DO NOT ENABLE THIS THEME.*

**govcms_zen**
A sub-theme of the Zen base-theme that includes markup and styling changes to customize govCMS's presentation layer, add accessibility improvements, and provided functionality through javascript. Low-level theme changes like colors and css3 enhancements are meant to be provided by the following sub-theme layer. This can be used with Sweaver as a basic, colourable theme.

**govcms_barton**
A ready-made example of a theme that has been lightly customized. *ENABLE this theme to see a standard representation of govCMS*

**GOVCMS_STARTERKIT**
An example sub-theme that you can use as a starting point to creating a sub-theme for your website. *ENABLE this theme to lightly customize colours and basic low-level markup on your govCMS website via code*

**STARTERKIT**
Zen's starterkit. govcms_zen was built using this theme. You should use Zen's STARTERKIT directly if the design components of your custom theme deviate strongly from those in govCMS. *ENABLE this theme for advanced customization of the govCMS distribution*

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
| govcms_zen |        |  govcms_barton
|          +------> |          |
|          |        |          |
+-----+----+        +----------+
      |
      |
      v
+----------+
|          |
| GOVCMS_STARTERKIT
|          |
|          |
+----------+
</pre>



