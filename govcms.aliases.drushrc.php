<?php

// Site govcms, environment dev
$aliases['dev'] = array(
  'site' => 'govcms',
  'env' => 'dev',
  'root' => '/var/www/current/app',
  'remote-host' => 'govcms.qa.previousnext.com.au',
  'remote-user' => 'deployer',
  'ssh-options' => '-p 11063',
  'path-aliases' => array(
    '%real-files' => '/var/www/shared/files/',
    '%dump-dir' => '/var/tmp',
   ),
);

// Site govcms, environment staging
$aliases['staging'] = array(
  'site' => 'govcms',
  'env' => 'dev',
  'root' => '/var/www/current/app',
  'remote-host' => 'govcms.staging.previousnext.com.au',
  'remote-user' => 'deployer',
  'ssh-options' => '-p 11064',
  'path-aliases' => array(
    '%real-files' => '/var/www/shared/files/',
    '%dump-dir' => '/var/tmp',
   ),
);
