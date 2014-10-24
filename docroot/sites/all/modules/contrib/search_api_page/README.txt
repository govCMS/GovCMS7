Search API Pages
----------------

This module allows you to create simple search pages and search blocks for
searching in your Search API indexes, similar to the core Search functionality.

Installation
------------

As the only pre-requisite you will need the Search API [1] module enabled and
correctly set up, along with at least one service class. Create a server and an
index (or use the default one) and configure them according to your needs.

[1] https://drupal.org/project/search_api

Then go to admin/config/search/search_api/page on your site (Administration »
Configuration » Search and metadata » Search API » Search pages) where you can
add a search page for your index.

Common problems
---------------

- Pager not displayed
  It can sometimes happen in specific setups, that even though your search
  returns more results than appear on the page, no pager is displayed for
  browsing the other results. This will most likely be due to a second pager
  being displayed somewhere on the page, which Drupal cannot handle without some
  additional configuration. To fix this problem, locate the other pager (the one
  being displayed) on the page and attempt to change the pager element it uses.
  E.g., for Views you can change the element by going to the configuration of
  the view in question, open the pager settings and set the "Pager ID" to 1 or
  greater. This should fix the problems with the pager.
  See [2] for details, and for help if the other pager doesn't come from Views.

  [2] https://drupal.org/node/1442686
