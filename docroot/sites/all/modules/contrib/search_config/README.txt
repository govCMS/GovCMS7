Search Config - http://drupal.org/project/search_config
=======================================================

DESCRIPTION
=========== 

This module has two core roles, modifying the search form interface and search
restrictions by role per content type.

The first is to provide an easy interface to modify the search forms provided by
core. These include some of the following options:

* Removing the basic search form display if there is an advanced search form present
* To move the basic keywords search field into the advanced form
* Options to override the advanced forms fieldset. These include:
  * Remove the collapsible wrapper and title
  * Force it to stay open, but keep the open look and feel
  * Expand initially, then collapsed during searches
  * Expand initially or when there are zero results during searches
* Label overrides provided for fields. These overrides are still translatable.
* Title display settings for individual fields; above, hidden or below
* Hiding or showing search fields completely or by role
* To repopulate the advanced form fields after a search
* Filter display options on the "Only of the type(s)" field
* Custom content type groupings to make the types filter more UI friendly
  This allows you to specify options like:
  [] Standard pages (ie: page, book,etc)
  [] Personal blogging pages (ie: blog, forum, etc)
  [] All other pages (computed list not including page, book, blog or forum content types)

Some of these features can be mimiced using the Views module and making a view
that replaces the standard search page. However, it would be difficult to
completely mimic all of this modules functionality in a view.

If you require alternative search fields, then views may be your best option.

Modify search functionality by role.

For content types, the approach of this module is to re-write the search query,
so that content is indexed and available as search results to users in role(s) 
that have permissions to view it, but not displayed to other roles.

This also updates the "Only of the type(s)" field options.

If you also require content restrictions, then the module that supplies that
functionality should also update the search permissions, so this feature of
this module does not need to be used.


PREREQUISITES
=============
Search module (Drupal core).


INSTALLATION
============
Standard module installation.

See http://drupal.org/node/70151 for further information.


UPGRADING
=========

There are no scripts to import the changes from Drupal 6 versions to the new
Drupal 7 version.

Search Config
-------------
* Follow standard Drupal procedures for any major upgrade
* Follow the steps to configure Search Config.
  
Search Restrict
--------------- 
* Disable and uninstall Search Restrict 6.x
* Upgrade to Drupal 7.x
* Install Search Config
* Follow the steps to reconfigure Search Config


CONFIGURATION
=============

-- General user interface settings --

* Navigate to the search configuration page 
  [E.g: http://example.com/admin/config/search/settings]
  
* Scroll down to the bottom and open the "Additional Node Search Configuration"
  fieldset. All UI related settings are found here.
  
  My personal favourite recipe for configuring this is to make both forms appear
  as one and to make the form field expand or contract depending on the search
  result count. To mimic this:
  
  - check "Move basic keyword search"
  
  - check "Populate the advanced form with default values"
  
  - select the "Expand initially or when there are zero results" option under
    "Control how the advanced form initially renders" radios
  
  - under "Labels and string overrides"
    - "Advanced form label overrides"
      Wrapping fieldset: Enter "Search"
      Wrapping fieldset (with search keys): "Refine your search"

  I find it nicer and more compact to move the keyword titles under the fields.
  This is done by going to:

  - under "Labels and string overrides"
    - "Basic form label overrides"
      Keywords Title Display: Select "below"
      
    - "Advanced form label overrides"
      Containing any ... Title Display: Select "below"
      Containing the phrase Title Display: Select "below"
      Containing none ... Title Display: Select "below"

  Since Keywords and Containing any fields are a bit confusing, even though
  these are different: the basic forms "Keywords" is AND field and the
  "Containing any ..." ia an OR field.
  
  So I disable the "Containing any ..." field:
    - under "Containing any of the words settings"
      Check "Hide this field"
  
  Finally to add the last touches, use the grouping options to provide nicer
  grouping options. Using the example from the introduction, this is done by:
 
  - Under "Only of the type(s) settings" settings
    - Update the "Replace type options with custom type groups" to:

page,book|Standard pages
blog,forum|Personal blogging
<other-types>|All other pages
 
  Thats it. With groupings, there is no need to use the filters to remove
  unwanted content types from the list. However, if you want to remove certain
  content types from all search results (dependant on the users role) read on. 
   
-- Content type restrictions --

* Navigate to the user permissions form 
  [E.g: http://example.com/admin/people/permissions]

* Configure the permissions per role under Search Configuration heading

The Search module provides two key permissions:

* Use search
  This is required to allow users to search content.
  
* Use advanced search
  This turns on the advanced form.
  All of this modules UI settings require this permisson to be turned on 
 
This module provides one global permission and one or more permissions depending
on the number of content types that are configured.

* Search all content 
  This is a bypass flag that will ensure that the user can search all content
  that they are normally allowed to see. This is granted by default to all
  users. You must disable this permission if you want to hide one or more types
  completely from a search.
  
* CONTENT TYPE XYZ: Search content of this type 
  For every content type, you have this new permission. If users do not have
  permission to "Search all content", then they will need this permission to
  see content items of this type showing up in the search results.

  
TODO
====
Local menu tab label overrides OR find the native method of doing this
Categories field
Languages field
Search result limits
Write tests

-- Maybes, depends on scale -- 

Add node level exclude from search options
Add new fields to the search form
 
MAINTAINERS
===========
Alan Davison (Alan D.) <http://drupal.org/user/198838>


ACKNOWLEDGEMENTS
================

For versions 6.x and eariler

Search Config
-------------
Nesta Campbell (canen) <http://drupal.org/user/16188>
Joseph Yanick (jbomb) <http://drupal.org/user/210851>

View all: http://drupal.org/node/78102/committers

Search Restrict
--------------- 
Robert Castelo (Robert Castelo) <http://drupal.org/user/3555>
Gerhard Killesreiter (killes@www.drop.org) <http://drupal.org/user/227>
Hans Nilsson (Blackdog) <http://drupal.org/user/110169>
Daniel F. Kudwien (Sun) <http://drupal.org/user/54136> 
