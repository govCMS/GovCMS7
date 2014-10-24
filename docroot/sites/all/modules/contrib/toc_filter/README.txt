
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Similar Modules

INTRODUCTION
------------

Converts header tags into a linked table of contents.

This module is designed to be lightweight and accomplishs the very specific task
of converting <h3> tags into an SEO friendly table of contents (TOC).

If you need a more complete heirarchical table on contents check out the
'Table of Contents' module. (http://drupal.org/project/tableofcontents)


INSTALLATION
------------

1. Copy/upload the toc_filter.module to the sites/all/modules directory
   of your Drupal installation.

2. Enable the 'TOC filter' module in 'Modules', (admin/modules)

3. Visit the 'Configuration > [Content authoring] Text formats'
   (admin/config/content/formats). Click "configure" next to the input format you want
   to enable the 'Table of Contents' filter on.

4. Enable (check) the 'Table of Contents' filter under the list of filters and save
   the configuration.

5. (optional) Visit the 'Configuration > [Content authoring] TOC filter'
   (admin/config/content/toc_filter). Select desired header tab for conversion to
   accordion and tab labels. The recommended default value is <h3>.


SIMILAR MODULES
---------------

- Table of Contents: Adds a filter that generates Tables of contents for pages
  with  '[toc ...]' tags or that have a predetermined number of headers.
  http://drupal.org/project/tableofcontents
  [A more powerful (and complex) solution to building heirachical TOCs]

- Table of Contents: Automatically create table of contents (jumplinks) for
  long pages in Drupal
  http://www.drupalcoder.com/blog/automatically-create-table-of-contents-jumplinks-for-long-pages-in-drupal


AUTHOR/MAINTAINER
-----------------

- Jacob Rockowitz
  http://drupal.org/user/371407
