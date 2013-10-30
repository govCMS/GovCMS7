<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * Changes from default views-view-unformatted.tpl.php:
 *  - Changes title from h3 to h2, for accessiblity.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h2><?php print $title; ?></h2>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  <div <?php if ($classes_array[$id]) { print 'class="' . $classes_array[$id] .'"';  } ?>>
    <?php print $row; ?>
  </div>
<?php endforeach; ?>
