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
function password_policy_constraint_letter_description() {
  return array('name' => t('Letter'), 'description' => t('Password must contain the specified minimum number of letters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_letter_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one letter.', 'Password must contain at least @count letters.');
}

/**
 * Password validation.
 */
function password_policy_constraint_letter_validate($password, $constraint, $account) {
  $chars = drupal_strlen($password);
  $num = 0;
  for ($i = 0; $i < $chars; ++$i) {
    $char = drupal_substr($password, $i, 1);
    if (ctype_alpha($char)) {
      $num++;
    }
  }
  return $num >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_letter_js($constraint, $account) {
  $s = '';
  $s .= "  var i=0;\n";
  $s .= "  var num=0;\n";
  $s .= "  var chr=\"\";\n";
  $s .= "  while(i<value.length) {\n";
  $s .= "    chr=value.charAt(i);\n";
  $s .= "    if(chr.toUpperCase() != chr.toLowerCase()) {\n";
  $s .= "      num++;\n";
  $s .= "    }\n";
  $s .= "    i++;\n";
  $s .= "  }\n";
  $s .= "  if (num<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_letter);\n";
  $s .= "  }\n";
  return $s;
}
