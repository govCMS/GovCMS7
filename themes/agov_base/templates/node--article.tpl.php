<?php

/**
 * @file
 * Article node template.
 */
hide($content['comments']);
hide($content['links']);
?>

<div <?php print $attributes; ?>>
  <div class="article-header">
    <?php if ($display_submitted): ?>
      print '<p class="article-author-date">' . $formatted_date . '</p>';
    <?php endif; ?>
  </div>
  <div<?php print $content_attributes; ?>>
    <?php print render($content);  ?>
  </div>
  <div class="clearfix">
    <?php print render($content['comments']); ?>
  </div>
</div>
