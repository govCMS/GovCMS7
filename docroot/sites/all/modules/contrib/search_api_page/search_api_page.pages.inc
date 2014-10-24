<?php
/**
 * @file
 * User page callbacks for the Search pages module.
 */

/**
 * Displays a search page.
 *
 * @param $id
 *   The search page's machine name.
 * @param $keys
 *   The keys to search for.
 */
function search_api_page_view($id, $keys = NULL) {
  $page = search_api_page_load($id);
  if (!$page) {
    return MENU_NOT_FOUND;
  }

  // Pre-process keys (unescape \ and /).
  $keys = explode("\\\\", $keys);
  $keys = str_replace("\\", "/", $keys);
  $keys = implode("\\", $keys);

  $ret['#contextual_links']['search_api_page'] = array(
    'admin/config/search/search_api/page',
    array($page->machine_name),
  );

  if (!isset($page->options['result_page_search_form']) || $page->options['result_page_search_form']) {
    $ret['form'] = drupal_get_form('search_api_page_search_form', $page, $keys);
  }

  if ($keys) {
    // Override per_page setting with GET parameter.
    $limit = $page->options['per_page'];
    if (!empty($page->options['get_per_page'])
        && !empty($_GET['per_page'])
        && ((int) $_GET['per_page']) > 0) {
      $limit = (int) $_GET['per_page'];
    }

    try {
      $results = search_api_page_search_execute($page, $keys, $limit);
    }
    catch (SearchApiException $e) {
      drupal_set_message(t('An error occurred while executing the search. Please try again, or contact the site administrator if the problem persists.'), 'error');
      $link = l(t('search page'), $_GET['q'], array('query' => drupal_get_query_parameters()));
      watchdog_exception('search_api_page', $e,
          '%type while executing a search: !message in %function (line %line of %file).',
          array(), WATCHDOG_ERROR, $link);
      return $ret;
    }

    // If spellcheck results were returned then add them to the render array.
    if (isset($results['search_api_spellcheck'])) {
      $ret['results']['#spellcheck'] = array(
        '#theme' => 'search_api_spellcheck',
        '#spellcheck' => $results['search_api_spellcheck'],
      // Let the theme function know where the key is stored by passing its arg
      // number. We can work this out from the number of args in the page path.
        '#options' => array(
          'arg' => array(count(arg(NULL, $page->path))),
        ),
        '#prefix' => '<p class="search-api-spellcheck-suggestion">',
        '#suffix' => '</p>',
      );
    }

    $ret['results']['#theme'] = "search_api_page_results__{$page->machine_name}";
    $ret['results']['#index'] = search_api_index_load($page->index_id);
    $ret['results']['#results'] = $results;
    $ret['results']['#view_mode'] = isset($page->options['view_mode']) ? $page->options['view_mode'] : 'search_api_page_result';
    $ret['results']['#keys'] = $keys;
    $ret['results']['#page'] = $page;

    // Load pager.
    if ($results['result count'] > $limit) {
      pager_default_initialize($results['result count'], $limit);
      $ret['results']['#pager']['#theme'] = 'pager';
    }

    if (!empty($results['ignored'])) {
      drupal_set_message(t('The following search keys are too short or too common and were therefore ignored: "@list".', array('@list' => implode(t('", "'), $results['ignored']))), 'warning');
    }
    if (!empty($results['warnings'])) {
      foreach ($results['warnings'] as $warning) {
        drupal_set_message(check_plain($warning), 'warning');
      }
    }
  }

  return $ret;
}

/**
 * Executes a search.
 *
 * @param Entity $page
 *   The page for which a search should be executed.
 * @param string $keys
 *   The keywords to search for.
 * @param int $limit
 *   The maximum number of results to return.
 *
 * @return array
 *   The search results as returned by SearchApiQueryInterface::execute().
 *
 * @throws SearchApiException
 *   If an error occurred during the search.
 */
