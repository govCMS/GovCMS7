Feature: External Libraries

  Ensure the external libraries are available

  Scenario: Load the html5-placeholder-shim file
    Given I am on "profiles/agov/libraries/html5placeholder/jquery.html5-placeholder-shim.js"
    Then the response status code should be 200
