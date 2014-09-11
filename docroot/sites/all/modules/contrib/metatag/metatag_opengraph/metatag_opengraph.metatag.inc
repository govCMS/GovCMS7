<?php

/**
 * @file
 * Metatag integration for the metatag_opengraph module.
 */

/**
 * Implements hook_metatag_config_default_alter().
 */
function metatag_opengraph_metatag_config_default_alter(array &$configs) {
  foreach ($configs as &$config) {
    switch ($config->instance) {
      case 'global':
        $config->config += array(
          'og:type' => array('value' => 'article'),
          'og:title' => array('value' => '[current-page:title]'),
          'og:site_name' => array('value' => '[site:name]'),
          'og:url' => array('value' => '[current-page:url:absolute]'),
        );
        break;
      case 'global:frontpage':
        $config->config += array(
          'og:type' => array('value' => 'website'),
          'og:title' => array('value' => '[site:name]'),
          'og:url' => array('value' => '[site:url]'),
        );
        break;
      case 'node':
        $config->config += array(
          'og:title' => array('value' => '[node:title]'),
          'og:description' => array('value' => '[node:summary]'),
        );
        break;
      case 'taxonomy_term':
        $config->config += array(
          'og:title' => array('value' => '[term:name]'),
          'og:description' => array('value' => '[term:description]'),
        );
        break;
      case 'user':
        $config->config += array(
          'og:type' => array('value' => 'profile'),
          'og:title' => array('value' => '[user:name]'),
        );
        if (variable_get('user_pictures')) {
          $config->config += array(
            'og:image' => array('value' => '[user:picture:url]'),
          );
        }

        break;
    }
  }
}

/**
 * Implements hook_metatag_info().
 */
