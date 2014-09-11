
What Is Username Enumeration Prevention

By default Drupal is very secure (especially Drupal 7). However, there is a way to exploit 
the system by using a technique called username enumeration. Both Drupal 6 and 7 have 
this issue, but it is much worse for people using Drupal 6. This is because Drupal 6 does 
not have any built in brute force prevention. When an attacker knows a username they can 
start a brute force attack to gain access with that user. To help prevent this, it is best 
if usernames on the system are not easy to find out.

Attackers can easily find usernames that exist by using the forgot password form and a 
technique called “username enumeration”. The attacker can enter a username that does not 
exist and they will get a response from Drupal saying so. All the attacker needs to do is 
keep trying usernames on this form until they find a valid user.

This module will stop this from happening. When the module is enabled, the error message 
will be replaced for the same message as a valid user and they will be redirected back to 
the login form. If the user does not exist, no password reset email will be sent, but the 
attacker will not know this is the case.

For a demonstration of this, visit the password reset page at zeusarticles.com and try to 
enter an invalid username. This will show you the same message as a valid username.

Additional Notes

Enabling this module is one step to preventing the usernames on the system from being found 
out but there are other known methods that are just as easy. These are:

1. If a user belongs to a role that has "access user profiles" granted to it, then that user 
   can serially visit all integers at the URL http://drupal.org/user/UID and get the username from 
   the loaded profile pages. With this permission, the user can call the core callback at 
   http://drupal.org/user/autocomplete/a and get the usernames. Replacing the “a” with each letter 
   of the alphabet, prints an array of usernames.
 
2. If a site has the views module installed then views exposes an autocomlete callback which can be 
   similarly be enumerated with letters of the alphabet to get all the usernames. 
   See http://drupal.org/admin/views/ajax/autocomplete/user/a for an example. This callback doesn't have 
   any access restrictions assigned by the views module.

   Installing this module will make the views autocomplete callback require the “access user profiles” 
   permission. This will prevent anonymous users from accessing the callback as long as the anonymous 
   user role does not have “access user profiles” enabled.

If any of the two issues above exist then the module will notify the site builder when the module is enabled.

Note: There may be other places where usernames could be exposed that this module may not know about. 
Examples are the "submitted by" information on nodes or comments, views, exposed filters or by other 
contributed modules. Users looking to hide the usernames from comments and nodes should look at using 
realname or some other tool.

Installing Username Enumeration Prevention:

Place the entirety of this directory in sites/all/modules/username_enumeration_prevention
 
Navigate to administer >> build >> modules. Enable Username Enumeration Prevention.

