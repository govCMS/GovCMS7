<?php

/**
 * @file
 * Header menu template.
 */
?>

<div<?php print $attributes; ?>>
  <div<?php print $content_attributes; ?>>
		<div id="skip-to-content">
			<a href="#region-content">
			  <?php print t('Skip to content'); ?>
			</a>
		</div>
    <?php print $content; ?>
  </div>
</div>