function metatag_opengraph_metatag_info() {
  $info['groups']['open-graph'] = array(
    'label' => t('Open Graph'),
    'form' => array(
      '#weight' => 50,
    ),
  );

  $info['tags']['fb:admins'] = array(
    'label' => t('Facebook Admins'),
    'description' => t('A comma-separated list of Facebook user IDs of people who are considered administrators or moderators of this page. Most sites will only need to assign this on the global settings page.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['fb:app_id'] = array(
    'label' => t('Facebook Application ID'),
    'description' => t('A comma-separated list of Facebook Platform Application IDs applicable for this site. Most sites will only need to assign this on the global settings page.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  if (module_exists('fb_social')) {
    $info['tags']['fb:app_id']['form']['#disabled'] = TRUE;
    $info['tags']['fb:app_id']['form']['#description'] = t('The FB_Social module will automatically output this meta tag, go to the <a href="!fb_social">FB_Social settings page</a> to customize it.', array('!fb_social' => url('admin/config/user-interface/fb_social')));
  }

  $info['tags']['og:site_name'] = array(
    'label' => t('Open Graph site name'),
    'description' => t('A human-readable name for your site, e.g., <em>IMDb</em>.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'context' => array('global'),
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );

  $info['tags']['og:title'] = array(
    'label' => t('Open Graph title'),
    'description' => t('The title of your object as it should appear within the graph, e.g., <em>The Rock</em>.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );

  $info['tags']['og:description'] = array(
    'label' => t('Open Graph description'),
    'description' => t('A one to two sentence description of your page.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );

  $info['tags']['og:type'] = array(
    'label' => t('Open Graph type'),
    'description' => t('The type of your object, e.g., <em>movie</em>.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
    'form' => array(
      '#type' => 'select',
      '#options' => _metatag_opengraph_type_options(),
      '#empty_option' => t('- None -'),
    ),
  );

  if (module_exists('select_or_other')) {
    // Enhance the og:type field to support custom types.
    $info['tags']['og:type']['form']['#type'] = 'select_or_other';
    $info['tags']['og:type']['form']['#other'] = t('Other (please type a value)');
    $info['tags']['og:type']['form']['#other_unknown_defaults'] = 'other';
    $info['tags']['og:type']['form']['#theme'] = 'select_or_other';
    $info['tags']['og:type']['form']['#element_validate'] = array('select_or_other_element_validate');
  }

  $info['tags']['og:image'] = array(
    'label' => t('Open Graph image'),
    'description' => t('An image URL which should represent your object within the graph. The image must be at least 50px by 50px and have a maximum aspect ratio of 3:1. We support PNG, JPEG and GIF formats.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );

  $info['tags']['og:url'] = array(
    'label' => t('Open Graph URL'),
    'description' => t('The canonical URL of your object that will be used as its permanent ID in the graph, e.g., <em>http://www.imdb.com/title/tt0117500/</em>.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );

  $info['tags']['og:latitude'] = array(
    'label' => t('Open Graph Latitude'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:longitude'] = array(
    'label' => t('Open Graph Longitude'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );

  $info['tags']['og:street-address'] = array(
    'label' => t('Open Graph Street Address'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:locality'] = array(
    'label' => t('Open Graph Locality'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:region'] = array(
    'label' => t('Open Graph Region'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:postal-code'] = array(
    'label' => t('Open Graph Postal Code'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:country-name'] = array(
    'label' => t('Open Graph Country Name'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );

  $info['tags']['og:email'] = array(
    'label' => t('Open Graph Email'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:phone_number'] = array(
    'label' => t('Open Graph Phone Number'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:fax_number'] = array(
    'label' => t('Open Graph Fax Number'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );

  $info['tags']['og:video'] = array(
    'label' => t('Open Graph Video (URL)'),
    'description' => t('A URL to a video file that complements this object.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:video:secure_url'] = array(
    'label' => t('Open Graph Video Secure'),
    'description' => t('A URL to a video file that complements this object using the HTTPS protocol.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:video:width'] = array(
    'label' => t('Open Graph Video Width'),
    'description' => t('The width of the video.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:video:height'] = array(
    'label' => t('Open Graph Video Height'),
    'description' => t('The height of the video.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
  );
  $info['tags']['og:video:type'] = array(
    'label' => t('Open Graph Video Type'),
    'description' => t('The type of the video file.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph',
    'element' => array(
      '#theme' => 'metatag_opengraph',
    ),
    'form' => array(
      '#type' => 'select',
      '#options' => array(
        'application/x-shockwave-flash' => 'Flash - playable directly from the feed',
        'text/html' => 'Separate HTML page',
      ),
      '#empty_option' => t('- None -'),
    ),
  );

  return $info;
}

function _metatag_opengraph_type_options() {
  $options = array(
    t('Activities') => array(
      'activity' => t('Activity'),
      'sport' => t('Sport'),
    ),
    t('Businesses') => array(
      'bar' => t('Bar'),
      'company' => t('Company'),
      'cafe' => t('Cafe'),
      'hotel' => t('Hotel'),
      'restaurant' => t('Restaurant'),
    ),
    t('Groups') => array(
      'cause' => t('Cause'),
      'sports_league' => t('Sports league'),
      'sports_team' => t('Sports team'),
    ),
    t('Organizations') => array(
      'band' => t('Band'),
      'government' => t('Government'),
      'non_profit' => t('Non-profit'),
      'school' => t('School'),
      'university' => t('University'),
    ),
    t('People') => array(
      'actor' => t('Actor'),
      'athlete' => t('Athlete'),
      'author' => t('Author'),
      'director' => t('Director'),
      'musician' => t('Musician'),
      'politician' => t('Politician'),
      'profile' => t('Profile'),
      'public_figure' => t('Public figure'),
    ),
    t('Places') => array(
      'city' => t('City'),
      'country' => t('Country'),
      'landmark' => t('Landmark'),
      'state_province' => t('State or province'),
    ),
    t('Products and Entertainment') => array(
      'album' => t('Album'),
      'book' => t('Book'),
      'drink' => t('Drink'),
      'food' => t('Food'),
      'game' => t('Game'),
      'movie' => t('Movie'),
      'product' => t('Product'),
      'song' => t('Song'),
      'tv_show' => t('TV show'),
    ),
    t('Websites') => array(
      'blog' => t('Blog'),
      'website' => t('Website'),
      'article' => t('Article'),
    ),
  );

  return $options;
}
