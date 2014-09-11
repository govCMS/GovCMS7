<?php

/**
 * @file
 * Extends the MediaInternetBaseHandler class to handle Vimeo videos.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetVimeoHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    // http://vimeo.com/*
    // http://vimeo.com/video/*
    // http://vimeo.com/groups/*/videos/*
    // http://vimeo.com/channels/*#$ID
    $patterns = array(
      '@vimeo\.com/(\d+)@i',
      '@vimeo\.com/video/(\d+)@i',
      '@vimeo\.com/groups/.+/videos/(\d+)@i',
      '@vimeo\.com/channels/.+#(\d+)@i',
    );

    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      // @TODO: Parse is called often. Refactor so that valid ID is checked
      // when a video is added, but not every time the embedCode is parsed.
      if (isset($matches[1]) && self::validId($matches[1])) {
        return file_stream_wrapper_uri_normalize('vimeo://v/' . $matches[1]);
      }
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    // Try to default the file name to the video's title.
    if (empty($file->fid) && $info = $this->getOEmbed()) {
      $file->filename = truncate_utf8($info['title'], 255);
    }

    return $file;
  }

  /**
   * Returns information about the media.
   *
   * See http://www.oembed.com.
   *
   * @return
   *   If oEmbed information is available, an array containing 'title', 'type',
   *   'url', and other information as specified by the oEmbed standard.
   *   Otherwise, NULL.
   */
  public function getOEmbed() {
    $uri = $this->parse($this->embedCode);
    $external_url = file_create_url($uri);
    $oembed_url = url('http://vimeo.com/api/oembed.json', array('query' => array('url' => $external_url)));
    $response = drupal_http_request($oembed_url);

    if (!isset($response->error)) {
      return drupal_json_decode($response->data);
    }
    else {
      throw new Exception("Error Processing Request. (Error: {$response->code}, {$response->error})");
      return;
    }
  }

  /**
   * Check if a Vimeo video ID is valid.
   *
   * @return boolean
   *   TRUE if the video ID is valid, or throws a
   *   MediaInternetValidationException otherwise.
   */
  static public function validId($id) {
    $uri = file_stream_wrapper_uri_normalize('vimeo://v/' . check_plain($id));
    $external_url = file_create_url($uri);
    $oembed_url = url('http://vimeo.com/api/oembed.json', array('query' => array('url' => $external_url)));
    $response = drupal_http_request($oembed_url, array('method' => 'HEAD'));

    if ($response->code == 401) {
      throw new MediaInternetValidationException('Embedding has been disabled for this Vimeo video.');
    }
    elseif ($response->code != 200) {
      throw new MediaInternetValidationException('The Vimeo video ID is invalid or the video was deleted.');
    }

    return TRUE;
  }
}
