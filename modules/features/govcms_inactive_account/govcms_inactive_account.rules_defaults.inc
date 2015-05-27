<?php
/**
 * @file
 * inactive_account.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function govcms_inactive_account_default_rules_configuration() {
  $items = array();
  $items['rules_suspend_account'] = entity_import('rules_config', '{ "rules_suspend_account" : {
      "LABEL" : "Suspend Account",
      "PLUGIN" : "action set",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "suspend_account_user" : { "label" : "Account", "type" : "user" } },
      "ACTION SET" : [ { "user_block" : { "account" : [ "suspend-account-user" ] } } ]
    }
  }');
  $items['rules_suspend_account_after_inactivity'] = entity_import('rules_config', '{ "rules_suspend_account_after_inactivity" : {
      "LABEL" : "Suspend Account after inactivity",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "rules_scheduler" ],
      "ON" : { "user_login" : [] },
      "DO" : [
        { "schedule" : {
            "component" : "rules_suspend_account",
            "date" : "+60 days",
            "identifier" : "Suspend Account [account:uid]",
            "param_suspend_account_user" : [ "account" ]
          }
        }
      ]
    }
  }');
  return $items;
}
