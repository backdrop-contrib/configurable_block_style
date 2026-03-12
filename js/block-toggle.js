(function ($, Backdrop) {
  Backdrop.behaviors.configurableBlockStyle = {
    attach: function (context, settings) {
      $('.is-collapsible', context).each(function() {
        var $block = $(this);
        var $toggle = $('.block-title-toggle', $block);
        var $caret = $('.toggle-caret', $block);
        var contentId = ($caret.length && $caret.attr('aria-controls')) || ($toggle.length && $toggle.attr('aria-controls'));
        var $content = $block.find('#' + contentId);
        if (!$toggle.length || !$caret.length || !$content.length) return;

        // Get the block's UUID from the content ID
        var blockId = contentId.replace('block-content-', '');
        var pagePath = window.location.pathname;
        var storageKey = 'block-collapsed-' + pagePath + '-' + blockId;

        // Restore state from localStorage for this specific block
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

        function toggleBlock(e) {
          e.preventDefault();
          e.stopPropagation();
          
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

        // Remove any existing event handlers
        $toggle.off('click keydown');
        $caret.off('click keydown');

        // If the title is a link, only the caret toggles
        if ($toggle.has($caret).length && $toggle.find('a').length) {
          $caret.on('click', toggleBlock);
          $caret.on('keydown', function(e) {
            if (e.key === 'Enter' || e.key === ' ') {
              toggleBlock(e);
            }
          });
        } else {
          // Otherwise, the whole toggle area toggles
          $toggle.on('click', toggleBlock);
          $toggle.on('keydown', function(e) {
            if (e.key === 'Enter' || e.key === ' ') {
              toggleBlock(e);
            }
          });
        }
      });
    }
  };
})(jQuery, Backdrop);