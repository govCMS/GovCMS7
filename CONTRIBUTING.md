Contributing
------------

govCMS is available for all to contribute to. If you'd like to contribute,
feel free to do so, but remember to follow these few simple rules:


Commits:
--------

- Only make commits of logical units of code. This could mean rebasing several
  commits into one to remove additional commits;
- Check for unnecessary whitespace with `git diff --check` before
  committing;
- Ensure all files committed are using Unix line endings (check the settings
  around "crlf" in git-config(1));
- Do not commit any commented out code or unneeded files;
- Remove all debug code e.g. dpm() functions;
- Use a terse commit message under roughly 50 characters;
- Associate any ticket/issue numbers in the message. The first line should
  include the issue number in the form "(#XXXX) Commit message";
- Add new tests (behat, simpletest or otherwise) for each new feature addition;
  Check out what currently exists for an understanding of the tests. This is
  important so we don't break future versions of govCMS unintentionally; and
- Document any new functionality you've introduced in the `README.md`.


Submitting a pull request:
-------------------------

- [Fork the govCMS repository on github](https://help.github.com/articles/using-pull-requests/)
  and clone your repository to your development environment;
- Make your feature addition or bug fix;
- __Always__ base your changes on the `master` branch on github (all new
  development happens here);
- Commit your code, but do not add to `CHANGELOG.txt`. This will be done at
  each point release.
- Add new modules or features to the make file rather than directly to the
  govCMS repository; and
- __Remember__: when you create [Pull Request](https://help.github.com/articles/using-pull-requests/),
  always select `master` branch as
  target, otherwise it will be closed (this is selected by default).


When to patch govCMS
--------------------

As govCMS is a platform that brings together Drupal core, contributed Drupal
modules, patches and custom functionality, a patch to govCMS may not be
appropriate sometimes. If a bug needs to be fixed in any non-govCMS code, an
issue should be filed against the appropriate project on drupal.org. From there,
a patch may be created and placed in the govCMS make file.


Coding standards
----------------

All custom modules and features added to govCMS are subject to linting and code
standards checks before being passed to manual review. This is to ensure that
only well written code makes it to manual review. The [Drupal coding standards](https://www.drupal.org/coding-standards)
are used to check govCMS.


Backwards compatibility
-----------------------

govCMS supports numerous websites online and operates on a frequent release
schedule. It is important that we maintain backwards compatibility of the
platform. Any regression to features in place on the platform will result in
rejection of the pull request. Exception may be made in rare cases where a
backwards compatibility break will fix a serious issue.


Running tests
-------------
Make sure that you don't break anything with your changes by running the test
suite locally:

```bash
composer install --prefer-dist
./bin/phing build
./bin/phing run-tests
```


Additional Resources
--------------------

- [General GitHub documentation](http://help.github.com/)

- [GitHub pull request documentation](http://help.github.com/send-pull-requests/)
