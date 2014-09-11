<?php

/**
 * @file
 * Restrict placement of digits in passwords.
 *
 * @link http://drupal.org/node/316768
 * @author David Kent Norman (http://deekayen.net/)
 */

/****************************************************************************/
/* Constraint API                                                           */
/****************************************************************************/

/**
 * Description of the constraint.
 */
function password_policy_constraint_digit_placement_description() {
  return array('name' => t('Digit Placement'), 'description' => t('Minimum number of digits necessary in the password overall, to allow digits as the first or last characters in the password. For example, set to 2, the passwords 2abcdefg and abcdefg4 are unacceptable, while 2qpcxrm3 and 9qpcx9rm are allowed. This is intended to prevent changing passwords by incrementing a single digit, such as password1, password2, password3.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_digit_placement_error($constraint) {
  return t('Password must have a minimum of %numChars %digits in order to place any digits at the start or end of the password.',
    array(
      '%numChars' => $constraint,
      '%digits' => format_plural($constraint, t('digit'), t('digits')),
    ));
}

/**
 * Password validation.
 */
function password_policy_constraint_digit_placement_validate($password, $constraint, $account) {
  $chars = drupal_strlen($password);
  $num = 0;
  for ($i = 0; $i < $chars; ++$i) {
    if (ctype_digit(drupal_substr($password, $i, 1))) {
      $num++;
    }
  }
  if ($num < (int) $constraint) {
    return preg_match("/^(\d+)|(\d+)$/", $password) != 1;
  }
  return TRUE;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_digit_placement_js($constraint, $account) {
  return <<<JSS
  function substr_count(haystack, needle) {
    var pos = 0, cnt = 0;

    haystack += '';
    needle += '';
    var offset = 0;
    var length = 0;
    offset--;

    while ((offset = haystack.indexOf(needle, offset+1)) != -1) {
      if (length > 0 && (offset+needle.length) > length) {
        return false;
      } else {
        cnt++;
      }
    }
    return cnt;
  }

  var i=0;
  var num=0;
  for (i=0;i<10;i++) {
    num += substr_count(value, i);
  }
  if (num<$constraint && value.match(/^(\d+)|(\d+)$/) != null) {
    strength="low";
    msg.push(translate.constraint_digit_placement);
  }
JSS;
}
