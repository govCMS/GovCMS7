<?php
/**
 * @file
 * Default template implementation to display the value of a field.
 */
?>
<button class="form-submit consultation__formal-submission-webform" data-js="webform-toggle" data-toggle="consultation__formal-submission-webform"><?php print t('Have Your Say Now'); ?></button>
</div>
<div id="consultation__formal-submission-webform">
  <div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
    <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
  <?php endif; ?>
  <div class="field-items"<?php print $content_attributes; ?>>
    <?php foreach ($items as $delta => $item): ?>
      <div class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>><?php print render($item); ?></div>
    <?php endforeach; ?>
  </div>
</div>
