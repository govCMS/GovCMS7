<?php


/**
 * Implements hook_crumbs_plugins().
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function views_crumbs_plugins($api) {

  // We try to get all views pages but avoid views_get_all_view() for performance.
  $q = db_select('menu_router', 'mr');
  $q->condition('page_callback', 'views_page');
  $q->fields('mr', array('path', 'page_arguments', 'title', 'title_callback'));

  $staticDisplays = array();
  $dynamicDisplays = array();

  foreach ($q->execute() as $row) {

    if (0
      // Title already given by the menu_router system?
      || !empty($row->title)
      || (!empty($row->title_callback) && 't' !== $row->title_callback)
    ) {
      continue;
    }

    $args = unserialize($row->page_arguments);

    if (2 > count($args)) {
      // Not really a views display, too few arguments.
      continue;
    }
    list($view_name, $view_display_id) = $args;

    if ('%' !== substr($row->path, -1)) {
      // The path does not end with "%", so the title should not depend on a
      // contextual filter.
      $staticDisplays[$view_name][$view_display_id][] = $row->path;
    }
    else {
      // This is a views display with contextual filters.
      # $staticDisplays[$view_name][$view_display_id][] = $row->path;
      $dynamicDisplays[$view_name][$view_display_id][] = $row->path;
    }
  }

  foreach ($staticDisplays as $view_name => $displays) {
    foreach ($displays as $view_display_id => $routes) {
      if (count($routes) > 1) {
        // More than one route for the same views display.
        // This would typically happen with the "Default menu tab" menu setting.
        // However, since these cases are filtered out above, this is rather an
        // edge case, which does not really happen.
        // As an easy solution, we simply pick the shortest or lexigraphically
        // first of the router paths.
        sort($routes);
      }
      $api->routeMonoPlugin(
        $routes[0],
        "pageTitle.$view_name.$view_display_id",
        new views_CrumbsMonoPlugin_PageTitle($view_name, $view_display_id));
    }
  }

  foreach ($dynamicDisplays as $view_name => $displays) {
    foreach ($displays as $view_display_id => $routes) {
      $api->routeMonoPlugin(
        // There should be only one route.
        // If there are more, we take the first.
        $routes[0],
        "argTitle.$view_name.$view_display_id",
        new views_CrumbsMonoPlugin_PageTitle($view_name, $view_display_id));
    }
  }
}

/**
 * Determines a breadcrumb item title based on the view title of a page view.
 * The same plugin class is used for Views displays with or without arguments.
 */
class views_CrumbsMonoPlugin_PageTitle implements crumbs_MonoPlugin_FindTitleInterface {

  /**
   * @var string
   */
  private $displayId;

  /**
   * @var string
   */
  private $viewName;

  /**
   * @param string $view_name
   * @param string $display_id
   */
  function __construct($view_name, $display_id) {
    $this->viewName = $view_name;
    $this->displayId = $display_id;
  }

  /**
   * @param crumbs_InjectedAPI_describeMonoPlugin $api
   *   Injected API object, with methods that allows the plugin to further
   *   describe itself.
   *
   * @return string|void
   *   As an alternative to the API object's methods, the plugin can simply
   *   return a string label.
   */
  function describe($api) {
    return t('Views page title');
  }

  /**
   * {@inheritdoc}
   */
  function findTitle($path, $item) {

    // Some checks, to verify that the menu_router entry has not changed since
    // this Crumbs plugin was created and cached.
    if (0
      || 'views_page' !== $item['page_callback']
      || 2 > count($item['page_arguments'])
      || $this->viewName !== $item['page_arguments'][0]
      || $this->displayId !== $item['page_arguments'][1]
    ) {
      return NULL;
    }

    if ('%' !== substr($item['route'], -1)) {
      return $this->viewsPageTitle();
    }
    else {
      $args = array_slice($item['page_arguments'], 2);
      return $this->viewsArgTitle($args);
    }
  }

  /**
   * Loads the view and determines a breadcrumb item title based on the title
   * configured for this view. This is used if the views path does NOT end with
   * '%'.
   *
   * @return null|string
   */
  private function viewsPageTitle() {

    // Build and initialize the view.
    $view = views_get_view($this->viewName);
    $view->set_display($this->displayId);

    // Trigger the title calculation by calling build_title().
    $view->build_title();
    $title = $view->get_title();

    if (is_string($title) && '' !== $title) {
      // Use decode_entities() to undo duplicate check_plain().
      // See https://drupal.org/comment/7916895#comment-7916895
      return decode_entities($title);
    }

    return NULL;
  }

  /**
   * Loads the view and determines a breadcrumb item title based on the last
   * argument. This is used for views paths that end with '%'.
   *
   * @param array $args
   *   Argument values from the url.
   *
   * @return null|string
   *   A breadcrumb item title for the last argument, or NULL if none found.
   *   This will use the breadcrumb token string configured for the Views arg.
   *
   * @see view::_build_arguments()
   */
  private function viewsArgTitle(array $args) {

    // Build and initialize the view.
    $view = views_get_view($this->viewName);
    $view->set_display($this->displayId);
    $view->set_arguments($args);

    // Trigger the argument calculation by calling build_title().
    $view->build_title();

    // Check the last argument for a breadcrumb item title.
    $last_arg = $this->getRelevantArgument($view->argument);
    if (!isset($last_arg)) {
      return NULL;
    }

    if (!empty($last_arg->options['breadcrumb_enable']) && !empty($last_arg->options['breadcrumb'])) {
      $token_string = $last_arg->options['breadcrumb'];
    }
    elseif (!empty($last_arg->options['title_enable']) && !empty($last_arg->options['title'])) {
      $token_string = $last_arg->options['title'];
    }

    if (!empty($token_string)) {
      // Use decode_entities() to undo duplicate check_plain().
      // See https://drupal.org/comment/7916895#comment-7916895
      return decode_entities(strtr($token_string, $view->build_info['substitutions']));
    }

    return NULL;
  }

  /**
   * @param views_handler_argument[] $arguments
   *
   * @return null|views_handler_argument
   */
  private function getRelevantArgument(array $arguments) {
    while (!empty($arguments)) {
      /** @var views_handler_argument $arg */
      $arg = array_pop($arguments);
      if (1
        && is_object($arg)
        && !$arg->is_exception()
        // Argument must have a value.
        && isset($arg->argument)
      ) {
        return $arg;
      }
    }

    return NULL;
  }

}
