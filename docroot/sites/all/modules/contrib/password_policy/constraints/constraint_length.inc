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
function password_policy_constraint_length_description() {
  return array('name' => t('Length'), 'description' => t('Password must be equal to or longer than the specified minimum length.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_length_error($constraint) {
  return format_plural($constraint, 'Password must be at least one character in length.', 'Password must be at least @count characters in length.');
}

/**
 * Password validation.
 */
function password_policy_constraint_length_validate($password, $constraint, $account) {
  $length = drupal_strlen($password);
  return $length >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_length_js($constraint, $account) {
  $s = '';
  $s .= "  if (!value.length || value.length<$constraint) {\n";
  $s .= "    strength=\"low\";\n";
  $s .= "    msg.push(translate.constraint_length);\n";
  $s .= "  }\n";
  return $s;
}
