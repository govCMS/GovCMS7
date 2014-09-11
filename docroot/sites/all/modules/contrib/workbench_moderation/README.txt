/**
 * @file
 * README file for Workbench Moderation.
 */

Workbench Moderation
Arbitrary moderation states and unpublished drafts for nodes

CONTENTS
--------

1.  Introduction
1.1  Concepts
1.1.1  Arbitrary publishing states
1.1.2  Node revision behavior
1.1.3  Moderation states and revisions
2.  Installation
2.1  Requirements
3.  Configuration
3.1  Configuring states
3.2  Configuring transitions
3.3  Checking permissions
3.3.1  Recommended permissions
4.  Using the module
5.  Troubleshooting
6.  Developer notes
6.1  Database schema
6.2  Views integration
7.  Feature roadmap

----
1.  Introduction

Workbench Moderation 

----
1.1  Concepts

Workbench Moderation adds arbitrary moderation states to Drupal core's
"unpublished" and "published" node states, and affects the behavior of node
revisions when nodes are published. Moderation states are tracked per-revision;
rather than moderating nodes, Workbench Moderation moderates revisions.

----
1.1.1  Arbitrary publishing states

In Drupal, nodes may be either unpublished or published. In typical
configurations, unpublished nodes are accessible only to the user who created
the node and to users with administrative privileges; published nodes are
visible to any visitor. For simple workflows, this allows authors and editors to
maintain drafts of content. However, when content needs to be seen by multiple
people before it is published--for example, when a site has an editorial or
moderation workflow--there are limited ways to keep track of nodes' status.
Workbench Moderation provides moderation states, so that unpublished content may
be reviewed and approved before it gets published.

----
1.1.2  Node revision behavior

Workbench Moderation affects the behavior of Drupal’s node revisions. When
revisions are enabled for a particular node type, editing a node creates a new
revision. This lets users see how a node has changed over time and revert
unwanted or accidental edits. Workbench Moderation maintains this revision
behavior: any time a node is edited, a new version is created.

When there are multiple versions of a node--it has been edited multiple times,
and each round of editing has been saved in a revision--there is one "current"
revision. The current revision will always be the revision displayed in the node
editing form when a user goes to edit a piece of content.

In Drupal core, publishing a node makes the current revision visible to site
visitors (in a typical configuration). Once a node is published, its current
revision is always the published version. Workbench Moderation changes this; it
allows you to use an older revision of a node as the published version, while
continuing to edit a newer draft.

@see workbench_moderation-core_revisions.png
@see workbench_moderation-wm_revisions.png

Internally, Workbench Moderation does this by managing the version of the node
stored in the {node} table. Drupal core looks in this table for the "current
revision" of a node. Drupal core equates the "current revision" of a node with
both the editable revision and, if the node is published, the published
revision. Workbench Moderation separates these two concepts; it stores the
published revision of a node in the {node} table, but uses the latest revision
in the {node_revision} table when the node is edited. Workbench Moderation's
treatment of revisions is identical to that of Drupal core until a node is
published.

----
1.1.3  Moderation states and revisions

Workbench Moderation maintains moderation states for revisions, rather than for
nodes. Since each revision may reflect a unique version of a node, the state may
need to be revisited when a new revision is created. This also allows users to
track the moderation history of a particular revision, right up through the
point where it is published.

Revisions are a linear; revision history may not fork. This means that only the
latest revision--Workbench Moderation calls this the "current draft"--may be
edited or moderated.

----
2.  Installation

Install the module and enable it according to Drupal standards.

After installation, enable moderation on a content type by visiting its
configuration page:

    Admin > Structure > Content Types > [edit Article]

In the tab block at the bottom of the form, select the "Publishing options" tab.
In this tab under "Default Options", Workbench Moderation has added a checkbox,
"Enable moderation of revisions". To enable moderation on this node type, check
the boxes labeled "create new revision" (required) and "enable moderation of
revisions", and then save the node type.

----
2.1  Requirements

Workbench Moderation may be used independently of other modules in the Workbench
suite, including the "Workbench" module. Unlike the "Workbench" module,
Workbench Moderation does not depend on Views. However, Workbench Moderation
does have Views integration, and it provides two useful views ("My Drafts" and
"Needs Review") that appear in the Workbench. If you wish to use Workbench
Moderation without Workbench, you may override or clone these views and place
them where your users can find them.

