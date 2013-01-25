<div class="<?php print $classes; ?>">
  <div class="field-label">Documents:</div>
  <ul class="field-items no-bullets">
    <?php foreach ($items as $delta => $item) : ?>
        <li class="field-item">
          <?php print render($item); ?>
        </li>
    <?php endforeach; ?>
    </ul>
</div>
