Feature: External Libraries

  Ensure the external libraries are available

  Scenario: Load the html5-placeholder-shim file
    When I visit "profiles/govcms/libraries/html5placeholder/jquery.placeholder.js"
    Then the response status code should be 200
