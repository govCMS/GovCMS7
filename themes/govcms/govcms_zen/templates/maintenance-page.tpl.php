<?php
/**
 * @file
 * Returns the HTML for a single Drupal page while offline.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728174
 */
?><!DOCTYPE html>
<!--[if IEMobile 7]><html class="iem7" <?php print $html_attributes; ?>><![endif]-->
<!--[if lte IE 6]><html class="lt-ie9 lt-ie8 lt-ie7" <?php print $html_attributes; ?>><![endif]-->
<!--[if (IE 7)&(!IEMobile)]><html class="lt-ie9 lt-ie8" <?php print $html_attributes; ?>><![endif]-->
<!--[if IE 8]><html class="lt-ie9" <?php print $html_attributes; ?>><![endif]-->
<!--[if (gte IE 9)|(gt IEMobile 7)]><!--><html <?php print $html_attributes; ?>><!--<![endif]-->
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>

  <?php if ($default_mobile_metatags): ?>
    <meta name="MobileOptimized" content="width">
    <meta name="HandheldFriendly" content="true">
    <meta name="viewport" content="width=device-width">
  <?php endif; ?>
  <meta http-equiv="cleartype" content="on">

  <?php print $styles; ?>
  <?php print $scripts; ?>
  <?php if ($add_respond_js): ?>
    <!--[if lt IE 9]>
    <script src="<?php print $base_path . $path_to_zen; ?>/js/html5-respond.js"></script>
    <![endif]-->
  <?php elseif ($add_html5_shim): ?>
    <!--[if lt IE 9]>
    <script src="<?php print $base_path . $path_to_zen; ?>/js/html5.js"></script>
    <![endif]-->
  <?php endif; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>

  <div class="palette-1 centered-box">

    <?php if ($logo): ?>
      <img class="centered-box__image" src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
    <?php endif; ?>

    <?php if ($site_name): ?>
      <h1 class="centered-box__title">
        <?php print $site_name; ?>
      </h1>
    <?php endif; ?>

    <?php print $messages; ?>
    <?php print $content; ?>

  </div>

<?php print $bottom; ?>

</body>
</html>
