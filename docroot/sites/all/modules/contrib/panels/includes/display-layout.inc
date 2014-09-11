<?php

/**
 * @file
 *
 * Handle the forms for changing a display's layout.
 */

/**
 * Handle calling and processing of the form for editing display layouts.
 *
 * Helper function for panels_edit_layout().
 *
 * @see panels_edit_layout() for details on the various behaviors of this function.
 */
function _panels_edit_layout($display, $finish, $destination, $allowed_layouts) {
  ctools_include('common', 'panels');

  $form_state = array(
    'display' => &$display,
    'finish' => $finish,
    'destination' => $destination,
    'allowed_layouts' => $allowed_layouts,
    're_render' => FALSE,
    'no_redirect' => TRUE,
  );

  $change_form_state = $form_state;

  $change_form = FALSE;

  // Examine $_POST to see which form they're currently using.
  if (empty($_POST) || empty($_POST['form_id']) || $_POST['form_id'] != 'panels_change_layout') {
    $output = drupal_build_form('panels_choose_layout', $form_state);
    if (!empty($form_state['executed'])) {
      // upon submission go to next form.
      $change_form_state['layout'] = $_SESSION['layout'][$display->did] = $form_state['layout'];
      $change_form = TRUE;
    }
  }
  else {
    $change_form_state['layout'] = $_SESSION['layout'][$display->did];
    $change_form = TRUE;
  }

  if ($change_form) {
    $output = drupal_build_form('panels_change_layout', $change_form_state);
    if (!empty($change_form_state['executed'])) {
      if (isset($change_form_state['back'])) {
        unset($_POST);
        return _panels_edit_layout($display, $finish, $destination, $allowed_layouts);
      }

      if (!empty($change_form_state['clicked_button']['#save-display'])) {
        drupal_set_message(t('Panel layout has been updated.'));
        panels_save_display($display);
      }

      if ($destination) {
        return panels_goto($destination);
      }
      return $change_form_state['display'];
    }
  }
  return $output;
}

/**
 * Form definition for the display layout editor.
 *
 * @ingroup forms
 */
function panels_choose_layout($form, &$form_state) {
  $display = &$form_state['display'];
  ctools_include('common', 'panels');
  ctools_include('cleanstring');

  $layouts = panels_common_get_allowed_layouts($form_state['allowed_layouts']);
  $categories = array();
  $current = '';
  foreach ($layouts as $id => $layout) {
    $category = ctools_cleanstring($layout['category']);
    // Default category to first in case layout doesn't exist or there isn't one.
    if (empty($current)) {
      $current = $category;
    }

    $categories[$category] = $layout['category'];
    $options[$category][$id] = panels_print_layout_icon($id, $layout, check_plain($layout['title']));

    // Set current category to what is chosen.
    if ($id == $display->layout) {
      $current = $category;
    }
  }

  ctools_add_js('layout', 'panels');

  $form['categories'] = array(
    '#title' => t('Category'),
    '#type' => 'select',
    '#options' => $categories,
    '#default_value' => $current,
  );

  $form['layout'] = array(
    '#prefix' => '<div class="panels-choose-layout panels-layouts-checkboxes clearfix">',
    '#suffix' => '</div>',
  );

  // We set up the dependencies manually because these aren't really form
  // items. It's possible there's a simpler way to do this, but I could not
  // think of one at the time.
  $dependencies = array();
  foreach ($options as $category => $radios) {
    $dependencies['panels-layout-category-' . $category] = array(
      'values' => array('edit-categories' => array($category)),
      'num' => 1,
      'type' => 'hide',
    );

    $form['layout'][$category] = array(
      '#prefix' => '<div id="panels-layout-category-' . $category . '-wrapper"><div id="panels-layout-category-' . $category . '" class="form-checkboxes clearfix"><div class="panels-layouts-category">' . $categories[$category] . '</div>',
      '#suffix' => '</div></div>',
    );

    foreach ($radios as $key => $choice) {
      // Set the first available layout as default value.
      if (empty($display->layout)) {
        $display->layout = $key;
      }
      // Generate the parents as the autogenerator does, so we will have a
      // unique id for each radio button.
      $form['layout'][$category][$key] = array(
        '#type' => 'radio',
        '#title' => $choice,
        '#parents' => array('layout'),
        '#id' => drupal_clean_css_identifier('edit-layout-' . $key),
        '#return_value' => check_plain($key),
        '#default_value' => in_array($display->layout, array_keys($layouts)) ? $display->layout : NULL,
      );
    }
  }

  ctools_add_js('dependent');
  $js['CTools']['dependent'] = $dependencies;
  drupal_add_js($js, 'setting');


  if (empty($form_state['no buttons'])) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
    );
  }

  return $form;
}

/**
 * Handle form submission of the display layout editor.
 */
function panels_choose_layout_submit($form, &$form_state) {
  $form_state['layout'] = $form_state['values']['layout'];
}

/**
 * Form definition for the display layout converter.
 *
 * This form is only triggered if the user attempts to change the layout
 * for a display that has already had content assigned to it. It allows
 * the user to select where the panes located in to-be-deleted panels should
 * be relocated to.
 *
 * @ingroup forms
 *
 * @param array $form
 *   A structured FAPI $form array.
 * @param &$form_state
 *   The Drupal $form_state
 */