Using the "Workbench" module with Workbench Moderation enables the display of
moderation status information and a mini moderation form on node viewing pages.

----
3.  Configuration

Workbench Moderation's configuration section is located at:

    Admin > Configuration > Workbench > Workbench Moderation

This administration section provides tabs to configure states, transitions, and
to check whether your permissions are configured to enable full use of
moderation features.

----
3.1  Configuring states

Workbench Moderation provides three default moderation states: "Draft", "Needs
Review", and "Published". The Draft and Published states are required. You can
edit, add, and remove states at:

    Admin > Configuration > Workbench > Workbench Moderation > States

----
3.2  Configuring transitions

Workbench Moderation also provides transitions between these three states. You
can add and remove transitions at:

    Admin > Configuration > Workbench > Workbench Moderation > Transitions

----
3.3  Checking permissions

In order to use moderation effectively, users need a complex set of permissions.
If non-administrative users encounter access denied (403) errors or fail to see
notifications about moderation states, the "Check permissions" tab can help you
determine what permissions are missing. Visit:

    Admin > Configuration > Workbench > Workbench Moderation > Check Permissions

Select a Drupal role, an intended moderation task, and the relevant node types,
and Workbench Moderation will give you a report of possible missing permissions.
Permissions configuration depends heavily on your configuration, so the report
may flag permissions as missing even when a particular role has enough access to
perform a particular moderation task.

----
3.3.1  Recommended permissions

For reference, these are the permission sets recommended by the "Check 
Permissions" tab:

    Author:
      Node:
        access content
        view own unpublished content
        view revisions
        create [content type] content
        edit own [content type] content
      Workbench Moderation:
        view moderation messages
        use workbench_moderation my drafts tab
    
    Editor:
      Node:
        access content
        view revisions
        revert revisions
        edit any [content type] content
      Workbench:
        view all unpublished content
      Workbench Moderation:
        view moderation messages
        view moderation history
        use workbench_moderation my drafts tab
        use workbench_moderation needs review tab
    
    Moderator:
      Node:
        access content
        view revisions
        edit any [content type] content
      Workbench:
        view all unpublished content
      Workbench Moderation:
        view moderation messages
        view moderation history
        use workbench_moderation needs review tab
    Publisher
      Node:
        access content
        view revisions
        revert revisions
        edit any [content type] content
      Workbench:
        view all unpublished content
      Workbench Moderation:
        view moderation messages
        view moderation history
        use workbench_moderation needs review tab
        unpublish live revision

----
4.  Using the module

Once the module is installed and moderation is enabled for one or more node
types, users with permission may:

* Use the "Moderate" node tab to view moderation history and navigate versions.

When the Workbench module is enabled, users with permission may also:

* See messages about moderation state when visiting a moderated node.
* Moderate content from the "View Draft" page.

----
5.  Troubleshooting

* If users get access denied (403) errors when creating, editing, moderating, or
  reverting moderated content, the "Check Permissions" tab in Workbench
  Moderation's administration section can help diagnose what access is missing.
  See heading 3.3 in this README.

* If you're building Views of moderation records, keep in mind that for a single
  node, there will be multiple revisions, and for each revision, there may be
  multiple moderation records. This means it will be very easy to end up with a
  View that shows particular nodes or revisions more than once. Try adding the
  "Workbench Moderation: Current" filter, or using Views' "Use grouping" option
  (under the "Advanced settings" heading on the view editing page).

----
6.  Developer notes

Workbench Moderation does not have a mature API.

----
6.1  Database schema

Workbench Moderation uses three tables to track content moderation states.

* workbench_moderation_states
  Stores administrator-configured moderation states.

* workbench_moderation_transitions
  Stores administrator-configured transitions between moderation states. These
  are simply pairs of moderation states: a "from" state and a "to" state.

* workbench_moderation_node_history
  Stores individual moderation records related to each node revision. Each
  record stores the nid and vid of a node, the original moderation state and the
  new moderation state, the uid of the user who did the moderation, and a
  timestamp.

----
6.2  Views integration

Workbench Moderation provides Views integration so that site builders may
include moderation information in node and node revision views.

* Filters, fields, sorts, and arguments are provided for moderation record data.

* A relationship is provided from moderation records to the user who made the
  moderation change.

* A "content type is moderated" filter is provided on for nodes to help in
  creating lists of only moderated content.

----
7.  Feature roadmap

* Allow configuration of 'Draft' and 'Published' states.
