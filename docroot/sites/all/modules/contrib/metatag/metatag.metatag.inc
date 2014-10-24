<?php

/**
 * Implements hook_metatag_config_default().
 */
function metatag_metatag_config_default() {
  $configs = array();

  $config = new stdClass();
  $config->instance = 'global';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'title' => array('value' => '[current-page:title] | [site:name]'),
    'generator' => array('value' => 'Drupal 7 (http://drupal.org)'),
    'canonical' => array('value' => '[current-page:url:absolute]'),
    'shortlink' => array('value' => '[current-page:url:unaliased]'),
  );
  $configs[$config->instance] = $config;

  $config = new stdClass();
  $config->instance = 'global:frontpage';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'title' => array('value' => variable_get('site_slogan') ? '[site:name] | [site:slogan]' : '[site:name]'),
    'canonical' => array('value' => '[site:url]'),
    'shortlink' => array('value' => '[site:url]'),
  );
  $configs[$config->instance] = $config;

  $config = new stdClass();
  $config->instance = 'global:403';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'canonical' => array('value' => '[site:url]'),
    'shortlink' => array('value' => '[site:url]'),
  );
  $configs[$config->instance] = $config;

  $config = new stdClass();
  $config->instance = 'global:404';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'canonical' => array('value' => '[site:url]'),
    'shortlink' => array('value' => '[site:url]'),
  );
  $configs[$config->instance] = $config;

  $config = new stdClass();
  $config->instance = 'node';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'title' => array('value' => '[node:title] | [site:name]'),
    'description' => array('value' => '[node:summary]'),
  );
  $configs[$config->instance] = $config;

  if (module_exists('taxonomy')) {
    $config = new stdClass();
    $config->instance = 'taxonomy_term';
    $config->api_version = 1;
    $config->disabled = FALSE;
    $config->config = array(
      'title' => array('value' => '[term:name] | [site:name]'),
      'description' => array('value' => '[term:description]'),
    );
    $configs[$config->instance] = $config;
  }

  $config = new stdClass();
  $config->instance = 'user';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'title' => array('value' => '[user:name] | [site:name]'),
  );
  $configs[$config->instance] = $config;

  // Before returning these, allow the bundled submodules to override them, thus
  // extending the "real" defaults before they can then be altered by other
  // modules.
  // See hook_metatag_bundled_config_alter() in the API documentation.
  drupal_alter('metatag_bundled_config', $configs);

  return $configs;
}

/**
 * Implements hook_metatag_config_instance_info().
 */
function metatag_metatag_config_instance_info() {
  $info['global']           = array('label' => t('Global'));
  $info['global:frontpage'] = array('label' => t('Front page'));
  $info['global:403']       = array('label' => t('403 access denied'));
  $info['global:404']       = array('label' => t('404 page not found'));

  // Add instance information for entities.
  $entity_types = entity_get_info();
  foreach ($entity_types as $entity_type => $entity_info) {
    if (metatag_entity_supports_metatags($entity_type)) {
      $info[$entity_type] = array('label' => $entity_info['label']);
      foreach ($entity_info['bundles'] as $bundle => $bundle_info) {
        if (count($entity_info['bundles'] == 1) && $bundle == $entity_type) {
          // Skip default bundles (entities that do not really have bundles).
          continue;
        }
        if (metatag_entity_supports_metatags($entity_type, $bundle)) {
          $info[$entity_type . ':' . $bundle] = array('label' => $bundle_info['label']);
        }
      }
    }
  }

  return $info;
}

/**
 * Implements hook_metatag_info().
 */
