(function ($, Backdrop) {
  /**
   * Handles the "Reset to defaults" button inside each settings fieldset.
   *
   * Each fieldset carries its field defaults in a data-cbs-defaults attribute
   * (JSON). On click, every matching input inside the fieldset is restored to
   * its default value and a change event is fired so Backdrop's #states
   * system hides/shows dependent fields immediately. The settings-changed
   * class is then removed so the dot indicator disappears.
   */
  Backdrop.behaviors.configurableBlockStyleAdmin = {
    attach: function (context, settings) {
      $('.fieldset-reset', context).once('fieldset-reset').on('click', function (e) {
        e.preventDefault();

        var $fieldset = $(this).closest('fieldset');
        var defaults = $fieldset.data('cbs-defaults');
        if (!defaults) {
          return;
        }

        $.each(defaults, function (name, value) {
          // Match inputs whose name ends with [name] — works for all fieldsets
          // since each field name is unique within the form.
          var $input = $fieldset.find('[name$="[' + name + ']"]');
          if (!$input.length) {
            return;
          }

          if ($input.is(':checkbox')) {
            $input.prop('checked', !!value).trigger('change');
          }
          else {
            $input.val(value).trigger('change');
          }
        });

        $fieldset.removeClass('settings-changed');
      });
    }
  };
})(jQuery, Backdrop);
