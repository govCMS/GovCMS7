<?php

/**
 * Creates various data related to the current page.
 *
 * The data is provided to the rest of the world via crumbs_Container_LazyData.
 * Each method in here corresponds to one key on the data cache.
 *
 * The $page argument on each method is the data cache itself.
 * The argument can be mocked with a simple stdClass, to test the behavior of
 * each method. (if we had the time to write unit tests)
 *
 * @property bool $breadcrumbSuppressed
 * @property array $breadcrumbData
 * @property array $trail
 * @property array $rawBreadcrumbItems
 * @property bool $showCurrentPage
 * @property bool $trailingSeparator
 * @property bool $showFrontPage
 * @property int $minTrailItems
 * @property string $separator
 * @property string $separatorSpan
 * @property int $minVisibleItems
 * @property array $breadcrumbItems
 * @property string $breadcrumbHtml
 * @property string $path
 *
 * @see crumbs_Container_AbstractLazyData::__get()
 * @see crumbs_Container_AbstractLazyData::__set()
 */
class crumbs_CurrentPageInfo extends crumbs_Container_AbstractLazyData {

  /**
   * @var crumbs_TrailCache
   */
  protected $trails;

  /**
   * @var crumbs_BreadcrumbBuilder
   */
  protected $breadcrumbBuilder;

  /**
   * @var crumbs_Router
   */
  protected $router;

  /**
   * @param crumbs_TrailCache $trails
   * @param crumbs_BreadcrumbBuilder $breadcrumbBuilder
   * @param crumbs_Router $router
   */
  function __construct($trails, $breadcrumbBuilder, $router) {
    $this->trails = $trails;
    $this->breadcrumbBuilder = $breadcrumbBuilder;
    $this->router = $router;
  }

  /**
   * Check if the breadcrumb is to be suppressed altogether.
   *
   * @return bool
   *
   * @see crumbs_CurrentPageInfo::$breadcrumbSuppressed
   */
  protected function breadcrumbSuppressed() {
    // @todo Make this work!
    return FALSE;
    $existing_breadcrumb = drupal_get_breadcrumb();
    // If the existing breadcrumb is empty, that means a module has
    // intentionally removed it. Honor that, and stop here.
    return empty($existing_breadcrumb);
  }

  /**
   * Assemble all breadcrumb data.
   *
   * @return array
   *
   * @see crumbs_CurrentPageInfo::$breadcrumbData
   */
  protected function breadcrumbData() {
    if (empty($this->breadcrumbItems)) {
      return FALSE;
    }
    return array(
      'trail' => $this->trail,
      'items' => $this->breadcrumbItems,
      'html' => $this->breadcrumbHtml,
    );
  }

  /**
   * Build the Crumbs trail.
   *
   * @return array
   *
   * @see crumbs_CurrentPageInfo::$trail
   */
  protected function trail() {
    return $this->trails->getForPath($this->path);
  }

  /**
   * Build the raw breadcrumb based on the $page->trail.
   *
   * Each breadcrumb item is a router item taken from the trail, with
   * two additional/updated keys:
   * - title: The title of the breadcrumb item as received from a plugin.
   * - localized_options: An array of options passed to l() if needed.
   *
   * The altering will happen in a separate step, so
   *
   * @return array
   *
   * @see crumbs_CurrentPageInfo::$rawBreadcrumbItems
   */
  protected function rawBreadcrumbItems() {
    if ($this->breadcrumbSuppressed) {
      return array();
    }
    if (user_access('administer crumbs')) {
      // Remember which pages we are visiting,
      // for the autocomplete on admin/structure/crumbs/debug.
      unset($_SESSION['crumbs.admin.debug.history'][$this->path]);
      $_SESSION['crumbs.admin.debug.history'][$this->path] = TRUE;
      // Never remember more than 15 links.
      while (15 < count($_SESSION['crumbs.admin.debug.history'])) {
        array_shift($_SESSION['crumbs.admin.debug.history']);
      }
    }
    $trail = $this->trail;
    if (count($trail) < $this->minTrailItems) {
      return array();
    }
    if (!$this->showFrontPage) {
      array_shift($trail);
    }
    if (!$this->showCurrentPage) {
      array_pop($trail);
    }
    if (!count($trail)) {
      return array();
    }
    $items = $this->breadcrumbBuilder->buildBreadcrumb($trail);
    if (count($items) < $this->minVisibleItems) {
      // Some items might get lost due to having an empty title.
      return array();
    }
    return $items;
  }

