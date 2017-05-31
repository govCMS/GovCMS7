# Introduction

The TDD7 is a unit testing framework for Drupal 7. It is not used in the
production code, but instead to make writing unit tests much much easier and
faster. It's designed to work with PHPUnit and does not need to bootstrap
an entire database, such as happens when using the DrupalWebTestCase with the
simpletest framework.

# How it works

All unit tests need a predefined set of data to work with. In simple examples,
this data is provided as function arguments. In Drupal, this data often comes
from the database. When using simpletest, a replica of the drupal database
structure is provided with an alternate database prefix. When using TDD7, the
database and node structure is mocked up in software, which is much faster.

When using TDD7, production code is moved out of the root namespace into
individual namespaces, using wrapper functions.

*Example here*

When this function is being tested, a set of wrapper functions such as
*node_load()* that call the the mock framework is loaded in the same namespace
as the tested function. The test data is loaded into the test framework.
When the tested function is run, it will call the wrapper functions instead of
the core functions, and the appropriate mock data will be returned.

# Concepts

## Production code
Production code refers to code that is deployed, and used in the end product.
This differs from mocks, rigging, and various other testing code that should
never be run on the production system.

## System Under Test
The 'System Under Test' or 'SUT' is the function, method, class or other code
that we are testing. This differs from testing code, core Drupal code, or
other modules that we are not testing.

## Writing tests first
Summarise here, writing the top level requirement and working back from there,
and red / green testing. Refer to other documents here.

## Namespacing
Using namespaces is an imperative part of using the TDD7 framework. Production
code should live in it's own namespace, usually divided on a per module basis.
Functions and classes can have the same name if they reside in different
namespaces.

If a function is called without a namespace prefix, and that function is not
found within the current namespace, PHP will look for that function in the
default namespace. We can use this in unit testing to provide override core
functions and provide predictable responses.

References:
* http://php.net/manual/en/language.namespaces.php


## Mocks
Mocks are classes and functions that look and respond like core PHP and Drupal
functions, but return test data. This test data should be loaded at the start of
each test.

## Wrapping Namespaced Code
Drupal hooks are in the global namespace, and test driven development requires
us to keep our production code out of the global namespace so that we can use
mock classes and functions.
To get around this problem, we call our module code from wrapper functions.
These wrapper functions should be a single line of code that passes all
arguments, and return the results without making any changes.

	<?php
	/**
	 * @file mymodule.module
	 */
	function mymodule_theme($existing = array(), $type = '', $theme = '', $path = '') {
	  return \myorg\mymodule\mymodule_theme($existing, $type, $theme, $path);
	}

This may sometimes be erroneously be referred to as a function stub.

## Basefixtures
Basefixtures contain the boilerplate code required to load and use the TDD7
module easily. This will include things such as the namespaced *node_load()*
functions.

## Rigging
Rigging builds on base test cases and enables the testing of commonly tested
drupal functions. This includes common items such as menu hook validity,
form array validity, callback existence and so on.

# Examples

## Using the Node mock
See the following files:
* docs/examples/ExampleDrupalNodeMock.inc
* docs/examples/tests/ExampleDrupalNodeMockTest.php

## Using Database mock
See the following files:
* docs/examples/ExampleDrupalDbMock.inc
* docs/examples/tests/ExampleDrupalDbMockTest.php

# To Do
?