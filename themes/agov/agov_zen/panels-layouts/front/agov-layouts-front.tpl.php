<?php
/**
 * @file
 * Provides themed representation of the front layout.
 * @copyright Copyright(c) 2012 Previous Next Pty Ltd
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Nick Schuch nick at previousnext dot com dot au
 *
 * Available variables
 * -------------------
 * $content array of panels.
 */

?>


<div class="gov-front-layout clearfix" <?php if (!empty($css_id)) : print "id=\"$css_id\""; endif; ?>>
  
  <?php if (!empty($content['main'])) : ?>
    <?php print $content['main'];?>
  <?php endif; ?>

  <?php if (!empty($content['left'])) : ?>
    <div class="alpha grid-4 gov-front-left gov-front-col">
      <?php print $content['left'];?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['right'])) : ?>
    <div class="omega grid-4 gov-front-right gov-front-col">
      <?php print $content['right'];?>
    </div>
  <?php endif; ?>

</div>
