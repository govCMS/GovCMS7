Description
===========

A very small module to make requests to http://example.com/favicon.ico forward to the actual site's true favicon.

This module takes the favicon for the current site/theme and makes it available at the url example.com/favicon.ico (where example.com is your domain). The problem is that some web browsers and web applications blindly make a call to example.com/favicon.ico looking for your sites favicon. In drupal this causes an error entry to show up in the logs because there is nothing there.

If you want your icon to show at that address you can put a copy of your favicon n the root drupal directory. But, what if you have a multisite configuration with different favicons. This module will allow that address to show the current themes favicon at example.com/favicon.ico and it will work for multisite configurations.

If no favicon is specified, the Drupal default misc/favicon.ico is returned.
