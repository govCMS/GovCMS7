<?php

/**
 * @file
 * Contains AcsfEventDispatcher.
 *
 * This class defines the base event dispatcher. This will take a specified list
 * of handlers and execute them serially. Any handler has the option to
 * interrupt the execution of the event.
 */

namespace Acquia\Acsf;

class AcsfEventDispatcher {

  /**
   * Constructor.
   */
  public function __construct() {
    $this->running = FALSE;
  }

  /**
   * Allows the interruption of the dispatcher.
   */
  public function interrupt() {
    $this->running = FALSE;
  }

  /**
   * Dispatches a list of event handlers.
   *
   * @param AcsfEvent $event
   *   The AcsfEvent that is being executed.
   */
  public function dispatch(AcsfEvent $event) {
    $this->running = TRUE;

    while ($this->running && $handler = $event->popHandler('incomplete')) {
      try {
        // Capture some information about the handler.
        $handler->started = microtime(TRUE);
        $handler->handle();
        $handler->completed = microtime(TRUE);
        $event->pushHandler($handler, 'complete');
      }
      catch (\Exception $e) {
        $handler->message = sprintf('Class %s handler failed for event %s: %s', get_class($handler), $event->type, $e->getMessage());
        $event->pushHandler($handler, 'failed');
      }
    }
  }

}
