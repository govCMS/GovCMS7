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
- __Always__ base your changes on the `7.x-2.x` branch on github (all new
  development happens here);
- Commit your code, but do not add to `CHANGELOG.txt`. This will be done at
  each point release.
- Add new modules or features to the make file rather than directly to the
  govCMS repository; and
- __Remember__: when you create [Pull Request](https://help.github.com/articles/using-pull-requests/),
  always select `7.x-2.x` branch as
  target, otherwise it will be closed (this is selected by default).
- The existing functionality might already be covered by Behat or PHPUnit tests. In case of changing such code with your PR you will also need to include any relevant adjustments to the test cases. (*/build/tests/behat/features*)
- Any new code should be covered with the tests.


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

Adding Behat tests
--------------------

All existing Behat scenarios are captured in *.feature* files and located in
*build/tests/behat/features*. If you are introducing a new functionality that
has not been captured by tests before you should provide a new
*test-name.feature* file in that folder (or relevant sub-folder) and script the
scenarios there. It can be a good idea to copy an existing feature and follow
the same principles for writing your own.

The simplest example of a scenario would be:
```
Feature: Home Page

  Ensure the home page is rendering correctly

  @api @javascript
  Scenario: Visit the homepage and check its content
    Given I am an anonymous user
    When I am on the homepage
    Then I should see "Welcome to govCMS"
    And I should see "Home"
```
Scenarios can be tagged with @api @drush @javascript or any other custom tags.
  - @api can be added when any interaction with the database is required
  - @javascript can be added when the scenario requires javascript
  - @drush can be added when the scenario needs to be run using Drush driver

*Note, scenarios without @javascript would usually be much faster, however they
won't produce a screenshot on failure.*

There are plenty of existing steps available already that handle some typical
activities on the site so you might also want to scan through the scenarios to
get a better idea. Additionally, you can have a look inside the
*/build/tests/behat/bootstrap* to find the contexts that define some of the
custom steps. If you want to perform a custom step then you would need to add
its definition to one of the existing contexts (or create a new sub-context).

Adding PHPUnit tests
--------------------
Support for PHPUnit tests is available within the distribution and can be
invoked from the parent directory of the build as follows:
```
build/bin/phing -f build/phing/build.xml test:phpunit
```

With the current configuration, the modules directory next to the docroot and
its contents are searched, so tests will only be run for the custom govCMS
modules. Files containing PHPunit tests should match the pattern '*Test.php'.

The iconomistTest.php may be used as a pattern for writing new tests for other
modules - it shows how to include TDD7, mock Drupal core functions and implement
tests. The heart of the implementation is the use of a namespace, within which
functions are defined with the same name as those being overridden. Since the
invocations in Drupal itself aren't prefixed with namespaces, the definitions
in the file's namespace can override them. These then invoke the static methods
defined in TDD7. The phpunit.conf file includes configuration for generating
code coverage information as well. This is commented out by default as it's not
needed for Jenkins. The output will be placed in a */coverage* directory.

Additional Resources
--------------------

- [General GitHub documentation](http://help.github.com/)

- [GitHub pull request documentation](http://help.github.com/send-pull-requests/)
