<?php
/**
 * @file
 * Provides themed representation of the front layout.
 *
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 *
 * aGov
 * @copyright Copyright(c) 2014 PreviousNext
 * @author Nick Schuch nick at previousnext dot com dot au
 *
 * govCMS (Forked on 1 April 2015 - http://cgit.drupalcode.org/govcms/commit/?id=64b602dcc7ddde0992c5c7cf5f3c4a795e5be08a)
 * The original foundation for the govCMS distribution is aGov; the Drupal distribution created by PreviousNext to provide a core set of elements, functionality and features that can be used to develop government websites
 * @copyright Copyright(c) 2015 Commonwealth of Australia as represented by Department of Finance
 * @author Department of Finance
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
