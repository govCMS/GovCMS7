/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.formalSubmissionToggle = {
    attach: function() {
      // Attach toggle functionality for Have Your Say webform.

      if ($("[data-js*='webform-toggle']").length > 0) {
        var webform_toggle = $("[data-js*='webform-toggle']");

        $(webform_toggle).once('webformToggle', function() {
          var toggled_form_id = $(this).attr('data-toggle');
          var form = document.getElementById(toggled_form_id);
          $(form).hide();

          $(webform_toggle).click(function () {
            var toggled_form_id = $(this).attr('data-toggle');
            var form = document.getElementById(toggled_form_id);

            $(this).hide();
            $(form).show();
            $('input', form).first().focus();
          });
        });
      }

      $('#consultation__formal-submission-webform  input[id*="remain-anonymous"]').change(function() {
        $('#consultation__formal-submission-webform  input[id*="private-submission"]')
          .attr('checked', false);
        if($(this).is(":checked")) {
          $('#consultation__formal-submission-webform  input[id*="hys-formal-your-name"]')
            .val('Anonymous')
            .attr('readonly', true);
        } else {
          $('#consultation__formal-submission-webform  input[id*="hys-formal-your-name"]')
            .val('')
            .attr('readonly', false);
        }
      });
      $('#consultation__formal-submission-webform  input[id*="private-submission"]').change(function() {
        $('#consultation__formal-submission-webform  input[id*="remain-anonymous"]')
          .attr('checked', false);
        if($(this).is(":checked")) {
          $('#consultation__formal-submission-webform  input[id*="hys-formal-your-name"]')
            .val('Not required - private submission')
            .attr('readonly', true);
        } else {
          $('#consultation__formal-submission-webform  input[id*="hys-formal-your-name"]')
            .val('')
            .attr('readonly', false);
        }
      });
    }
  };

  Drupal.behaviors.formalSubmissionValidation = {
    attach: function(context) {
      var fileUploadsEnabled    = Drupal.settings.govcms_consultation.fileUploadsEnabled;
      var shortCommentsEnabled  = Drupal.settings.govcms_consultation.shortCommentsEnabled;
      var message               = 'It looks like you haven\'t added a submission. Please add a submission to have your say.';
      var shortCommentSelector  = 'textarea[name$="[short_comments]"]';
      var firstFileSelector     = 'input[name$="formal_uploads_hys_formal_upload_file_1]"]';
      var submittedFileSelector = 'div[id$="formal-uploads-hys-formal-upload-file-1-upload"] > .file';
      var $form = $('#consultation__formal-submission-webform');

      if (fileUploadsEnabled && !shortCommentsEnabled) {
        $form.find(firstFileSelector).attr('required', 'true');
      }
      else if (shortCommentsEnabled && !fileUploadsEnabled) {
        $form.find(shortCommentSelector).attr('required', 'true');
      }
      else if (shortCommentsEnabled && fileUploadsEnabled) {
        $form.find('.webform-submit').unbind('click.formalSubmissionValidation').bind('click.formalSubmissionValidation', function(e) {
          $form.find('.custom-message').remove();
          // Get fields
          var $filesInput = $form.find(firstFileSelector);
          var $filesSubmitted = $form.find(submittedFileSelector);
          var $shortDescription = $form.find(shortCommentSelector).val();
          var pass = false;
          var has_file = ($filesInput.length > 0 && $filesInput[0].value.length > 0) || $filesSubmitted.length > 0;

          try {
            // Check for at least one field to be populated
            if ($shortDescription.length > 0 || has_file) {
              pass = true;
            }
            if (!pass) {
              // Show error message
              $form.find('.webform-component--step-1-your-submission > .fieldset-wrapper').each(function() {
                $(this).prepend('<div class="messages--error messages error custom-message">'+message+'</div>');
                $(window).scrollTop($('.custom-message').position().top);
              });
            }
          }
          catch(e) {
            console.log('An error occured validating form. Allowing to pass. ' + e);
            pass = true;
          }
          return pass;
        });
      }
    }
  };

  Drupal.behaviors.uploadMultipleSubmissions = {
    attach: function(context) {
      // Attach toggle functionality for Have Your Say webform.
      $('fieldset[class*="--hys-formal-uploads"]', context).each(function() {

        var $parent = $(this);
        var $files = $parent.children('.fieldset-wrapper').children('div[id*="hys-formal-upload-file-"]');

        function refreshSubmissionView() {
          var currentFileSlot = 0;
          var fileSlots = [];

          $files.each(function(index, item) {
            var $file = $(item).find('input');
            fileSlots.push($file);
            // Find current file slot
            if ($file[0].value != undefined && $file[0].value.length > 0) {
              currentFileSlot++;
            }
          });

          // Hide unused
          $files.hide();

          for (var i = 0; i < (currentFileSlot + 1); i++) {
            if (fileSlots[i] !== undefined) {
              fileSlots[i].parent().parent().parent().show();
            }
          };
        }
        $files.unbind('change.multi_submission').bind('change.multi_submission', refreshSubmissionView);
        refreshSubmissionView();
      });
    }
  };

  Drupal.behaviors.shortCommentMaxLength = {
    attach: function (context) {
      var maxLengthHandler = function(e) {
        var target = e.target;
        if (target.value.length > 500) {
          target.value = target.value.substring(0, 500);
        }
      };

      $('textarea[name="submitted[step_1_your_submission][short_comments]"]')
        .attr('maxlength', 500)
        .keyup(maxLengthHandler)
        .keydown(maxLengthHandler);
    }
  };

  Drupal.behaviors.formalSubmissionNotify = {
    attach: function() {
      try {
        var formalSubmissionNotify = $("input[name='submitted[email_notification]']");
        if (formalSubmissionNotify.length > 0) {
          // Set the value of each email_notification field.
          $(formalSubmissionNotify).each(function() {
            $(this).val(Drupal.settings.govcms_consultation.formalSubmissionNotify);
          });
        }
      } catch(e) {}
    }
  };

  Drupal.behaviors.detectFileExtension = {
    attach: function (context, settings) {

      $('.js-file-extension .file a').each(function(i, obj) {

        var file = obj.textContent;
        var extension = file.substr( (file.lastIndexOf('.') +1) );

        switch(extension) {
          case 'pdf':
          case 'PDF':
            $(obj).text("Download PDF");
            break;
          case 'doc':
          case 'docx':
          case 'DOC':
          case 'DOCX':
            $(obj).text("Download DOC");
            break;
          default:
            $(obj).text("Download File");
            break;
        }
      });

    }
  };

})(jQuery, Drupal);
