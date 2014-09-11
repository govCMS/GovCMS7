/**
 * @file
 * Sets the summary for Workbench moderation on vertical tabs.
 */

(function ($) {

Drupal.behaviors.workbenchModerationSettingsSummary = {
  attach: function(context) {
    $('fieldset.node-form-options', context).drupalSetSummary(function (context) {
      var vals = [];

      $('input:checked', context).parent().each(function () {
        vals.push(Drupal.checkPlain($.trim($(this).text())));
      });

      if ($('select[name="workbench_moderation_state_new"]', context).val()) {
        vals.push(Drupal.checkPlain($('select[name="workbench_moderation_state_new"] option:selected').text()));
      }
      return vals.join(', ');
    });
  }
};

})(jQuery);
