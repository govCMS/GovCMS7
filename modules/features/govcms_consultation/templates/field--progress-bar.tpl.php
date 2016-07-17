<?php
/**
 * @file
 * Default template implementation to display the value of a field.
 */
?>
<?php if (!$label_hidden): ?>
  <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>:&nbsp;</div>
<?php endif; ?>
<div class="consultation__progress-bar <?php print $consultation['status_class']; ?>"<?php print $content_attributes; ?>>
  <div class="consultation__progress-bar__text">
    <div class="consultation__progress-bar__start-date">
      <?php print t('Start') . ' ' . format_date($consultation['start'], 'long'); ?></div>
    <div class="consultation__progress-bar__end-date">
      <?php print t('End') . ' ' . format_date($consultation['end'], 'long'); ?></div>
  </div>
  <div class="consultation__progress-bar__bar">
    <div class="consultation__progress-bar__progress" style="width: <?php print round($consultation['percentage']); ?>%;"></div>
  </div>
  <div class="consultation__progress-bar__days-remain">
    <span class="consultation__progress-bar__label"><?php print t('Days Remaining'); ?> </span>
    <span class="consultation__progress-bar__highlighted"><?php print $consultation["days_remain"]; ?></span> <?php print 'of ' . $consultation["days_total"]; ?>
  </div>

  <?php if(isset($consultation['status_message'])): ?>
    <div class="consultation__progress-bar__highlighted">
      <?php print $consultation['status_message']; ?>
    </div>
  <?php endif; ?>

</div>
