/**
 * @file
 * Displays tweets using jquery.tweet.js
 *
 */

(function ($) {

  Drupal.behaviors.govTweets = {
    attach: function (context, settings) {
      var username  = Drupal.settings.twitter_feed.username;
      var count = Drupal.settings.twitter_feed.count;

        $("#tweets").tweet({
          avatar_size: 40,
          count: count,
          username: username,
          loading_text: Drupal.t('Loading Tweets...'),
            template: '<div class="clearfix">{avatar}{text}</div>{time}'
        });

    }
  }

}(jQuery));
