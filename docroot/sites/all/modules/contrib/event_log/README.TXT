03-07-2013, Copyright by Cipix Internet. E-mail: info@cipix.nl.

CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Known issues
 * Installation

INTRODUCTION
------------

Current Maintainer: Bas van Meurs <bas@cipix.nl>

This module logs specific events. The events are saved in the database and can
be viewed on the page admin/reports/events. Furthermore, a views integration is
provided in which you can relate for instance a node to its events. You could
use this to display the total number of views, or the number of times that the
node has been modified and by which users.

Currently, the following events are supported:
- User authentication (login/logout/request password)
- Node operations (CRUD)
- User operations (CRUD)
- Menu operations (custom menu's and menu items CUD operations)
- Taxonomy operations (vocabulary and term CUD operations)

The event log can be easily extended with custom events. For more information
please have a look at the API documentation and the available sub modules.

KNOWN ISSUES
------------

None.

INSTALLATION
------------

Enable the module and the sub modules for the events that you'd like to log.
From that point onwards the events will be logged.

After performing some operations the page admin/reports/events will show the
events.

In the views screen, a new base table 'Event log' will appear. Furthermore,
several relationships to and from the event log are automatically added.