<?php 
/**
 * @file
 * Page layout template.
 */
?>

<!doctype html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>
<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <!--[if lt IE 9]>
    <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->
  <!--[if IE]>
    <link rel="stylesheet" href="/profiles/agov/themes/agov_base/css/ie.css" type="text/css" media="screen" />
  <![endif]-->
  <!--[if lte IE 8]>
  	<link type="text/css" rel="stylesheet" media="all" href="/profiles/agov/themes/agov_base/css/ie8-and-below.css" />
  <![endif]-->
</head>
<body<?php print $attributes;?>>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
