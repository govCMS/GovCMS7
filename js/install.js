jQuery(document).ready(function() {
  jQuery('#agov-install-register-fields').hide();
  jQuery('#edit-agov-register-confirm').change(function() {
    jQuery('#agov-install-register-fields').toggle(300);
  });
});