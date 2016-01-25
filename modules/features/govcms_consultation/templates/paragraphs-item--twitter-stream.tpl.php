<?php
/**
 * @file
 * Channels theme implementation for a Twitter grid display.
 */
?>
<div class="twitter-stream spacer">
    <h2><?php print $content['field_pbundle_title'][0]['#markup']; ?></h2>
    <a class="twitter-grid" href="https://twitter.com/<?php print variable_get('consultation_twitter_account'); ?>/timelines/<?php print $content['field_twitter_widget_id'][0]['#markup']; ?>"></a>
    <script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>
</div>
