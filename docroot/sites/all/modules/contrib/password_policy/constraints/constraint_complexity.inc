<?php
/**
 * @file
 * Password policy constraint callbacks.
 */

/****************************************************************************/
/* Constraint API                                                           */
/****************************************************************************/

/**
 * Description of the constraint.
 */
function password_policy_constraint_complexity_description() {
  return array('name' => t('Complexity'), 'description' => t('Password must contain the specified minimum number of character types (lowercase, uppercase, digit or punctuation).'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_complexity_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one character of the following types: lowercase, uppercase, digit or punctuation.', 'Password must contain at least @count characters of different types (lowercase, uppercase, digit or punctuation).');
}

/**
 * Password validation.
 */
function password_policy_constraint_complexity_validate($password, $constraint, $account) {
  $chars = drupal_strlen($password);
  $num = 0;
  $upper = 0;
  $lower = 0;
  $digit = 0;
  $punct = 0;
  for ($i = 0; $i < $chars; ++$i) {
    $char = drupal_substr($password, $i, 1);
    if (ctype_upper($char)) {
      $upper = 1;
    }
    elseif (ctype_lower($char)) {
      $lower = 1;
    }
    elseif (ctype_digit($char)) {
      $digit = 1;
    }
    elseif (ctype_punct($char)) {
      $punct = 1;
    }
  }
  $num = $upper + $lower + $digit + $punct;
  return $num >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_complexity_js($constraint, $account) {
  $s = '';
  $s .= "  var i=0;\n";
  $s .= "  var num=0;\n";
  $s .= "  var upper=0;\n";
  $s .= "  var lower=0;\n";
  $s .= "  var digit=0;\n";
  $s .= "  var punct=0;\n";
  $s .= "  var chr=\"\";\n";
  $s .= "  while(i<value.length) {\n";
  $s .= "    chr=value.charAt(i);\n";
  $s .= "    if(chr.toUpperCase() != chr.toLowerCase()) {\n";
  $s .= "      if(chr == chr.toUpperCase()) {\n";
  $s .= "        upper=1;\n";
  $s .= "      }\n";
  $s .= "      else {\n";
  $s .= "        lower=1;\n";
  $s .= "      }\n";
  $s .= "    }\n";
  $s .= "    else if(\"1234567890\".indexOf(chr) != -1) {\n";
  $s .= "      digit=1;\n";
  $s .= "    }\n";
  $s .= "    else if(chr.toUpperCase() == chr.toLowerCase() && \"1234567890\".indexOf(chr) == -1 && chr != ' ') {\n";
  $s .= "      punct=1;\n";
  $s .= "    }\n";
  $s .= "    i++;\n";
  $s .= "  }\n";
  $s .= "  num=upper+lower+digit+punct\n";
  $s .= "  if (num<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_complexity);\n";
  $s .= "  }\n";
  return $s;
}
