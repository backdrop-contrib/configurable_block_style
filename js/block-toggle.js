document.addEventListener('DOMContentLoaded', function() {
  var blocks = document.querySelectorAll('.is-collapsible');
  blocks.forEach(function(block) {
    var toggle = block.querySelector('.block-title-toggle');
    var caret = block.querySelector('.toggle-caret');
    var contentId = (caret && caret.getAttribute('aria-controls')) || (toggle && toggle.getAttribute('aria-controls'));
    var content = document.getElementById(contentId);
    if (!toggle || !caret || !content) return;

    var blockId = block.id || contentId;
    var storageKey = 'block-collapsed-' + blockId;

    // Restore state from localStorage
    var collapsed = localStorage.getItem(storageKey) === 'true';
    if (collapsed) {
      content.classList.add('hide');
      caret.setAttribute('aria-expanded', 'false');
      if (toggle !== caret) toggle.setAttribute('aria-expanded', 'false');
      caret.style.transform = '';
    } else {
      content.classList.remove('hide');
      caret.setAttribute('aria-expanded', 'true');
      if (toggle !== caret) toggle.setAttribute('aria-expanded', 'true');
      caret.style.transform = 'rotate(90deg)';
    }

    function toggleBlock() {
      var expanded = caret.getAttribute('aria-expanded') === 'true';
      if (expanded) {
        content.classList.add('hide');
        caret.setAttribute('aria-expanded', 'false');
        if (toggle !== caret) toggle.setAttribute('aria-expanded', 'false');
        caret.style.transform = '';
        localStorage.setItem(storageKey, 'true');
      } else {
        content.classList.remove('hide');
        caret.setAttribute('aria-expanded', 'true');
        if (toggle !== caret) toggle.setAttribute('aria-expanded', 'true');
        caret.style.transform = 'rotate(90deg)';
        localStorage.setItem(storageKey, 'false');
      }
    }

    // If the title is a link, only the caret toggles
    if (toggle.contains(caret) && toggle.querySelector('a')) {
      caret.addEventListener('click', toggleBlock);
      caret.addEventListener('keydown', function(e) {
        if (e.key === 'Enter' || e.key === ' ') {
          e.preventDefault();
          toggleBlock();
        }
      });
    } else {
      // Otherwise, the whole toggle area toggles
      toggle.addEventListener('click', toggleBlock);
      toggle.addEventListener('keydown', function(e) {
        if (e.key === 'Enter' || e.key === ' ') {
          e.preventDefault();
          toggleBlock();
        }
      });
    }
  });
}); 