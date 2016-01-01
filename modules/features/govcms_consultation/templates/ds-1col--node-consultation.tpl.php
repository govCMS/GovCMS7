<?php
/**
 * @file
 * Display Suite 1 column template.
 */
?>

<?php if (isset($status_message) && $status_message != ''): ?>
  <div class="messages--status messages status">
    <?php print $status_message; ?>
  </div>
<?php endif; ?>

<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> clearfix">

<?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
<?php endif; ?>

<?php print $ds_content; ?>
</<?php print $ds_content_wrapper ?>>

<?php if (!empty($drupal_render_children)): ?>
    <?php print $drupal_render_children ?>
<?php endif; ?>