function metatag_metatag_info() {
  $info['groups']['advanced'] = array(
    'label' => t('Advanced'),
    'form' => array(
      '#weight' => 100,
    ),
  );

  // "Simple" meta tags go first.
  $weight = 0;

  $info['tags']['title'] = array(
    'label' => t('Page title'),
    'description' => t("The text to display in the title bar of a visitor's web browser when they view this page. This meta tag may also be used as the title of the page when a visitor bookmarks or favorites this page."),
    'class' => 'DrupalTitleMetaTag',
    'weight' => ++$weight,
  );

  $info['tags']['description'] = array(
    'label' => t('Description'),
    'description' => t("A brief and concise summary of the page's content, preferably 150 characters or less. The description meta tag may be used by search engines to display a snippet about the page in search results."),
    'class' => 'DrupalTextMetaTag',
    'weight' => ++$weight,
    'form' => array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#wysiwyg' => FALSE,
    ),
  );

  $info['tags']['abstract'] = array(
    'label' => t('Abstract'),
    'description' => t("A brief and concise summary of the page's content, preferably 150 characters or less. The abstract meta tag may be used by search engines for archiving purposes."),
    'class' => 'DrupalTextMetaTag',
    'weight' => ++$weight,
    'form' => array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#wysiwyg' => FALSE,
    ),
  );

  $info['tags']['keywords'] = array(
    'label' => t('Keywords'),
    'description' => t("A comma-separated list of keywords about the page. This meta tag is <em>not</em> supported by most search engines."),
    'class' => 'DrupalTextMetaTag',
    'weight' => ++$weight,
  );

  // More advanced meta tags.
  $info['tags']['robots'] = array(
    'label' => t('Robots'),
    'description' => t("Provides search engines with specific directions for what to do when this page is indexed."),
    'class' => 'DrupalListMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
    'form' => array(
      '#options' => array(
        'index' => t('Allow search engines to index this page (assumed).'),
        'follow' => t('Allow search engines to follow links on this page (assumed).'),
        'noindex' => t('Prevents search engines from indexing this page.'),
        'nofollow' => t('Prevents search engines from following links on this page.'),
        'noarchive' => t('Prevents cached copies of this page from appearing in search results.'),
        'nosnippet' => t('Prevents descriptions from appearing in search results, and prevents page caching.'),
        'noodp' => t('Blocks the !opendirectory description from appearing in search results.', array('!opendirectory' => l('Open Directory Project', 'http://www.dmoz.org/'))),
        'noydir' => t('Prevents Yahoo! from listing this page in the <a href="@ydir">Yahoo! Directory</a>.', array('@ydir' => 'http://dir.yahoo.com/')),
        'noimageindex' => t('Prevent search engines from indexing images on this page.'),
        'notranslate' => t('Prevent search engines from offering to translation this page in search results.'),
      ),
    ),
  );

  $info['tags']['news_keywords'] = array(
    'label' => t('Google News Keywords'),
    'description' => t('A comma-separated list of keywords about the page. This meta tag is used as an indicator in <a href="@google_news">Google News</a>.', array('@google_news' => 'http://support.google.com/news/publisher/bin/answer.py?hl=en&answer=68297')),
    'class' => 'DrupalTextMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
  );

  $info['tags']['standout'] = array(
    'label' => t('Google Standout'),
    'description' => t("Highlight standout journalism on the web, especially for breaking news; used as an indicator in <a href=\"@google_news\">Google News</a>. Warning: Don't abuse it, to be used a maximum of 7 times per calendar week!", array('@google_news' => 'https://support.google.com/news/publisher/answer/191283?hl=en&ref_topic=2484650')),
    'class' => 'DrupalTextMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
  );

  $info['tags']['generator'] = array(
    'label' => t('Generator'),
    'description' => t("Describes the name and version number of the software or publishing tool used to create the page."),
    'class' => 'DrupalTextMetaTag',
    'header' => 'X-Generator',
    'context' => array('global'),
    'group' => 'advanced',
    'weight' => ++$weight,
  );

  $info['tags']['rights'] = array(
    'label' => t('Rights'),
    'description' => t("Details about intellectual property, such as copyright or trademarks; does not automatically protect the site's content or intellectual property."),
    'class' => 'DrupalTextMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
    'replaces' => array(
      'copyright',
    ),
  );

  $info['tags']['image_src'] = array(
    'label' => t('Image'),
    'description' => t("An image associated with this page, for use as a thumbnail in social networks and other services."),
    'class' => 'DrupalLinkMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'image',
    ),
  );

  $info['tags']['canonical'] = array(
    'label' => t('Canonical URL'),
    'description' => t("Preferred page location or URL to help eliminate duplicate content for search engines."),
    'class' => 'DrupalLinkMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'canonical',
    ),
  );

  $info['tags']['shortlink'] = array(
    'label' => t('Shortlink URL'),
    'description' => t('A brief URL, often created by a URL shortening service.'),
    'class' => 'DrupalLinkMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'shortlink',
    ),
  );

  $info['tags']['publisher'] = array(
    'label' => t('Publisher URL'),
    'description' => '',
    'class' => 'DrupalLinkMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'url',
    ),
  );

  $info['tags']['author'] = array(
    'label' => t('Author URL'),
    'description' => t("Used by some search engines to confirm authorship of the content on a page. Should be either the full URL for the author's Google+ profile page or a local page with information about the author."),
    'class' => 'DrupalLinkMetaTag',
    'group' => 'advanced',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'url',
    ),
  );

  $info['tags']['original-source'] = array(
    'label' => t('Original Source'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'advanced',
    'description' => t("Used to indicate the URL that broke the story, and can link to either an internal URL or an external source. If the full URL is not known it is acceptable to use a partial URL or just the domain name."),
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'url',
    ),
  );

   $info['tags']['revisit-after'] = array(
     'label' => t('Revisit After'),
     'description' => t('Tell search engines when to index the page again. Very few search engines support this tag, it is more useful to use an <a href="@xmlsitemap">XML Sitemap</a> file.', array('@xmlsitemap' => 'http://drupal.org/project/xmlsitemap')),
     'class' => 'DrupalDateIntervalMetaTag',
     'group' => 'advanced',
     'weight' => ++$weight,
     'devel_generate' => array(
       'type' => 'date',
     ),
   );

   $info['tags']['content-language'] = array(
     'label' => t('Content language'),
     'description' => t("A deprecated meta tag for defining this page's two-letter language code(s)."),
     'class' => 'DrupalTextMetaTag',
     'group' => 'advanced',
     'weight' => ++$weight,
     'element' => array(
       '#theme' => 'metatag_http_equiv',
     ),
   );

  return $info;
}
