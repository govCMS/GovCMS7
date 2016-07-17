<?php
/**
 * @file
 * Template implementation to display the promotional text of channel.
 */
?>
<?php foreach ($items as $delta => $item): ?>
  <h4><?php print render($item); ?></h4>
<?php endforeach; ?>