function search_api_page_search_execute(Entity $page, $keys, $limit = 10) {
  $offset = pager_find_page() * $limit;
  $options = array(
    'search id' => 'search_api_page:' . $page->path,
    'search_api_page id' => $page->machine_name,
    'parse mode' => $page->options['mode'],
  );

  if (!empty($page->options['search_api_spellcheck'])) {
    $options['search_api_spellcheck'] = TRUE;
  }

  $query = search_api_query($page->index_id, $options)
    ->keys($keys)
    ->range($offset, $limit);
  if (!empty($page->options['fields'])) {
    $query->fields($page->options['fields']);
  }
  if (!empty($page->options['language_filter'])) {
    $languages = array_unique(array_map('_search_api_page_map_languages', $page->options['language_filter']));
    if (count($languages) == 1) {
      $query->condition('search_api_language', reset($languages));
    }
    else {
      $filter = $query->createFilter('OR');
      foreach ($languages as $lang) {
        $filter->condition('search_api_language', $lang);
      }
      $query->filter($filter);
    }
  }
  return $query->execute();
}

/**
 * Maps some special languages to their correct value.
 *
 * Callback for array_map() in search_api_page_search_execute().
 *
 * @param string $lang
 *   "current", "default" or a valid ISO 639 language code.
 *
 * @return string
 *   The ISO 639 language code of the language represented by $lang.
 */
function _search_api_page_map_languages($lang) {
    if ($lang == 'current') {
      return $GLOBALS['language_content']->language;
    }
    elseif ($lang == 'default') {
      return language_default('language');
    }
    return $lang;
}

/**
 * Preprocess variables for search-api-page-results.tpl.php.
 *
 * @param array $variables
 *   An associative array containing:
 *   - index: The index this search was executed on.
 *   - results: An array of search results, as returned by
 *     SearchApiQueryInterface::execute().
 *   - view_mode: The view mode to use for results. Either one of the searched
 *     entity's view modes (if applicable), or "search_api_page_result" to use
 *     the module's builtin theme function to render results.
 *   - keys: The keywords of the executed search.
 *   - page: The search page whose search results are being displayed.
 *
 * @see search-api-page-results.tpl.php
 */
