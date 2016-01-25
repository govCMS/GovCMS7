<?php
/**
 * @file
 * Template implementation to display the promotional text of channel.
 */
?>
<?php foreach ($items as $delta => $item): ?>
  <?php print render($item); ?>
<?php endforeach; ?>
