<?php

require_once __DIR__ . '/../vendor/autoload.php';

class UnitTestDummyHandlerInterrupt extends \Acquia\Acsf\AcsfEventHandler {
  public function handle() {
    $this->event->dispatcher->interrupt();
  }
}

