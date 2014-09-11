/**
 * @file
 * README file for Workbench.
 */

Workbench
A framework for simplified content management.

CONTENTS
--------

1.  Introduction
1.1   Use-case
1.2   Examples
1.3   Terminology
2.  Installation
3.  Permissions
4.  Configuration
5.  Using the module
5.1  My Content
5.2  Create Content
6.  Troubleshooting
7.  Developer notes
7.1   API documentation
7.2   Database schema
7.3   Views integration
8.  Feature roadmap


----
1.  Introduction

Workbench provides a simplified user interface and an API to integrate other
Drupal modules.  Workbench on its own provides Content contributors a way to
easily access their own content.

Workbench gains more features when you install and enable these modules:

Workbench Access - http://drupal.org/project/workbench_access
Workbench Moderation - http://drupal.org/project/workbench_moderation
Workbench Media - http://drupal.org/project/workbench_media
Workbench Files - http://drupal.org/project/workbench_files

One way to think about Workbench is that it becomes the Dashboard for Content
Contributors.  Basically, putting all of the content needs of a user in one
place.

----
1.1  Use Case

Drupal provides a great framework for building functionality.  Workbench helps
harness content-focused features in one unified user interface.  The goal
is that a user does not need to learn Drupal in order to add content to the
site.

Users need access to their account, their content, and to add new content.
Instead of having to know how to navigate to My Account (/user/[uid]),
Add content (node/add), and Find Content (admin/content), the user goes to
My Workbench instead.

Simple changes like this help ease the learning curve for new users.

With additional Workbench modules like Workbench Access and Workbench
Moderation, Workbench becomes a full system which controls who can access
content and provide editorial workflow so that only the correct content is
published.

----
2.  Installation

Views is required in order to install Workbench.

Install the module and enable it according to Drupal standards.


----
3.  Permissions

Once a user role has access to create content, Workbench becomes
immediately useful.

 Workbench Permissions

 -- Administer Workbench settings
 Only Administrators should have access to this.  Workbench without its other
 modules does not have any configuration settings.  It becomes more useful
 when additional workbench modules are enabled.

 -- Access My Workbench
 For any user role who may access their own workbench a.k.a My Workbench

 -- View all unpublished content
 Allows a user to see content that is not Published on the site.  This
 becomes even more useful when Workbench Moderation is enabled.

A typical permission setup so that a user can take advantage of Workbench
looks like:

Node Permissions
 -- Article: Create new content
 -- Article: Edit own content
 -- Article: Delete own content
 -- Basic page: Create new content
 -- Basic page: Edit own content
 -- Basic page: Delete own content

System Permissions
 -- View the administration theme

Toolbar Permissions
 -- Use the administration toolbar

Workbench Permissions
 -- Access My Workbench

----
4.  Configuration

Workbench does not have any Configuration settings.  Additional Workbench
modules have their own configuration.

----
5.  Using the module

As an Administrator or a user with Access My Workbench permissions, you will
see My Workbench in the toolbar to the right of the Home icon.

----
5.1  My Content
On the My Content tab, you can see three areas:

 - My Profile
 - Content I've Edited
 - All Recent Content

This is your content dashboard.  As soon as you Add or edit content, it will
be displayed in the Content I've Edited block.

Notice the sub tabs:

 - Content I've Edited
 - All Recent Content

These go to full page lists with filters available to shorten the list of
content.  You can filter the list by:

 - Title (keywords)
 - Type (Content type)
 - Published (status of the content)
 - Items per page (defaults to 25)

Any lists of content include columns labels which can sort the current list.
Each item in the list links to the full content or you can click edit to
start editing.

----
5.2  Create Content

Click the Create Content tab to view a list of types of content that you can
create.  Remember, we're dealing with Entities now.  Initially, Workbench
shows various Node Types that you have permission to create.  When
Workbench Media is enabled, the Media item is added to this list as well.

Click the type of content you want to add, then follow the usual procedure for
adding content.

----
6.  Troubleshooting

Some helpful tips.

For automatic navigation to Workbench, be sure to give your user role
access to the Administration Toolbar; otherwise you need to add access to
one of the menus.

Be sure your user role has permission to create content.  Without those
permissions, Workbench will only give you access to your user account.

----
7.  Developer notes

The following section documents technical details of interest to developers.

----
7.1   API documentation

Workbench does not offer a generic API.  Please check the other
Workbench modules like Workbench Access for descriptions of their APIs.

----
7.2   Database schema

Workbench does not create any tables during installation.  Other Workbench
modules like Workbench Access and Workbench Moderation create tables.
Please review each module's README.txt file to learn more about schema
changes.

----
7.3   Views integration

Workbench creates several base views for the My Content tab.  Other
Workbench modules further alter these views.  You can alter the views
via Views UI as well.

----
8.  Feature roadmap

 -- integrate workflow module as an alternative to workbench_moderation
 -- publish permissions per content type
 -- email notifications
 -- integrate scheduler module for scheduled start/end publish dates
 -- general UX improvements
