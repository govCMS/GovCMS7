
Unit tests and web tests for the Crumbs module.
==================================================


Test discovery
===================

We are using the simpletest integration of xautoload.
See http://drupal.org/node/1751540

This means, web and unit tests for Crumbs are only available if xautoload or
something equivalent is enabled.

This solution is meant to directly port the Drupal 8 behavior.
This means:

1) Toplevel only.
   Only tests at the top level directly under "Drupal\crumbs\Tests\" are found.

   As much as we would like it, the following will not be found:
     lib/Drupal/crumbs/Tests/Plugin/MenuTest.php
   So it has to be:
     lib/Drupal/crumbs/Tests/MenuPluginTest.php

2) PSR-0 only.
   There won't be:
     lib/Tests/Plugin/Menu.php
     lib/Tests/MenuPluginTest.php
   It has to be:
     lib/Drupal/crumbs/Tests/MenuPluginTest.php