function template_preprocess_search_api_page_results(array &$variables) {
  $results = $variables['results'];

  $variables['items'] = $variables['index']->loadItems(array_keys($variables['results']['results']));
  $variables['result_count'] = $results['result count'];
  $variables['sec'] = round($results['performance']['complete'], 3);
  $variables['search_performance'] = array(
      '#theme' => 'search_api_page_search_performance',
      '#markup' => format_plural(
        $results['result count'],
        'The search found 1 result in @sec seconds.',
        'The search found @count results in @sec seconds.',
        array('@sec' => $variables['sec'])
      ),
      '#prefix' => '<p class="search-performance">',
      '#suffix' => '</p>',
  );

  // Make the help text depend on the parse mode used.
  switch ($variables['page']->options['mode']) {
    case 'direct':
      if ($variables['index']->server()->class == 'search_api_solr') {
        $variables['no_results_help'] = t('<ul>
<li>Check if your spelling is correct.</li>
<li>Remove quotes around phrases to search for each word individually. <em>bike shed</em> will often show more results than <em>&quot;bike shed&quot;</em>.</li>
<li>Consider loosening your query with <em>OR</em>. <em>bike OR shed</em> will often show more results than <em>bike shed</em>.</li>
</ul>');
      }
      else {
        $variables['no_results_help'] = t('<ul>
<li>Check if your spelling is correct.</li>
<li>Use fewer keywords to increase the number of results.</li>
</ul>');
      }
      break;
    case 'single':
      $variables['no_results_help'] = t('<ul>
<li>Check if your spelling is correct.</li>
<li>Use fewer keywords to increase the number of results.</li>
</ul>');
      break;
    case 'terms':
      $variables['no_results_help'] = t('<ul>
<li>Check if your spelling is correct.</li>
<li>Remove quotes around phrases to search for each word individually. <em>bike shed</em> will often show more results than <em>&quot;bike shed&quot;</em>.</li>
<li>Use fewer keywords to increase the number of results.</li>
</ul>');
      break;
  }

  // Prepare CSS classes.
  $classes_array = array(
    'search-api-page',
    'search-api-page-' . drupal_clean_css_identifier($variables['page']->machine_name),
    'view-mode-' . drupal_clean_css_identifier($variables['view_mode']),
  );
  $variables['classes'] = implode(' ', $classes_array);

  // Distinguish between the native search_api_page_result "view mode" and
  // proper entity view modes (e.g., Teaser, Full content, RSS and so forth).
  if ($variables['view_mode'] != 'search_api_page_result') {
    $variables['search_results'] = entity_view($variables['index']->getEntityType(), $variables['items'], $variables['view_mode']);
  }
  else {
    $variables['search_results'] = array();
    foreach ($results['results'] as $item) {
      $variables['search_results'][] = array(
        '#theme' => 'search_api_page_result',
        '#index' => $variables['index'],
        '#result' => $item,
        '#item' => $variables['items'][$item['id']],
      );
    }
  }
  // Load CSS.
  $base_path = drupal_get_path('module', 'search_api_page') . '/';
  drupal_add_css($base_path . 'search_api_page.css');
}

/**
 * Process variables for search-result.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $result
 *
 * @see search_api_page-result.tpl.php
 */
function template_preprocess_search_api_page_result(&$variables) {
  $index = $variables['index'];
  $variables['id'] = $variables['result']['id'];
  $item = $variables['item'];

  $wrapper = $index->entityWrapper($item, FALSE);

  $variables['url'] = $index->datasource()->getItemUrl($item);
  $variables['title'] = $index->datasource()->getItemLabel($item);

  if (!empty($variables['result']['excerpt'])) {
    $variables['excerpt'] = $variables['result']['excerpt'];
    $text = $variables['result']['excerpt'];
  }
  else {
    $fields = $index->options['fields'];
    $fields = array_intersect_key($fields, drupal_map_assoc($index->getFulltextFields()));
    $fields = search_api_extract_fields($wrapper, $fields);
    $text = '';
    $length = 0;
    foreach ($fields as $field_name => $field) {
      if (search_api_is_list_type($field['type']) || !isset($field['value'])) {
        continue;
      }
      $val_length = drupal_strlen($field['value']);
      if ($val_length > $length) {
        $text = $field['value'];
        $length = $val_length;

        $format = NULL;
        if (($pos = strrpos($field_name, ':')) && substr($field_name, $pos + 1) == 'value') {
          $tmp = $wrapper;
          try {
            foreach (explode(':', substr($field_name, 0, $pos)) as $part) {
              if (!isset($tmp->$part)) {
                $tmp = NULL;
              }
              $tmp = $tmp->$part;
            }
          }
          catch (EntityMetadataWrapperException $e) {
            $tmp = NULL;
          }
          if ($tmp && $tmp->type() == 'text_formatted' && isset($tmp->format)) {
            $format = $tmp->format->value();
          }
        }
      }
    }
    if ($text && function_exists('text_summary')) {
      $text = text_summary($text, $format);
    }
  }

  // Check for existence. User search does not include snippets.
  $variables['snippet'] = isset($text) ? $text : '';

  // Meta information
  global $language;
  if (isset($item->language) && $item->language != $language->language && $item->language != LANGUAGE_NONE) {
    $variables['title_attributes_array']['xml:lang'] = $item->language;
    $variables['content_attributes_array']['xml:lang'] = $item->language;
  }

  $info = array();
  if (!empty($item->name)) {
    $info['user'] = $item->name;
  }
  if (!empty($item->created)) {
    $info['date'] = format_date($item->created, 'short');
  }
  // Provide separated and grouped meta information..
  $variables['info_split'] = $info;
  $variables['info'] = implode(' - ', $info);
}
