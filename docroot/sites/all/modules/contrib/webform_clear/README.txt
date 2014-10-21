********************************************************************
                     D R U P A L    M O D U L E
********************************************************************
Name: Webform Clear Module
Drupal: 7.x
********************************************************************
DESCRIPTION:

Removes Webform submissions from the database after they have been
emailed. Any uploaded files associated to the Webform will also be
deleted.

This can happen either never, immediately, or after a specified
period. A default value for the clearing period can be set both site
wide basis, and per Webform.


********************************************************************
PREREQUISITES:

  Webform module


********************************************************************
INSTALLATION:

Note: It is assumed that you have Drupal up and running.  Be sure to
check the Drupal web site if you need assistance.

1. Place the entire module directory into your Drupal directory:
   sites/all/modules/


2. Enable the module by navigating to:

   administer > build > modules

   Click the "Save configuration" button at the bottom to commit your
   changes.

3. Go to "admin/config/content/webform_clear" if you want to change
   the default storage period for Webforms to something other than "Do
   not delete".

   Submissions to any Webforms created/edited before changing this
   default value will not be affected. Submissions to any Webforms
   created after changing this default value will be affected.

4. In the "Form settings" for a Webform ('node/NODE ID/webform/configure'),
   this value can be overriden by users with the "Set up Webform
   submission storage periods" permission.

   For other users, this dropdown will be disabled (grayed out) and be
   set to whatever it was set to by another user, or to the default
   value.
