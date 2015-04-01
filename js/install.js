jQuery(document).ready(function() {
  jQuery('#govcms-install-register-fields').hide();
  jQuery('#edit-govcms-register-confirm').change(function() {
    jQuery('#govcms-install-register-fields').toggle(300);
  });
});