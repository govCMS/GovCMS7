<?php
/**
 * @file
 * Returns the HTML for Panels Everywhere's navigation pane.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/2052513
 */
?>
<?php if (!empty($main_menu)): ?>
  <nav id="main-menu" role="navigation" tabindex="-1">
    <?php print $main_menu; ?>
  </nav>
<?php endif; ?>

<?php if (!empty($secondary_menu)): ?>
  <nav id="secondary-menu" role="navigation">
    <?php print $secondary_menu; ?>
  </nav>
<?php endif; ?>

<?php print $breadcrumb; ?>
