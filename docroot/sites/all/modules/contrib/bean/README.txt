Bean (Bean Entities Aren't Nodes)
==================================

The bean module was created to have the flexibility of
Block Nodes without adding to the node space.

Bean Types
----------

A Bean Type (or Block Type) is a bundle of beans (blocks).
Each Bean type is defined by a ctools plugin and are fieldable.
Currently Bean Types are only defined in hook_bean_plugins().

If you enable bean_admin_ui you can add/edit bean types at
admin/structure/block-types

Beans
-----
An overview of all beans created is at: admin/content/blocks

If views is installed and enabled, a default called 'Bean Block List' is available to replace the default block list at: admin/content/blocks

Beans can be added at: block/add

Example Bean Type Plugins
-------------------------
indytechcook's original bean plugin gist: https://gist.github.com/1460818
Context Bean: Context Bean block types display other beans (block entities). http://drupal.org/project/context_bean
Examples: http://drupal.org/project/bean_examples
Flickr Integration: http://drupal.org/project/bean_flickr
Leafbean - Leaflet + Bean for a simple map block: http://drupal.org/sandbox/rerooting/1787416
Leaflet GeoJSON Bean: http://drupal.org/project/leaflet_geojson
Openlayers Blocks: http://drupal.org/project/openlayers_blocks
Bean Panels - provides loose bean placement in panels, content need not exist: http://drupal.org/project/bean_panels
Relevant Content: http://drupal.org/project/bean_relevant
Service Links: http://drupal.org/project/bean_service_links (Integration with the Service Links module)
Slideshow: http://drupal.org/project/beanslide
Slideshow: https://github.com/opensourcery/os_slideshow
Taxonomy plugins: http://drupal.org/project/bean_tax
Twitter Pull integration: http://drupal.org/project/bean_twitter_pull (Integration with the Twitter Pull module)
Flickr Integration: http://drupal.org/project/bean_flickr
MapBox.js Integration: http://drupal.org/project/mapboxjs
(Latest list of plugins: http://drupal.org/node/1475632)

Articles and Videos
-------------------
Bean Tutorial: http://treehouseagency.com/blog/neil-hastings/2011/09/21/building-custom-block-entities-beans
Bean Presentation: http://www.archive.org/details/DrupalBeanModuleTutorial-UsingBeanAdminUiAndWritingBeanPlugins-
Admin UI tutorial: http://youtu.be/Eu1YNy-BNG8
Easily convert Boxes to Beans: https://github.com/skwashd/bean_boxes
Views without Views: http://thinkshout.com/blog/2012/06/sean/introducing-relevant-content-bean
Bean Intro: http://previousnext.com.au/blog/introduction-bean-module
Extending An Already Defined Bean: http://drupal.org/node/1826204
