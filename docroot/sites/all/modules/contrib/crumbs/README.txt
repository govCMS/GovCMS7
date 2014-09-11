
This text is horribly out of date, especially for the 2.x branch ...


The ultimate breadcrumbs solution. Powerful, flexible, and as simple and DRY as can be.
(code will come soon)

Breadcrumbs based on:
- menus
- taxonomy
- system path fragments
- existing path alias fragments
- not yet existent pathauto alias fragments
- organic groups
- forum paths

Features:
- easy to extend.
- admin form to rearrange rules. no further configuration needed.
- guaranteed consistency: If d's breadcrumb is "a > b > c > d", then d's breadcrumb is "a > b > c".
- infinite loop prevention.

Requirements:
- PHP 5.2

How it works:
A plugin is an object that takes a path and returns a parent path.
If the rule returns NULL, the next rule is tried.

This process is repeated with the parent path, until either
- no further parent can be found.
- the returned path is the frontpage.
- the path is its own parent path.
- there is a loop consisting of more than one path.

In addition, every rule object has a chance to set a different title for a breadcrumb item (default is obtained from core menu system), or to let the item be skipped in the trail.











