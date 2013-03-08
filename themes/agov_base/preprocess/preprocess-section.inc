<?php

// Adds ARIA role

if($vars['attributes_array']['id'] == 'section-footer') {
  $vars['attributes_array']['role'] = 'contentinfo';
}