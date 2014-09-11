<?php

/**
 * Implementation of hook_crumbs_plugins()
 *
 * @param crumbs_InjectedAPI_hookCrumbsPlugins $api
 */
function commerce_checkout_crumbs_plugins($api) {

  // The parent path and title for checkout/%/% will be determined by the
  // commerce_checkout_CrumbsMonoPlugin_checkoutPages plugin.
  $api->routeMonoPlugin('checkout/%/%', 'checkoutPages');

  // The parent path for 'checkout/%' should always be 'cart'.
  $api->routeParentPath('checkout/%', 'cartToCheckout', 'cart');

  // This plugin needs to be explicitly enabled.
  $api->disabledByDefault('*');
}


class commerce_checkout_CrumbsMonoPlugin_checkoutPages implements crumbs_MonoPlugin_FindParentInterface, crumbs_MonoPlugin_FindTitleInterface {

  /**
   * {@inheritdoc}
   */
  function describe($api) {
    $api->titleWithLabel(t('Previous page in checkout process'), t('Parent'));
  }

  /**
   * {@inheritdoc}
   */
  function findParent($path, $item) {
    // $item['map'][2] should contain the checkout step.
    if (empty($item['map'][2])) {
      return NULL;
    }
    // $item['map'][1] should contain the order.
    if (!is_object($item['map'][1])) {
      return NULL;
    }
    list(, $order, $page) = $item['map'];
    if (!empty($page['prev_page'])) {
      return 'checkout/' . $order->order_id . '/' . $page['prev_page'];
    }
    else {
      // If the step has no 'prev_page', then the parent is 'cart'.
      return 'cart';
    }
  }

  /**
   * {@inheritdoc}
   */
  function findTitle($path, $item) {
    if (empty($item['map'][2]['name'])) {
      return NULL;
    }
    if (!is_object($item['map'][1])) {
      return NULL;
    }
    list(, $order, $page) = $item['map'];
    return t($page['name']);
  }
}
