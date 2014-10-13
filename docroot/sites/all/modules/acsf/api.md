ACSF API Documentation
======================

## Events

To handle events ACSF uses a custom event system along with a code registry of event handlers. These events are comprised of a dispatcher which will execute each handler registered in the system for a specified event. Events can be highly composed (e.g. for testing), or can be instantiated and executed simply using a factory method that utilizes system defaults:

### Fully composed event example:

```
$type = 'site_duplication_scrub';
$registry = acsf_get_registry();
$context = array('key' => 'value');
$event = new AcsfEvent(
  new AcsfEventDispatcher(),
  new AcsfLog(),
  $type,
  $registry,
  $context
);
$event->run();
var_dump($event->debug());
```

### Factory method event example:

```
$event = AcsfEvent::create('my_event', array('key' => 'value'));
$event->run();
var_dump($event->debug());
```

Client code that implements `AcsfEventHandler` will have access to the event, including the shared context. Events can be debugged for performance and to check for any exceptions that might have been caught.

```
class AcsfSiteInfoHandler extends AcsfEventHandler {

  /**
   * Implements AcsfEventHandler::handle().
   */
  public function handle() {
    $site = AcsfSite::load();
    $site->refresh();
  }

}
```

Client code may register events using `hook_acsf_registry()`.

*Note:* Custom handler classes must use the same name as their file with a `.inc` extension. For example, the class `AcsfSiteInfoHandler` belongs in `AcsfSiteInfoHandler.inc`. If your class is autoloaded, you may exclude the `path` definition.

```
/**
 * Implements hook_acsf_registry().
 */
function your_module_acsf_registry() {
  return array(
    'events' => array(
      array(
        'weight' => -1,
        'type' => 'acsf_install',
        'class' => 'YourClassName',
        'path' => drupal_get_path('module', 'your_module') . '/classes',
      ),
    ),
  );
}
```

## Messages

All communication from the site to the Factory will be done via the AcsfMessage API. The `AcsfMessage` interface is a wrapper around a HTTP request to the Site Factory. Each implementation must include an `AcsfMessage` compatible class as well as an implementation of `AcsfMessageResponse`.

```
$m = new AcsfMessageRest('GET', 'site-api/v1/sync/', array('site_id' => 406));
$m->send();
$m->getResponseCode();
$m->getResponseBody();
```