  /**
   * Determine if we want to show the breadcrumb item for the current page.
   *
   * @return bool
   *
   * @see crumbs_CurrentPageInfo::$showCurrentPage
   */
  protected function showCurrentPage() {
    return variable_get('crumbs_show_current_page', FALSE) & ~CRUMBS_TRAILING_SEPARATOR;
  }

  /**
   * @return bool
   *
   * @see crumbs_CurrentPageInfo::$trailingSeparator
   */
  protected function trailingSeparator() {
    return variable_get('crumbs_show_current_page', FALSE) & CRUMBS_TRAILING_SEPARATOR;
  }

  /**
   * Determine if we want to show the breadcrumb item for the front page.
   *
   * @return bool
   *
   * @see crumbs_CurrentPageInfo::$showFrontPage
   */
  protected function showFrontPage() {
    return variable_get('crumbs_show_front_page', TRUE);
  }

  /**
   * If there are fewer trail items than this, we hide the breadcrumb.
   *
   * @return int
   *
   * @see crumbs_CurrentPageInfo::$minTrailItems
   */
  protected function minTrailItems() {
    return variable_get('crumbs_minimum_trail_items', 2);
  }

  /**
   * Determine separator string, e.g. ' &raquo; ' or ' &gt; '.
   *
   * @return string
   *
   * @see crumbs_CurrentPageInfo::$separator
   */
  protected function separator() {
    return variable_get('crumbs_separator', ' &raquo; ');
  }

  /**
   * Determine separator string, e.g. ' &raquo; ' or ' &gt; '.
   *
   * @return string
   *
   * @see crumbs_CurrentPageInfo::$separatorSpan
   */
  protected function separatorSpan() {
    return variable_get('crumbs_separator_span', FALSE);
  }

  /**
   * If there are fewer visible items than this, we hide the breadcrumb.
   * Every "trail item" does become a "visible item", except when it is hidden:
   * - The frontpage item might be hidden based on a setting.
   * - The current page item might be hidden based on a setting.
   * - Any item where the title is FALSE will be hidden / skipped over.
   *
   * @return int
   *
   * @see crumbs_CurrentPageInfo::$minVisibleItems
   */
  protected function minVisibleItems() {
    $n = $this->minTrailItems;
    if (!$this->showCurrentPage) {
      --$n;
    }
    if (!$this->showFrontPage) {
      --$n;
    }
    return $n;
  }

  /**
   * Build altered breadcrumb items.
   *
   * @return array
   *
   * @see crumbs_CurrentPageInfo::$breadcrumbItems
   */
  protected function breadcrumbItems() {
    $breadcrumb_items = $this->rawBreadcrumbItems;
    if (empty($breadcrumb_items)) {
      return array();
    }
    $router_item = $this->router->getRouterItem($this->path);
    // Allow modules to alter the breadcrumb, if possible, as that is much
    // faster than rebuilding an entirely new active trail.
    drupal_alter('menu_breadcrumb', $breadcrumb_items, $router_item);
    return $breadcrumb_items;
  }

  /**
   * Build the breadcrumb HTML.
   *
   * @return string
   *
   * @see crumbs_CurrentPageInfo::$breadcrumbHtml
   */
  protected function breadcrumbHtml() {
    $breadcrumb_items = $this->breadcrumbItems;
    if (empty($breadcrumb_items)) {
      return '';
    }
    $links = array();
    if ($this->showCurrentPage) {
      $last = array_pop($breadcrumb_items);
      foreach ($breadcrumb_items as $i => $item) {
        $links[$i] = theme('crumbs_breadcrumb_link', $item);
      }
      $links[] = theme('crumbs_breadcrumb_current_page', array(
        'item' => $last,
        'show_current_page' => $this->showCurrentPage,
      ));
    }
    else {
      foreach ($breadcrumb_items as $i => $item) {
        $links[$i] = theme('crumbs_breadcrumb_link', $item);
      }
    }
    return theme('breadcrumb', array(
      'breadcrumb' => $links,
      'crumbs_breadcrumb_items' => $breadcrumb_items,
      'crumbs_trail' => $this->trail,
      'crumbs_separator' => $this->separator,
      'crumbs_separator_span' => $this->separatorSpan,
      'crumbs_trailing_separator' => $this->trailingSeparator,
    ));
  }

  /**
   * Determine current path.
   *
   * @return string
   *
   * @see crumbs_CurrentPageInfo::$path
   */
  protected function path() {
    return $_GET['q'];
  }

}