function panels_change_layout($form, &$form_state) {
  // Provide a temporary display and renderer.
  $form_state['layout_display'] = $display = panels_new_display();
  if (isset($form_state['cache_key'])) {
    $display->cache_key = $form_state['cache_key'];
  }

  $new_layout = panels_get_layout($form_state['layout']);
  $new_layout_regions = panels_get_regions($new_layout, $display);

  $old_layout = panels_get_layout($form_state['display']->layout);
  $old_layout_regions = panels_get_regions($old_layout, $form_state['display']);

  $display->layout = $form_state['layout'];
  $renderer = panels_get_renderer_handler('editor', $display);

  $renderer->meta_location = 'inline';

  ctools_add_css('panels_admin', 'panels');
  ctools_add_css('panels_dnd', 'panels');
  ctools_add_css('dropdown');

  // For every region that had content in the old layout, create a custom pane
  // in the new layout that represents that region.
  $keys = array_keys($new_layout_regions);
  $default_region = reset($keys);
  foreach ($old_layout_regions as $region_id => $region_name) {
    if (!empty($form_state['display']->panels[$region_id])) {
      $pane = panels_new_pane('custom', 'custom', TRUE);
      $pane->pid = $region_id;
      $pane->configuration['title'] = t('Panes');
      $pane->configuration['admin_title'] = $region_name;
      // Get a list of pane titles used.
      $titles = array();
      foreach ($form_state['display']->panels[$region_id] as $pid) {
        $content_type = ctools_get_content_type($form_state['display']->content[$pid]->type);
        $titles[$pid] = ctools_content_admin_title($content_type, $form_state['display']->content[$pid]->subtype, $form_state['display']->content[$pid]->configuration, $form_state['display']->context);
      }
      $pane->configuration['body'] = '<ul><li>' . implode('</li><li>', $titles) . '</li></ul>';

      // If the region id matches, make it the same; otherwise, put it
      // in the default region.
      $pane->panel = empty($new_layout_regions[$region_id]) ? $default_region : $region_id;

      // Add the pane to the approprate spots.
      $display->content[$pane->pid] = $pane;
      $display->panels[$pane->panel][] = $pane->pid;
    }
  }

  $form['container'] = array(
    '#prefix' => '<div class="change-layout-display clearfix">',
    '#suffix' => '</div>',
  );

  $form['container']['old_layout'] = array(
    '#markup' => panels_print_layout_icon($form_state['display']->layout, $old_layout, check_plain($old_layout['title'])),
  );

  $form['container']['right_arrow'] = array(
    '#markup' => theme('image', array('path' => drupal_get_path('module', 'panels') . '/images/go-right.png')),
  );
  $form['container']['new_layout'] = array(
    '#markup' => panels_print_layout_icon($form_state['layout'], $new_layout, check_plain($new_layout['title'])),
  );

  $edit_form_state = array(
    'display' => $display,
    'renderer' => $renderer,
    'no buttons' => TRUE,
    'no preview' => TRUE,
    'no display settings' => TRUE,
    'display_title' => '',
  );

  ctools_include('display-edit', 'panels');
  $form = panels_edit_display_form($form, $edit_form_state);

  if (empty($form_state['no buttons'])) {
    $form['back'] = array(
      '#type' => 'submit',
      '#value' => t('Back'),
      '#submit' => array('panels_choose_layout_back'),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => $form_state['finish'],
      '#submit' => array('panels_change_layout_submit'),
      '#save-display' => TRUE,
    );
  }
  return $form;
}

/**
 * Handle submission of the change layout form.
 *
 * This submit handler will move panes around and save the display.
 */
function panels_change_layout_submit($form, &$form_state) {
  $display = $form_state['display'];
  $layout_display = $form_state['layout_display'];

  $switch = array();

  // Calculate the pids submitted by the display and make a list of
  // translation to the regions. Remember the 'pid' of the pane
  // is the region id in the old layout.
  if (!empty($form_state['values']['panel']['pane'])) {
    foreach ($form_state['values']['panel']['pane'] as $region_id => $panes) {
      if ($panes) {
        $pids = explode(',', $panes);
        // need to filter the array, b/c passing it in a hidden field can generate trash
        foreach (array_filter($pids) as $pid) {
          $switch[$pid] = $region_id;
        }
      }
    }
  }

  $content = array();
  foreach ($switch as $region_id => $new_region_id) {
    if (isset($display->panels[$region_id])) {
      if (!isset($content[$new_region_id])) {
        $content[$new_region_id] = array();
      }
      $content[$new_region_id] = array_merge($content[$new_region_id], $display->panels[$region_id]);
    }
  }

  // Go through each pane and make sure its region id is correct.
  foreach ($content as $region_id => $region) {
    foreach ($region as $pid) {
      $display->content[$pid]->panel = $region_id;
    }
  }

  $display->panels = $content;

  $display->layout = $form_state['layout'];
}

/**
 * Handle submission of the change layout form.
 *
 * This submit handler sets a flag on the form state, which is then used
 * by the calling wrapper to restart the process.
 */
function panels_choose_layout_back($form, &$form_state) {
  $form_state['back'] = TRUE;
}
