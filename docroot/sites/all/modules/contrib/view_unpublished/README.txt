View Unpublished
----------------
This small module adds the missing permissions "view any unpublished content"
and "view unpublished $content_type content" to Drupal 7.

This module also integrates with the core Content overview screen at /admin/content.
If you choose the "not published" filter, Drupal will show you unpublished
content you're allowed to see.

Using view_unpublished with Views
---------------------------------
Use the "Published or admin" filter, NOT "published = yes". Views will then
respect your custom permissions. Thanks to hanoii (6.x) and pcambra (7.x) for
this feature.

Common issues
-------------
* If for some reason this module seems not to work, try rebuilding your node
permissions: admin/reports/status/rebuild. Note that this can take significant
time on larger installs and it is HIGHLY recommended that you back up your site
first.

* Block caching: In D7, block caching is disabled for modules that implement
hook_node_grants, such as view_unpublished. There are a couple ways around this
issue, if block caching is valuable to you:
  
  -The core patch in Issue #1930960: Block caching disable hardcoded on sites with
   hook_node_grant() causes serious performance troubles when not necessary
   Patch: https://drupal.org/comment/8647155#comment-8647155
   
  -Block Cache Alter module: https://drupal.org/project/blockcache_alter

Releated isses on drupal.org
----------------------------
[New node permission "view any unpublished content"](http://drupal.org/node/273595)
[Enable Node Grants for Unpublished Nodes](http://drupal.org/node/452538)

Thanks to:
----------
Florian Weber (webflo) and thekevinday for their work on the D7 port.