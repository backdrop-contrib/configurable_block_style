(function ($, Backdrop) {
  Backdrop.behaviors.configurableBlockStyle = {
    attach: function (context, settings) {
      $('.is-collapsible', context).each(function() {
        var block = this;
        var $toggle = $('.block-title-toggle', block);
        var $caret = $('.toggle-caret', block);
        var contentId = ($caret.length && $caret.attr('aria-controls')) || ($toggle.length && $toggle.attr('aria-controls'));
        var $content = $('#' + contentId);
        if (!$toggle.length || !$caret.length || !$content.length) return;

        var blockId = block.id || contentId;
        var storageKey = 'block-collapsed-' + blockId;

        // Restore state from localStorage
        var collapsed = localStorage.getItem(storageKey) === 'true';
        if (collapsed) {
          $content.addClass('hide');
          $caret.attr('aria-expanded', 'false');
          if (!$toggle.is($caret)) $toggle.attr('aria-expanded', 'false');
          $caret.css('transform', '');
        } else {
          $content.removeClass('hide');
          $caret.attr('aria-expanded', 'true');
          if (!$toggle.is($caret)) $toggle.attr('aria-expanded', 'true');
          $caret.css('transform', 'rotate(90deg)');
        }

        function toggleBlock() {
          var expanded = $caret.attr('aria-expanded') === 'true';
          if (expanded) {
            $content.addClass('hide');
            $caret.attr('aria-expanded', 'false');
            if (!$toggle.is($caret)) $toggle.attr('aria-expanded', 'false');
            $caret.css('transform', '');
            localStorage.setItem(storageKey, 'true');
          } else {
            $content.removeClass('hide');
            $caret.attr('aria-expanded', 'true');
            if (!$toggle.is($caret)) $toggle.attr('aria-expanded', 'true');
            $caret.css('transform', 'rotate(90deg)');
            localStorage.setItem(storageKey, 'false');
          }
        }

        // If the title is a link, only the caret toggles
        if ($toggle.has($caret).length && $toggle.find('a').length) {
          $caret.on('click', toggleBlock);
          $caret.on('keydown', function(e) {
            if (e.key === 'Enter' || e.key === ' ') {
              e.preventDefault();
              toggleBlock();
            }
          });
        } else {
          // Otherwise, the whole toggle area toggles
          $toggle.on('click', toggleBlock);
          $toggle.on('keydown', function(e) {
            if (e.key === 'Enter' || e.key === ' ') {
              e.preventDefault();
              toggleBlock();
            }
          });
        }
      });
    }
  };
})(jQuery, Backdrop); 