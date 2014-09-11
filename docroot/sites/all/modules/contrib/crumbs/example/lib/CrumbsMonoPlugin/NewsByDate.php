<?php

class crumbs_example_CrumbsMonoPlugin_NewsByDate implements crumbs_MonoPlugin {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->setTitle('Breadcrumbs for news/(year)/(month)/(day)');
  }

  /**
   * This one only makes sense if you created a view with path "news/%/%/%"
   *
   * @param string $path
   * @param array $item
   *
   * @return string
   *   A candidate for the breadcrumb item title.
   */
  function findTitle__news_x_x_x($path, $item) {
    // Title will be the day.
    return $item['map'][3];
  }

  /**
   * This one only makes sense if you created a view with path "news/%/%"
   *
   * @param string $path
   * @param array $item
   *
   * @return string
   *   A candidate for the breadcrumb item title.
   */
  function findTitle__news_x_x($path, $item) {
    // Title will be the month. But we want the human-readable version!
    list(, $year, $month) = $item['map'];
    // Pick the middle of the month,
    // so we don't have to think about time zones and rounding.
    $unixtime = strtotime("$year-$month-15");
    // Return full month name as the title.
    return t(date('F', $unixtime));
  }

  /**
   * This one only makes sense if you created a view with path "news/%"
   *
   * @param string $path
   * @param array $item
   *
   * @return string
   *   A candidate for the breadcrumb item title.
   */
  function findTitle__news_x($path, $item) {
    // Title will be the year.
    return $item['map'][1];
  }

  /**
   * Breadcrumb item title for path "news".
   *
   * @param string $path
   * @param array $item
   *
   * @return string
   *   A candidate for the breadcrumb item title.
   */
  function findTitle__news($path, $item) {
    return t('News');
  }
}
