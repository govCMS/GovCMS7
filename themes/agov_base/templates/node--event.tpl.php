<?php

/**
 * @file
 * Event node template.
 */
?>

<div <?php print $attributes; ?>>

  <div<?php print $content_attributes; ?>>
    <?php
      hide($content['field_location']);
      hide($content['field_cost']);
      hide($content['field_contact']);
      print render($content);
    ?>
  </div>
  <div class="clearfix">
  <span class="element-invisible">Event details</span>
    <dl class="event-details">
      <dt class="title clearfix"><?php print render($content['field_location']['#title']); ?>:</dt>
      <dd class="description"><?php print render ($content['field_location']['#items'][0]['safe_value']); ?></dd>

      <dt class="title clearfix"><?php print render($content['field_cost']['#title']); ?>:</dt>
      <dd class="description"><?php print render ($content['field_cost']['#items'][0]['safe_value']); ?></dd>

      <dt class="title clearfix"><?php print render($content['field_contact']['#title']); ?>:</dt>
      <dd class="description"><?php print render ($content['field_contact']['#items'][0]['safe_value']); ?></dd>
    </dl>
  </div>
</div>
