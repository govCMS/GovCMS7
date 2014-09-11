<?php

/**
 * Implements hook_help()
 *
 * @param string $path
 * @param string $arg
 *
 * @return null|string
 */
function crumbs_help($path, $arg) {
  switch ($path) {
    case 'admin/structure/crumbs':
    case 'admin/structure/crumbs/weights':
      // TODO: Isn't there a better way to define long translated strings?
      $help = <<<EOT
<p>To build a breadcrumb trail, Crumbs takes the system path of the current
page, and determines a "parent path". This process is repeated with the parent,
until it arrives at the front page path, or until a loop is detected.</p>
<p>There are plenty of criteria available, that Crumbs can use to find a parent
path. This settings form allows to enable, disable and prioritize these
criteria.</p>
<p>Criteria further up in the "Enabled" section take precedence over those
further down. Criteria in the "Disabled" section have their effect nullified.
Criteria in the "Inherit / automatic" section inherit the status from
the parent wildcard criterion, unless they are "disabled by default".</p>
EOT;
      return t($help);
  }

  return NULL;
}
