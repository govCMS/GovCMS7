<?php

/**
 * @file
 * Provides PHPUnit tests for the Acsf Events system.
 */

/**
 * Defines the Drupal root directory as the acsf directory.
 */
define('DRUPAL_ROOT', __DIR__ . '/..');

class UnitTest extends PHPUnit_Framework_TestCase {

  public function setUp() {
    $files = array(
      __DIR__ . '/../vendor/autoload.php',
      __DIR__ . '/UnitTestDummyHandler1.inc',
      __DIR__ . '/UnitTestDummyHandler2.inc',
      __DIR__ . '/UnitTestDummyHandler3.inc',
      __DIR__ . '/UnitTestDummyHandlerInterrupt.inc',
      __DIR__ . '/UnitTestDummyHandlerIncompatible.inc',
    );
    foreach ($files as $file) {
      require_once $file;
    }
  }

  /**
   * Tests that the handlers are initially empty.
   */
  public function testAcsfEventHandlersEmpty() {
    $event = new \Acquia\Acsf\AcsfEvent(new \Acquia\Acsf\AcsfEventDispatcher(), new \Acquia\Acsf\AcsfLog(), 'unit_test', array(), array());
    $this->assertEmpty($event->debug());
  }

  /**
   * Tests that the push and pop methods work as expected.
   */
  public function testAcsfEventPushPop() {
    $classes = array(
      'UnitTestDummyHandler1',
      'UnitTestDummyHandler2',
      'UnitTestDummyHandler3',
    );
    $event = new \Acquia\Acsf\AcsfEvent(new \Acquia\Acsf\AcsfEventDispatcher(), new \Acquia\Acsf\AcsfLog(), 'unit_test', array(), array());
    foreach ($classes as $class) {
      $event->pushHandler(new $class($event));
    }
    $debug = $event->debug();
    $this->assertCount(3, $debug['handlers']['incomplete']);
    $handlers = array();
    while ($handler = $event->popHandler()) {
      $handlers[] = $handler;
    }
    $this->assertCount(3, $handlers);
    $this->assertEmpty($event->debug());
  }

  /**
   * Tests that events get run as expected.
   */
  public function testAcsfEventExecute() {
    $registry = acsf_get_registry();
    $event = new \Acquia\Acsf\AcsfEvent(new \Acquia\Acsf\AcsfEventDispatcher(), new \Acquia\Acsf\AcsfLog(), 'unit_test', $registry, array());
    $event->run();
    $debug = $event->debug();
    $this->assertCount(3, $debug['handlers']['complete']);
  }

  /**
   * Tests that the events system handles interrupts correctly.
   */
  public function testAcsfEventInterrupt() {
    $registry = acsf_get_registry(TRUE);
    $event = new \Acquia\Acsf\AcsfEvent(new \Acquia\Acsf\AcsfEventDispatcher(), new \Acquia\Acsf\AcsfLog(), 'unit_test', $registry, array());
    $event->run();
    $debug = $event->debug();
    $this->assertCount(1, $debug['handlers']['incomplete']);
    $this->assertCount(3, $debug['handlers']['complete']);
  }

  /**
   * Tests the create method.
   */
  public function testAcsfEventCreate() {
    $event = \Acquia\Acsf\AcsfEvent::create('unit_test', array());
    $event->run();
    $debug = $event->debug();
    $this->assertCount(3, $debug['handlers']['complete']);
  }

  /**
   * Tests that incompatible handlers may not be added.
   *
   * @expectedException PHPUnit_Framework_Error
   */
  public function testAcsfEventHandlerIncompatibleClass() {
    $event = new \Acquia\Acsf\AcsfEvent(new \Acquia\Acsf\AcsfEventDispatcher(), new \Acquia\Acsf\AcsfLog(), 'unit_test', array(), array());
    // UnitTestDummyHandlerIncompatible erroneously extends stdClass when it
    // should be a subclass of AcsfEventHandler.
    $event->pushHandler(new UnitTestDummyHandlerIncompatible());
  }

  /**
   * Tests that incompatible handler types may not be used.
   *
   * @expectedException \Acquia\Acsf\AcsfEventHandlerIncompatibleException
   */
  public function testAcsfEventHandlerIncompatibleType() {
    $registry = acsf_get_registry(FALSE, 'UnitTestDummyHandler1');
    $event = new \Acquia\Acsf\AcsfEvent(new \Acquia\Acsf\AcsfEventDispatcher(), new \Acquia\Acsf\AcsfLog(), 'unit_test', $registry, array());
    // Pass in a bogus handler type to trigger an exception.
    $event->popHandler('bogus_type');
  }

}

/**
 * Mocks acsf_get_registry for testing.
 *
 * The real function returns an array of event handlers, much the same as what
 * this version of the function returns, except that this function returns dummy
 * data.
 *
 * @param bool $include_interrupt
 *   Whether or not to include the interrupt class, which will interrupt the
 *   event processing so that feature may be tested.
 * @param string $handler
 *   A specific handler to return.
 *
 * @return array
 *   An array of dummy event handlers.
 */
function acsf_get_registry($include_interrupt = FALSE, $handler = NULL) {
  $classes = array(
    'UnitTestDummyHandler1',
    'UnitTestDummyHandler2',
    'UnitTestDummyHandlerInterrupt',
    'UnitTestDummyHandler3',
  );
  if (!$include_interrupt) {
    $classes = array_diff($classes, array('UnitTestDummyHandlerInterrupt'));
  }
  if ($handler) {
    $classes = array_intersect($classes, array($handler));
  }
  $handlers = array();
  foreach ($classes as $class) {
    $handlers[] = array(
      'type' => 'unit_test',
      'class' => $class,
      'path' => 'tests'
    );
  }
  return array('events' => $handlers);
}

