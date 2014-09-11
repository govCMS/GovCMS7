<?php
/**
 * @file
 * Metatag integration for the metatag Twitter Cards module.
 */

/**
 * Implements hook_metatag_config_default_alter().
 */
function metatag_twitter_cards_metatag_config_default_alter(array &$configs) {
  foreach ($configs as &$config) {
    switch ($config->instance) {
      case 'global':
        $config->config += array(
          'twitter:card' => array('value' => 'summary'),
          'twitter:description' => array('value' => '[site:slogan]'),
          'twitter:title' => array('value' => '[site:name]'),
          'twitter:url' => array('value' => '[current-page:url:absolute]'),
        );
        break;

      case 'global:frontpage':
        $config->config += array(
          'twitter:description' => array('value' => ''),
        );
        break;

      case 'node':
        $config->config += array(
          'twitter:card' => array('value' => 'summary'),
          'twitter:description' => array('value' => '[node:summary]'),
          'twitter:title' => array('value' => '[node:title]'),
        );
        break;

      case 'taxonomy_term':
        $config->config += array(
          'twitter:card' => array('value' => 'summary'),
          'twitter:title'=> array('value' => '[term:name]'),
        );
        break;
    }
  }
}

/**
 * Implements hook_metatag_info().
 */
function metatag_twitter_cards_metatag_info() {
  $info['groups']['twitter-cards'] = array(
    'label' => t('Twitter card'),
    'description' => t('A set of meta tags specially for controlling the summaries displayed when content is shared on <a href="!url">Twitter</a>.', array('!url' => 'http://twitter.com/')),
    'form' => array(
      '#weight' => 60,
    ),
  );

  $info['tags']['twitter:card'] = array(
    'label' => t('Twitter card type'),
    'description' => t('Notes: no other fields are required for a <em>Summary</em> card, a <em>Photo</em> card requires the \'image\' field, while a <em>Media player</em> card requires the \'title\', \'description\', \'media player URL\', \'media player width\', \'media player height\' and \'image\' fields.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'form' => array(
      '#type' => 'select',
      '#options' => array(
        'summary' => t('Summary (default)'),
        'photo' => t('Photo'),
        'player' => t('Media player'),
      ),
      '#empty_option' => t('- None -'),
    ),
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:site'] = array(
    'label' => t('Site\'s Twitter account'),
    'description' => t('The @username for the website, which will be displayed in the Card\'s footer; must include the @ symbol.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'context' => array('global'),
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:site:id'] = array(
    'label' => t('Site\'s Twitter account ID'),
    'description' => t('The numerical Twitter account ID for the website, which will be displayed in the Card\'s footer.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'context' => array('global'),
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:creator'] = array(
    'label' => t('Creator\'s Twitter account'),
    'description' => t('The @username for the content creator / author for this page, including the @ symbol.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:creator:id'] = array(
    'label' => t('Creator\'s Twitter account ID'),
    'description' => t('The numerical Twitter account ID for the content creator / author for this page.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:url'] = array(
    'label' => t('Page URL'),
    'description' => t('The permalink / canonical URL of the current page.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:title'] = array(
    'label' => t('Title'),
    'description' => t('The page\'s title, which should be concise; it will be truncated at 70 characters by Twitter. This field is required unless this the \'type\' field is set to "photo".'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:description'] = array(
    'label' => t('Description'),
    'description' => t('A description that concisely summarizes the content of the page, as appropriate for presentation within a Tweet. Do not re-use the title text as the description, or use this field to describe the general services provided by the website. The string will be truncated, by Twitter, at the word to 200 characters.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:image'] = array(
    'label' => t('Image URL'),
    'description' => t('The URL to a unique image representing the content of the page. Do not use a generic image such as your website logo, author photo, or other image that spans multiple pages. Images larger than 120x120px will be resized and cropped square based on longest dimension. Images smaller than 60x60px will not be shown. If the \'type\' is set to <em>Photo</em> then the image must be at least 280x150px.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:image:width'] = array(
    'label' => t('Image width'),
    'description' => t('The width of the image being linked to, in pixels.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:image:height'] = array(
    'label' => t('Image height'),
    'description' => t('The height of the image being linked to, in pixels.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:player'] = array(
    'label' => t('Media player URL'),
    'description' => t('The full URL for loading a media player. Required when using a <em>Media player</em> card.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:player:width'] = array(
    'label' => t('Media player width'),
    'description' => t('The width of the media player iframe, in pixels. Required when using a <em>Media player</em> card.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:player:height'] = array(
    'label' => t('Media player height'),
    'description' => t('The height of the media player iframe, in pixels. Required when using a <em>Media player</em> card.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:player:stream'] = array(
    'label' => t('MP4 media stream URL'),
    'description' => t('The full URL for an MP4 video (h.264) or audio (AAC) stream, takes precidence over the other media player field.'),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  $info['tags']['twitter:player:stream:content_type'] = array(
    'label' => t('MP4 media stream MIME type'),
    'description' => t('The MIME type for the media contained in the stream URL, as defined by <a href="!url">RFC 4337</a>.', array('!url' => 'http://tools.ietf.org/rfc/rfc4337.txt')),
    'class' => 'DrupalTextMetaTag',
    'group' => 'twitter-cards',
    'element' => array(
      '#theme' => 'metatag_twitter_cards',
    ),
  );
  return $info;
}
