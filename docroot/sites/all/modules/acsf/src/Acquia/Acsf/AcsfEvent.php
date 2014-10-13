<?php

/**
 * @file
 * Contains AcsfEvent.
 *
 * An event within the ACSF framework encapsulates a dispatcher and a list of
 * event handlers. The event will contain an internal context that is accessible
 * from the handlers.
 *
 * $type = 'site_duplication_scrub';
 * $registry = acsf_get_registry();
 * $context = array('key' => 'value');
 * $event = new AcsfEvent(
 *   new AcsfEventDispatcher(),
 *   new AcsfLog(),
 *   $type,
 *   $registry,
 *   $context);
 * $event->run();
 */

namespace Acquia\Acsf;

class AcsfEvent {

  protected $handlers;

  /**
   * Constructor.
   *
   * @param AcsfEventDispatcher $dispatcher
   *   The event dispatcher object.
   * @param AcsfLog $log
   *   The log object.
   * @param string $type
   *   The type of event to run.
   * @param array $registry
   *   The registry from acsf_registry.
   * @param array $context
   *   An arbitrary context for handlers.
   * @param AcsfSite $site
   *   The site being operated upon (optional).
   */
  public function __construct(AcsfEventDispatcher $dispatcher, AcsfLog $log, $type, array $registry, array $context, AcsfSite $site = NULL) {

    $this->dispatcher = $dispatcher;
    $this->log = $log;
    $this->type = $type;
    $this->site = $site;
    $this->registry = $registry;
    $this->context = $context;
    $this->handlers = array(
      'incomplete' => array(),
      'complete' => array(),
      'failed' => array(),
    );
  }

  /**
   * Creates an event using ACSF defaults.
   *
   * @param string $type
   *   The type of event to execute.
   * @param array $context
   *   A custom context to pass to event handlers.
   */
  public static function create($type, array $context = array()) {
    $registry = acsf_get_registry();
    $event = new static(
      new AcsfEventDispatcher(),
      new AcsfLog(),
      $type,
      $registry,
      $context);

    return $event;
  }

  /**
   * Produces data that can be used to track and debug an event.
   */
  public function debug() {
    $debug = array();

    foreach (array_keys($this->handlers) as $key) {
      foreach ($this->handlers[$key] as $handler) {
        $debug['handlers'][$key][] = array(
          'class' => get_class($handler),
          'started' => $handler->started,
          'completed' => $handler->completed,
          'message' => $handler->message,
        );
      }
    }

    return $debug;
  }

  /**
   * Loads event handlers for the appropriate event.
   */
  protected function loadHandlers() {
    foreach ($this->registry['events'] as $info) {
      if ($info['type'] == $this->type) {
        $class = $info['class'];
        if (!empty($info['path'])) {
          $path = trim($info['path'], '/');
          require_once sprintf('%s/%s/%s.inc', DRUPAL_ROOT, $path, $class);
        }
        $this->pushHandler(new $class($this), 'incomplete');
      }
    }
  }

  /**
   * Pops (actually shifts to preserve order) a handler from the internal list.
   *
   * @param string $type
   *   The type of handler: incomplete, complete or failed.
   *
   * @return AcsfEventHandler
   *   The next event handler.
   */
  public function popHandler($type = 'incomplete') {
    if (array_key_exists($type, $this->handlers)) {
      return array_shift($this->handlers[$type]);
    }
    else {
      throw new AcsfEventHandlerIncompatibleException(sprintf('The handler type "%s" is incompatible with this event.', $type));
    }
  }

  /**
   * Pushes a handler to in internal list.
   *
   * @param AcsfEventHandler $handler
   *   The handler to add.
   * @param string $type
   *   The type of handler: incomplete, complete or failed.
   */
  public function pushHandler(AcsfEventHandler $handler, $type = 'incomplete') {
    if (!is_subclass_of($handler, '\Acquia\Acsf\AcsfEventHandler')) {
      throw new AcsfEventHandlerIncompatibleException(sprintf('The handler class "%s" is incompatible with this event, must subclass AcsfEventHandler.', get_class($handler)));
    }

    if (array_key_exists($type, $this->handlers)) {
      $this->handlers[$type][] = $handler;
    }
    else {
      throw new AcsfEventHandlerIncompatibleException(sprintf('The handler type "%s" is incompatible with this event.', $type));
    }
  }

  /**
   * Dispatches all event handlers.
   */
  public function run() {
    $this->loadHandlers();
    $this->dispatcher->dispatch($this);
  }

}
