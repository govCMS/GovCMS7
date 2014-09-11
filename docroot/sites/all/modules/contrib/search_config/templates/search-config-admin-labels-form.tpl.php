<?php
  $labels = $form['#field-labels'];
  foreach (array('basic' => t('Basic'), 'advanced' => t('Advanced')) as $form_key => $form_name) :
?>
<table>
  <tr>
    <th colspan="2"><?php print t('!type form label overrides', array('!type' => $form_name)); ?></th>
    <th><?php print t('Title display'); ?></th>
  </tr>
<?php
    foreach ($labels as $key => $titles) :
      if (strpos($key, $form_key) === FALSE) {
        continue;
      }
      $has_title_display = isset($form['title_display'][$key]);
?>
  <tr>
    <td style="vertical-align: top;">
      <label for="<?php print $form['labels'][$key]['#id'] ?>"><?php print $labels[$key][0] ?> </label>
      <em><?php print $labels[$key][1]; ?></em>
    </td>
    <td style="vertical-align: top;"<?php print $has_title_display ? '' : ' colspan="2"' ?>><?php print drupal_render($form['labels'][$key]); ?></td>
    <?php if ($has_title_display) : ?><td><?php print drupal_render($form['title_display'][$key]); ?></td><?php endif; ?>
  </tr>
<?php
    endforeach;
?>
</table>
<?php
  endforeach;
