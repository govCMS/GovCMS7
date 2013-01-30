<?php 
/**
 * @file
 * Alpha's theme implementation to display a region.
 */
?>

<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
		
		<?php if ($is_front): ?>
		  <?php print '<h1 class="element-invisible">' . drupal_get_title() . '</h1>'; ?>
		<?php else: ?>
		  <?php print '<h1>' . drupal_get_title() . '</h1>'; ?>
		<?php endif; ?>
		
		<?php if (!empty($tabs) && !$is_front && !empty($tabs['#primary'])): ?>
			<div class="tabbed-nav"><?php print render($tabs); ?></div>
		<?php endif; ?>
    
		<?php print $content; ?>
  
	</div>
</div>
