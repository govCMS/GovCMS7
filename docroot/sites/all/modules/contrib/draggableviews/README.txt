DraggableViews
==============

This module provides dragging entities and saving their order.

Quick install:
 1) Activate Draggableviews module at admin/modules
 2) Navigate to view edit-page, click on the first link at the Format section and then choose style "table".
 3) Click Add button at the "Fields" section and choose field "Content:title", add and apply.
 4) Click Add button at the "Fields" section and choose field "Content:Draggable views (Draggable views)", add and apply.
 5) Click Add button at the "Sort criteria" section and choose field "Content:Draggable views weight", add and choose sort asc, then apply.
 6) Save the view and you're done.

In the case of table standard drupal tabledrag.js javascript is used.

We also support jQuery UI Sortable javascript. In order to use it please set display style HTML List.
By default HTML list is displayed like grid. If you would like it to be displayed as list override
CSS styles for example in following way:
  .draggableviews-processed li.views-row { float: none; width: 100%; margin-left: 0; }

One view/display to set order another to display
================================================

You can create one view to set the order and another view to display the order. Or even
create one view with two separate displays. In a view that displays the order there
should be no draggableviews field (that makes view sortable), then in the settings of
the "draggableviews weight" sorting criteria there will be selectbox "Display sort as"
where you can choose the source view of your weights. This is applicable when you use
 Native handler.

Permissions
===========

Please add "Access draggable views" permission to users who should be able to reorder views.

Arguments handling
==================

Every time we save the order of a view, current set of arguments are saved with order.
You can see this in draggableviews_structure table "args" column. By default when we display order we use all
currently passed arguments to a view to "match" arguments in "args" column. This means that we can create
a view with contextual filter or exposed filter criteria and save different orders for different sets of arguments.

We can also completely ignore passed arguments using "Do not use any arguments (use empty arguments)" option
in Arguments handling of Sort criteria Draggable views weight. Be aware that in this case empty arguments set
will be used. So you can set order for a view when no arguments passed and then whatever arguments passed,
empty set will be used.

Prepare arguments with PHP code is an option when you would like to alter arguments before they passed to
"matching" with "args" column. For us this means that we can create for example several exposed filters,
but pass values of only one of values of exposed filters instead of all of them (like we create two exposed
filters: author and node type, but take into account for ordering only node type).
Please be aware that in PHP code arguments are passed as $arguments variable and you should return array.
Contextual filters are number keyed and exposed filters are name keyed.

Contextual link "Order view"
============================

If there is view with sort order draggableviews weight and the order is set by another view we show "Order view"
contextual link for opening a view that sets the order.
