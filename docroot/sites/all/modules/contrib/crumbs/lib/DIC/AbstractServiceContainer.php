<?php

/**
 * Dependency injection container for lazy-instantiated services.
 */
abstract class crumbs_DIC_AbstractServiceContainer {

  /**
   * @var object[]
   */
  private $services = array();

  /**
   * Magic method that is triggered when someone calls $container->$name.
   *
   * @param string $name
   *   The machine name of the service.
   *   Must be a valid PHP identifier, without commas and such.
   *
   * @return object
   */
  function __get($name) {
    return isset($this->services[$name])
      ? $this->services[$name]
      // Create the service, if it does not already exist.
      : $this->services[$name] = $this->createService($name);
  }

  /**
   * @param string $name
   *
   * @return object
   *   The service.
   * @throws Exception
   */
  private function createService($name) {
    // Method to be implemented in a subclass.
    $method = $name;
    if (!method_exists($this, $method)) {
      throw new \Exception("Unknown service '$name'.");
    }
    return $this->$method();
  }

} 
