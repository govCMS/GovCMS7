<?php
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * each column roughly equal in width. It is 5 rows high; the top
 * middle and bottom rows contain 1 column, while the second
 * and fourth rows contain 2 columns.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left_above']: Content in the left column in row 2.
 *   - $content['right_above']: Content in the right column in row 2.
 *   - $content['middle']: Content in the middle row.
 *   - $content['left_below']: Content in the left column in row 4.
 *   - $content['right_below']: Content in the right column in row 4.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>
<div class="panel-display panel-2col-bricks clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="panel-panel panel-col-top">
    <div class="inside"><?php print $content['top']; ?></div>
  </div>
  <div class="center-wrapper">
    <div class="panel-panel panel-col-first">
      <div class="inside"><?php print $content['left_above']; ?></div>
    </div>

    <div class="panel-panel panel-col-last">
      <div class="inside"><?php print $content['right_above']; ?></div>
    </div>
  </div>
  <div class="panel-panel panel-col-middle">
    <div class="inside"><?php print $content['middle']; ?></div>
  </div>
  <div class="center-wrapper">
    <div class="panel-panel panel-col-first">
      <div class="inside"><?php print $content['left_below']; ?></div>
    </div>

    <div class="panel-panel panel-col-last">
      <div class="inside"><?php print $content['right_below']; ?></div>
    </div>
  </div>
  <div class="panel-panel panel-col-bottom">
    <div class="inside"><?php print $content['bottom']; ?></div>
  </div>
</div>
