<?php
/**
 * @file
 * Template implementation to display the promotional text of channel.
 */
?>
<?php foreach ($items as $delta => $item): ?>
  <h2><?php print render($item); ?></h2>
<?php endforeach; ?>
