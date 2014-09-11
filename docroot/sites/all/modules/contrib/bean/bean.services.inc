<?php

/**
 * @file
 * Contains callbacks for service resource manipulation.
 */

/**
 * Implements hook_services_resources().
 */
function bean_services_resources() {
  return array(
    '#api_version' => 3002,
    'bean' => array(
      'operations' => array(
        'retrieve' => array(
          'help' => t('This method returns a bean.'),
          'callback' => 'bean_services_retrieve',
          'access arguments' => array('view bean page'),
          'args' => array(
            array(
              'name' => 'bid',
              'type' => 'int',
              'description' => t('The id of the bean to get.'),
              'source' => array('path' => '0'),
              'optional' => FALSE,
            ),
          ),
        ),
        'create' => array(
          'help' => t('This method creates a bean.'),
          'callback' => 'bean_services_create',
          'access callback' => 'bean_services_access',
          'access arguments' => array('add'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'data',
              'type' => 'struct',
              'description' => t('An object representing the bean.'),
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
        'update' => array(
          'help' => t('This method updates a bean.'),
          'callback' => 'bean_services_update',
          'access callback' => 'bean_services_access',
          'access arguments' => array('edit'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'bid',
              'type' => 'int',
              'description' => t('The id of the bean to update.'),
              'source' => array('path' => '0'),
              'optional' => FALSE,
            ),
            array(
              'name' => 'data',
              'type' => 'struct',
              'description' => t('An object representing the bean.'),
              'source' => 'data',
              'optional' => FALSE,
            ),
          ),
        ),
        'delete' => array(
          'help' => t('This method deletes a bean.'),
          'callback' => 'bean_services_delete',
          'access callback' => 'bean_services_access',
          'access arguments' => array('delete'),
          'access arguments append' => TRUE,
          'args' => array(
            array(
              'name' => 'bid',
              'type' => 'int',
              'description' => t('The id of the bean to delete.'),
              'source' => array('path' => '0'),
              'optional' => FALSE,
            ),
          ),
        ),
        'index' => array(
          'help' => t('This method returns a listing of beans.'),
          'callback' => 'bean_services_index',
          'access arguments' => array('administer beans'),
          'args' => array(
            array(
              'name' => 'page',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('The zero-based index of the page to get, defaults to 0.'),
              'default value' => 0,
              'source' => array('param' => 'page'),
            ),
            array(
              'name' => 'fields',
              'optional' => TRUE,
              'type' => 'string',
              'description' => t('The fields to return.'),
              'default value' => '*',
              'source' => array('param' => 'fields'),
            ),
            array(
              'name' => 'parameters',
              'optional' => TRUE,
              'type' => 'array',
              'description' => t('Fields an values to filter the list by.'),
              'default value' => array(),
              'source' => array('param' => 'parameters'),
            ),
            array(
              'name' => 'pagesize',
              'optional' => TRUE,
              'type' => 'int',
              'description' => t('Number of records to get per page.'),
              'default value' => 20,
              'source' => array('param' => 'pagesize'),
            ),
          ),
        ),
      ),
    ),
  );
}

/**
 * Adds a new bean to a node and returns the bid.
 *
 * @param $bean Bean
 *   An object as would be returned from bean_load().
 * @return
 *   Unique identifier for the bean (bid) or errors if there was a problem.
 */
function bean_services_create($bean) {
  if (empty($bean['type'])) {
    return services_error(t('A type must be provided.'));
  }

  // Include the bean_form.
  module_load_include('inc', 'bean', 'includes/bean.pages');

  $bean_new = bean_create($bean);

  // Setup form_state.
  $form_state = array();
  $form_state['values'] = $bean;
  $form_state['values']['op'] = t('Save');
  $form_state['build_info']['args'] = array(&$bean_new);

  $ret = drupal_form_submit('bean_form', $form_state);

  // Error if needed.
  if ($errors = form_get_errors()) {
    return services_error(implode(" ", $errors), 406, array('form_errors' => $errors));
  }

  $bean = $form_state['bean'];

  return array(
    'bid' => $bean->bid,
    'uri' => services_resource_uri(array('bean', $bean->bid)),
  );
}

/**
 * Updates a bean and returns the bid.
 *
 * @param $bid
 *   Unique identifier for this bean.
 * @param $bean Bean
 *   An object as would be returned from bean_load().
 * @return
 *   Unique identifier for the bean (bid) or FALSE if there was a problem.
 */
function bean_services_update($bid, $bean) {
  // Include the bean_form.
  module_load_include('inc', 'bean', 'includes/bean.pages');

  $bean['bid'] = $bid;

  $old_bean = bean_load($bid);
  if (empty($old_bean)) {
    return services_error(t('Bean @bid not found.', array('@bid' => $bid)), 404);
  }

  // Setup form_state.
  $form_state = array();
  $form_state['values'] = $bean;
  $form_state['values']['op'] = t('Save');
  $form_state['build_info']['args'] = array(&$old_bean);

  drupal_form_submit('bean_form', $form_state);

  if ($errors = form_get_errors()) {
    return services_error(implode(" ", $errors), 406, array('form_errors' => $errors));
  }

  return $bid;
}

/**
 * Returns a specified bean.
 *
 * @param $bid
 *   Unique identifier for the specified bean.
 * @return
 *   The bean object.
 */
function bean_services_retrieve($bid) {
  return bean_load($bid);
}

/**
 * Delete a bean.
 *
 * @param $bid
 *   Unique identifier of the bean to delete.
 * @return
 *   True.
 */
function bean_services_delete($bid) {
  $bean = bean_load($bid);
  if (empty($bean)) {
    return services_error(t('There is no bean found with id @bid.', array('@bid' => $bid)), 404);
  }

  // Delete bean.
  bean_delete($bean);

  // Clear the bean cache so an anonymous user sees that the bean was deleted.
  bean_reset();
  return TRUE;
}

/**
 * Return an array of optionally paged bids based on a set of criteria.
 *
 * An example request might look like:
 *
 * http://domain/endpoint/bean?fields=bid,label&parameters[type]=mytype
 *
 * This would return an array of objects with only bid and label defined, where
 * type = 'mytype'.
 *
 * @param $page
 *   Page number of results to return (in pages of 20).
 * @param $fields
 *   The fields you want returned.
 * @param $parameters
 *   An array containing fields and values used to build a sql WHERE clause
 *   indicating items to retrieve.
 * @param $page_size
 *   Integer number of items to be returned.
 * @return
 *   An array of bean objects.
 **/
function bean_services_index($page, $fields, $parameters, $page_size) {
  $bean_select = db_select('bean', 't')
    ->orderBy('delta', 'ASC');

  services_resource_build_index_query($bean_select, $page, $fields, $parameters, $page_size, 'bean');

  $results = services_resource_execute_index_query($bean_select);

  return services_resource_build_index_list($results, 'bean', 'bid');
}

/**
 * Access callback for the bean resource.
 *
 * @param $op
 *  The operation that's going to be performed.
 * @param $args
 *  The arguments that will be passed to the callback.
 * @return
 *  Whether access is given or not.
 */
function bean_services_access($op, $args) {
  $bean = NULL;
  if (!empty($args[0])) {
    if (is_numeric($args[0])) {
      $bean = bean_load($args[0]);
    }
    else if (is_array($args[1])) {
      $bean = (object) $args[1];
    }
  }

  if (!empty($args[0]) && !is_object($bean)) {
    return FALSE;
  }

  return bean_access($op, $bean);
}
