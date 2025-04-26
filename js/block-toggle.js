document.addEventListener('DOMContentLoaded', function() {
  var toggles = document.querySelectorAll('.block-title-toggle');
  toggles.forEach(function(toggle) {
    var contentId = toggle.getAttribute('aria-controls');
    var content = document.getElementById(contentId);
    var caret = toggle.querySelector('.toggle-caret');
    if (!content || !caret) return;
    function toggleBlock() {
      var expanded = toggle.getAttribute('aria-expanded') === 'true';
      if (expanded) {
        content.classList.add('hide');
        toggle.setAttribute('aria-expanded', 'false');
        caret.style.transform = '';
      } else {
        content.classList.remove('hide');
        toggle.setAttribute('aria-expanded', 'true');
        caret.style.transform = 'rotate(90deg)';
      }
    }
    toggle.addEventListener('click', toggleBlock);
    toggle.addEventListener('keydown', function(e) {
      if (e.key === 'Enter' || e.key === ' ') {
        e.preventDefault();
        toggleBlock();
      }
    });
    // Set initial state
    if (content.classList.contains('hide')) {
      toggle.setAttribute('aria-expanded', 'false');
      caret.style.transform = '';
    } else {
      toggle.setAttribute('aria-expanded', 'true');
      caret.style.transform = 'rotate(90deg)';
    }
  });
}); 