<?php

/**
 * @file
 * Contains AcsfEventHandler.
 *
 * The purpose of this class is to define an interface for events within Site
 * Factory. Customers who have access to customize their code base can write
 * client code to this interface to interact with events in a standardized way.
 */

namespace Acquia\Acsf;

abstract class AcsfEventHandler {

  // The time that the handler was started.
  public $started = 0;

  // The time that the handler was completed.
  public $completed = 0;

  // Any messages triggered by the handler.
  public $message = '';

  /**
   * Constructor.
   *
   * @param AcsfEvent $event
   *   The event that has been initiated.
   */
  public function __construct(AcsfEvent $event) {
    $this->event = $event;
  }

  /**
   * Handle the event.
   */
  abstract public function handle();

}
